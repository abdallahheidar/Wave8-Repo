#include "PWM.h"
#define Max_duty 100
#define Top_value 255
#define Zero 0
#define T1_PWM_FAST 0xA108
static uint32 On_time_value=Zero;

 /*Describtion: this function initialize the  pwm for both motors 1 and 2  */
extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	uint8 error=NO_ERROR;
	Timer_cfg_s Pwm;
	Pwm.Timer_CH_NO=TIMER_CH1;
	Pwm.Timer_Mode=TIMER_MODE;
	Pwm.Timer_Polling_Or_Interrupt=T1_COMP_MODE_OCR1A_TOP;
	Pwm.Timer_Prescaler=TIMER_PRESCALER_256;
	error=Timer_Init(&Pwm);
	return error;
}

 /*Describtion: this function start the  pwm for specific motor with specific speed  */
extern ERROR_STATUS Pwm_Start(uint8 Channel,uint8 Duty,uint32 Frequncy){
	uint8 error1=NO_ERROR,error2=NO_ERROR;
	On_time_value=((Duty*Top_value)/Max_duty);
	OCR1A=On_time_value;
	OCR1B=On_time_value;
	error1=Timer_Start(TIMER_CH1,Zero);
	TCCR1|=T1_PWM_FAST;
	return error1;
}

 /*Describtion: this function updatethe  pwm of specific motor with new speed  */
extern ERROR_STATUS Pwm_Update(uint8 Channel,uint8 Duty,uint32 Frequncy){
	uint8 error;
	On_time_value=((Duty*Top_value)/Max_duty);
	error=Timer_Stop(TIMER_CH1);
	error=Timer_SetValue(TIMER_CH1,On_time_value);
    error=Timer_Start(TIMER_CH1,Zero);
	return error;
}

 /*Describtion: this function stops the pwm by stopping the timer  */
extern ERROR_STATUS Pwm_Stop(uint8 Channel){
	uint8 error=NO_ERROR;
	error=Timer_Stop(TIMER_CH1);
	return NO_ERROR;
}
