/*
 * control.c
 *
 *  Created on: Jun 18, 2017
 *      Author: lchico
 */

#include "chip.h"
#include "adc_18xx_43xx.h"
#include "string.h"
#include "stdio.h"
#include "sensores.h"
#include "FreeRTOS.h"
#include "task.h"
#include "control.h"
#include "actuadores.h"
#include "modem.h"

extern state_t actuatorState[];
extern float Temperatura;
extern int alarm_values[];
extern state_t alarmState[];


void vStartControlTask( void ){
	xTaskCreate( 	prvControlTask,						/* Crea la tarea prvTemperaturaTask. */
					( const int8_t * const ) "Control", 		/* Texto con el nombre de la tarea (solamente para Debug).  El kernel no usa este nombre. */
					configCONTROL_STACK_SIZE,			/* Tamaño del stack asociado a la tarea. */
					NULL,									/* Parámetro no usado (NULL). */
					configCONTROL_TASK_PRIORITY,		/* Prioridad de la tarea. */
					NULL );									/* No se requiere de un manejador para esta tarea (NULL). */
}

static void prvControlTask( void *pvParameters ){
	( void ) pvParameters;
	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; ){
		vTaskDelayUntil( &xLastWakeTime, 1000 * TIMER_CONTROL);
		/* CHECK TEMPERATURE */
		if (((float) alarm_values[1] - Temperatura) < 0){  /* Si TEMPERATURA > MAXIMO */
			if ( alarmState[0] == ON){   /*  Y esta en control automático */
				actuatorState[0]=ON; /* Activo electrovalvula */
				actuatorState[4]=ON; /* Bomba refrigeracion */
			}
			sms_flag++; /* SETEO FLAG PARA EVIO DE REPORTE SI ENVIO SMS */
		}else if(((float) alarm_values[0] - Temperatura) > 0) { // O SI LA TEMPERATURA < MINIMA
			if ( alarmState[0] == ON){   /*  Y esta en control automático */
				actuatorState[0]= OFF; /* Desactivo electrovalvula */
				actuatorState[4]= OFF; /* Apago la bomba de refrigeracion refrigeracion */
			}
			sms_flag++; /* SETEO FLAG PARA EVIO DE REPORTE SI ENVIO SMS */
		}else{
			sms_flag=0;
		}
		/* CHECK BATTERY

		// Estoy usando bateria?
			// => SI, SETEO FLAG ENVIO SMS
		// SI ALGUN FLAG DE SMS ESTA ENCENDIDO Y ESTA ACTIVO EL ENVIO DE SMS?
			// => SI ENTONCES ENVIO NOTIFICACION DE ALERTA Y ESTADO (REPORT)
		 */
	}
}



