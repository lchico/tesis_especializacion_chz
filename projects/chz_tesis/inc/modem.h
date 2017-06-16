/*
 * gsm.h
 *
 *  Created on: 27/08/2011
 *      Author: Vera
 */

#ifndef GSM_H_
#define GSM_H_



#define MSG_AT_INIT "ATZ\r\n"
#define MSG_AT_SIGNAL "AT+CSQ\r\n"
#define AT_TEXT_MODE "AT+CMGF=1\r\n"
#define AT_WRITE_SMS "AT+CMGW"
#define AT_DELETE "AT+CMGD"
#define AT_ADDRES_TYPE "145"
#define AT_MSJ_STATUS "UNSENT"
#define AT_READ_SMS "AT+CMGR"
#define AT_SEND_SMS "AT+CMSS"
#define MSG_AT_OK "OK"
#define MSG_AT_ERROR "ERROR"

#define INIT_NEW_MSJ '+'
#define INIT_ERROR_MSJ 'E'
#define INIT_OK_MSJ 'O'
#define END_OK_MSJ 'K'
#define END_RTA_AT '\n'
#define RETURN_CARRY '\r'
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

#define CEL_PHONE "+5491164958758"
#define BUFFER_PHONE_NUMBER 13 //54-911-54548829 => CANTIDAD DE NUMEROS
#define MIN_GSM_SIGNAL 31
#define RTA_CHAR_MIN_SIGNAL 14
#define RTA_CMGL_UNSENT 9

struct gsm{
	char message[BUFFER_MSJ];
	char rta_message[BUFFER_MSJ+BUFFER_PHONE_NUMBER];
	char phone[BUFFER_PHONE_NUMBER];
	int msj_status;
	int nro_msj;
};

void send_modem(char *msg);
Status check_response(void);
void control_modem(void);

/*
Status gsm_at_init(LPC_UART_TypeDef *UARTx);
Status	gsm_signal(LPC_UART_TypeDef *UARTx);
Status gsm_set_text_mode(LPC_UART_TypeDef *UARTx);
Status gsm_save_sms(LPC_UART_TypeDef *UARTx,struct gsm *data);
Status gsm_delete_sms(LPC_UART_TypeDef *UARTx, int i); //i debe ser mayor 0
Status gsm_msj_not_send(LPC_UART_TypeDef *UARTx, int *not_send);
Status gsm_send_sms(LPC_UART_TypeDef *UARTx,int *msj_to_send);
void clear_array_message(int *message);
*/

#endif /* GSM_H_ */
