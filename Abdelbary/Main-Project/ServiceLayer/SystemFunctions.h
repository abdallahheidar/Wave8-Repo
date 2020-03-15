/*
 * SystemFunctions.h
 *
 * Created: 3/9/2020 7:53:44 PM
 *  Author: mahmo
 */ 


#ifndef SYSTEMFUNCTIONS_H_
#define SYSTEMFUNCTIONS_H_
#include "../common_macros.h"

/* MCUCR */
#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

#define SLEEP_MODE_IDLE (0x00<<4)
#define SLEEP_MODE_ADC (0x01<<4)
#define SLEEP_MODE_PWR_DOWN (0x02<<4)
#define SLEEP_MODE_PWR_SAVE (0x03<<4)
#define SLEEP_MODE_STANDBY (0x06<<4)
#define SLEEP_MODE_EXT_STANDBY (0x07<<4)






#endif /* SYSTEMFUNCTIONS_H_ */