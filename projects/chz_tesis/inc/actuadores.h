/*
 * actuadores.h
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */

#ifndef PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_
#define PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_


enum {portNum_1 = 0,
	  portNum_2,
	  portNum_3,
	  portNum_4
};


char* getActuatorState(int portNum);

void toggleActuatorState(int portNum);

const char *actuatorsHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char *AJAXHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

void task(void * a);


#endif /* PROJECTS_CHZ_TESIS_INC_ACTUADORES_H_ */
