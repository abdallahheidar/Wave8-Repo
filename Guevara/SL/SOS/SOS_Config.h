/*
 * TMU_Config.h
 *
 * Created: 24/02/2020 01:23:15 م
 *  Author: mo
 */


#ifndef SOS_CONFIG_H_
#define SOS_CONFIG_H_
#include "../../Infrastructure/std_types.h"
#include "../../MCAL/Timer/Timer.h"

/******************************************************************************/
typedef struct TMU_ConfigType{

	uint8_t u8_resolution;
	uint8_t u8_Timer_channel;

}TMU_ConfigType;
/***********************************************************************/


#define TIMER_RESOLUTION_1_MS     1
#define NUM_OF_TICKS_FOR_1_MS	 14
extern const TMU_ConfigType TMU_Configuration;
#endif /* SOS_CONFIG_H_ */
