/*
 * alarms.c
 *
 *  Created on: 6 de jun. de 2016
 *      Author: pato
 */

#include "include.h"
#include "alarms.h"

state_t alarmState[4] = {OFF,OFF,OFF,OFF};

char* getAlarmState(int alarmNum){

	char *ptrAlarmState;

	if(OFF == alarmState[alarmNum])
		return ptrAlarmState = "NORMAL";
	else
		return ptrAlarmState = "ALARMA";

}

void toggleAlarmState(int alarmNum){

	if( OFF == alarmState[alarmNum])
		alarmState[alarmNum] = ON;

	else if(ON == alarmState[alarmNum])
		alarmState[alarmNum] = OFF;

}
