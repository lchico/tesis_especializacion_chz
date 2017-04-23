/*
 * http_ssi.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: pato
 */

#ifndef INC_HTTP_SSI_H_
#define INC_HTTP_SSI_H_

#include "lpc_types.h"
#include "actuators.h"

uint16_t SSIHandler( int iIndex, char *pcBuffer, int iBufferLength );

/* Definitions of the various SSI callback functions within the pccSSITags
array.  If pccSSITags is updated, then these definitions must also be updated. */
#define ssiACT1_INDEX			0
#define ssiACT2_INDEX			1
#define ssiACT3_INDEX			2
#define ssiACT4_INDEX			3
#define ssiSENSOR1_INDEX		4
#define ssiSENSOR2_INDEX		5
#define ssiSENSOR3_INDEX		6
#define ssiALARMA1_INDEX		7
#define ssiALARMA2_INDEX		8
#define ssiALARMA3_INDEX		9
#define ssiALARMA4_INDEX		10

/* The SSI strings that are embedded in the served html files.  If this array
is changed, then the index position defined by the #defines such as
ssiACT1_INDEX above must also be updated. */
static const char *pccSSITags[] =
{
	"act1",
	"act2",
	"act3",
	"act4",
	"sensor1",
	"sensor2",
	"sensor3",
	"alarma1",
	"alarma2",
	"alarma3",
	"alarma4"
};



#endif /* INC_HTTP_SSI_H_ */
