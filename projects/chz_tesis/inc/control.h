/*
 * control.h
 *
 *  Created on: Jun 18, 2017
 *      Author: lchico
 */

#ifndef PROJECTS_CHZ_TESIS_SRC_CONTROL_H_
#define PROJECTS_CHZ_TESIS_SRC_CONTROL_H_

#define configTEMPERATURA_STACK_SIZE configMINIMAL_STACK_SIZE

#define configCONTROL_STACK_SIZE configMINIMAL_STACK_SIZE
#define configCONTROL_TASK_PRIORITY tskIDLE_PRIORITY+2
#define TIMER_CONTROL 1 // Check temperature TIMER_SAMPLE seconds.

static void prvControlTask( void *pvParameters );
void vStartControlTask( void );




#endif /* PROJECTS_CHZ_TESIS_SRC_CONTROL_H_ */
