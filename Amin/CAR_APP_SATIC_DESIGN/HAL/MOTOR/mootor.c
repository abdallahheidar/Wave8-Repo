 #include "motor.h"
 #include "DIO.h"
 #include "PWM.h"
#define  MOTOR_FREQUENCY 1
 
 
 /*Describtion: this function initialize the motor direction for motor 1 and 2 and intialize the enable pin for both motors*/
 ERROR_STATUS Motor_Init(uint8 Motor_Number){
	  uint8 eror=0;
 		 DIO_Cfg_s ST_dio1;
		 DIO_Cfg_s ST_dio2;
		Pwm_Cfg_s ST_Pwm;
		  switch (Motor_Number)
		 {
		 case (MOTOR_1):
		 	/* set IN1,2,enable as digital output */
			ST_dio1.GPIO = GPIOD;
		 	ST_dio1.dir = OUTPUT;
		 	ST_dio1.pins = BIT2|BIT3|BIT4;
			eror=DIO_init(&ST_dio1);
			//pwm a1
			ST_Pwm.Channel = PWM_CH1A;
		 	ST_Pwm.Prescaler = T1_PRESCALER_256;
		 	Pwm_Init(&ST_Pwm);
			return NO_ERROR;
			break;
			case (MOTOR_2):
			/* set IN3 ,4 ,enable as digital output */
			ST_dio2.GPIO = GPIOD;
		 	ST_dio2.dir = OUTPUT;
		 	ST_dio2.pins = BIT5|BIT6|BIT7;
			eror=DIO_init(&ST_dio2);
			//pwm b1
			ST_Pwm.Channel = PWM_CH1B;
		 	ST_Pwm.Prescaler = T1_PRESCALER_256;
		 	Pwm_Init(&ST_Pwm);
			return NO_ERROR;
			break;
		 }
 return ERROR;
 }
 
 /*Describtion: this function chose motor and set its direction */
 ERROR_STATUS Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction){
	switch(Motor_Number)
		{
		case (MOTOR_1):
			if(Motor_Direction == MOTOR_FORWARD)
			{
				DIO_Write(GPIOD, BIT2, OUTPUT);
				DIO_Write(GPIOD, BIT3, LOW);
			}
			else if(Motor_Direction == MOTOR_BACKWARD)
			{
				DIO_Write(GPIOD, BIT2, LOW);
				DIO_Write(GPIOD, BIT3, OUTPUT);
			}
			return NO_ERROR;
			break;
			case (MOTOR_2):
			if(Motor_Direction == MOTOR_FORWARD)
			{
				DIO_Write(GPIOD, BIT6, OUTPUT);
				DIO_Write(GPIOD, BIT7, LOW);
			}
			else if(Motor_Direction == MOTOR_BACKWARD)
			{
				DIO_Write(GPIOD, PIN6, LOW);
				DIO_Write(GPIOD, PIN7, OUTPUT);
			}
			return NO_ERROR;
			break;
		}

	
 return ERROR;	 
 }

 
 /*Describtion: this function choose motor and set its direction and speed */
 ERROR_STATUS Motor_Start(uint8 Motor_Number, uint8 Mot_Speed){
	switch(Motor_Number)
		{
		case (MOTOR_1):
			Pwm_Start(PWM_CH1A, Mot_Speed, MOTOR_FREQUENCY);
			return NO_ERROR;
			break;
		case (MOTOR_2):
			Pwm_Start(PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
			return NO_ERROR;
			break; 
	 
		}
return ERROR; 
 }
 
 
 /*Describtion: this function choose motor and update its direction and speed */
 ERROR_STATUS Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed){
	 switch(Motor_Number)
		{
		case (MOTOR_1):
			Pwm_Update(PWM_CH1A,Speed, MOTOR_FREQUENCY);
			return NO_ERROR;
			break;
		case (MOTOR_2):
			Pwm_Update(PWM_CH1B,Speed, MOTOR_FREQUENCY);
			return NO_ERROR;
			break;
		}
return ERROR;	 
 }
 
 
 
 
 /*Describtion: this function choose motor and stop it */

 ERROR_STATUS Motor_Stop(uint8 Motor_Number){
	switch(Motor_Number)
		{
		case MOTOR_1:
			Pwm_Stop(PWM_CH1A);
			DIO_Write(GPIOD, PIN2, LOW);
			DIO_Write(GPIOD, PIN3, LOW);
			return NO_ERROR;
			break;
		case MOTOR_2:
			Pwm_Stop(PWM_CH1B);
			DIO_Write(GPIOD, PIN6, LOW);
			DIO_Write(GPIOD, PIN7, LOW);
			return NO_ERROR;
			break; }	 
         return ERROR;	 
 }
 
 
 