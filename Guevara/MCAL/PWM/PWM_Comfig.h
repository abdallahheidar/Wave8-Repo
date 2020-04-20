/*
 * PWM_Comfig.h
 *
 * Created: 17/02/2020 04:21:55 م
 *  Author: mo
 */


#ifndef PWM_COMFIG_H_
#define PWM_COMFIG_H_



/*********************************/
/*            MACROS             */
/*********************************/


#include "../../Infrastructure/registers.h"
#include "../../Infrastructure/Error.h"
#include "../../Infrastructure/std_types.h"
#define PWM_CH0  (0)
#define PWM_CH1A (1)
#define PWM_CH1B (2)
#define PWM_CH2  (3)
/**********************************************************/
#define		PWM_PRESCALER_NO				(0)
#define		PWM_PRESCALER_8					(1)
#define		PWM_PRESCALER_32				(2)
#define		PWM_PRESCALER_64				(3)
#define		PWM_PRESCALER_128				(4)
#define		PWM_PRESCALER_256				(5)
#define		PWM_PRESCALER_1024				(6)
/*****************************************************/
#define MAX_HOLD 255
#define MAX_HOLD_T1 65535
#define FULL_SPEED 100
/****************************************************/
#define E_OK 0
#define E_NOK 1
typedef uint8_t ERROR_STATUS;
/****************************************************/
typedef struct Pwm_Cfg_s
{
	uint8_t Channel;
	uint8_t Prescaler;
}Pwm_Cfg_s;
/*****************************************************/
extern Pwm_Cfg_s PWM_Configuration_0;
extern Pwm_Cfg_s PWM_Configuration_1A;
extern Pwm_Cfg_s PWM_Configuration_1B;
extern Pwm_Cfg_s PWM_Configuration_2;

/****************************************************/
#define T1_OC1A_CLEAR 0x8000
#define T1_OC1B_CLEAR 0x2000
#define T1_OC1A_OC1B  0xA000
/****************************************************/
#define T1_PWM_Phase_8 0x0120

#define T0_PWM_FAST  0x48
#define T0_INVERTING 0x30
#define T0_NON_INVERTING 0x20

#define T2_PWM_FAST  0x48
#define T2_NON_INVERTING 0x20
/*********************************************************/
#define TIMER_STOPT02 0xF8
#define TIMER_STOPT1 0xFFF8
/***********************************************************/
#define		PWM_PRESCALER_NO_CONFIG				(1)
#define		PWM_PRESCALER_8_CONFIG				(2)
#define		PWM_PRESCALER_64_CONFIG				(3)
#define		PWM_PRESCALER_256_CONFIG			(4)
#define		PWM_PRESCALER_1024_CONFIG			(5)

/****************************************************/
#define		PWM_PRESCALER_32_CONFIG_T2				(3)
#define		PWM_PRESCALER_64_CONFIG_T2				(4)
#define		PWM_PRESCALER_128_CONFIG_T2				(5)
#define		PWM_PRESCALER_256_CONFIG_T2				(6)
#define		PWM_PRESCALER_1024_CONFIG_T2 			(7)

#endif /* PWM_COMFIG_H_ */
