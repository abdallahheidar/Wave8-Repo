/***************************************************/
/* Layer: MCAL                                     */
/* Module: PWM                                     */
/* File: PWM.h                                     */
/* Author: Team A                                  */
/* Description: PWM header file                    */
/***************************************************/
#ifndef PWM_H_
#define PWM_H_

/*********************************/
/*            MACROS             */
/*********************************/


#include "std_types.h"
#include "registers.h"
#include "Common_Macros.h"


#define PWM_CH0  (0)
#define PWM_CH1A (1)
#define PWM_CH1B (2)
#define PWM_CH2  (3)

#define  PRESCALER_1          1
#define  PRESCALER_8          2
#define  PRESCALER_32         3
#define  PRESCALER_64         4
#define  PRESCALER_128        5
#define  PRESCALER_256        6
#define  PRESCALER_1024       7

#define     PWM_FREQUENCY_100           0

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
extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 1) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ  (not implemented yet)                   */
/*Frequency (Prescaler 8) --> 100HZ                                              */
/*Frequency (Prescaler 64) --> 490HZ     (not implemented yet)                   */
/*Frequency (Prescaler 256) --> 122HZ    (not implemented yet)                   */
/*Frequency (Prescaler 1024) --> 31HZ    (not implemented yet)                   */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint8_t Frequncy);

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint8_t Frequncy);

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
extern ERROR_STATUS Pwm_Stop(uint8_t Channel);

#endif /* PWM_H_ */