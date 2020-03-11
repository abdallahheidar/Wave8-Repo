/*
 ============================================================================
 Name        : TMU_Cfg.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef TMU_CFG_H_
#define TMU_CFG_H_

/*********************************includes**********************************/
#include "../Common/std_types.h"
/***************************************************************************/


/*********************************definitions*******************************/

/* Number of the configured TMU Channels */
#define NUMBER_OF_TASKS            4

/* Pre-compile option for timer channel number */
#define TASK_TIMER_CH_NUM              0

/* Pre-compile option for resolution */
#define SOS_TICK_RESOLUTIO                 1

/* Pre-compile option for repetition */
#define TASK_REPETITION                1   /*  0=>one shoot   1=>infinite */


/************************************************************************/
/*			          Structures Definitions	                        */
/************************************************************************/


/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/

#endif /* TMU_CFG_H_ */
