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



//uint16_t CalCeroTempe = 1262; // Calibración del ADC de temperatura.
uint16_t CalCeroTempe = 200; // Calibración del ADC de temperatura.
float FEscalaTempe = 0.1025f; // Factor de escala de temperatura.
float Temperatura = 0;
float UmbralTempeMax = 50.0f; // Umbral de temperatura máxima en ºC.
float UmbralTempeMin = -10.0f; // Umbral de temperatura mínima en ºC.


/* P0.23 -> AD0 */
void adcInit(void)
{
	ADC_CLOCK_SETUP_T adc;

	Chip_ADC_Init(LPC_ADC0, &adc);
	Chip_ADC_SetSampleRate(LPC_ADC0, &adc, 88000);

	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_SetBurstCmd(LPC_ADC0, ENABLE);

}


uint16_t get_temp(){
	uint16_t data;
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &data);
	return data;
//	sprintf(temp_buff,"%d",data);
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



void vStartTemperaturaTask( void ){
	xTaskCreate( 	prvTemperaturaTask,						/* Crea la tarea prvTemperaturaTask. */
					( const int8_t * const ) "Temper", 		/* Texto con el nombre de la tarea (solamente para Debug).  El kernel no usa este nombre. */
					configTEMPERATURA_STACK_SIZE,			/* Tamaño del stack asociado a la tarea. */
					NULL,									/* Parámetro no usado (NULL). */
					configTEMPERATURA_TASK_PRIORITY,		/* Prioridad de la tarea. */
					NULL );									/* No se requiere de un manejador para esta tarea (NULL). */
}

static void prvTemperaturaTask( void *pvParameters ){
	( void ) pvParameters;
	portTickType xLastWakeTime;
	uint16_t temp_value;
	float ret;
	static samples_t temperature;
	int i=0;
	temperature.num_samples=0;
	temperature.first_last=0;
	temperature.sum_total=0;
	for (i=0 ; i<MUESTRAS ;i++)
		temperature.samples[i]=0;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		vTaskDelayUntil( &xLastWakeTime, 1000 );
		temp_value=get_temp();
		ret=average( &temperature, temp_value);
		Temperatura= (ret - CalCeroTempe)*FEscalaTempe;
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
	sprintf( ( char * ) pcWriteBuffer, "%2f", Temperatura );
}
