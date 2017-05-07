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

typedef enum state {OFF = 0, ON = !OFF} state_t;

state_t actuatorState[4] = {OFF,OFF,OFF,OFF};

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

void task(void * a)
{
	while (1) {
		ciaaToggleOutput(5);
		vTaskDelay(500 / portTICK_RATE_MS);
	}
}
