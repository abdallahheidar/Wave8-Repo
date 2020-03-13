/*
 * App.c
 *
 * Created: 2/24/2020 10:25:29 PM
 * Author : Mohamed Ramadan
 */ 

#include "Sos.h"

#define  F_CPU  (16000000UL)	 
	 

int main(){
	SREG|=(1<<7);
	PORTA_DIR = 0xFF;
	//PORTA_DATA = 0x80;
	
	
	Sos_Init(&ConfigPtr);


	Sos_Start(&Sos_Cfg_start_Fun1);
	Sos_Start(&Sos_Cfg_start_Fun2);
	Sos_Start(&Sos_Cfg_start_Fun3);
	
	while(1)
	{
		
		Sos_Dispatch();
		
	}
	
	
	
}
