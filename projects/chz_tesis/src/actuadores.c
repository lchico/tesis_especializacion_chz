/*
 * actuadores.c
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */

#include "actuadores.h"
#include "string.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ciaaIO.h"
#include "ciaaUART.h"
#include "stdlib.h"
#include "modem.h"
#include "lwip/ip_addr.h"

extern uint8_t configIP_ADDR[4] ;
extern uint8_t configNET_MASK[4] ;
extern uint8_t configGW_IP_ADDR[4];
extern struct netif lpc_netif;
extern Bool reset_server;


state_t actuatorState[NRO_ACTUADORES] = {ON,OFF,OFF,OFF}; //,OFF,OFF};

int cotas_values[NRO_ALARMS] = {TMIN,TMAX,BMIN};
/*
 *  Alarm 0 => Temperatura
 *  Alarm 1 =>  Batteri Level
 */


state_t alarmState[NRO_ALARMS] = {ON,ON};
state_t ctrlautoState=ON;


void encender_refrigeracion(void){
	ciaaWriteOutput(BOMBA, ON ); /* Rele ADC0 - CHANEL 1 */
	actuatorState[ELECTROVALVULA0]=ON; /* Activo electrovalvula */
	actuatorState[BOMBA]=ON; /* Bomba refrigeracion */
}

void apagar_refrigeracion(void){
	ciaaWriteOutput(BOMBA, OFF); /* Rele ADC0 - CHANEL 3 */
	actuatorState[ELECTROVALVULA0]=OFF; /* Activo electrovalvula */
	actuatorState[BOMBA]=OFF; /* Bomba refrigeracion */
}


void update_actuadores(void){
	int i=0;
	for (i=0; i<NRO_ACTUADORES;i++ ){
		ciaaWriteOutput(i, actuatorState[i]);
	}
}


const char *actuadoresHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
	int i=0;
	/* Update all parameters and alarm state */
	for (i=0; i < iNumParams; i++){
		if( strcmp(pcParam[i], "act0") == 0){
			if( strcmp(pcValue[i], "ON") == 0){
				actuatorState[ACTUADOR0] = ON;
			}else{
				actuatorState[ACTUADOR0] = OFF;
			}
			continue;
		}
		if( strcmp(pcParam[i], "act1") == 0){
			if( strcmp(pcValue[i], "ON") == 0){
				actuatorState[ACTUADOR1] = ON;
			}else{
				actuatorState[ACTUADOR1] = OFF;
			}
			continue;
		}
		if( strcmp(pcParam[i], "act2") == 0){
			if( strcmp(pcValue[i], "ON") == 0){
				actuatorState[ELECTROVALVULA0] = ON;
			}else{
				actuatorState[ELECTROVALVULA0] = OFF;
			}
			continue;
		}
		if( strcmp(pcParam[i], "act3") == 0){
			if( strcmp(pcValue[i], "ON") == 0){
				actuatorState[BOMBA] = ON;
			}else{
				actuatorState[BOMBA] = OFF;
			}
			continue;
		}
	}
	return "/index.shtml";
}


const char *configHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
	int i=0;
	/* Update all parameters and alarm state */
	for (i=0; i < iNumParams; i++){
		if( strcmp(pcParam[i], "Tmin") == 0){		/* Temperatura min */
			cotas_values[0]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "Tmax") == 0){			/* Temperatura max */
			cotas_values[1]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "Bmin") == 0){			/* Bateria min */
			cotas_values[2]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "alm0") == 0){			/* Alarma por Temperatura */
			if( strcmp(pcValue[0], "ON") == 0){
				alarmState[TEMP]= ON;
			}else{
				alarmState[TEMP]= OFF;
			}
			continue;
		}
		if( strcmp(pcParam[i], "alm1") == 0){		/* Alarma por Bateria menor al minimo */
			if( strcmp(pcValue[i], "ON") == 0){
				alarmState[BAT]= ON;
			}else{
				alarmState[BAT]= OFF;
			}
			continue;
		}
		if( strcmp(pcParam[i], "ctr0") == 0){ 		/* Control Automatico */
			if( strcmp(pcValue[i], "ON") == 0){
				ctrlautoState = ON;
			}else{
				ctrlautoState = OFF;
			}
			continue;
		}
	}
	return "/index.shtml";
}

const char *modemHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
	int i=0;
	/* Update all parameters and alarm state */
	for (i=0; i < iNumParams; i++){
		if( strcmp(pcParam[i], "first") == 0){		/* Complete name first contact */
			sprintf(contact_report[0].name,pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "cel0") == 0){			/*Complete fist contact celphone*/
			sprintf(contact_report[0].phone,pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "st0") == 0){			/* Check if contact will be active */
			if( strcmp(pcValue[i], "ON") == 0){
				contact_report[0].state=ON;
			}else{
				contact_report[0].state=OFF;
			}
			continue;
		}
		if( strcmp(pcParam[i], "second") == 0){		/* Complete name first contact */
			sprintf(contact_report[1].name,pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "cel1") == 0){			/*Complete fist contact celphone*/
			sprintf(contact_report[1].phone,pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "st1") == 0){			/* Check if contact will be active */
			if( strcmp(pcValue[i], "ON") == 0){
				contact_report[1].state=ON;
			}else{
				contact_report[1].state=OFF;
			}
			continue;
		}
	}
	return "/index.shtml";
}



/*********************************************************************//**
 * @brief               Función para ejecutar al invocar ipaddr.cgi.
 *
 * @param[in]   index Índice dentro de los parámetros de CGI recibidos.
 * @param[in]   numParams Número de parámetros CGI recibidos.
 * @param[in]   *param[] Puntero al vector con los parámetros CGI recibidos.
 * @param[in]   *value[] Puntero al vector con los valores de los parámetros CGI recibidos.
 * @return              Nombre de la página html que devuelve al finalizar.
 **********************************************************************/
const char *cgi_ipaddr(int index, int numParams, char *param[], char *value[])
{
        uint32_t i = 0;
        uint32_t j = 0;
        char cTempString[ 6 ];
        int32_t DatoTemporal;
        struct ip_addr ipTemp;

        (void) index;     // Solo para evitar el warning del compilador.
        (void) numParams; // Solo para evitar el warning del compilador.

        for (i = 0; i < 4; i++){
                sprintf((char *)cTempString, "addr%u", i+1);
                if (strstr(param[i], (char *)cTempString) != (char *)0) {   /* parámetro encontrado */
                        DatoTemporal = atoi(value[i]);
                        if ((DatoTemporal >= 0) && (DatoTemporal <= 255)){
                                configIP_ADDR[i] = DatoTemporal;
                                j++;
                        }
                }
        }
        if (j == 4){
                IP4_ADDR(&ipTemp, configIP_ADDR[0], configIP_ADDR[1], configIP_ADDR[2], configIP_ADDR[3]);
                netif_set_ipaddr(&lpc_netif, &ipTemp); // Cambiar la dirección IP.
        }

        for (i = 0; i < 4; i++){
                sprintf((char *)cTempString, "mask%u", i+1);
                if (strstr(param[i+4], (char *)cTempString) != (char *)0) {   /* parámetro encontrado */
                        DatoTemporal = atoi(value[i+4]);
                        if ((DatoTemporal >= 0) && (DatoTemporal <= 255)){
                                configNET_MASK[i] = DatoTemporal;
                                j++;
                        }
                }
        }
        if (j == 8){
                IP4_ADDR(&ipTemp, configNET_MASK[0], configNET_MASK[1], configNET_MASK[2], configNET_MASK[3]);
                netif_set_netmask(&lpc_netif, &ipTemp); // Cambiar la Máscara.
        }

        for (i = 0; i < 4; i++){
                sprintf((char *)cTempString, "gway%u", i+1);
                if (strstr(param[i+8], (char *)cTempString) != (char *)0) {   /* parámetro encontrado */
                        DatoTemporal = atoi(value[i+8]);
                        if ((DatoTemporal >= 0) && (DatoTemporal <= 255)){
                                configGW_IP_ADDR[i] = DatoTemporal;
                                j++;
                        }
                }
        }
        if (j == 12){
                IP4_ADDR(&ipTemp, configGW_IP_ADDR[0], configGW_IP_ADDR[1], configGW_IP_ADDR[2], configGW_IP_ADDR[3]);
                netif_set_gw(&lpc_netif, &ipTemp); // Cambiar el Default Gateway.
        }

        if (j==12){
        	NVIC_DisableIRQ(ETHERNET_IRQn);
    		netif_set_down(&lpc_netif);
       		reset_server=TRUE;
            return (char *)0;
        }
        else {
                return (char *)0;/*si no se encuentra el URI, HTTPD envía error 404*/
        }
}
