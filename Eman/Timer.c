/*
 * Timer.c
 *
 * Created: 2/15/2020 6:44:32 PM
 *  Author: Ema
 */ 

#include "Timer.h"

static volatile uint8_t Timer_Mode;
static volatile uint8_t Timer_Prescaler;
static void (*guTimer_Cbk_ptr)(void);


ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	ERROR_STATUS ERROR = E_OK;
	
	Timer_Mode = Timer_cfg->Timer_Mode;				//save timer mode 
	guTimer_Cbk_ptr = Timer_cfg->Timer_Cbk_ptr;		//save callback function
	
	/*Check the prescaler for each channel and set the mode*/
	switch(Timer_cfg->Timer_Ch)
	{
		case TIMER_CH0:
		{
			switch(Timer_cfg->Timer_PreScaler)
			{
				case TIMER_PRESCALER_NO:
				Timer_Prescaler = T0_PRESCALER_NO;
				break;
				case TIMER_PRESCALER_8:
				Timer_Prescaler = T0_PRESCALER_8;
				break;
				case TIMER_PRESCALER_32:
				ERROR = E_NOK;
				break;
				case TIMER_PRESCALER_64:
				Timer_Prescaler = T0_PRESCALER_64;
				break;
				case TIMER_PRESCALER_128:
				ERROR = E_NOK;
				break;
				case TIMER_PRESCALER_256:
				Timer_Prescaler = T0_PRESCALER_256;
				break;
				case TIMER_PRESCALER_1024:
				Timer_Prescaler = T0_PRESCALER_1024;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
			
			CLEAR_BIT(TCNT0,0xFF);
			SET_BIT(TCCR0,((Timer_cfg->Timer_Mode)|(T0_OC0_DIS)));
			SET_BIT(TIMSK,Timer_cfg->Timer_Interrupt_Mode);
		}
		break;
		case TIMER_CH1:
		{
			switch(Timer_cfg->Timer_PreScaler)
			{
				case TIMER_PRESCALER_NO:
				Timer_Prescaler = T1_PRESCALER_NO;
				break;
				case TIMER_PRESCALER_8:
				Timer_Prescaler = T1_PRESCALER_8;
				break;
				case TIMER_PRESCALER_32:
				ERROR = E_NOK;
				break;
				case TIMER_PRESCALER_64:
				Timer_Prescaler = T1_PRESCALER_64;
				break;
				case TIMER_PRESCALER_128:
				ERROR = E_NOK;
				break;
				case TIMER_PRESCALER_256:
				Timer_Prescaler = T1_PRESCALER_256;
				break;
				case TIMER_PRESCALER_1024:
				Timer_Prescaler = T1_PRESCALER_1024;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
			
			 SET_BIT(TCCR1,(Timer_cfg->Timer_Mode));
			 SET_BIT(TIMSK,Timer_cfg->Timer_Interrupt_Mode);
		}
		break;
		case TIMER_CH2:
		{
			switch(Timer_cfg->Timer_PreScaler)
			{
				case TIMER_PRESCALER_NO:
				Timer_Prescaler = T2_PRESCALER_NO;
				break;
				case TIMER_PRESCALER_8:
				Timer_Prescaler = T2_PRESCALER_8;
				break;
				case TIMER_PRESCALER_32:
				Timer_Prescaler = T2_PRESCALER_32;
				break;
				case TIMER_PRESCALER_64:
				Timer_Prescaler = T2_PRESCALER_64;
				break;
				case TIMER_PRESCALER_128:
				Timer_Prescaler = T2_PRESCALER_128;
				break;
				case TIMER_PRESCALER_256:
				Timer_Prescaler = T2_PRESCALER_256;
				break;
				case TIMER_PRESCALER_1024:
				Timer_Prescaler = T2_PRESCALER_1024;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
			
			SET_BIT(TCCR2,(Timer_cfg->Timer_Mode));
			SET_BIT(TIMSK,Timer_cfg->Timer_Interrupt_Mode);
		}
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	return ERROR;
}


ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{	
	ERROR_STATUS ERROR = E_OK;
	
	/*Start the timer according to the channel by setting the prescaler value, plus initializing the timer to get the desired number of ticks*/
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		{
			switch(Timer_Mode)
			{
				case T0_NORMAL_MODE:
				TCNT0 = (T0_MAX_VALUE-Timer_Count);
				break;
				case T0_COMP_MODE:
				OCR0 = Timer_Count;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
			SET_BIT(TCCR0,Timer_Prescaler);
		}
		break;
		case TIMER_CH1:	
		{
			switch(Timer_Mode)
			{
				case T1_NORMAL_MODE:
				TCNT1 = (T1_MAX_VALUE-Timer_Count);
				break;
				case T1_COMP_MODE_OCR1A_TOP:
				OCR1A = Timer_Count;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
			SET_BIT(TCCR1,Timer_Prescaler);
		}
		break;
		case TIMER_CH2:
		{
			switch(Timer_Mode)
			{
				case T2_NORMAL_MODE:
				TCNT2 = (T2_MAX_VALUE-Timer_Count);
				break;
				case T2_COMP_MODE:
				OCR2 = Timer_Count;
				break;
				default:
				ERROR = E_NOK;
				break;
			}
			SET_BIT(TCCR2,Timer_Prescaler);
		}
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	return ERROR;
}

ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
	ERROR_STATUS ERROR = E_OK;
	
	/*Stop the timer by clearing the prescaler */
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		CLEAR_BIT(TCCR0,0x07);
		break;
		case TIMER_CH1:
		CLEAR_BIT(TCCR1B,0x07);
		break;
		case TIMER_CH2:
		CLEAR_BIT(TCCR2,0x07);
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	
	return ERROR;
}

ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, BOOL* Data)
{
	ERROR_STATUS ERROR = E_OK;
	
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		{
			switch(Timer_Mode)
			{
				case T0_NORMAL_MODE:
				// return TIFR bit for normal mode
				break;
				case T0_COMP_MODE:
				// return TIFR bit for compare mode
				break;
				default:
				ERROR = E_NOK;
				break;
			}
		}
		break;
		case TIMER_CH1:
		{
			switch(Timer_Mode)
			{
				case T1_NORMAL_MODE:
				// return TIFR bit for normal mode
				break;
				case T1_COMP_MODE_ICR1_TOP:
				// return TIFR bit for compare mode
				break;
				case T1_COMP_MODE_OCR1A_TOP:
				// return TIFR bit for compare mode
				break;
				default:
				ERROR = E_NOK;
				break;
			}
		}
		break;
		case TIMER_CH2:
		{
			switch(Timer_Mode)
			{
				case T2_NORMAL_MODE:
				// return TIFR bit for normal mode
				break;
				case T2_COMP_MODE:
				// return TIFR bit for compare mode
				break;
				default:
				ERROR = E_NOK;
				break;
			}
		}
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	return ERROR;
}

ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data)
{
	ERROR_STATUS ERROR = E_OK;
	
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
		*Data = TCNT0;
		break;
		case TIMER_CH1:
		*Data = TCNT1;
		break;
		case TIMER_CH2:
		*Data = TCNT2;
		break;
		default:
		ERROR = E_NOK;
		break;
	}
	return ERROR;
}

ISR(TIMER0_COMP_vect)
{
	guTimer_Cbk_ptr();
}

ISR(TIMER1_COMPA_vect)
{
	guTimer_Cbk_ptr();
}

ISR(TIMER2_COMP_vect)
{
	guTimer_Cbk_ptr();
}
