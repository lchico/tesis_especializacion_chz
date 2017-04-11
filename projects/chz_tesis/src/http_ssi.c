/*
 * http_ssi.c
 *
 *  Created on: 20 de may. de 2016
 *      Author: pato
 */


#include "http_ssi.h"
#include "httpd.h"

#include "lpc_types.h"
#include "string.h"


uint16_t SSIHandler( int iIndex, char *pcBuffer, int iBufferLength )
{

	/* Unused parameter. */
	( void ) iBufferLength;

	/* The SSI handler function that generates text depending on the index of
	the SSI tag encountered. */

	char *ptrState;

	static uint8_t debugInt1 = 0;
	static uint8_t debugInt2 = 100;
	static uint8_t debugInt3 = 100;

	switch( iIndex )
	{

	case ssiACT1_INDEX:
		ptrState = "Ho";
		strcpy( pcBuffer, ptrState );
		break;

	case ssiACT2_INDEX:
		ptrState = "Ho";
		strcpy( pcBuffer, ptrState );
		break;

	default:
		strcpy( pcBuffer, "Error" );
		break;
	}

	return strlen( pcBuffer );
}
