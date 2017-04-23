/*----------------------------------------------------------*/
/* Definición de variables globales para insertar en el HTML*/
/*----------------------------------------------------------*/

#include "include.h"
#include "actuators.h"
#include "string.h"

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

	if( strcmp(pcParam[0], "cmd1") == 0)
	{
		if( strcmp(pcValue[0], "INICIAR") == 0)
			actuatorState[0] = ON;
		else if ( strcmp(pcValue[0], "DETENER") == 0)
			actuatorState[0] = OFF;
	}

	if( strcmp(pcParam[0], "cmd2") == 0)
	{
		if( strcmp(pcValue[0], "INICIAR") == 0)
			actuatorState[1] = ON;
		else if ( strcmp(pcValue[0], "DETENER") == 0)
			actuatorState[1] = OFF;
	}

	if( strcmp(pcParam[0], "cmd3") == 0)
	{
		if( strcmp(pcValue[0], "INICIAR") == 0)
			actuatorState[2] = ON;
		else if ( strcmp(pcValue[0], "DETENER") == 0)
			actuatorState[2] = OFF;
	}

	if( strcmp(pcParam[0], "cmd4") == 0)
	{
		if( strcmp(pcValue[0], "INICIAR") == 0)
			actuatorState[3] = ON;
		else if ( strcmp(pcValue[0], "DETENER") == 0)
			actuatorState[3] = OFF;
	}

	return "/index.shtml";
}


const char *AJAXHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {


	char *ptrState = getActuatorState(portNum_1);

	return ptrState;
}
