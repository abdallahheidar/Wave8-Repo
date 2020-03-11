#include "extint.h"
#include "ICU.h"
#include "util/delay.h"
#include "registers.h"
#include "Timer.h"
#include "avr/interrupt.h"

#define		T0_PRESCALER_1024               0x05

#define     Rising                     0
#define     Falling                    1
#define		wait_Rising				   2
#define		wait_Falling			   3


volatile uint8_t Edge_Status_Control=0;
volatile uint8_t ICU_Edge_Status = wait_Rising;

volatile uint32_t value=0;
Icu_cfg_s ICU_CFG_S;
static volatile uint8_t counter=0;



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
uint8_t Icu_Init(Icu_cfg_s * Icu_Cfg){
	Timer_Cfg_S Timer_Cfg;
	
	uint8_t	Er_Status = 0;
	uint8_t ICU_Ch_Number  = Icu_Cfg->ICU_Ch_No;
	uint8_t ICU_Ch_TimerNo = Icu_Cfg->ICU_Ch_Timer;
	switch (ICU_Ch_Number)
	{
		case ICU_CH0:
			GICR|=(1<<6);			//enable interrupt 0
			SREG|=(1<<7);			//enable Global Interrupt
			Er_Status =E_OK;	
			break;
		case ICU_CH1:
			GICR|=(1<<7);			//enable interrupt 0
			SREG|=(1<<7);			//enable Global Interrupt
			Er_Status =E_OK;
			break;
		case ICU_CH2:
			EINT2_Enable();
			SREG|=(1<<7);
			Er_Status =E_OK;
			break;
		default:
			Er_Status =E_NOK;
	}
	Timer_Cfg.Timer_CH_NO = ICU_Ch_TimerNo;
	Timer_Cfg.Timer_Mode  = 0;
	Timer_Cfg.Timer_Polling_Or_Interrupt = 0;
	Timer_Cfg.Timer_Prescaler = T2_PRESCALER_1024;
	Timer_Init(&Timer_Cfg);
	return Er_Status;
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
uint8_t Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time){
	
	uint8_t	Er_Status = 0;
	Edge_Status_Control = Icu_EdgeToEdge;
	Er_Status = E_OK;
	
	switch (Icu_Channel)
	{
	case ICU_TIMER_CH0:
			switch (Icu_EdgeToEdge)
			{
			case ICU_RISE_TO_FALL:
				/*clear the ICS2 pin in MCUCSR for falling edge*/
				EINT2_Falling_Edge();
				break;
			case ICU_FALE_TO_RISE:
				/*set the ICS2 pin in MCUCSR for rising edge*/
				EINT2_R_s_Edge();
				break;
			}
		break;
	case ICU_TIMER_CH1:
		switch (Icu_EdgeToEdge)
		{
			case ICU_RISE_TO_FALL:
				/*clear the ICS2 pin in MCUCSR for falling edge*/
				EINT2_Falling_Edge();
				break;
			case ICU_FALE_TO_RISE:
				/*set the ICS2 pin in MCUCSR for rising edge*/
				EINT2_R_s_Edge();
				break;
		}
		break;
	case ICU_TIMER_CH2:
		switch (Icu_EdgeToEdge)
		{
			case ICU_RISE_TO_FALL:
				if(ICU_Edge_Status==wait_Rising){
					/*set the ICS2 pin in MCUCSR for rising edge*/
					EINT2_R_s_Edge();
					//enable interrupt
					EINT2_Enable();
						
					}
					while(ICU_Edge_Status!=Rising){}
					//ICU_Edge_Flag = Rising_Edge;
					//start timer2 counting and p rescaling
					Timer_Start(ICU_TIMER_CH2,0);
					//Disable External Interrupt as per data sheet
					EINT2_Disable();
					//writing falling edge on external interrupt
					EINT2_Falling_Edge();
					//Enable External Interrupt
					EINT2_Enable();
					ICU_Edge_Status = wait_Falling;
					
			    	
						
					while (ICU_Edge_Status!= Falling){}
					
					//read the counter value in SwICU_Read function
					Timer_GetValue(ICU_TIMER_CH2,&value);
					//stop timer2
					Timer_Stop(ICU_TIMER_CH2);
					//Disable External Interrupt as per data sheet
					EINT2_Disable();
					//set external interrupt to rising edge
					EINT2_R_s_Edge();
					//Enable External Interrupt
					EINT2_Enable();
					//reinitialize the counter 2
					TCNT2 = 0;
		
					ICU_Edge_Status = wait_Rising;
					
				break;
			
		/*	case ICU_RISE_TO_FALL:
				
				break;
			
			case ICU_RISE_TO_RISE:
			
			break;	*/
		}
		
		break;	
	}
	/*
	if (ICU_Edge_Flag == Rising_Edge)
	{
		
		//start timer2 counting and p rescaling
		Timer_Start(Icu_Channel,0);
		//Disable External Interrupt as per data sheet
		EINT2_Disable();
		//writing falling edge on external interrupt
		EINT2_Falling_Edge();
		Icu_EdgeToEdge =ICU_RISE_TO_FALL;
		//Enable External Interrupt
		EINT2_Enable();
		GIFR &=~(1<<5);
		
	}
	else
	{
		
		//DIO_Write(PORTC_DATA,BIT0,HIGH);
		
		//stop timer2
		Timer_Stop(Icu_Channel);
		
		
		//read the counter value in SwICU_Read function
		Timer_GetValue(Icu_Channel,(uint16_t*)Icu_Time);
		//Disable External Interrupt as per data sheet
		EINT2_Disable();
		
		EINT2_R_s_Edge();
		Icu_EdgeToEdge =ICU_FALE_TO_RISE;
		//Enable External Interrupt
		EINT2_Enable();
		//reinitialize the counter 0
		TCNT0 = 0;
		
	}
	*/
	*Icu_Time = value;
	//*Icu_Time = 300;
	//TCNT0=value;
	return Er_Status;
}

ISR(INT2_vect){
	GIFR |=(1<<5);
	/*check if the trigger is rising edge*/
	if (ICU_Edge_Status == wait_Rising )
	{
		ICU_Edge_Status = Rising;
		
		
		
	/*	counter++;
		TCNT0 = Edge_Status_Control;*/
		
	}
	else if (ICU_Edge_Status == wait_Falling)
	{
		
		ICU_Edge_Status = Falling;
		
	}
}