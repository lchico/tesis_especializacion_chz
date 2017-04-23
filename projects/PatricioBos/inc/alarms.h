/*
 * alarms.h
 *
 *  Created on: 6 de jun. de 2016
 *      Author: pato
 */

#ifndef INC_ALARMS_H_
#define INC_ALARMS_H_

enum {alarmNum_1 = 0,
	  alarmNum_2,
	  alarmNum_3,
	  alarmNum_4
};


char* getAlarmState(int alarmNum);

void toggleAlarmState(int alarmNum);


#endif /* INC_ALARMS_H_ */
