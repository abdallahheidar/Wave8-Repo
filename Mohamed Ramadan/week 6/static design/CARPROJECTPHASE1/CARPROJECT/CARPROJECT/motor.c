#include "motor.h"
#include "PWM.h"

DIO_Cfg_s DIO_Cfg_M1;
DIO_Cfg_s DIO_Cfg_M2;

DIO_Cfg_s DIO_Cfg_M1A;
DIO_Cfg_s DIO_Cfg_M1B;
DIO_Cfg_s DIO_Cfg_M2A;
DIO_Cfg_s DIO_Cfg_M2B;

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
 uint8_t Motor_Init(uint8_t Motor_Number){
	 uint8_t Err_Status = 0;
	 
	 DIO_Cfg_M1.GPIO=MOTOR_EN_1_GPIO;
	 DIO_Cfg_M1.dir =OUTPUT;
	 DIO_Cfg_M1.pins = MOTOR_EN_1_BIT;
	 
	 DIO_Cfg_M2.GPIO=MOTOR_EN_2_GPIO;
	 DIO_Cfg_M2.dir =OUTPUT;
	 DIO_Cfg_M2.pins = MOTOR_EN_2_BIT;
	 
	 DIO_Cfg_M1A.GPIO=MOTOR_OUT_1A_GPIO;
	 DIO_Cfg_M1A.dir =OUTPUT;
	 DIO_Cfg_M1A.pins = MOTOR_OUT_1A_BIT;
	 
	 DIO_Cfg_M1B.GPIO=MOTOR_OUT_1B_GPIO;
	 DIO_Cfg_M1B.dir =OUTPUT;
	 DIO_Cfg_M1B.pins = MOTOR_OUT_1B_BIT;
	 
	 DIO_Cfg_M2A.GPIO=MOTOR_OUT_2A_GPIO;
	 DIO_Cfg_M2A.dir =OUTPUT;
	 DIO_Cfg_M2A.pins = MOTOR_OUT_2A_BIT;
	 
	 DIO_Cfg_M2B.GPIO=MOTOR_OUT_2B_GPIO;
	 DIO_Cfg_M2B.dir =OUTPUT;
	 DIO_Cfg_M2B.pins = MOTOR_OUT_2B_BIT;
	 
	 switch (Motor_Number)
	 {
	 case MOTOR_1:
		DIO_init(&DIO_Cfg_M1);
		DIO_init(&DIO_Cfg_M1A);
		DIO_init(&DIO_Cfg_M1B);
	 	break;
	 case MOTOR_2:
		 DIO_init(&DIO_Cfg_M2);
		 DIO_init(&DIO_Cfg_M2A);
		 DIO_init(&DIO_Cfg_M2B);
		 break;	 
	 default:
		 Err_Status = E_NOK;	 
	 }
	 
	return  Err_Status;
 }

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
uint8_t Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction){
		 uint8_t Err_Status = 0;
		 
	switch (Motor_Number)
	{
		case MOTOR_1:
			switch (Motor_Direction)
			{
			case MOTOR_STOP:
				DIO_Write(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
				DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
				DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
				break;
			case MOTOR_FORWARD:
				DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, HIGH);
				DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
				break;
			case MOTOR_BACKWARD:
				DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
				DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, HIGH);
				break;		
			}
			break;
		case MOTOR_2:
			switch (Motor_Direction)
			{
				case MOTOR_STOP:
				DIO_Write(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, LOW);
				DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
				DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
				break;
				case MOTOR_FORWARD:
				DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, HIGH);
				DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
				break;
				case MOTOR_BACKWARD:
				DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
				DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, HIGH);
				break;
			}
			break;
		default:
			Err_Status = E_NOK;
	}
	
	return  Err_Status;
}

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Start the motor.
*/
uint8_t Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed){
		uint8_t Err_Status = 0;
		switch (Motor_Number)
		{
		case MOTOR_1:
			//Pwm_Start(PWM_CH1A,Mot_Speed,250);
			//Pwm_Start(PWM_CH1A,Mot_Speed,250);
			Pwm_Start(PWM_CH1A_CH1B,Mot_Speed,250);
			break;
		case MOTOR_2:
			//Pwm_Start(PWM_CH1B,Mot_Speed,250);
			Pwm_Start(PWM_CH1A_CH1B,Mot_Speed,250);
			break;
		default:
			Err_Status =E_NOK;		
		}
	return Err_Status;
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor speed from getting the motor number and the speed.
*/
uint8_t Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed){
		uint8_t Err_Status = 0;
		switch (Motor_Number)
		{
			case MOTOR_1:
				Pwm_Start(PWM_CH1A,Speed,250);
				break;
			case MOTOR_2:
				Pwm_Start(PWM_CH1B,Speed,250);
				break;
			case MOTOR_1_2:
				Pwm_Start(PWM_CH1A_CH1B,Speed,250);
				break;	
			default:
				Err_Status =E_NOK;
		}
		return Err_Status;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: stop the motor.
*/
uint8_t Motor_Stop(uint8_t Motor_Number){
	
	 uint8_t Err_Status = 0;
	 
	 switch (Motor_Number)
	 {
		 case MOTOR_1:
			 DIO_Write(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
			 DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			 DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
			break;
		 case MOTOR_2:
			 DIO_Write(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, LOW);
			 DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
			 DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
			break;
		 default:
			Err_Status = E_NOK;
	 }
	 
	 return  Err_Status;
}

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
 uint8_t Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status){
	 uint8_t Err_Status = 0;
	 if (Mot_status==NULL)
	 {
		 Err_Status=E_NOK;
	 } 
	 else
	 {
		switch (Motor_Number)
		{
		case MOTOR_1:
			DIO_Read(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,Mot_status);
			break;
		case MOTOR_2:
			DIO_Read(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,Mot_status);
			break;
		default:
			Err_Status =E_NOK;		
		}
		 
		 
	 }
	 
return Err_Status;	 
 }





























