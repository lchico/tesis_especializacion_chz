/*
 * actuadores.h
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */

#ifndef PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_
#define PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_


/*
 * Actuador 0 => Optional
 * Actuador 1 => Optional
 * Electrovalvula 0 => Habilita el tanque
 * Motor 0 => Motor Bomba refrigeración
 *
*/
enum actuador_t {ACTUADOR0,ACTUADOR1,ELECTROVALVULA0,BOMBA};
#define NRO_ACTUADORES 4


#define NRO_ALARMS 3
typedef enum {TEMPERATURA=0,BATERIA,CONTROLAUTOMATICO} alarm_t;

/* NRO_ALARM 3 =>
 * Temperature: Max and Min
 * Battery: Min
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
#define BMIN 1

/* NRO_ALARM  because the temperature have to be between two values*/


typedef enum state {OFF = 0, ON = !OFF} state_t;
extern state_t actuatorState[NRO_ACTUADORES] ;
extern int cotas_values[NRO_ALARMS];
extern state_t alarmState[];
extern state_t ctrlautoState;



enum {portNum_1 = 0,
	  portNum_2,
	  portNum_3,
	  portNum_4
};

enum{
	TEMP=0,
	BAT
};
char* getActuatorState(int portNum);

void toggleActuatorState(int portNum);

const char *actuadoresHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char *configHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) ;
const char *modemHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char *cgi_ipaddr(int index, int numParams, char *param[], char *value[]);

void encender_refrigeracion(void);
void apagar_refrigeracion(void);
void update_actuadores(void);


#endif /* PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_ */
