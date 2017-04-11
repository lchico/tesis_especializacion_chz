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
#define ssiACT1_INDEX			0
#define ssiACT2_INDEX			1

/* The SSI strings that are embedded in the served html files.  If this array
is changed, then the index position defined by the #defines such as
ssiACT1_INDEX above must also be updated. */
static const char *pccSSITags[] =
{
	"act1",
	"act2",
};



#endif /* INC_HTTP_SSI_H_ */
