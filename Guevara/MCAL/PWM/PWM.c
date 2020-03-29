/*
 * PWM.c
 *
 * Created: 17/02/2020 04:21:17 م
 *  Author: mo
 */

#include "PWM.h"
/*holds prescaler values*/
static uint8_t sgl_Prescaler=0;
static uint8_t sgl_is_started=0;
/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                           */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/

ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{uint8_t Ret=0;
	switch(Pwm_Cfg->Channel)
		{
			case PWM_CH0:
			TCCR0|=T0_PWM_FAST |T0_NON_INVERTING;
			Ret=E_OK;
			break;

			case PWM_CH1A:
			TCCR1 |= T1_PWM_Phase_8 | T1_OC1A_OC1B|0x0020;
			Ret=E_OK;
			break;

			case PWM_CH1B:
			TCCR1 |= T1_PWM_Phase_8 | T1_OC1A_OC1B;
			Ret=E_OK;
			break;


			case PWM_CH2:
			TCCR2 |=T2_PWM_FAST |T2_NON_INVERTING;
			Ret=E_OK;
			break;
			default:
			Ret=E_NOK;
			break;
		}
	sgl_Prescaler=Pwm_Cfg->Prescaler;
return Ret;
	/*0xA000
	TCCR1 |= en_mode | en_OC;
	u32g_T1_Prescaler=en_prescal;
	OCR1A =u16_outputCompareA;
	OCR1B =u16_outputCompareB;
	TCNT1=u16_initialValue;
	*/
}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{uint8_t Ret=0;
	float dutyReal;
uint32_t pwm_time_on = MAX_HOLD;

if(Frequncy <= 31372 && Frequncy > 3921 )
	sgl_Prescaler=PWM_PRESCALER_NO;
else if(Frequncy <= 3921 && Frequncy > 980)
	sgl_Prescaler=PWM_PRESCALER_8;
else if(Frequncy <= 980 && Frequncy > 490)
	sgl_Prescaler=PWM_PRESCALER_32;
else if(Frequncy <= 490 && Frequncy > 245)
	sgl_Prescaler=PWM_PRESCALER_64;
else if(Frequncy <= 245 && Frequncy > 122)
	sgl_Prescaler=PWM_PRESCALER_128;
else if(Frequncy <= 122 && Frequncy > 31)
	sgl_Prescaler=PWM_PRESCALER_256;
else if(Frequncy <= 31 && Frequncy > 0)
	sgl_Prescaler=PWM_PRESCALER_1024;
else{Ret=E_NOK;}
switch(sgl_Prescaler)
{
	case PWM_PRESCALER_NO:
	{
		switch(Channel)
		{
			case PWM_CH0:
			{
				TCCR0|=PWM_PRESCALER_NO_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH1A:
			{
			TCCR1|=PWM_PRESCALER_NO_CONFIG;
			Ret=E_OK;
			break;
			}			
			case PWM_CH1B:
			{	TCCR1|=PWM_PRESCALER_NO_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_NO_CONFIG;
				Ret=E_OK;
				break;
			}
			
			default:
			{
				Ret=E_NOK;
				break;
			}
		
		
		}
		Ret=E_OK;
		break;
	}

	
	case PWM_PRESCALER_8:
	{
		switch(Channel)
		{
			case PWM_CH0:
			{
				TCCR0|=PWM_PRESCALER_8_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH1A:
			case PWM_CH1B:
			{	TCCR1|=PWM_PRESCALER_8_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_8_CONFIG;
			Ret=E_OK;	
				break;
			}
			
			default:
			{
				Ret=E_NOK;
				break;
			}
		
		
		}
		Ret=E_OK;
		break;
	}
	
	case PWM_PRESCALER_32:
	{
		switch(Channel)
		{
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_32_CONFIG_T2;
				Ret=E_OK;
				break;
			}
			default:
			{
				Ret=E_NOK;
			}
		
		}
		Ret=E_OK;
		break;
	}
	
	case PWM_PRESCALER_64:
	{
		switch(Channel)
		{
			case PWM_CH0:
			{
				TCCR0|=PWM_PRESCALER_64_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH1A:
			case PWM_CH1B:
			{	TCCR1|=PWM_PRESCALER_64_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_64_CONFIG_T2;
				Ret=E_OK;
				break;
			}
			default:
			{
				Ret=E_NOK;
				break;
			}
		
		
		}
		Ret=E_OK;
		break;
	}
	
	case PWM_PRESCALER_256:
	{
		switch(Channel)
		{
			case PWM_CH0:
			{
				TCCR0|=PWM_PRESCALER_64_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH1A:
			case PWM_CH1B:
			{	TCCR1|=PWM_PRESCALER_64_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_64_CONFIG_T2;
				Ret=E_OK;
				break;
			}
			default:
			{
				Ret=E_NOK;
				break;
			}
		
		
		}
		Ret=E_OK;
		break;
	}
	
	case PWM_PRESCALER_128:
	{
		switch(Channel)
		{
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_128_CONFIG_T2;
				Ret=E_OK;
				break;
			}
			default:
			{
				Ret=E_NOK;
				break;
			}
		
		}
		Ret=E_OK;
		break;
	}
	
	case PWM_PRESCALER_1024:
	{
		switch(Channel)
		{
			case PWM_CH0:
			{
				TCCR0|=PWM_PRESCALER_1024_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH1A:
			{	TCCR1|=PWM_PRESCALER_NO_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH1B:
			{	TCCR1|=PWM_PRESCALER_1024_CONFIG;
				Ret=E_OK;
				break;
			}
			case PWM_CH2:
			{TCCR2|=PWM_PRESCALER_1024_CONFIG_T2;
				Ret=E_OK;
				break;
			}
			default:
			Ret=E_NOK;
			break;
		
		}
		Ret=E_OK;
		break;
	}
	default:
	Ret=E_NOK;
	break;

	
	
}

switch(Channel)
		{
			case PWM_CH0:{
			pwm_time_on=MAX_HOLD;
			dutyReal=((float)Duty/(float)FULL_SPEED);
			pwm_time_on=(float)pwm_time_on*dutyReal;
			OCR0=pwm_time_on;
			Ret=E_OK;
			break;
			}			
			case PWM_CH1A:{
			pwm_time_on=MAX_HOLD;
			dutyReal=((float)Duty/(float)FULL_SPEED);
			pwm_time_on=(float)pwm_time_on*dutyReal;
			OCR1A=pwm_time_on;
			OCR1B=pwm_time_on;
			Ret=E_OK;
			break;
			}			
			case PWM_CH1B:{
			pwm_time_on=MAX_HOLD;
			dutyReal=((float)Duty/(float)FULL_SPEED);
			pwm_time_on=(float)pwm_time_on*dutyReal;
			OCR1A=pwm_time_on;
			OCR1B=pwm_time_on;
			Ret=E_OK;
			break;
			}
			case PWM_CH2:{
			pwm_time_on=MAX_HOLD;	
			dutyReal=((float)Duty/(float)FULL_SPEED);
			pwm_time_on=(float)pwm_time_on*dutyReal;
			OCR2=pwm_time_on;
			Ret=E_OK;
			}			
			break;
			default:
			Ret=E_NOK;
			break;
		}
sgl_is_started=1;
return Ret;
}
/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/


ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
uint8_t Ret=0;
if (sgl_is_started == 1)
{
	Pwm_Start( Channel,Duty,Frequncy);
Ret=E_OK;
}else{Ret=E_NOK;}
	

return Ret;
}

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/

ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
uint8_t Ret=0;
switch(Channel)
{
	case PWM_CH0:
	TCCR0 &=TIMER_STOPT02;
	Ret=E_OK;
	break;

	case PWM_CH1A:
	case PWM_CH1B:
	TCCR0 &=TIMER_STOPT1;
	Ret=E_OK;
	break;


	case PWM_CH2:
	TCCR2 &=TIMER_STOPT02;
	Ret=E_OK;
	break;
	default:
	Ret=E_NOK;
	break;
}

return Ret;
}
