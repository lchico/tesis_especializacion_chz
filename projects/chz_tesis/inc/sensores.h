/*
 * http_ssi.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: pato
 */

#ifndef INC_SENSORES_H_
#define INC_SENSORES_H_

#define MUESTRAS 10 // Cantidad de muestras de Temp. y Hum a tomar por el ADC (hacer coincidir con las de DC).

#define configTEMPERATURA_STACK_SIZE configMINIMAL_STACK_SIZE
#define configTEMPERATURA_TASK_PRIORITY tskIDLE_PRIORITY+4

typedef struct {
	uint16_t first_last;
	uint16_t num_samples;
	uint16_t samples[MUESTRAS];
	uint16_t sum_total;
}samples_t;


void adcInit(void);
uint16_t get_temp(void);
float average(samples_t *temp,uint16_t values);
void vStartTemperaturaTask( void );
static void prvTemperaturaTask( void *pvParameters );
void GetTemperatura( signed char *pcWriteBuffer );




#endif /* INC_SENSORES_H_ */
