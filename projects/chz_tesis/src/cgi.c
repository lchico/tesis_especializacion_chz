/*
 * cgi.c
 *
 *  Created on: Apr 18, 2017
 *      Author: lchico
 */

#include "cgi.h"
#include "httpd.h"
#include "actuadores.h"

#include "board_api.h"

tCGI cgi_handlers[]={
		{"/actuadores.cgi",actuatorsHandler},
		{"/alarm.cgi",alarmHandler},
		{"/network.cgi",actuatorsHandler},
//		{"/testAJAX.cgi",AJAXHandler},
};
tCGI * ptrCGIHandlers;


//Initialise cgi environment
void CGIinit( void) {

//	cgi_handler.pcCGIName = "/actuadores.cgi";
//
//	cgi_handler.pfnCGIHandler = actuatorsHandler;

	http_set_cgi_handlers(cgi_handlers, 3);
}
