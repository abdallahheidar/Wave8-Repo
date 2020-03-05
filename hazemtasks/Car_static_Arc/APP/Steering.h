/*
 * Steering.h
 *
 *  Created on: Dec 21, 2019
 *      Author: Zayed & Saad
 */

#ifndef STEERING_H_
#define STEERING_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "..\common\std_types.h"
#include "..\Common\common_macros.h"
#include "..\Hall\\motor.h"


/*
 *  INCLUDE MOTOR.H HERE
 */

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/

/*Command Macros to call the steering api*/
#define		CAR_STOP		   0
#define		CAR_FORWARD		1
#define		CAR_BACKWARD	2
#define		CAR_RIGHT		3
#define		CAR_LEFT	      4
#define     STOP_SPEED    0
#define     DEFAULT_FREQUNCY  50
   


/************************************************************************/
/*		      STEERING FUNCTIONS' PROTOTYPES		        */
/************************************************************************/


/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

ERROR_STATUS Steering_Init(void);

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function controls the command and the speed of the car.
 * 							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed);





#endif /* STEERING_H_ */