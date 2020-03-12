/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/
#include "Timer.h"
#include "avr/interrupt.h"
/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/
#define ZERO	0
#define ONE		1
/********* Sos_FLag_Fun variable store no of timer ticks************/
volatile extern uint16_t Sos_FLag_Fun ;

/********* global variable to store the prescaler*************/
uint16_t prescaler_Timer0;    
uint16_t prescaler_Timer1;
uint16_t prescaler_Timer2;

/************************************************************************/
/*		        PORTA Initialization		        */
/************************************************************************/
void PORTA_Init(void){
	/**initialize portA as output port**/
	PORTA_DIR = 0xFF;
}
/************************************************************************/
/*		         TIMER FUNCTIONS' Implementations		        */
/************************************************************************/

/**
 * Input: Pointer to a structure contains the information needed to initialize the timer. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

uint8_t Timer_Init(Timer_Cfg_S* Timer_Cfg){
	uint8_t Er_Status =0;
	
	if (Timer_Cfg == NULL){
		Er_Status = E_NOK;
	}else
	{
	uint8_t CH_NO = 0;
	CH_NO = Timer_Cfg->Timer_CH_NO;
	switch (CH_NO)
	{
	case TIMER_CH0:
		TCCR0 |= Timer_Cfg->Timer_Mode;
		TIMSK |= Timer_Cfg->Timer_Polling_Or_Interrupt;
		prescaler_Timer0 = Timer_Cfg->Timer_Prescaler;
		Er_Status=E_OK;
		break;
	case TIMER_CH1:
		TCCR1 |= Timer_Cfg->Timer_Mode;
		TIMSK |= Timer_Cfg->Timer_Polling_Or_Interrupt;
		prescaler_Timer1 = Timer_Cfg->Timer_Prescaler;
		Er_Status=E_OK;
		break;
	case TIMER_CH2:
		TCCR2 |= Timer_Cfg->Timer_Mode;
		TIMSK |= Timer_Cfg->Timer_Polling_Or_Interrupt;
		prescaler_Timer2 = Timer_Cfg->Timer_Prescaler;
		Er_Status=E_OK;
		break;
	default:
		Er_Status=E_NOK;		
	}
	}
	return	Er_Status;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function starts the needed timer.
 * 							
 */
uint8_t Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count){
	uint8_t Er_Status =0;
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
			TCNT0|=Timer_Count;				//set the initial value of the timer0
			TCCR0|=prescaler_Timer0;
			Er_Status = E_OK;
			break;
		case TIMER_CH1:
			TCNT1|=Timer_Count;				//set the initial value of the timer1
			TCCR1|=prescaler_Timer1;
			Er_Status = E_OK;
			break;
		case TIMER_CH2:
			TCNT2|=Timer_Count;				//set the initial value of the timer2
			TCCR2|=prescaler_Timer2;
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;
	}
return Er_Status;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function stops the needed timer.
 * 							
 */
uint8_t Timer_Stop(uint8_t Timer_CH_NO){
	uint8_t Er_Status =0;
	switch (Timer_CH_NO)
	{
		case TIMER_CH0:
			Clr_Bit(TCCR0,PIN0);
			Clr_Bit(TCCR0,PIN1);
			Clr_Bit(TCCR0,PIN2);			//No clocking so the timer is stopped
			Er_Status = E_OK;
			break;
		case TIMER_CH1:
			Clr_Bit(TCCR1B,PIN0);
			Clr_Bit(TCCR1B,PIN1);
			Clr_Bit(TCCR1B,PIN2);			//No clocking so the timer is stopped
			Er_Status = E_OK;
			break;
		case TIMER_CH2:
			Clr_Bit(TCCR2,PIN0);
			Clr_Bit(TCCR2,PIN1);
			Clr_Bit(TCCR2,PIN2);			//No clocking so the timer is stopped
			
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;	
	}
return Er_Status;	
	
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 	ERROR_STATUS						
 */
uint8_t Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t* Timer_Status){	
	uint8_t Er_Status =0;
	switch (Timer_CH_NO)
	{
		case 0:
			if ((TIFR & BIT0)||(TIFR & BIT1))
			{
				*Timer_Status = True;
				TIFR|=(BIT0|BIT1);
			} 
			else
			{
				*Timer_Status = False;
			}
			Er_Status = E_OK;
			break;
		case 1:
			if ((TIFR & BIT2)||(TIFR & BIT3)||(TIFR & BIT4))
			{
				*Timer_Status = True;
				TIFR|=(BIT2|BIT3|BIT4);
			}
			else
			{
				*Timer_Status = False;
			}
			Er_Status = E_OK;
			break;
		case 2:
			if ((TIFR & BIT6)||(TIFR & BIT7))
			{
				*Timer_Status = True;
				TIFR|=(BIT6|BIT7);
			}
			else
			{
				*Timer_Status = False;
			}
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;
				
	}
	 
	return Er_Status; 
 }

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to return the value of the timer.
 * 							
 */
uint8_t Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Timer_Value){
		
		uint8_t Er_Status =0;
		switch (Timer_CH_NO)
		{
			case 0:
				//*Timer_Value = TCNT0;
				Er_Status = E_OK;
				break;
			case 1:
				//*Timer_Value = TCNT1;
				Er_Status = E_OK;
				break;
			case 2:
				*Timer_Value = TCNT2;
				OCR0= *Timer_Value; 
				Er_Status = E_OK;
				break;
			default:
				Er_Status = E_NOK;	
		}	
	return	Er_Status;
	
}
/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to set its value.
 * 	Timer_Value: This is the value that you will set the timer by it.
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to set the value of the timer.
 * 							
 */
uint8_t Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Timer_Value){
	uint8_t Er_Status =0;
	switch (Timer_CH_NO)
	{
		case 0:
			TCNT0 = Timer_Value ;
			Er_Status = E_OK;
			break;
		case 1:
			TCNT1 = Timer_Value ;
			Er_Status = E_OK;
			break;
		case 2:
			TCNT2 = Timer_Value ;
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;
	}
	return	Er_Status;
}





//function to test only not included in static design of code

void timer2DelayMs(uint16_t u16_delay_in_ms){
	
	while(u16_delay_in_ms--){
		Timer_Start(TIMER_CH2,6);
		while (! (TIFR & (1<<0)));
		TIFR |= (1<<6);
		Timer_Stop(TIMER_CH2);
	}
}


//function to test only not included in static design of code

void timer0DelayMs(uint16_t u16_delay_in_ms){
	
	while(u16_delay_in_ms--){
		Timer_Start(TIMER_CH0,6);
		while (! (TIFR & (1<<0)));
		TIFR |= (1<<0);
		Timer_Stop(TIMER_CH0);
	}
}


//function to test only not included in static design of code
void timer1DelayMs(uint16_t u16_delay_in_ms){
	//uint16_t counter_timer1=0;
	while (u16_delay_in_ms--)
	{
		Timer_Start(TIMER_CH1,1);
		while (!(TIFR & (1<<4)));
		Set_Bit(TIFR,4);
		Timer_Stop(TIMER_CH1);
	}

}


ISR(TIMER2_OVF_vect){
	//here we need to make counter instead of flag due to more than one dispature and handle overflow in counter
	Sos_FLag_Fun = 1;
	//PORTA_DATA = 0x01;
	
}

