#include "Timer.h"



uint16_t prescaler_Timer;    //global variable to store the prescaler
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

uint8_t Timer_Init(Timer_cfg_s* Timer_Cfg_S){
	
	TCCR0 |= Timer_Cfg_S->Timer_CH_NO;
	TCCR0 |= Timer_Cfg_S->Timer_Mode;
	TCCR0 |= Timer_Cfg_S->Timer_Polling_Or_Interrupt;
	//TCCR0 |= Timer_Cfg_S->Timer_Prescaler;
	prescaler_Timer = Timer_Cfg_S->Timer_Prescaler;
}

