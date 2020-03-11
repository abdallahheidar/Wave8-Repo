/*
 * File		: car_sm.h
 * Created	: 19/2/2020 7:30:37 AM
 * Author	: Mohamed Ramadan
 */

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/

#include "Us.h"
#include "car_sm.h"
#include "util/delay.h"

#define  FreeWay          0
#define  TakeLeft        1
#define  AvoidAccident    2


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
	
	//Ultrasonic Initialization
	Us_Init();
	
	Steering_Init();
	//Initiate steering car machine
	Steering_SteerCar(CAR_FORWARD,30);
	
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
	 uint16_t Car_Distance = 0;
	 uint16_t Car_state =0;
	 
	 uint16_t *Get_Distance = NULL;
	 
	 uint8_t Err_Status = 0;
	 Err_Status = E_OK;
	  
	Us_Trigger();
	//getting the distance measured ultrasonic
	Us_GetDistance(Get_Distance);
	
	//get the state of the car according to the distance 
	Car_Distance = *Get_Distance;
	
	if (Car_Distance>25 && Car_Distance<=35)
	{
		//Car_state =TakeLeft;
		//only change move direction of motor
		Steering_SteerCar(CAR_LEFT,40);
		_delay_ms(10);
	} 
	else if(Car_Distance<=25)
	{
		//Car_state =AvoidAccident;
		Steering_SteerCar(CAR_BACKWARD,40);
		_delay_ms(50);
		Steering_SteerCar(CAR_FORWARD,35);
		_delay_ms(10);
	}else if(Car_Distance>35)
	{
		//Car_state =FreeWay;
		Steering_SteerCar(CAR_FORWARD,35);
		_delay_ms(5);
		
	}
/*	
	switch (Car_state)
	{
	case FreeWay:
		Steering_SteerCar(CAR_FORWARD,25);
		_delay_ms(20);
		break;
	case AvoidAccident:
		Steering_SteerCar(CAR_BACKWARD,40);
		_delay_ms(35);
		Steering_SteerCar(CAR_FORWARD,35);
		_delay_ms(10);
		break;
	case TakeLeft:
		//only change move direction of motor
		Steering_SteerCar(CAR_LEFT,40);
		_delay_ms(5);
		break;
	}
*/
	return Err_Status;
}