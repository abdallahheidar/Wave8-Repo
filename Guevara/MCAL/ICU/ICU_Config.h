/*
 * ICU_Config.h
 *
 * Created: 18/02/2020 03:19:39 م
 *  Author: mo
 */
#ifndef ICU_CONFIG_H_
#define ICU_CONFIG_H_

#include "../../Infrastructure/registers.h"
#include "../../Infrastructure/Error.h"
#include "../../Infrastructure/std_types.h"
#include "../../Infrastructure/Intturpts Manger/Interrupts.h"
/************************************************************************/
/*				               Constants                                */
/************************************************************************/
#define ICU_CH0			(0)			/* defines External Interrupt 0 */
#define ICU_CH1			(1)       	/* defines External Interrupt 1 */
#define ICU_CH2			(2)			/* defines External Interrupt 2 */

#define ICU_TIMER_CH0	(0)			/* defines Timer 0 */
#define ICU_TIMER_CH1	(1)			/* defines Timer 1 */
#define ICU_TIMER_CH2	(2)			/* defines Timer 2 */

#define ICU_RISE_TO_RISE		(0)
#define ICU_RISE_TO_FALL		(1)
#define ICU_FALE_TO_RISE		(2)

/************************************************************************/
/*				               Structures                               */
/************************************************************************/
typedef struct Icu_cfg_s
{
	uint8_t ICU_Ch_No;		/* To choose the External Interrupt number */
	uint8_t ICU_Ch_Timer;     /* To choose the Timer number */
}Icu_cfg_s;


/***************************************************************************/
typedef unsigned char ERROR_STATUS;
#define E_OK                     0
#define E_NOK                    1
/********************************************************************************/
extern Icu_cfg_s ICU_Configuration;


#endif /* ICU_CONFIG_H_ */
