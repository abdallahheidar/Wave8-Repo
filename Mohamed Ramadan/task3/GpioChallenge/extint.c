
#include "extint.h"
#include "registers.h"
#include "gpio.h"

void EINT2_Init(void){
	GICR|=(1<<BIT5);		//set the INT2 in GICR Register to enable external interrupt module
	//Set_Bit(GICR,BIT5);
}

void EINT2_R_s_Edge(void){
	MCUCSR|=(1<<BIT6);		//set the ISC2 in MCUCSR Register to set ext as rising edge	
	//Set_Bit(MCUCSR,BIT6);
}

void EINT2_Falling_Edge(void){
	MCUCSR &= ~(1<<BIT6);		//clear the ISC2 in MCUCSR Register to set ext as faling edge	
	//Clr_Bit(MCUCSR,BIT6);
}