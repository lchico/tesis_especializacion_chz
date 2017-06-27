/*
 * http_ssi.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: pato
 */

#ifndef INC_HTTP_SSI_H_
#define INC_HTTP_SSI_H_

#include "lpc_types.h"


uint16_t SSIHandler( int iIndex, char *pcBuffer, int iBufferLength );

/* Definitions of the various SSI callback functions within the pccSSITags
array.  If pccSSITags is updated, then these definitions must also be updated. */


#define ssiALARM0_INDEX			0
#define ssiALARM1_INDEX			1

#define ssiCTR0_INDEX			2

#define ssiTMAX_INDEX			3
#define ssiTMIN_INDEX			4
#define ssiBMIN_INDEX			5

#define ssiACT0_INDEX			6	/* Actuador 0 */
#define ssiACT1_INDEX			7	/* Actuador 1 */
#define ssiACT2_INDEX			8	/* Electroválvula 0 */
#define ssiACT3_INDEX			9	/* Bomba Refrigeración */

#define ssiSEN0_INDEX			10	/* Sensor Temperatura */
#define ssiSEN1_INDEX			11  /* Sensor Battery */
#define ssiSEN2_INDEX			12  /* Sensor Signal GPRS */

#define ssiCEL0_INDEX			13  /* Sensor Battery */
#define ssiCEL1_INDEX			14  /* Sensor Signal GPRS */


/* The SSI strings that are embedded in the served html files.  If this array
is changed, then the index position defined by the #defines such as
ssiACT1_INDEX above must also be updated. */
static const char *pccSSITags[] =
{
	"alm0",
	"alm1",
	"ctr0",
	"Tmax",
	"Tmin",
	"Bmin",
	"act0",
	"act1",
	"act2",
	"act3",
	"sen0",
	"sen1",
	"sen2",
	"cel0",
	"cel1",
};



#endif /* INC_HTTP_SSI_H_ */
