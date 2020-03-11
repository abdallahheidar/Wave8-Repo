/*
 * App.c
 *
 * Created: 2/24/2020 10:25:29 PM
 * Author : Mohamed Ramadan
 */ 

#include "Tmu.h"

#define  F_CPU  (16000000UL)	 
	 

int main(){
	SREG|=(1<<7);
	PORTA_DIR = 0xFF;
	//PORTA_DATA = 0x80;
	
	
	Tmu_Init(&ConfigPtr);


	Tmu_Start(&TMU_Cfg_start_Fun1);
	Tmu_Start(&TMU_Cfg_start_Fun2);
	Tmu_Start(&TMU_Cfg_start_Fun3);
	
	while(1)
	{
		
		TMU_Dispatch();
		
	}
	
	
	
}
