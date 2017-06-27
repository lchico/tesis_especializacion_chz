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
	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; ){
		vTaskDelayUntil( &xLastWakeTime, 1000 * TIMER_CONTROL);
		/* CHECK TEMPERATURE */
		if (((float) cotas_values[1] - Temperatura) < 0){  /* Si TEMPERATURA > MAXIMO */
			if ( ctrlautoState == ON){   /*  Y esta en control automático */
				encender_refrigeracion();	/* Enciendo Bomba */
			}
			sms_flag=SOBRE_TEMPERATURA_ALERT; 				/* FLAG P/ENVIO SMS */
		}else if(((float) cotas_values[0] - Temperatura) > 0) { // O SI LA TEMPERATURA < MINIMA
			if ( ctrlautoState == ON){ 							/*  control automático */
				apagar_refrigeracion();
			}
			sms_flag=BAJA_TEMPERATURA_ALERT; /* FLAG P/ENVIO SMS */
		}else{
			sms_flag=ALL_OK;
		}
		/* CHECK BATTERY */
		if (Bateria < 0){  /* Si BATERIA < MAXIMO */
			if ( alarmState[BATERIA] == ON){   /*  Y esta en control automático */
				sms_flag=BATERIA_ALERT; /* SETEO FLAG PARA EVIO DE REPORTE SI ENVIO SMS */
			}

		}
		update_actuadores();
		// Estoy usando bateria?
			// => SI, SETEO FLAG ENVIO SMS
		// SI ALGUN FLAG DE SMS ESTA ENCENDIDO Y ESTA ACTIVO EL ENVIO DE SMS?
			// => SI ENTONCES ENVIO NOTIFICACION DE ALERTA Y ESTADO (REPORT)
	}
}



