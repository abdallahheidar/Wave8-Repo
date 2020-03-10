/*
 * motor.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "motor.h"


/*- DEFINES ------------------------------------------------*/

#define MOTORS_GPIO			(GPIOD)

#define MOTOR_EN_1_BIT		(BIT5)
#define MOTOR_EN_2_BIT		(BIT4)

#define MOTOR_OUT_1A_BIT	(BIT2)
#define MOTOR_OUT_1B_BIT	(BIT3)

#define MOTOR_OUT_2A_BIT	(BIT6)
#define MOTOR_OUT_2B_BIT	(BIT7)

#define MOTOR_FREQUENCY		(100)


/*- GLOBAL STATIC VARIABLES --------------------------------*/

static uint8_t gu8_Motor1_InitFlag = 0;
static uint8_t gu8_Motor2_InitFlag = 0;


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Motor_Init(uint8_t Motor_Number)
{
	uint8_t au8_Ret = E_OK;

	/* A structure to initialize the motor driver */
	DIO_Cfg_s MotorPinsInitialization = {MOTORS_GPIO, 0, OUTPUT};

	/* A structure to initialize the PWM module */
	Pwm_Cfg_s PwmInitialization = {0, 0};

	switch(Motor_Number)
	{
	case MOTOR_1:
		/* Initialize DIO pins for motor1 */
		MotorPinsInitialization.pins = MOTOR_OUT_1A_BIT | MOTOR_OUT_1B_BIT;
		PwmInitialization.Channel = PWM_CH1A;
		gu8_Motor1_InitFlag = 1;
		break;
	case MOTOR_2:
		/* Initialize DIO pins for motor2 */
		MotorPinsInitialization.pins = MOTOR_OUT_2A_BIT | MOTOR_OUT_2B_BIT;
		PwmInitialization.Channel = PWM_CH1B;
		gu8_Motor2_InitFlag = 1;
		break;
	case (MOTOR_1 | MOTOR_2):
		/* Initialize DIO pins for motor1 & motor2 */
		MotorPinsInitialization.pins = MOTOR_OUT_1A_BIT | MOTOR_OUT_1B_BIT | MOTOR_OUT_2A_BIT | MOTOR_OUT_2B_BIT;
		PwmInitialization.Channel = PWM_CH1A | PWM_CH1B;
		gu8_Motor1_InitFlag = 1;
		gu8_Motor2_InitFlag = 1;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	au8_Ret |= DIO_init(&MotorPinsInitialization);
	au8_Ret |= Pwm_Init(&PwmInitialization);

	return au8_Ret;
}

ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
	uint8_t au8_Ret = E_OK;

	uint8_t au8_motorBitA = 0;
	uint8_t au8_motorBitB = 0;

	/* A switch case to determine whether to set the direction of motor1, motor2, or motor1 and motor2 */
	switch(Motor_Number)
	{
	case MOTOR_1:
		au8_motorBitA = MOTOR_OUT_1A_BIT;
		au8_motorBitB = MOTOR_OUT_1B_BIT;
		break;
	case MOTOR_2:
		au8_motorBitA = MOTOR_OUT_2A_BIT;
		au8_motorBitB = MOTOR_OUT_2B_BIT;
		break;
	case (MOTOR_1 | MOTOR_2):
		{
		au8_motorBitA = MOTOR_OUT_1A_BIT | MOTOR_OUT_2A_BIT;
		au8_motorBitB = MOTOR_OUT_1B_BIT | MOTOR_OUT_2B_BIT;
		}
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	/* A switch case to determine the selected motor's direction */
	switch(Motor_Direction)
	{
	case MOTOR_FORWARD:
		au8_Ret |= DIO_Write(MOTORS_GPIO, au8_motorBitA, HIGH);
		au8_Ret |= DIO_Write(MOTORS_GPIO, au8_motorBitB, LOW);
		break;

	case MOTOR_BACKWARD:
		au8_Ret |= DIO_Write(MOTORS_GPIO, au8_motorBitA, LOW);
		au8_Ret |= DIO_Write(MOTORS_GPIO, au8_motorBitB, HIGH);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
	uint8_t au8_Ret = E_OK;

	/* A switch case to determine which motor to start */
	switch(Motor_Number)
	{
	case MOTOR_1:
		au8_Ret |= Pwm_Start(PWM_CH1A, Mot_Speed, MOTOR_FREQUENCY);
		break;
	case MOTOR_2:
		au8_Ret |= Pwm_Start(PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
		break;
	case (MOTOR_1 | MOTOR_2):
		{
		au8_Ret |= Pwm_Start(PWM_CH1A | PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
		break;
		}
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
	uint8_t au8_Ret = E_OK;

	/* A switch case to determine which motor to update its speed */
	switch(Motor_Number)
	{
	case MOTOR_1:
		au8_Ret |= Pwm_Update(PWM_CH1A, Speed, MOTOR_FREQUENCY);
		break;
	case MOTOR_2:
		au8_Ret |= Pwm_Update(PWM_CH1B, Speed, MOTOR_FREQUENCY);
		break;
	case (MOTOR_1 | MOTOR_2):
		{
		au8_Ret |= Pwm_Update(PWM_CH1A | PWM_CH1B, Speed, MOTOR_FREQUENCY);
		break;
		}
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	uint8_t au8_Ret = E_OK;

	/* A switch case to determine which motor to stop */
	switch(Motor_Number)
	{
	case MOTOR_1:
		au8_Ret |= Pwm_Stop(PWM_CH1A);
		break;
	case MOTOR_2:
		au8_Ret |= Pwm_Stop(PWM_CH1B);
		break;
	case (MOTOR_1 | MOTOR_2):
		{
		au8_Ret |= Pwm_Stop(PWM_CH1A | PWM_CH1B);
		break;
		}
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
{
	uint8_t au8_Ret;

	/* A switch case to determine which motor to get its status */
	switch(Motor_Number)
	{
	case MOTOR_1:
		*Mot_status = gu8_Motor1_InitFlag;
		break;
	case MOTOR_2:
		*Mot_status = gu8_Motor2_InitFlag;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}
