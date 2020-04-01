/*
 * PWM.c
 *
 * Created: 18/02/2020 09:53:30 ص
 *  Author: TOSHIBA
 */ 





/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "PWM.h"
#include "../DIO/DIO.h"
#include <stdio.h>

/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/

#define DEBBUGE 1
#ifdef  DEBBUGE
#define STATIC
#else
#define STATIC static
#endif

#define INIT_MODULE			1
#define UNINIT_MODULE		0
#define PWM_CH1A_INIT_MASK  0x01
#define PWM_CH1B_INIT_MASK  0x02
#define MAX_DUTY_CYCLE 100 
#define MIN_DUTY_CYCLE 0


#define OCR1A_NON_INVERTING_MODE (0x80)
#define OCR1B_NON_INVERTING_MODE (0x20)
#define PHASE_CORRECT_WG11_00BITS  (0x02)
#define PHASE_CORRECT_WG12_13BITS  (0x10)
#define WRITE_TO_TCCRA  (0xf3);
#define STOP_OCR1A   (0x3F)
#define STOP_OCR1B   (0xCF)




#define FRE_100_ICR_ (78)




#define TIMER1_NO_CLOCK       (0xfff8)
#define TIMER1_PRESCALER_NO   (0x0001)
#define TIMER1_PRESCALER_8    (0x0002)
#define TIMER1_PRESCALER_64   (0x0003)
#define TIMER1_PRESCALER_256  (0x0004)
#define TIMEr1_PRESCALER_1024 (0x0005)

STATIC uint8_t u8_PWM_CH_InitStatus= UNINIT_MODULE;
STATIC uint8_t u8_PWM_CH1A_Prescaler;
STATIC uint8_t u8_PWM_CH1B_Prescaler;

extern u8_ERROR_STATUS_t Pwm_Init(gstr_Pwm_Cfg_t *psrt_Pwm_Cfg)
{
	u8_ERROR_STATUS_t u8_PWM_ErrorStatus = E_OK;
	uint8_t u8_InitStause =  INIT_MODULE;

	 
	if (psrt_Pwm_Cfg!=NULL){
		
		switch (psrt_Pwm_Cfg->u8_Channel){
			
			case  PWM_CH1A :
			if ((u8_PWM_CH_InitStatus & PWM_CH1A_INIT_MASK )== UNINIT_MODULE)
			{
				/* make the OCR1a pin  output*/
				PORTD_DIR|=BIT5;
				TCCR1A&=WRITE_TO_TCCRA  ;//if it go wrong comment this part
				TCCR1A|=OCR1A_NON_INVERTING_MODE| PHASE_CORRECT_WG11_00BITS;
				TCCR1B|= PHASE_CORRECT_WG12_13BITS ;
				
				switch(psrt_Pwm_Cfg->u8_Prescaler){
					case PWM_PRESCALER_NO:
						u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_NO;
					break;
					case PWM_PRESCALER_8 :
						u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_8;
					break;
					case PWM_PRESCALER_64:
						u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_64;
					break;
					case PWM_PRESCALER_256:
						u8_PWM_CH1A_Prescaler=TIMER1_PRESCALER_256;
					break;
					case PWM_PRESCALER_1024:
						u8_PWM_CH1A_Prescaler=TIMEr1_PRESCALER_1024;
					break;
					default:
						u8_PWM_ErrorStatus = PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler;
						u8_InitStause =  UNINIT_MODULE;
					break;
				}
				u8_PWM_CH_InitStatus |= (PWM_CH1A_INIT_MASK *u8_InitStause );
				//PORTD_DIR|=BIT5;
			}
			else
			{
				u8_PWM_ErrorStatus = PWM_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT;
			}
			break;
			case PWM_CH1B:
			if ((u8_PWM_CH_InitStatus & PWM_CH1B_INIT_MASK )== UNINIT_MODULE)
			{
				TCNT1=0;
				ICR1=0;
				OCR1B=0;
				/* make the OCR1B pin  output*/
				PORTD_DIR|=BIT4;
				TCCR1A&=WRITE_TO_TCCRA  ;
				TCCR1A|=OCR1B_NON_INVERTING_MODE| PHASE_CORRECT_WG11_00BITS;
				TCCR1B|= PHASE_CORRECT_WG12_13BITS ;
				
				switch(psrt_Pwm_Cfg->u8_Prescaler){
					case PWM_PRESCALER_NO:
						u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_NO;
					break;
					case PWM_PRESCALER_8 :
						u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_8;
					break;
					case PWM_PRESCALER_64:
						u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_64;
					break;
					case PWM_PRESCALER_256:
						u8_PWM_CH1B_Prescaler=TIMER1_PRESCALER_256;
					break;
					case PWM_PRESCALER_1024:
						u8_PWM_CH1B_Prescaler=TIMEr1_PRESCALER_1024;
					break;
					default:
						u8_PWM_ErrorStatus = PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler;
						u8_InitStause =  UNINIT_MODULE;
					break;
				}
				u8_PWM_CH_InitStatus |= (PWM_CH1B_INIT_MASK*u8_InitStause) ;
			}
			else
			{
				u8_PWM_ErrorStatus = PWM_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT;
			}
			break;
			
			default:
			 u8_PWM_ErrorStatus = PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL ;
			break;
		}
	}
	
	else 
		 u8_PWM_ErrorStatus = PWM_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
		 
	return u8_PWM_ErrorStatus;
}

extern u8_ERROR_STATUS_t Pwm_Start(uint8_t u8_Channel,uint8_t u8_Duty,uint32_t u32_Frequncy)
{
	u8_ERROR_STATUS_t u8_PWM_ErrorStatus = E_OK; 
	switch (u8_Channel)
	{
		case PWM_CH1A:
		if((u8_PWM_CH_InitStatus & PWM_CH1A_INIT_MASK) == PWM_CH1A_INIT_MASK )
		{
			
			if( (u8_Duty >= MIN_DUTY_CYCLE) && (u8_Duty<= MAX_DUTY_CYCLE))
			{
				
				switch(u32_Frequncy)
				{
					case FREQ_100_:
						ICR1=FRE_100_ICR_;
						OCR1A=((uint32_t) FRE_100_ICR_*u8_Duty)/100;
						TCCR1|=TIMEr1_PRESCALER_1024 ;
					break;
						
					default:
						
						u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
					break ;
				}
					
			}
			else
			{
										

				u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
					
			}
		}
		else
		{
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM ;
		}
			
		break;
			
		case PWM_CH1B :
		if((u8_PWM_CH_InitStatus & PWM_CH1B_INIT_MASK) == PWM_CH1B_INIT_MASK )
		{
			if( (u8_Duty >= MIN_DUTY_CYCLE) && (u8_Duty<= MAX_DUTY_CYCLE))
			{
				switch(u32_Frequncy)
				{
						
					case FREQ_100_:
						ICR1=FRE_100_ICR_;
						OCR1B=((uint32_t) FRE_100_ICR_*u8_Duty)/100;
						TCCR1|=TIMEr1_PRESCALER_1024 ;
					break;
					default:
						u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
					break ;
				}
			}
			else
			{
				u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
					
			}
		}
		else
		{
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM ;
		}
		break;
			
		default:
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL;
		break;
	}
	
	return u8_PWM_ErrorStatus ;
}

extern u8_ERROR_STATUS_t Pwm_Update(uint8_t u8_Channel,uint8_t u8_Duty,uint32_t u32_Frequncy)
{
	u8_ERROR_STATUS_t u8_PWM_ErrorStatus = E_OK;
	switch (u8_Channel)
	{
			
		case PWM_CH1A:
		if((u8_PWM_CH_InitStatus & PWM_CH1A_INIT_MASK) == PWM_CH1A_INIT_MASK )
		{
			if( (u8_Duty >= MIN_DUTY_CYCLE) && (u8_Duty<= MAX_DUTY_CYCLE))
			{
				switch(u32_Frequncy)
				{
				
					case FREQ_100_:
						ICR1=FRE_100_ICR_;
						OCR1A=(FRE_100_ICR_*u8_Duty)/100;
					break;
					default:
						u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
					break ;
				}
			}
			else
			{
				u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
				
			}
		}
		else
		{
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM ;
		}
			
		break;
			
		case PWM_CH1B :
		if((u8_PWM_CH_InitStatus & PWM_CH1B_INIT_MASK) == PWM_CH1B_INIT_MASK )
		{
			if( (u8_Duty >= MIN_DUTY_CYCLE) && (u8_Duty<= MAX_DUTY_CYCLE))
			{
				switch(u32_Frequncy)
				{
				
					case FREQ_100_:
						ICR1=FRE_100_ICR_;
						OCR1B=(FRE_100_ICR_*u8_Duty)/100;
					break;
					default:
						u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
					break ;
				}
			}
			else
			{
				u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;	
			}
		}
		else
		{
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM ;
		}
		break;
		default:
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL;
		break;
	}
	return u8_PWM_ErrorStatus;
}

extern u8_ERROR_STATUS_t Pwm_Stop(uint8_t u8_Channel)
{
	u8_ERROR_STATUS_t u8_PWM_ErrorStatus = E_OK;

	switch (u8_Channel){
		case PWM_CH1A  :
			if((u8_PWM_CH_InitStatus & PWM_CH1A_INIT_MASK) == PWM_CH1A_INIT_MASK )
			{
				TCCR1A&= STOP_OCR1A;
			}
			else
			{
				u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM ;	
			}
		break;
		case PWM_CH1B:
			if((u8_PWM_CH_InitStatus & PWM_CH1B_INIT_MASK) == PWM_CH1B_INIT_MASK )
			{
			
				TCCR1A&= STOP_OCR1B;
			}
			else
			{
				u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM ;
			}
		break;
		
		default:
			u8_PWM_ErrorStatus =PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL;
		break;
	}
	return u8_PWM_ErrorStatus;
}