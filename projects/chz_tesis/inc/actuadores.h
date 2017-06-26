/*
 * actuadores.h
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */

#ifndef PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_
#define PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_


/*
 * Actuador 0 => Electrovalvula 0
 * Motor 1 => Motor Bomba refrigeración
 *
*/
enum actuador_t {ACTUADOR0,ACTUADOR1,ELECTROVALVULA0,BOMBA};
#define NRO_ACTUADORES 4


#define NRO_ALARMS 3
typedef enum {TEMPERATURA=0,BATERIA,SIGNAL_GPRS} alarm_t;

/* NRO_ALARM 3 =>
 * Temperature: Max and Min
 * Battery: Min
 * Signal GPRS: Min
 */

/* Default levels to Alarm */
#define TMAX 18
#define TMIN 16

/*Scale 0: Need power supply.
 * 		1: It's 20%
 * 		2: It's 40%
 * 		.
 * 		5: It's 100% charge complete / power supply connect.
 */
#define BMIN 2
/* Signal modem
 * Its 0 to 4 where signal 0 its too low and 4 the best signal
 */
#define SMIN 2


/* NRO_ALARM + 1 because the temperature have to be between two values*/


typedef enum state {OFF = 0, ON = !OFF} state_t;
extern state_t actuatorState[NRO_ACTUADORES] ;
extern int alarm_values[NRO_ALARMS+1];
extern state_t alarmState[];


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

void encender_refrigeracion(void);
void apagar_refrigeracion(void);


#endif /* PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_ */
