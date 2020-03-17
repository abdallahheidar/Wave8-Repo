/*
 * CPU_power_management.c
 *
 * Created: 3/9/2020 1:33:02 AM
 *  Author: A_ayman
 */ 
#include "CPU_power_management.h"

void CPU_Sleep_Mode_Enable ( uint8_t CPU_Sleep_Mode)
{
	
	MCUCR &= ~(1<<4) &~(1<<5) & ~(1<<6);
	MCUCR |= 1<<7;       //Enable Power management
	MCUCR |= CPU_Sleep_Mode;
	__asm__ __volatile__ ( "sleep" "\n\t" :: ); 
}

uint8_t CPU_Sleep_Mode_Time_Calculate (uint8_t u8_Timer_Channel)
{
	static uint8_t u8_Time_Calc =0;
	static uint8_t u8_Total_Time_Calc =0;
	//Timer_Get_Value(u8_Timer_Channel,&u8_Time_Calc );
	u8_Total_Time_Calc = u8_Time_Calc-u8_Total_Time_Calc ;
	return u8_Total_Time_Calc ;
	
	
}