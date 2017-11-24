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

extern sms_flags_t sms_flag;

void vStartControlTask( void ){
	xTaskCreate( 	prvControlTask,						/* Crea la tarea prvControlTask. */
					( const int8_t * const ) "Control", 		/* Texto con el nombre de la tarea (solamente para Debug).  El kernel no usa este nombre. */
					configCONTROL_STACK_SIZE,			/* Tamaño del stack asociado a la tarea. */
					NULL,									/* Parámetro no usado (NULL). */
					configCONTROL_TASK_PRIORITY,		/* Prioridad de la tarea. */
					NULL );									/* No se requiere de un manejador para esta tarea (NULL). */
}

static void prvControlTask( void *pvParameters ){
	( void ) pvParameters;
	static portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; ){
		vTaskDelayUntil( &xLastWakeTime, 1000 * TIMER_CONTROL);

		/* CHECK TEMPERATURE */
		if ((float) cotas_values[1] < Temperatura){  /* Si TEMPERATURA > MAXIMO */
			if ( ctrlautoState == ON){   /*  Y esta en control automático */
				encender_refrigeracion();	/* Enciendo Bomba */
			}
			sms_flag=SOBRE_TEMPERATURA_ALERT; 				/* FLAG P/ENVIO SMS */
		}
		if((float) cotas_values[0] > Temperatura) { // O SI LA TEMPERATURA < MINIMA
			if ( ctrlautoState == ON){ 							/*  control automático */
				apagar_refrigeracion();
			}
			sms_flag=BAJA_TEMPERATURA_ALERT; /* FLAG P/ENVIO SMS */
		}
		/* CHECK BATTERY */
		if (Bateria < cotas_values[2]){  /* Si BATERIA < Cota_Min */
			if ( alarmState[BATERIA] == ON){   /*  Y esta en control automático */
				sms_flag=BATERIA_ALERT; /* SETEO FLAG PARA EVIO DE REPORTE SI ENVIO SMS */
			}
		}
		update_actuadores();
		ciaaToggleOutput(5);
	}
}



