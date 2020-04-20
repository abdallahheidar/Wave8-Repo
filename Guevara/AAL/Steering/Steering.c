/*
 * Steering.c
 *
 * Created: 19/02/2020 06:54:45 ص
 *  Author: mo
 */ 

#include "Steering.h"


ERROR_STATUS Steering_Init(void)
{
	uint8_t ret=0;
	ret=Motor_Init(MOTOR_1|MOTOR_2);
	return ret;
}


ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	uint8_t ret=0;
		switch(Steering_CarCmd)
	{
		case CAR_FORWARD:
			ret= Motor_Direction(MOTOR_1|MOTOR_2, CAR_FORWARD);
			ret=Motor_Start(MOTOR_1|MOTOR_2,speed);
			break;
			case CAR_BACKWARD:
			ret= Motor_Direction(MOTOR_1|MOTOR_2,CAR_BACKWARD);
			ret=Motor_Start(MOTOR_1|MOTOR_2,speed);
			break;
			case CAR_LEFT:
			ret= Motor_Direction(MOTOR_1, CAR_FORWARD);
			ret= Motor_Direction(MOTOR_2, CAR_BACKWARD);
			ret=Motor_Start(MOTOR_1|MOTOR_2,speed);

/*************************************************************/
			ret= Motor_Direction(MOTOR_1, CAR_STOP);
			ret= Motor_Direction(MOTOR_2, CAR_STOP);
			break;
			case CAR_RIGHT:
			ret= Motor_Direction(MOTOR_1, CAR_BACKWARD);
			ret= Motor_Direction(MOTOR_2, CAR_FORWARD);
			ret=Motor_Start(MOTOR_1|MOTOR_2,speed);
		/*	timer2Start();
			timer2DelayMs(100);
*//***********************************************************/
			ret= Motor_Direction(MOTOR_1, CAR_STOP);
			ret= Motor_Direction(MOTOR_2, CAR_STOP);
			break;
	}
	
	
return ret;
}