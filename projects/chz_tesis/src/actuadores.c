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
