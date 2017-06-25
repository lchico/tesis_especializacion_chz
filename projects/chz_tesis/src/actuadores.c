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

state_t actuatorState[NRO_ACTUADORES] = {OFF,OFF,OFF,ON}; //,OFF,OFF};

int alarm_values[NRO_ALARMS+1] = {TMIN,TMAX,BMIN,SMIN};
/*
 *  Alarm 0 => Temperatura
 *  Alarm 1 =>  Batteri Level
 *  Alarm 2 => Signal GPRS
 */

state_t alarmState[NRO_ALARMS] = {ON,ON,ON};


void encender_refrigeracion(void){
	ciaaWriteOutput(1, ON ); /* Rele ADC0 - CHANEL 1 */
	actuatorState[ELECTROVALVULA0]=ON; /* Activo electrovalvula */
	actuatorState[BOMBA]=ON; /* Bomba refrigeracion */
}

void apagar_refrigeracion(void){
	ciaaWriteOutput(1, OFF); /* Rele ADC0 - CHANEL 3 */
	actuatorState[ELECTROVALVULA0]=OFF; /* Activo electrovalvula */
	actuatorState[BOMBA]=OFF; /* Bomba refrigeracion */
}


const char *actuatorsHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
	if( strcmp(pcParam[0], "act0") == 0)
	{
		if( strcmp(pcValue[0], "ON") == 0){
			actuatorState[ELECTROVALVULA0] = ON;
		}else if ( strcmp(pcValue[0], "DETENER") == 0){
			actuatorState[ELECTROVALVULA0] = OFF;
		}
	}else if( strcmp(pcParam[0], "act1") == 0){
			if( strcmp(pcValue[0], "ON") == 0){
				actuatorState[BOMBA] = ON;
			}else if ( strcmp(pcValue[0], "DETENER") == 0){
				actuatorState[BOMBA] = OFF;
			}
	}else if( strcmp(pcParam[0], "act2") == 0){
			if( strcmp(pcValue[0], "ON") == 0){
				actuatorState[ACTUADOR0] = ON;
			}else if ( strcmp(pcValue[0], "DETENER") == 0){
				actuatorState[ACTUADOR0] = OFF;
			}
	}else if( strcmp(pcParam[0], "act3") == 0){
			if( strcmp(pcValue[0], "ON") == 0){
				actuatorState[ACTUADOR1] = ON;
			}else if ( strcmp(pcValue[0], "DETENER") == 0){
				actuatorState[ACTUADOR1] = OFF;
			}
	}
	return "/configuracion.shtml";
}


const char *alarmHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
	int i=0;
	/* Desactivate all alarms */
	for (i=0 ; i< NRO_ALARMS; i++)
		alarmState[i] = OFF;
	/* Update all parameters and alarm state */
	for (i=0; i < iNumParams; i++){
		if( strcmp(pcParam[i], "Tmin") == 0){
			alarm_values[0]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "Tmax") == 0){
			alarm_values[1]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "Bmin") == 0){
			alarm_values[2]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "Smin") == 0){
			alarm_values[3]= atoi(pcValue[i]);
			continue;
		}
		if( strcmp(pcParam[i], "alm0") == 0){
			alarmState[0]= ON;
			continue;
		}
		if( strcmp(pcParam[i], "alm1") == 0){
			alarmState[1]= ON;
			continue;
		}
		if( strcmp(pcParam[i], "alm2") == 0){
			alarmState[2]= ON;
			continue;
		}

	}
	return "/configuracion.shtml";
}

