/*
 * Motor.c
 *
 * Created: 18/02/2020 01:38:30 م
 *  Author: mo
 */
#include "motor.h"
static uint8_t gsv_is_Started=0;
static uint8_t gsv_is_intialized=0;
ERROR_STATUS Motor_Init(uint8_t Motor_Number)
{uint8_t Ret=0;
    switch(Motor_Number)
    {
        case MOTOR_1:
        /*Enable PWM Bit...output*/
        /*IN1*/
        /*IN2*/
			gsv_is_intialized=MOTOR_1;
			Ret=Pwm_Init(&PWM_Configuration_1A);
			Ret=DIO_init(&Motorone);

			  break;

          case MOTOR_2:
				gsv_is_intialized=MOTOR_2;
				Ret=Pwm_Init(&PWM_Configuration_1B);
				Ret=DIO_init(&Motortwo);
				break;

          case ALL_MOTOR:
			       {
				/*Enable PWM Bit...output*/
				/*IN1*/
				/*IN2*/
				/*ENABLE PWM BIT FOR MOTOR 2*/
				/*IN3*/
				/*IN4*/
				gsv_is_intialized=ALL_MOTOR;
			Ret=Pwm_Init(&PWM_Configuration_1A);
			Ret=Pwm_Init(&PWM_Configuration_1B);
			Ret=DIO_init(&ALL_Motor);
				break;
			   }
      default:
      Ret=E_NOK;
      break;
    }
return Ret;
}

ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{uint8_t Ret=0;

  switch(Motor_Number)
  {
  	case MOTOR_1:{
  	switch(Motor_Direction)
  	{
  		case MOTOR_FORWARD:
  		{
  			Ret=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
  			Ret=DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);

  			break;
  		}
  		case MOTOR_BACKWARD:
  		{
  		Ret=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
        Ret=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);

  			break;
  		}
  		case MOTOR_STOP:{Ret=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
  		Ret=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
  		break;}

  	}
  		break;
  	}
  	case MOTOR_2:
  	{
  		switch(Motor_Direction)
  		{
  			case MOTOR_FORWARD:
  			{
  				Ret=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
          Ret=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);

  				break;
  			}
  			case MOTOR_BACKWARD:
  			{
  				Ret=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
  			Ret=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
  				break;
  			}
  			case MOTOR_STOP:
  			{
  				Ret=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
  				Ret=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
  				break;
  			}

  		}

  		break;
  	}
  	case ALL_MOTOR:
  	{
  switch(Motor_Direction)
  {
  	case MOTOR_FORWARD:
  	{
  		Ret=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
  		Ret=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);

  	Ret=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
  		Ret=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);

  		break;
  	}
  	case MOTOR_BACKWARD:
  	{

  		Ret=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
      Ret=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
  		Ret=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
  		Ret=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);

  		break;	}
  	case MOTOR_STOP:
  	{
  			Ret=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
  			Ret=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);

  			Ret=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
  			Ret=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);

  		break;
  	}
    default:
    Ret=E_NOK;
    break;
  	}

    }
  	break;



    }
return Ret;
}


ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
  uint8_t Ret=0;
switch (Motor_Number) {
  case MOTOR_1:
  {gsv_is_Started=MOTOR_1;
    Ret=Pwm_Start(PWM_CH1A,Mot_Speed,30);
    break;
  }
  case MOTOR_2:
  {
    gsv_is_Started=MOTOR_2;
    Ret=Pwm_Start(PWM_CH1B,Mot_Speed,30);
    break;
  }
  case ( MOTOR_1 | MOTOR_2 ) :
  {
    gsv_is_Started=MOTOR_1 | MOTOR_2;
    Ret=Pwm_Start(PWM_CH1B,Mot_Speed,30);
    break;
  }
  default:
  Ret=E_NOK;
  break;
}


return Ret;
}
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
  uint8_t Ret=0;

switch (Motor_Number) {
  case MOTOR_1:
  { if(gsv_is_intialized == Motor_Number)
    Ret=Pwm_Start(PWM_CH1A,Speed,30);
    else{Ret=E_NOK;}
    break;
  }
  case MOTOR_2:
  {
    if(gsv_is_intialized == Motor_Number)
      Ret=Pwm_Start(PWM_CH1B,Speed,30);
      else{Ret=E_NOK;}
    break;
  }
  case ( MOTOR_1 | MOTOR_2 ) :
  {
    if(gsv_is_intialized == Motor_Number)
        Ret=Pwm_Start(PWM_CH1B,Speed,30);
        else{Ret=E_NOK;}
    break;
  }
  default:
  Ret=E_NOK;
  break;
}

return Ret;
}

ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	uint8_t Ret=0;
	switch(Motor_Number)
	{
		case MOTOR_1 :
		Ret=Pwm_Stop(PWM_CH1A);
		break;
		case MOTOR_2:
		Ret=Pwm_Stop(PWM_CH1B);
		break;
		default:
		Ret=E_NOK;
		break;
	}


	return Ret;
}

 ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
 {
	 if(gsv_is_intialized == Motor_Number)
		*Mot_status=1;
	 else
	 {
		*Mot_status=0;
	 }
	 
 }
