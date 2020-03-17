/*
 * LCD.c
 *
 * Created: 3/13/2020 2:01:04 PM
 * Author : A_ayman
 */ 

#include "HAL/LCD/LCD.h"
#include <util/delay.h>
#include "APP/APP.h"
#include "SL/SOS/SOS.h"

int main(void)
{
	sei();
	PORTC_DIR = 0XFF;
	PORTD_DIR = 0x00;
	
   //internal Pull up resistors 
	PORTD_DATA = 0x03;
	LCD_Init ();
   Sos_Init(&init);
   gstr_Task_Info_t str_Task_Info ={0,1,1,Task_1m};
   gstr_Task_Info_t str_Task_Info2 ={0,50,1,Task_25m};
	Sos_Create_Task(&str_Task_Info);
   Sos_Create_Task(&str_Task_Info2);
  Sos_Run();
  }