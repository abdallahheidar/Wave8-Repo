/***************************************************/
/* Layer: MCAL                                     */
/* Module: PWM                                     */
/* File: PWM.h                                    */
/* Author: Mohamed Ramadan                        */
/* Description: PWM header file                    */
/***************************************************/
#ifndef PWM_H_
#define PWM_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/
#include "std_types.h"
#include "DIO.h"
/*********************************/
/*            MACROS             */
/*********************************/
#define PWM_CH1A_CH1B  (0)
#define PWM_CH1A (1)
#define PWM_CH1B (2)
#define PWM_CH2  (3)
#define PWM_CH0 (4)


#define		PWM_PRESCALER_NO				0x0000 //(0)
#define		PWM_PRESCALER_8					0x0001//(1)
#define		PWM_PRESCALER_32				0x0002//(2)
#define		PWM_PRESCALER_64				0x0003//(3)
#define		PWM_PRESCALER_128				0x0004	//(4)
#define		PWM_PRESCALER_256					//(5)
#define		PWM_PRESCALER_1024				0x0005	//(6)


#define		T1_FAST_PWM_MODE_ICR1_TOP		0x0218
#define		T1_OC1A_CLEAR					0x8000		
#define		T1_OC1B_CLEAR					0x2000
#define		T1_POLLING						0

#define		InitialValue				    0

typedef struct Pwm_Cfg_s
{
	uint8_t Channel;
	uint8_t Prescaler;
}Pwm_Cfg_s;

/*********************************/
/*    FUNCTIONS DECLARATION      */
/*********************************/

/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
extern uint8_t Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */

/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
extern uint8_t Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
extern uint8_t Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy);

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
extern uint8_t Pwm_Stop(uint8_t Channel);

#endif /* PWM_H_ */