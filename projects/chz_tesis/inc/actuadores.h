/*
 * actuadores.h
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */

#ifndef PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_
#define PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_

/* NRO_ALARM 3 =>
 * Temperature: Max and Min
 * Battery: Min
 * Signal GPRS: Min
 */
#define NRO_ALARMS 3

/* Default levels to Alarm */
#define TMAX 18
#define TMIN 16

/*Scale 0: It's connect to power
 * 		1: It's 20%
 * 		2: It's 40%
 * 		.
 * 		5: It's 100% charge complete
 */
#define BMIN 2
/* Signal modem
 * Its 0 to 4 where signal 0 its too low and 4 the best signal
 */
#define SMIN 2

/* NRO_ALARM + 1 because the temperature have to be between two values*/


typedef enum state {OFF = 0, ON = !OFF} state_t;


enum {portNum_1 = 0,
	  portNum_2,
	  portNum_3,
	  portNum_4
};


char* getActuatorState(int portNum);

void toggleActuatorState(int portNum);

const char *actuatorsHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char *alarmHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) ;
const char *AJAXHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

void task(void * a);


#endif /* PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_ */
