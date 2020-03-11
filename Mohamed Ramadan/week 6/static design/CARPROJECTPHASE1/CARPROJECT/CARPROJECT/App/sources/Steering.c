#include "Steering.h"
#include "PWM.h"
#include "Timer.h"
#include "motor.h"


//Timer structures
Timer_Cfg_S Cfg_S_T2;
Timer_Cfg_S Cfg_S_T0;
Timer_Cfg_S Cfg_S_T1;

//PWM Structures
Pwm_Cfg_s  Pwm_Cfg_PWM_1A;
Pwm_Cfg_s  Pwm_Cfg_PWM_1B;

//ICU structures
Icu_cfg_s Icu_cfg_INT2;


/************************************************************************/
/*		      STEERING FUNCTIONS' Implementation		        */
/************************************************************************/


/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

uint8_t Steering_Init(void){
	uint8_t Err_Status = 0;
	Err_Status =E_OK;
	//Initialize Timer structure
	Cfg_S_T2.Timer_CH_NO =TIMER_CH2;
	Cfg_S_T2.Timer_Mode  =TIMER_MODE;
	Cfg_S_T2.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	Cfg_S_T2.Timer_Prescaler =  T2_PRESCALER_256;
	
	
	//initialize PWM structure
	Pwm_Cfg_PWM_1A.Channel   = PWM_CH1A;
	Pwm_Cfg_PWM_1A.Prescaler = T1_PRESCALER_1024;

	Pwm_Cfg_PWM_1B.Channel   = PWM_CH1B;
	Pwm_Cfg_PWM_1B.Prescaler = T1_PRESCALER_1024;
	
	
	//Initialize  ICU structure
	Icu_cfg_INT2.ICU_Ch_No = ICU_CH2;
	Icu_cfg_INT2.ICU_Ch_Timer = ICU_TIMER_CH2;
	
	//Initialize timer
	Timer_Init(&Cfg_S_T2);
	
	//Initialize PWM
	Pwm_Init(&Pwm_Cfg_PWM_1A);
	Pwm_Init(&Pwm_Cfg_PWM_1B);
	
	//ICU Initialization structure
	Icu_Init(&Icu_cfg_INT2);
	
	//Initialize Motor
	Motor_Init(MOTOR_1);
	Motor_Init(MOTOR_2);
	
	
	
	return Err_Status;
}


/**
 * Input: 
 * 	car Direction: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function controls the command and the speed of the car.
 * 							
 */
uint8_t Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed){
	uint8_t Err_Status = 0;
	Err_Status = E_OK;
	
	switch (Steering_CarCmd)
	{
	case MOTOR_STOP:
		Motor_Direction(MOTOR_1,MOTOR_STOP);
		Motor_Direction(MOTOR_2,MOTOR_STOP);
		Motor_Stop(MOTOR_1);
		Motor_Stop(MOTOR_2);
		break;
	case MOTOR_FORWARD:
		Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		Motor_Direction(MOTOR_2,MOTOR_FORWARD);
		Motor_Start(MOTOR_1,speed);
		Motor_Start(MOTOR_2,speed);
		break;
	case MOTOR_BACKWARD:
		Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		Motor_Start(MOTOR_1,speed);
		Motor_Start(MOTOR_2,speed);
		break;
	default:
		Err_Status = E_NOK;			
	}
	
	
	return Err_Status;
}