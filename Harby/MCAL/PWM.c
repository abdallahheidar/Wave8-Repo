/*
 * PWM.c
 *
 *  Created on: Feb 17, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "PWM.h"


/*- DEFINES ------------------------------------------------*/

#define STOP	(0)

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

#define PERCENTAGE	100

#define	TIMER_PRESCALER_MASK	0xF8
#define	TIMER_PRESCALER_NO		1UL
#define	TIMER_PRESCALER_8		8UL
#define	TIMER_PRESCALER_64		64UL


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{
	uint8_t au8_Ret = E_OK;

	/* PWM mode */
	CLEAR_BIT(TCCR1A_R, FOC1B);
	CLEAR_BIT(TCCR1A_R, FOC1A);

	/* Fast PWM mode 16-bit timer mode chosen */
	CLEAR_BIT(TCCR1A_R, WGM10);
	SET_BIT(TCCR1A_R, WGM11);
	SET_BIT(TCCR1B_R, WGM12);
	SET_BIT(TCCR1B_R, WGM13);

	/* A switch case to determine which channel to be used for PWM operation */
	switch(Pwm_Cfg->Channel)
	{
	case PWM_CH1A:
		SET_BIT(TCCR1A_R, COM1A0);
		SET_BIT(TCCR1A_R, COM1A1);
		PORTD_DIR |= BIT5;
		break;
	case PWM_CH1B:
		SET_BIT(TCCR1A_R, COM1B0);
		SET_BIT(TCCR1A_R, COM1B1);
		PORTD_DIR |= BIT4;
		break;
	case (PWM_CH1A | PWM_CH1B):
	{
		SET_BIT(TCCR1A_R, COM1A0);
		SET_BIT(TCCR1A_R, COM1A1);
		SET_BIT(TCCR1A_R, COM1B0);
		SET_BIT(TCCR1A_R, COM1B1);
		PORTD_DIR |= BIT4 | BIT5;
		break;
	}
	default:
		au8_Ret = E_NOK;
		break;
	}

	/* Zero the timer counter register */
	TCNT1_R = 0;

	return au8_Ret;
}

ERROR_STATUS Pwm_Start(uint8_t Channel, uint8_t Duty, uint32_t Frequency)
{
	uint8_t au8_Ret = E_OK;

	/* An operation to determine the duty cycle according to the used inverting mode */
	Duty = PERCENTAGE - Duty;

	if(Frequency >= 4 && Frequency <= 40000)
	{
		/* An if condition to determine the prescaler and the ICR register according to the required frequency */
		if(Frequency >= 300)
		{
			ICR1_R = F_CPU / (TIMER_PRESCALER_NO * Frequency);
			TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | BIT0;
		}else if(Frequency >= 40)
		{
			ICR1_R = F_CPU / (TIMER_PRESCALER_8 * Frequency);
			TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | BIT1;
		}else if(Frequency >= 4)
		{
			ICR1_R = F_CPU / (TIMER_PRESCALER_64 * Frequency);
			TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | BIT0 | BIT1;
		}
	}else
	{
		au8_Ret = E_NOK;
	}

	if(Duty >= 0 && Duty <= 100)
	{
		/* A switch case to determine the required channel to produce the PWM signal on */
		switch(Channel)
		{
		case PWM_CH1A:
			SET_BIT(TCCR1A_R, COM1A0);
			SET_BIT(TCCR1A_R, COM1A1);
			OCR1A_R = Duty * (ICR1_R / PERCENTAGE);
			break;
		case PWM_CH1B:
			SET_BIT(TCCR1A_R, COM1B0);
			SET_BIT(TCCR1A_R, COM1B1);
			OCR1B_R = Duty * (ICR1_R / PERCENTAGE);
			break;
		case (PWM_CH1A | PWM_CH1B):
		{
			SET_BIT(TCCR1A_R, COM1A0);
			SET_BIT(TCCR1A_R, COM1A1);
			SET_BIT(TCCR1A_R, COM1B0);
			SET_BIT(TCCR1A_R, COM1B1);
			OCR1A_R = Duty * (ICR1_R / PERCENTAGE);
			OCR1B_R = Duty * (ICR1_R / PERCENTAGE);
			break;
		}
		default:
			au8_Ret = E_NOK;
			break;
		}
	}else
	{
		au8_Ret = E_NOK;
	}

	return au8_Ret;
}

ERROR_STATUS Pwm_Update(uint8_t Channel, uint8_t Duty, uint32_t Frequency)
{
	uint8_t au8_Ret = E_OK;

	/* An operation to determine the duty cycle according to the used inverting mode */
	Duty = PERCENTAGE - Duty;

	/* An if condition to determine the prescaler and the ICR register according to the required frequency */
	if(Frequency >= 4 && Frequency <= 40000)
	{
		/* An if condition to determine the prescaler and the ICR register according to the required frequency */
		if(Frequency >= 300)
		{
			ICR1_R = F_CPU / (TIMER_PRESCALER_NO * Frequency);
			TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | BIT0;
		}else if(Frequency >= 40)
		{
			ICR1_R = F_CPU / (TIMER_PRESCALER_8 * Frequency);
			TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | BIT1;
		}else if(Frequency >= 4)
		{
			ICR1_R = F_CPU / (TIMER_PRESCALER_64 * Frequency);
			TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | BIT0 | BIT1;
		}
	}else
	{
		au8_Ret = E_NOK;
	}

	if(Duty >= 0 && Duty <= 100)
	{
		/* A switch case to determine the required channel to produce the PWM signal on */
		switch(Channel)
		{
		case PWM_CH1A:
			OCR1A_R = Duty * (ICR1_R / PERCENTAGE);
			break;
		case PWM_CH1B:
			OCR1B_R = Duty * (ICR1_R / PERCENTAGE);
			break;
		case (PWM_CH1A | PWM_CH1B):
		{
			OCR1A_R = Duty * (ICR1_R / PERCENTAGE);
			OCR1B_R = Duty * (ICR1_R / PERCENTAGE);
			break;
		}
		default:
			au8_Ret = E_NOK;
			break;
		}
	}else
	{
		au8_Ret = E_NOK;
	}

	return au8_Ret;
}

ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
	uint8_t au8_Ret = E_OK;

	/* A switch case to determine the required channel to stop the PWM running on it */
	switch(Channel)
	{
	case PWM_CH1A:
		CLEAR_BIT(TCCR1A_R, COM1A0);
		CLEAR_BIT(TCCR1A_R, COM1A1);
		break;
	case PWM_CH1B:
		CLEAR_BIT(TCCR1A_R, COM1B0);
		CLEAR_BIT(TCCR1A_R, COM1B1);
		break;
	case (PWM_CH1A | PWM_CH1B):
	{
		CLEAR_BIT(TCCR1A_R, COM1A0);
		CLEAR_BIT(TCCR1A_R, COM1A1);
		CLEAR_BIT(TCCR1A_R, COM1B0);
		CLEAR_BIT(TCCR1A_R, COM1B1);
		break;
	}
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}
