/*
 * App.c
 *
 * Created: 2/24/2020 10:25:29 PM
 * Author : Mohamed Ramadan
 */ 

#include "Sos.h"
#include "avr/interrupt.h"

#define  F_CPU  (16000000UL)	 
	 

int main(){
	/**enable global interrupt**/
	sei();
	
	/**Initialize the SOS **/
	Sos_Init(&ConfigPtr);

	/**SOS start three tasks**/
	Sos_Start(&Sos_Cfg_start_Fun1);
	Sos_Start(&Sos_Cfg_start_Fun2);
	Sos_Start(&Sos_Cfg_start_Fun3);
	
	while(1)
	{
		/**perform the tasks**/
		Sos_Dispatch();
		
	}
	
	
	
}
