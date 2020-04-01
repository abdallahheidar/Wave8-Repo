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
#include "dcMotorConfig.h"
#include "../../Infrastructure/std_types.h"
#include "../../Infrastructure/registers.h"
#include "../../Infrastructure/common_macros.h"
/*********************************************/
 /*				Defines  					 */
 /********************************************/

#define MOTOR_1			1
#define MOTOR_2 		2

#define MOTOR_STOP 		0
#define MOTOR_FORWARD 	1
#define MOTOR_BACKWARD 	2

/*				ERROR CODE					*/


#define MOTOR_MODULE_ERROR_NUMBER     (50)
#define  ERROR_NULL_PTR                (1)
#define  ERROR_UNILTILZED_MODULE	   (2)
#define  ERROR_MULTIPLE_INIT		   (3)
#define  ERROR_MODULE_UNSTARTED		   (4)
#define  ERROR_INVALIDE_PARAMETAR	   (5)



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
u8_ERROR_STATUS_t Motor_Init(uint8_t u8_Motor_Number);
 
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
 * Descriptio: Controls the motor direction from getting the motor number and the direction.
*/
u8_ERROR_STATUS_t Motor_Direction(uint8_t u8_Motor_Number, uint8_t u8_Motor_Direction);

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
u8_ERROR_STATUS_t Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed);

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
u8_ERROR_STATUS_t Motor_SpeedUpdate(uint8_t u8_Motor_Number, uint8_t u8_Speed);

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: stop the motor.
*/
u8_ERROR_STATUS_t Motor_Stop(uint8_t u8_Motor_Number);

 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether intialized or not
 */
u8_ERROR_STATUS_t Motor_GetStatus(uint8_t u8_Motor_Number, uint8_t* pu8_Mot_status);

#endif // MOTOR_H_