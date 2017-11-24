/*
 * sensores.c
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */
#ifndef INC_SENSORES_H_
#define INC_SENSORES_H_

#define MUESTRAS 10 // Cantidad de muestras de Temp. y Hum a tomar por el ADC (hacer coincidir con las de DC).

#define configTEMPERATURA_STACK_SIZE configMINIMAL_STACK_SIZE
#define configTEMPERATURA_TASK_PRIORITY tskIDLE_PRIORITY+2
#define TIMER_SAMPLE 1 // Check temperature TIMER_SAMPLE seconds.

extern uint16_t Bateria;
extern float Temperatura;

typedef struct {
	uint16_t first_last;
	uint16_t num_samples;
	uint16_t samples[MUESTRAS];
	uint16_t sum_total;
}samples_t;


void adcInit(void);
uint16_t get_temp(void);
float average(samples_t *temp,uint16_t values);
void vStartSensorTask( void );
static void prvSensorTask( void *pvParameters );
void GetTemperatura( signed char *pcWriteBuffer );
void GetBateria( signed char *pcWriteBuffer );
void scale_battery(float aux);





#endif /* INC_SENSORES_H_ */
