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

extern int alarm_values[];
extern state_t alarmState[];



uint16_t SSIHandler( int iIndex, char *pcBuffer, int iBufferLength )
{

	/* Unused parameter. */
	( void ) iBufferLength;

	/* The SSI handler function that generates text depending on the index of
	the SSI tag encountered. */

	char *ptrState;

	switch( iIndex )
	{
/*
	case ssiALARM0_INDEX:
			sprintf(pcBuffer,"%i", alarmState[0]);	// Alarm temperature active/inactive
			break;
	case ssiALARM1_INDEX:
			sprintf(pcBuffer,"%i", alarmState[1]); //Alarm  Battery active/inactive
			break;
	case ssiALARM2_INDEX:
			sprintf(pcBuffer,"%i", alarmState[2]); //Alarm  Battery active/inactive
			break;
	case ssiTMIN_INDEX:
			sprintf(pcBuffer,"%i", alarm_values[0]); // Temperature min alarm update value
			break;
	case ssiTMAX_INDEX:
			sprintf(pcBuffer,"%i", alarm_values[1]); // Temperature max alarm update value
			break;
	case ssiBMIN_INDEX:
			sprintf(pcBuffer,"%i", alarm_values[2]); //Battery min level update value
			break;
	case ssiSMIN_INDEX:
		sprintf(pcBuffer,"%i", alarm_values[3]); // Battery min level update value
			break;
*/
	case ssiACT0_INDEX:
			ptrState = "ON";
			strcpy( pcBuffer, ptrState );
			break;
	case ssiACT1_INDEX:
		ptrState = "OFF";
		strcpy( pcBuffer, ptrState );
		break;
	case ssiACT2_INDEX:
			ptrState = "ON";
			strcpy( pcBuffer, ptrState );
			break;
	case ssiACT3_INDEX:
			ptrState = "OFF";
			strcpy( pcBuffer, ptrState );
			break;

	case ssiSEN0_INDEX:
		get_temp(pcBuffer);
		break;

	case ssiSEN1_INDEX:
			get_temp(pcBuffer);
			break;

	case ssiSEN2_INDEX:
			get_temp(pcBuffer);
			break;

	default:
		strcpy( pcBuffer, "Error" );
		break;
	}

	return strlen( pcBuffer );
}
