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

/*
 * Actuador 0 => Electrovalvula 0
 * Actuador 1 => Electrovalvula 1
 * Actuador 2 => Electrovalvula 2
 * Motor 1 => Motor Bomba refrigeración
 *
*/
state_t actuatorState[4] = {OFF,OFF,OFF,OFF};
int alarm_values[NRO_ALARMS+1] = {TMIN,TMAX,BMIN,SMIN};

/*
 *  Alarm 0 => Temperatura
 *  Alarm 1 =>  Batteri Level
 *  Alarm 2 => Signal GPRS
 */
state_t alarmState[NRO_ALARMS] = {ON,ON,ON};

/*
char* getActuatorState(int portNum){
	char *ptrActuatorState;

	if(OFF == actuatorState[portNum])
		return ptrActuatorState = "APAGADO";	//(char *) estadoActuadorApagado;
	else
		return ptrActuatorState = "ENCENDIDO";	//(char *) estadoActuadorEncendido;
}

void toggleActuatorState(int portNum){

	if( OFF == actuatorState[portNum])
		actuatorState[portNum] = ON;

	else if(ON == actuatorState[portNum])
		actuatorState[portNum] = OFF;

}
*/

void encender_refrigeracion(void){
	ciaaWriteOutput(1, ON );

	actuatorState[0]=ON; /* Activo electrovalvula */
	actuatorState[3]=ON; /* Bomba refrigeracion */
}

void apagar_refrigeracion(void){
	ciaaWriteOutput(1, OFF);
	actuatorState[0]=OFF; /* Activo electrovalvula */
	actuatorState[3]=OFF; /* Bomba refrigeracion */
}


const char *actuatorsHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
	if( strcmp(pcParam[0], "Tmin") == 0)
	{
		if( strcmp(pcValue[0], "ON") == 0)
			ciaaToggleOutput(7);
		else if ( strcmp(pcValue[0], "DETENER") == 0)
			actuatorState[0] = OFF;
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



void task(void * a)
{
	while (1) {
		ciaaToggleOutput(5);

		control_modem();
		vTaskDelay(3500 / portTICK_RATE_MS);
	}
}
