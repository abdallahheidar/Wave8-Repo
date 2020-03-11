#include "extint.h"
#include "timers.h"
#include "SwICU.h"


void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge){
timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_64,0,0,0,T2_POLLING);

}



EN_SwICU_Edge_t SwICU_GetCfgEdge(void){
	return MCUCSR;
}

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge){
	switch (a_en_inputCaptureEdgeedge)
	{
	case SwICU_EdgeFalling:
		EINT2_Falling_Edge();				//set external interrupt triggered at falling edge
		break;
	case SwICU_EdgeRisiging:
		EINT2_R_s_Edge();				//set external interrupt trigerred at rising edge
		break;	
	}

}

void SwICU_Read(volatile uint8_t * a_pu8_capt){
	a_pu8_capt=TCNT0;
}


void SwICU_Stop(void){

}

void SwICU_Start(void){
	timer2Start();
	ultrasonicstart();
}

void SwICU_Enable(void){


}

void SwICU_Disable(void){


}