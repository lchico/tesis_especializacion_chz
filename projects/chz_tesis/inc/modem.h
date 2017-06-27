/*
 * gsm.h
 *
 *  Created on: 27/08/2011
 *      Author: Vera
 */

#ifndef GSM_H_
#define GSM_H_

#include "actuadores.h"

#define configMODEM_STACK_SIZE configMINIMAL_STACK_SIZE*2
#define configMODEM_TASK_PRIORITY tskIDLE_PRIORITY+4
#define TIMER_MODEM 2 // Check temperature TIMER_SAMPLE seconds.

#define MSG_AT_INIT "ATZ\r\n"
#define MSG_AT_SIGNAL "AT+CSQ\r\n"
#define MSG_AT_TEXT_MODE "AT+CMGF=1\r\n"
#define AT_WRITE_SMS "AT+CMGW"
#define AT_DELETE "AT+CMGD"
#define AT_ADDRES_TYPE "145"
#define AT_MSJ_STATUS "UNSENT"
#define AT_READ_SMS "AT+CMGR"
#define AT_SEND_SMS "AT+CMGS"
#define MSG_AT_OK "OK"
#define MSG_AT_ERROR "ERROR"

#define CHAR_WAIT_TO_WRIETE ">"
#define CTRL_Z_AT 0x1A
#define CHAR_MEM_SET '0'
#define TWO_CHAR_END_LINE 2 // CORRESPONDE A LOS DOS CARACTERES DE FIN DE LINEA \r\n

#define GSM_NSEND_TIMEOUT 0x0000000FUL
#define BUFFER_MSJ 200
//#define BUFFER_LIST 250

#define NO_MESSAGE 0
#define FIRST_MESSAGE 0
#define MAX_ATTEMPTS 3
#define MAX_MESSAGE 35 //NUMEROS DE MENSAJES MAXIMO QUE SE PUEDEN ALMACENAR
#define BUFFER_COMMAND_SMS 50
#define BUFFER_MSJ_SIGNAL 25
#define BUFFER_AUX 250
#define BUFFER_MIN 5

#define DEFAULT_CEL_PHONE "64958758"
#define BUFFER_PHONE_NUMBER 13 //54-911-54548829 => CANTIDAD DE NUMEROS
#define MIN_GSM_SIGNAL 31
#define RTA_CHAR_MIN_SIGNAL 14
#define RTA_CMGL_UNSENT 9
#define CANTIDAD_CONTACTOS 2

#define NRO_SMS_FLAGS 4 // Menos el ALL_SMS ya que no lo uso en el arreglo de sms_falgs
#define TIEMPO_REENVIAR_SMS 10000 // VERIFICAR TIEMPO EQUIVALENTE


typedef enum sms_flags_t {SOBRE_TEMPERATURA_ALERT=0,BAJA_TEMPERATURA_ALERT,BATERIA_ALERT,GSM_ALERT,ALL_OK} sms_flags_t;

typedef struct {
	char name[20];
	char phone[BUFFER_PHONE_NUMBER];
	state_t state;
}contact_t;



extern sms_flags_t sms_flag;
extern contact_t contact_report[];


void send_msg_modem(char *msg);
Status check_response(void);
Status get_signal(void);
void control_modem(void);
void GetGSM_signal( signed char *pcWriteBuffer );
void send_report(contact_t *contact_report);
void vStartModemTask( void );
static void prvModemTask( void *pvParameters );
void init_contact(void);


#endif /* GSM_H_ */
