#include <stdio.h>
#include <string.h>
#include "ciaaUART.h"
#include "ciaaIO.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sensores.h"
#include "modem.h"
#include "actuadores.h"

typedef enum {AT_OK,CHECK_ALARMS,AT_SIGNAL,SET_TEXMODE,WELCOME_MSG,SEND_REPORT} modem_state_t;

static modem_state_t mstate=SET_TEXMODE;
static int gsm_signal=0;
sms_flags_t sms_flag=ALL_OK;

void control_modem(void){
	int i=0;
	static portTickType sms_timeout[NRO_SMS_FLAGS];

	switch (mstate){
		case SET_TEXMODE:
				send_msg_modem(MSG_AT_TEXT_MODE);
				if ( SUCCESS == check_response()){
					mstate= AT_SIGNAL;
					/* Reinicio los timeout de las alertas por SMS
					 * dando un tiempo hasta que el sistema este en equilibrio.
					 */
					for (i=0;i<NRO_SMS_FLAGS; i++){
						sms_timeout[i]=xTaskGetTickCount();
					}
				}
				break;
		case WELCOME_MSG:
			//send_msg_modem("Perfect");
				if ( SUCCESS == check_response() ){
					mstate= AT_SIGNAL;
				}
				break;
		case AT_SIGNAL:
				send_msg_modem(MSG_AT_SIGNAL);
				get_signal();
				if( sms_flag != ALL_OK ){
					mstate= SEND_REPORT;
				}
				break;
		case SEND_REPORT:
			  /* Si el mensaje fue enviado recientemente espero
			   * un tiempo TIEMPO_REENVIAR_SMS hasta volver a
			   * enviar el mensaje si la
			   */
			 	if (xTaskGetTickCount()- sms_timeout[sms_flag] > TIEMPO_REENVIAR_SMS ){
				 	// send_report();
				 	 // CHECK STATUS
				 	 //if ( SUCCESS == ){
						//mstate= SET_TEXMODE;
				 	 //}
			 		sms_flag=ALL_OK;
			 		mstate=AT_SIGNAL;
			 		sms_timeout[sms_flag]=xTaskGetTickCount(); /* reset timeout */
			 	}
				break;

		default :
			send_msg_modem("ERRORRORRRRR\n\r");
			break;

	}
}

void send_report(){
	char command[150];
	signed char temperatura[5];
	char at_ok[10];
	GetTemperatura( temperatura);
	sprintf(command,"%s=\"%s\"\r\n",AT_SEND_SMS,CEL_PHONE);
	send_msg_modem(command);
	vTaskDelay(500 / portTICK_RATE_MS);
	uartRecv(CIAA_UART_232,command,150*sizeof(char));
	vTaskDelay(500 / portTICK_RATE_MS);

	sprintf(command,"Temp:%.2f Bat:%i%% y Signal:%i\rBomba: %s Eval: %s Act0: %s Act1: %s.%c",
			Temperatura,Bateria*20,gsm_signal,actuatorState[BOMBA]?"ON":"OFF",
			actuatorState[ELECTROVALVULA0]?"ON":"OFF",actuatorState[ACTUADOR0]?"ON":"OFF",
			actuatorState[ACTUADOR1]?"ON":"OFF",CTRL_Z_AT);
	send_msg_modem(command);
	vTaskDelay(500 / portTICK_RATE_MS);
	sprintf(command,"%c",CTRL_Z_AT);
	send_msg_modem(command);
	vTaskDelay(500 / portTICK_RATE_MS);
	uartRecv(CIAA_UART_232,command,150*sizeof(char));
	vTaskDelay(800 / portTICK_RATE_MS);
	uartRecv(CIAA_UART_232,command,150*sizeof(char));
	vTaskDelay(500 / portTICK_RATE_MS);
	sscanf(command,"%*s%s%s",at_ok);
	//check_response();
}


Status check_response(void){
	char at_ok[10];
	char rta_at[25];
	if ( 0 < uartRecv(CIAA_UART_232,rta_at,25) ){
		sscanf(rta_at,"%*s%s",at_ok);
		if( strcmp(at_ok,"OK") == 0 ){
			return SUCCESS;
		}
	}
	return ERROR;
}

Status get_signal(void){
	int qsig;
	char at_ok[10];
	char rta_at[25];
	if ( 0 < uartRecv(CIAA_UART_232,rta_at,UART_BUF_SIZE) ){
		sscanf(rta_at,"%*s%s%s",at_ok);
		qsig=atoi(at_ok);
		if(qsig != 0){
			if( qsig < 5){
				gsm_signal =0;
			}else if (qsig < 10){
					gsm_signal =1;
			}else if (qsig < 15){
				gsm_signal = 2;
			}else if (qsig < 20){
				gsm_signal = 3;
			}else if (qsig >= 20){
				gsm_signal = 4;
			}
			return SUCCESS;
		}
	}
	return ERROR;
}

void send_msg_modem(char *msg){
		uartSend(CIAA_UART_232,msg, strlen(msg)*sizeof(char));
		vTaskDelay(600 / portTICK_RATE_MS);
}

void GetGSM_signal( signed char *pcWriteBuffer )
{
	*pcWriteBuffer = ( signed char ) 0x00;
	sprintf( ( char * ) pcWriteBuffer, "%i", gsm_signal );
}


void vStartModemTask( void ){
	xTaskCreate( 	prvModemTask,						/* Crea la tarea prvTemperaturaTask. */
					( const int8_t * const ) "MODEM", 		/* Texto con el nombre de la tarea (solamente para Debug).  El kernel no usa este nombre. */
					configMODEM_STACK_SIZE,			/* Tamaño del stack asociado a la tarea. */
					NULL,									/* Parámetro no usado (NULL). */
					configMODEM_TASK_PRIORITY,		/* Prioridad de la tarea. */
					NULL );									/* No se requiere de un manejador para esta tarea (NULL). */
}

static void prvModemTask( void *pvParameters ){
	( void ) pvParameters;
	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; ){
		vTaskDelayUntil( &xLastWakeTime, 1000 * TIMER_MODEM);
		ciaaToggleOutput(5);
		control_modem();
	}
}
