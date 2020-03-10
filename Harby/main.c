/*
 * tmuapp.c
 *
 * Created: 24-Feb-20 11:26:07 AM
 * Author : ahmed
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
//#include <avr/io.h>
#include "SERVICE/TMU.h"
#include "MCAL/DIO.h"
#include "Error_table.h"
#include "MCAL/registers.h"

/************************************************************************/
/*					MAIN                                                */
/************************************************************************/

/** APPLICATION
*	Description
** a small application of two toggles one of them is done once"one shot" 
other is done periodicly 
*/

//typedef struct{
//	uint8_t u8_periodic_state;
//	uint8_t u8_id;
//	uint32_t u32_counts;
//	uint8_t u8_TaskState;
//	callback task_ptr;
//}TMU_TaskType;
//
//typedef struct{
//	uint8_t u8_timer_chnl;
//}st_TMU_init;


void SOS_app2(void)
{
	(PORTB_DIR)++;
}

void SOS_app1(void)
{
	(PORTA_DIR)++;
}

int main(void)
{
	st_TMU_init InitCfg = {
			TMU_TMR_CH0
	};
	
	TMU_TaskType TaskCfg1 = {
			TMU_PERIODIC,
			0,
			500,
			0,
			&SOS_app1
	};

	TMU_TaskType TaskCfg2 = {
			TMU_PERIODIC,
			1,
			500,
			0,
			&SOS_app2
	};
	
	TMU_Init(&InitCfg);

	TMU_Start_Timer(&TaskCfg2);
	TMU_Start_Timer(&TaskCfg1);

	while(1)
	{
		TMU_Dispatch();
	}
}

