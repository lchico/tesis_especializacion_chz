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


void get_temp(char *temp_buff){
	static uint16_t data;
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &data);
	sprintf(temp_buff,"%d",data);
}
