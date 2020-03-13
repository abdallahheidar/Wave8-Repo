#include "steering.h"

 /*Describtion: this function initialize the steering*/
ERROR_STATUS Steering_Init(void)
{
	uint8 error=NO_ERROR;
	
	error=Motor_Init(MOTOR_1);
	error=Motor_Init(MOTOR_2);
	error=Motor_Start(MOTOR_1, 30);
	error=Motor_Start(MOTOR_2, 30);
	return error;
}


/*Describtion: this function initialize the steering with specific direction (forward,backward,left,right)*/
ERROR_STATUS Steering_SteerCar(uint8 carDirection, uint8 speed)
{
	switch(carDirection)
	{
	case (CAR_STOP):
		Motor_Stop(MOTOR_1);
		Motor_Stop(MOTOR_2);
		break;
	case (CAR_FORWARD):
		Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		Motor_Start(MOTOR_1, speed);
		Motor_Start(MOTOR_2, speed);
		break;
	case (CAR_BACKWARD):
		Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		Motor_Start(MOTOR_1, speed);
		Motor_Start(MOTOR_2, speed);
		break;
	case (CAR_RIGHT):
    	Motor_Stop(MOTOR_2);
		Motor_Direction(MOTOR_1, MOTOR_FORWARD);
	 //  Motor_Direction(MOTOR_2, MOTOR_STOP);
		Motor_Start(MOTOR_1, speed);
		
		break;
	case (CAR_LEFT):
	    Motor_Stop(MOTOR_1);
		//Motor_Direction(MOTOR_1, MOTOR_STOP);
		Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		Motor_Start(MOTOR_2, speed);
		break;
	}
	return NO_ERROR;
}