/*
 * ICU.c
 *
 * Created: 18/02/2020 04:03:03 م
 *  Author: mo
 */ 
/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
#include "ICU.h"
static volatile uint32_t u32_sgv_TimerVal=0;
static volatile uint8_t u8_ovf_happend=0;
static volatile uint32_t u32_Time_rising_edge=0;
static volatile uint32_t u32_Time_faling_edge=0;
static volatile uint32_t Timer_High=0;
static volatile uint32_t Timer_Low=0;
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	uint8_t Ret=0;
//Enable Global int
G_interrupt_Enable();
//Enable EXTI
switch(Icu_Cfg->ICU_Ch_No)
{
case ICU_CH0:
EX_interrupt_enable0();
break;
case ICU_CH1:
EX_interrupt_enable1();
break;
case ICU_CH2:
EX_interrupt_enable2();
break;
}

switch(Icu_Cfg->ICU_Ch_Timer)
{
	case ICU_TIMER_CH0:
		//Enable Timer0
		TCCR0=0x05;
		TIMSK=0x01;
		break;
	case ICU_TIMER_CH1:
		TCCR1=0x0005;
		TIMSK=0x04;
		break;
	case ICU_TIMER_CH2:
		TCCR2=0x07;
		TIMSK=0x04;
		break;
}

return Ret;
}
/***************************************************************************
 * Function		: Icu_ReadTime
 * Input		:
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{
uint8_t Ret=0;
switch(Icu_Channel)
{
	case ICU_TIMER_CH0:
	TCCR0|=0x03;
	Ret=E_OK;
	break;
	case ICU_TIMER_CH1:
	TCCR1|=0x0005;
	Ret=E_OK;	
	break;
	case ICU_TIMER_CH2:
	TCCR2|=0x07;
	Ret=E_OK;
	break;
	
	default:
	Ret=E_NOK;
	break;
}  

switch(Icu_EdgeToEdge)
{
	case ICU_RISE_TO_RISE:
	*Icu_Time=Timer_High+Timer_Low;
	Ret=E_OK;
	break;
	case ICU_RISE_TO_FALL:
	*Icu_Time=Timer_High;
	Ret=E_OK;
	break;
	case ICU_FALE_TO_RISE:
	*Icu_Time=Timer_Low;
	Ret=E_OK;
	break;
	
	default:
	Ret=E_NOK;
	break;
}

return Ret;
}
void EXTI(void)
{	u32_sgv_TimerVal=(uint32_t)TCNT0+((uint32_t)u8_ovf_happend*255);
	u8_ovf_happend=0;
		if(READBIT(MCUCSR,6))
		{
		u32_Time_rising_edge=u32_sgv_TimerVal;
		Timer_Low = u32_Time_rising_edge - u32_Time_faling_edge;
		/*****************************************/	
		CLEAR_BIT(MCUCSR,6);   /*Make it falling*/
		/***************************************/
		}else{
			u32_Time_faling_edge=u32_sgv_TimerVal;
			Timer_High =u32_Time_faling_edge - u32_Time_rising_edge;
			/*********************************/	
			SET_BIT(MCUCSR,6);		/*Make it Rising*/
			/********************************/
			}	

//UDR=Timer_High;
}/*
void timer_interrupt(void)
{
	u8_ovf_happend=1;
}*/