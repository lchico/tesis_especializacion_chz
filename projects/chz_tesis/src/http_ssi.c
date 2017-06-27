/*
 * http_ssi.c
 *
 *  Created on: 20 de may. de 2016
 *      Author: pato
 */


#include "http_ssi.h"
#include "httpd.h"

#include "lpc_types.h"
#include "sensores.h"
#include "string.h"
#include "actuadores.h"
#include "modem.h"



uint16_t SSIHandler( int iIndex, char *pcBuffer, int iBufferLength )
{
	/* Unused parameter. */
	( void ) iBufferLength;

	/* The SSI handler function that generates text depending on the index of
	the SSI tag encountered. */
	char *ptrState;

	switch( iIndex )
	{
	case ssiALARM0_INDEX:
			sprintf(pcBuffer,"%i", alarmState[0]);	// Alarm temperature active/inactive
			break;
	case ssiALARM1_INDEX:
			sprintf(pcBuffer,"%i", alarmState[1]); //Alarm  Battery active/inactive
			break;
	case ssiCTR0_INDEX:
			sprintf(pcBuffer,"%i", ctrlautoState ); //Alarm  Battery active/inactive
			break;
	case ssiTMIN_INDEX:
			sprintf(pcBuffer,"%i", cotas_values[0]); // Temperature min alarm update value
			break;
	case ssiTMAX_INDEX:
			sprintf(pcBuffer,"%i", cotas_values[1]); // Temperature max alarm update value
			break;
	case ssiBMIN_INDEX:
			sprintf(pcBuffer,"%i", cotas_values[2]); //Battery min level update value
			break;
	case ssiACT0_INDEX:
			ptrState = actuatorState[0]?"ON":"OFF";
			strcpy( pcBuffer, ptrState );
			break;
	case ssiACT1_INDEX:
			ptrState =  actuatorState[1]?"ON":"OFF";
			strcpy( pcBuffer, ptrState );
			break;
	case ssiACT2_INDEX:
			ptrState =  actuatorState[2]?"ON":"OFF";
			strcpy( pcBuffer, ptrState );
			break;
	case ssiACT3_INDEX:
			ptrState =  actuatorState[3]?"ON":"OFF";
			strcpy( pcBuffer, ptrState );
			break;
	case ssiSEN0_INDEX:
			//get_temp(pcBuffer);
			GetTemperatura( pcBuffer );
			break;
	case ssiSEN1_INDEX:
			GetBateria( pcBuffer );
			break;
	case ssiSEN2_INDEX:
			// get signal gsm
			GetGSM_signal( pcBuffer );
			break;
	case ssiCEL0_INDEX:
			sprintf(pcBuffer,"%s", contact_report[0].phone); // Cellphone first contact
			break;
	case ssiCEL1_INDEX:
			sprintf(pcBuffer,"%s", contact_report[1].phone); // Cellphone first contact
			break;
	default:
		strcpy( pcBuffer, "Error" );
		break;
	}
	return strlen( pcBuffer );
}
