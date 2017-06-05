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
#define ssiALARM2_INDEX			2

#define ssiTMAX_INDEX			3
#define ssiTMIN_INDEX			4
#define ssiBMIN_INDEX			5
#define ssiSMIN_INDEX			6

#define ssiACT0_INDEX			7
#define ssiACT1_INDEX			8
#define ssiACT2_INDEX			9
#define ssiACT3_INDEX			10
#define ssiSEN0_INDEX			11
#define ssiSEN1_INDEX			12
#define ssiSEN2_INDEX			13


/* The SSI strings that are embedded in the served html files.  If this array
is changed, then the index position defined by the #defines such as
ssiACT1_INDEX above must also be updated. */
static const char *pccSSITags[] =
{
	"alm0",
	"alm1",
	"alm2",
	"Tmax",
	"Tmin",
	"Bmin",
	"Smin",
	"act0",
	"act1",
	"act2",
	"act3",
	"sen0",
	"sen1",
	"sen2",
};



#endif /* INC_HTTP_SSI_H_ */
