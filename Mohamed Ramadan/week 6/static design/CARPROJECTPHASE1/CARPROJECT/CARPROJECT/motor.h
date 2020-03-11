#ifndef MOTOR_H_
#define MOTOR_H_
/*
 * File		: Motor.h
 * Author	: Sharaf & Osama
 * Version	: 1.1
 */

/*********************************************
 *				Includes  					 *
 ********************************************/
#include "motorConfig.h"
#include "std_types.h"
#include "DIO.h"

/*********************************************
 *				Defines  					 *
 ********************************************/

#define MOTOR_1			1
#define MOTOR_2 		2
#define MOTOR_1_2		3

#define MOTOR_STOP 		0
#define MOTOR_FORWARD 	1
#define MOTOR_BACKWARD 	2

/*********************************************
 *	  	   Function prototypes				 *
 ********************************************/

/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 uint8_t Motor_Init(uint8_t Motor_Number);
 
/**
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backword
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor direction from getting the motor number and the direction.
*/
uint8_t Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction);

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Start the motor.
*/
uint8_t Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed);

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor speed from getting the motor number and the speed.
*/
uint8_t Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed);

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: stop the motor.
*/
uint8_t Motor_Stop(uint8_t Motor_Number);

 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether initialized or not
 */
 uint8_t Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status);

#endif // MOTOR_H_