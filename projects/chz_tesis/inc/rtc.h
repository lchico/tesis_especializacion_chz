/*
 * rtc.h
 *
 *  Created on: Aug 29, 2017
 *      Author: lchico
 */

#ifndef PROJECTS_CHZ_TESIS_INC_RTC_H_
#define PROJECTS_CHZ_TESIS_INC_RTC_H_


typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;



typedef struct {
	WORD	year;	/* 1..4095 */
	BYTE	month;	/* 1..12 */
	BYTE	mday;	/* 1.. 31 */
	BYTE	wday;	/* 1..7 */
	BYTE	hour;	/* 0..23 */
	BYTE	min;	/* 0..59 */
	BYTE	sec;	/* 0..59 */
} RTC;



int rtc_initialize (RTC * rtc);		/* Initialize RTC */
int rtc_gettime (RTC*);			/* Get time */
int rtc_settime (const RTC*);	/* Set time */


#endif /* PROJECTS_CHZ_TESIS_INC_RTC_H_ */
