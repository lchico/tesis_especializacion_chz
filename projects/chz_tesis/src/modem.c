#include <stdio.h>
#include <string.h>
#include "ciaaUART.h"

#include "FreeRTOS.h"
#include "task.h"
#include "sensores.h"
#include "modem.h"

typedef enum {AT_OK,CHECK_ALARMS,AT_SIGNAL,SET_TEXMODE,WELCOME_MSG,SEND_REPORT} modem_state_t;

static modem_state_t mstate=SET_TEXMODE;
static int gsm_signal=0;
int sms_flag=0;

void control_modem(void){

	switch (mstate){
		case SET_TEXMODE:
				send_msg_modem(MSG_AT_TEXT_MODE);
				vTaskDelay(1500 / portTICK_RATE_MS);
				if ( SUCCESS == check_response()){
					mstate= AT_SIGNAL;
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
				vTaskDelay(1500 / portTICK_RATE_MS);
				get_signal();
				if(sms_flag > 0){
					mstate= SEND_REPORT;
				}

				break;
		case SEND_REPORT:
				//send_report();
				// CHECK STATUS
				//if ( SUCCESS == check_response()){
					//mstate= SET_TEXMODE;
				//}
				sms_flag=0;
				mstate=AT_SIGNAL;
				vTaskDelay(4500 / portTICK_RATE_MS);
				break;

		default :
			send_msg_modem("ERRORRORRRRR\n\r");
			break;

	}
}

void send_report(){
	char command[50];
	signed char temperatura[5];
	GetTemperatura( temperatura);
	sprintf(command,"%s=\"%s\"\r\n","AT+CMGS","64958758");
	send_msg_modem(command);
	vTaskDelay(500 / portTICK_RATE_MS);
	sprintf(command,"Temperatura:%s y Gsm:%i.%c",temperatura,gsm_signal,CTRL_Z_AT);
	send_msg_modem(command);
	vTaskDelay(500 / portTICK_RATE_MS);
	sprintf(command,"%c",CTRL_Z_AT);
	send_msg_modem(command);
	vTaskDelay(500 / portTICK_RATE_MS);
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
			}else if (qsig > 25){
				gsm_signal = 4;
			}
			return SUCCESS;
		}
	}
	return ERROR;
}

void send_msg_modem(char *msg){
		uartSend(CIAA_UART_232,msg, strlen(msg)*sizeof(char));
}

void GetGSM_signal( signed char *pcWriteBuffer )
{
	*pcWriteBuffer = ( signed char ) 0x00;
	sprintf( ( char * ) pcWriteBuffer, "%i", gsm_signal );
}

/*

OK  Status	gsm_signal(LPC_UART_TypeDef *UARTx){
	char rta_at[BUFFER_MSJ_SIGNAL];
	char aux[BUFFER_AUX];
	uint32_t i;

	memset(rta_at,CHAR_MEM_SET,BUFFER_MSJ_SIGNAL);
	memset(aux,CHAR_MEM_SET,BUFFER_AUX);

	UART_Send(UARTx,(uint8_t *)AT_SIGNAL, sizeof(AT_SIGNAL), BLOCKING);
	i=0;
	i=UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_MSJ_SIGNAL, BLOCKING);
	if ( i < RTA_CHAR_MIN_SIGNAL )	// #min the car for this question.
		 return ERROR;
	//sscanf(rta_at,"%*s%*s%d",&gsm_signal);
	//if (gsm_signal > MIN_GSM_SIGNAL)
	//		return ERROR;
	return SUCCESS;
}

OK  Status gsm_set_text_mode(LPC_UART_TypeDef *UARTx){
	char rta_at[BUFFER_AUX];
	char at_ok[BUFFER_MIN];

	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
	memset(at_ok,CHAR_MEM_SET,BUFFER_MIN);

	gsm_at_init(UARTx);

	UART_Send(UARTx,(uint8_t *)AT_TEXT_MODE, sizeof(AT_TEXT_MODE), BLOCKING);
	UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_AUX, BLOCKING);
	sscanf(rta_at,"%*s%s",at_ok);
	if( strcmp("OK",at_ok) !=0 )
		return ERROR;
	return SUCCESS;
}

Status gsm_save_sms(LPC_UART_TypeDef *UARTx, struct gsm *data){
	char rta_at[BUFFER_AUX];
	char at_write[BUFFER_MIN],aux[BUFFER_AUX];
	char command[BUFFER_COMMAND_SMS];
	int i;

	memset(command,CHAR_MEM_SET,BUFFER_COMMAND_SMS);
	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
	memset(at_write,CHAR_MEM_SET,BUFFER_MIN);
	strcpy(data->phone,CEL_PHONE);
	if( SUCCESS != gsm_set_text_mode(UARTx))return ERROR;

	sprintf(command,"%s=\"%s\",%s,\"STO %s\"\r\n",AT_WRITE_SMS,data->phone,AT_ADDRES_TYPE,AT_MSJ_STATUS);

	UART_Send(UARTx,(uint8_t *)command, strlen(command), BLOCKING);
	UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_AUX, BLOCKING);
	sscanf(rta_at,"%*s%*s%s",at_write);
	if( strcmp(CHAR_WAIT_TO_WRIETE,at_write) !=0 ){
		return ERROR;
	}

	UART_Send(UARTx,(uint8_t *)data->message, strlen(data->message), BLOCKING);
	UART_Receive(LPC_UART3,(uint8_t *)rta_at,strlen(data->message), BLOCKING);
	for(i=0;i<1000000;i++);
	UART_SendByte(UARTx,CTRL_Z_AT);
	UART_SendByte(UARTx,CTRL_Z_AT);

	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);

	UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_MSJ, BLOCKING);

	sscanf(rta_at,"%*s %d %s",&(data->nro_msj),aux);
	if ( strcmp(aux,AT_OK)!= 0 )
			return ERROR;
	return SUCCESS;
}

Status gsm_at_init(LPC_UART_TypeDef *UARTx){
	char rta_at[BUFFER_AUX];
	char at_ok[BUFFER_MIN];

	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
	memset(at_ok,CHAR_MEM_SET,BUFFER_MIN);

	UART_Send(UARTx,(uint8_t *)AT_INIT, sizeof(AT_INIT), BLOCKING);
	UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_AUX, BLOCKING);
	sscanf(rta_at,"%*s%s",at_ok);
	if( strcmp(at_ok,AT_OK) != 0 ){
		UART_SendByte(UARTx,RETURN_CARRY);
		UART_SendByte(UARTx,CTRL_Z_AT);
		UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_AUX, BLOCKING);
		return ERROR;
	}
	return SUCCESS;
}


Status gsm_delete_sms(LPC_UART_TypeDef *UARTx, int nro_msj){
	char rta_at[BUFFER_AUX];
	char at_ok[BUFFER_MIN],aux[BUFFER_AUX];
	char command[BUFFER_COMMAND_SMS];

	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
	memset(at_ok,CHAR_MEM_SET,BUFFER_MIN);

	sprintf(command,"%s=%i\r\n",AT_DELETE,nro_msj);

	UART_Send(UARTx,(uint8_t *)command, strlen(command), BLOCKING);
	UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_AUX, BLOCKING);

	sscanf(rta_at,"%s%s",aux,at_ok);

	if( strcmp("OK",at_ok) !=0 )
		return ERROR;
	return SUCCESS;
}

//Veo todos los mensajes que hay para enviar, y de haber relleno el arreglo con los mensajes
//es decir si hay un mensaje not_sent=[2 0 0 0 ..0] es decir tengo un mensaje guardado en la
//posicion 2.

Status gsm_msj_not_send(LPC_UART_TypeDef *UARTx, int *not_sent){
	char rta_at[BUFFER_AUX], at_ok[BUFFER_MIN],	aux[BUFFER_AUX], state[BUFFER_AUX];
	char command[BUFFER_COMMAND_SMS];
	int i,j;

	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
	memset(at_ok,CHAR_MEM_SET,BUFFER_MIN);
	memset(command,CHAR_MEM_SET,BUFFER_COMMAND_SMS);

	if( SUCCESS != gsm_set_text_mode(LPC_UART3))return ERROR;
	j=0;
	for(i=1;i<MAX_MESSAGE;i++){
		memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
		memset(aux,CHAR_MEM_SET,BUFFER_AUX);

		sprintf(command,"%s=%i\r\n",AT_READ_SMS,i);
		UART_Send(UARTx,(uint8_t *)command, strlen(command), BLOCKING);
		UART_Receive(UARTx,(uint8_t *)rta_at,BUFFER_AUX, BLOCKING);
		sscanf(rta_at,"%*s%s%*s%6s",state,aux);
		if(strcmp(aux,AT_MSJ_STATUS)==0){
			not_sent[j]=i;
			j++;
		}else if(strcmp(state,AT_ERROR)==0){
			not_sent[i-1]=0;
			return ERROR;
		}
	}
	return SUCCESS;
}

Status gsm_send_sms(LPC_UART_TypeDef *UARTx,int *msj_to_send){
	char rta_at[BUFFER_AUX];
	char rta_status[BUFFER_MIN];//,aux[BUFFER_AUX];
	char command[BUFFER_COMMAND_SMS];
	int i;

	memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
	memset(rta_status,CHAR_MEM_SET,BUFFER_MIN);

	if( SUCCESS != gsm_set_text_mode(UARTx))return ERROR;

	for(i=0; (msj_to_send[i] > 0) && (i < MAX_MESSAGE); i++ ){
		sprintf(command,"%s=%i,\"%s\",%s\r\n",AT_SEND_SMS,msj_to_send[i],CEL_PHONE,AT_ADDRES_TYPE);
		UART_Send(UARTx,(uint8_t *)command, strlen(command), BLOCKING);
		UART_Receive(UARTx,(uint8_t *)rta_at,strlen(command), BLOCKING);
		memset(rta_at,CHAR_MEM_SET,BUFFER_AUX);
		UART_Receive(UARTx,(uint8_t *)rta_at,strlen(command), BLOCKING);
		sscanf(rta_at,"%s",rta_status);
		if(strcmp(rta_status,AT_ERROR)!=0){
			gsm_delete_sms(UARTx,msj_to_send[i]);
		}

		// Verificar la respuesta si el mensaje fue enviado correctamente.
	}
	return SUCCESS;
}

void clear_array_message(int *message){
	int i;
		for(i=0;i<MAX_MESSAGE;i++)
			message[i]=0;
}

*/
