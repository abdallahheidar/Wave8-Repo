/*
 * File		: car_sm.h
 * Created	: 19/2/2020 7:30:37 AM
 * Author	: Mohamed Ramadan
 */

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/

#include "car_sm.h"
#include "motor.h"

#define  FreeWay          (>30)
#define  TakeRight        (<30)
#define  AvoidAccident    (<5)
   
/*************************************************************/
/*                     FUNCTIONS Implementation              */
/*************************************************************/

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
uint8_t Car_SM_Init(void){
	uint8_t Err_Status = 0;
	Err_Status = E_OK;
	
	//Initiate steering car machine
	Steering_SteerCar(MOTOR_FORWARD,80);
	//Ultrasonic Initialization
	Us_Init();
	
	return Err_Status;
}

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
uint8_t Car_SM_Update(void){
	 uint16_t Car_State = 0;
	 uint16_t *Get_Distance = NULL;
	 
	 uint8_t Err_Status = 0;
	 Err_Status = E_OK;
	  
	
	//getting the distance measured ultrasonic
	Us_GetDistance(Get_Distance);
	
	//get the state of the car according to the distance 
	Car_State = *Get_Distance;
	
	switch (Car_State)
	{
	case FreeWay:
		//motor direction to forward and move on
		Steering_SteerCar(MOTOR_FORWARD,80);      
		
		break;
	case TakeRight:
		//only change move direction of motor
		Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		
		break;
	case AvoidAccident:
		//stop motor
		Motor_Direction(MOTOR_1,MOTOR_STOP);
		Motor_Direction(MOTOR_2,MOTOR_STOP);
		//motor backward direction
		Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		break;	
	default:
		 Err_Status = E_NOK;
	}
	
	return Err_Status;
}