/*
 * sensores.c
 *
 *      Author: Luis Chico
 */

#include "chip.h"
#include "adc_18xx_43xx.h"
#include "string.h"
#include "stdio.h"
#include "sensores.h"
#include "FreeRTOS.h"
#include "task.h"




uint16_t CalCeroTempe = 200; // Calibración del ADC de temperatura.
float FEscalaTempe = 0.1025f; // Factor de escala de temperatura.
float Temperatura = 0;

uint16_t CalCeroBatt = 200; // Calibración del ADC de temperatura.
float FEscalaBatt = 0.1025f; // Factor de escala de temperatura.
uint16_t Bateria = 5; // Put the max value to evil send SMS by battery


/* P0.23 -> AD0 */
void adcInit(void)
{
	ADC_CLOCK_SETUP_T adc;

	Chip_ADC_Init(LPC_ADC0, &adc);
	Chip_ADC_SetSampleRate(LPC_ADC0, &adc, 88000);
	/* Temperature adc PIN: 3 de J16 contando desde J4 */
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE);
	/* Battery adc PIN: 1 de J16 contando desde J4 */
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH3, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH3, ENABLE);

	Chip_ADC_SetBurstCmd(LPC_ADC0, ENABLE);
}


uint16_t get_temp(){
	uint16_t data;
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &data);
	return data;
}


uint16_t get_battery(){
	uint16_t data;
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH3, &data);
	return data;
}


float average(samples_t *temp,uint16_t values){
	/* Theses for the first num MUESTRAS */
	if (temp->num_samples < MUESTRAS){
		temp->samples[temp->first_last]=values; // this don't needed
		(temp->num_samples)++; // add the nro new sample
		(temp->first_last)=(temp->first_last+1)%MUESTRAS;//Update the position for the fist sample
		temp->sum_total+=values; // Update sum all samples
		return (temp->sum_total/temp->num_samples);
	}else{ /* After de num MUESTRAS have to comples the cirular array of samples*/
		temp->sum_total-=temp->samples[temp->first_last]; // substract last values of sample
		temp->samples[temp->first_last]=values; // Save the new values
		temp->first_last=(temp->first_last + 1) % MUESTRAS; // Update the last values
		temp->sum_total+=values; // Update sum all samples
		return (temp->sum_total/MUESTRAS);
	}

}



void vStartSensorTask( void ){
	xTaskCreate( 	prvSensorTask,						/* Crea la tarea prvTemperaturaTask. */
					( const int8_t * const ) "Sensor", 		/* Texto con el nombre de la tarea (solamente para Debug).  El kernel no usa este nombre. */
					configTEMPERATURA_STACK_SIZE,			/* Tamaño del stack asociado a la tarea. */
					NULL,									/* Parámetro no usado (NULL). */
					configTEMPERATURA_TASK_PRIORITY,		/* Prioridad de la tarea. */
					NULL );									/* No se requiere de un manejador para esta tarea (NULL). */
}

static void prvSensorTask( void *pvParameters ){
	( void ) pvParameters;
	static portTickType xLastWakeTime;
	uint16_t temp_value,battery_value;
	float ret;
	static samples_t temperature,battery;
	int i=0;
	temperature.num_samples=0;
	temperature.first_last=0;
	temperature.sum_total=0;
	battery.num_samples=0;
	battery.first_last=0;
	battery.sum_total=0;
	for (i=0 ; i<MUESTRAS ;i++){
		temperature.samples[i]=0;
		battery.samples[i]=0;
	}

	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		vTaskDelayUntil( &xLastWakeTime, 1000 * TIMER_SAMPLE );
		temp_value=get_temp();
		ret=average( &temperature, temp_value);
		Temperatura= (ret - CalCeroTempe)*FEscalaTempe;

		battery_value=get_battery();
		ret=average( &battery, battery_value);
		ret = (ret - CalCeroBatt)*FEscalaBatt;
		scale_battery(ret);
	}

}

void scale_battery(float aux){
	if( aux < 5){
		Bateria = 0;
	}else if (aux < 10){
		Bateria = 1;
	}else if (aux < 15){
		Bateria = 2;
	}else if (aux < 20){
		Bateria = 3;
	}else if (aux < 25){
		Bateria = 4;
	}else{
		Bateria = 5;
	}
}


/*********************************************************************//**
 * @brief 		Función para enviar por SSI la temperatura leida.
 *
 * @param[out]	*pcWriteBuffer Puntero para escribir el texto html a enviar.
 * @return 		None
 **********************************************************************/
void GetTemperatura( signed char *pcWriteBuffer )
{
	*pcWriteBuffer = ( signed char ) 0x00;
	sprintf( ( char * ) pcWriteBuffer, "%.2f", Temperatura );
}

/*********************************************************************//**
 * @brief 		Función para enviar por SSI la temperatura leida.
 *
 * @param[out]	*pcWriteBuffer Puntero para escribir el texto html a enviar.
 * @return 		None
 **********************************************************************/

void GetBateria( signed char *pcWriteBuffer )
{
	*pcWriteBuffer = ( signed char ) 0x00;
	sprintf( ( char * ) pcWriteBuffer, "%i", Bateria );
}
