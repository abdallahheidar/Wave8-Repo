#include "PWM.h"
//#include "Timer.h"
#include "DIO.h"
# define F_CPU 16000000UL
/*********************************/
/*            MACROS             */
/*********************************/
#define T0_PWM_GPIO		GPIOB
#define T0_PWM_BIT		BIT3

#define T1A_PWM_GPIO	GPIOD
#define T1A_PWM_BIT		BIT4

#define T1B_PWM_GPIO	GPIOD
#define T1B_PWM_BIT		BIT5

#define T2_PWM_GPIO		GPIOD
#define T2_PWM_BIT		BIT7


/******************************/
/*    PWM Structure Configuration   */
/******************************/
DIO_Cfg_s DIO_Cfg_S_PWM0;
DIO_Cfg_s DIO_Cfg_S_PWM1_A;
DIO_Cfg_s DIO_Cfg_S_PWM1_B;
DIO_Cfg_s DIO_Cfg_S_PWM2;

/*********************************/
/*    FUNCTIONS Implementation      */
/*********************************/

/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                           */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/	
uint8_t Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	uint8_t	Er_Status=0;
	uint8_t PWM_CH = Pwm_Cfg->Channel;
	
	DIO_Cfg_S_PWM0.GPIO = T0_PWM_GPIO;
	DIO_Cfg_S_PWM0.dir  = OUTPUT;
	DIO_Cfg_S_PWM0.pins = T0_PWM_BIT;
	
	DIO_Cfg_S_PWM1_A.GPIO = T1A_PWM_GPIO;
	DIO_Cfg_S_PWM1_A.dir  = OUTPUT;
	DIO_Cfg_S_PWM1_A.pins = T1A_PWM_BIT;
	
	DIO_Cfg_S_PWM1_B.GPIO = T1B_PWM_GPIO;
	DIO_Cfg_S_PWM1_B.dir  = OUTPUT;
	DIO_Cfg_S_PWM1_B.pins = T1B_PWM_BIT;
	
	DIO_Cfg_S_PWM2.GPIO = T2_PWM_GPIO;
	DIO_Cfg_S_PWM2.dir  = OUTPUT;
	DIO_Cfg_S_PWM2.pins = T2_PWM_BIT;
	
	
	if (Pwm_Cfg == NULL)
	{
		Er_Status = E_NOK;
	} 
	else
	{	
	switch (PWM_CH)
	{
		case PWM_CH0:
			//OC0 pin for PWm on timer0
			DIO_init(&DIO_Cfg_S_PWM0);
			Er_Status = E_OK;
			break;
		case PWM_CH1A:
			//OC1A pin for PWm on timer1
			DIO_init(&DIO_Cfg_S_PWM1_A);
			TCCR1|= T1_FAST_PWM_MODE_ICR1_TOP;
			TCCR1|=	T1_OC1A_CLEAR;
			TCCR1|= PWM_PRESCALER_1024;
			TCNT1|=InitialValue;
			OCR1A|=InitialValue;
			OCR1B|=InitialValue;
			ICR1 |=InitialValue;
			TIMSK|=T1_POLLING;
			Er_Status = E_OK;
			break;
		case PWM_CH1B:
			//OC1B pin for PWm on timer1
			DIO_init(&DIO_Cfg_S_PWM1_B);
			TCCR1|= T1_FAST_PWM_MODE_ICR1_TOP;
			TCCR1|= T1_OC1B_CLEAR;
			TCCR1|= PWM_PRESCALER_1024;
			TCNT1|=InitialValue;
			OCR1A|=InitialValue;
			OCR1B|=InitialValue;
			ICR1 |=InitialValue;
			TIMSK|=T1_POLLING;
			Er_Status = E_OK;
			break;
		case PWM_CH2:
			//OC2 pin for PWm on timer2
			DIO_init(&DIO_Cfg_S_PWM2);
			Er_Status = E_OK;
			break;	
			
// 		case PWM_CH1A_CH1B:
// 			DIO_init(&DIO_Cfg_S_PWM1_A);
// 			DIO_init(&DIO_Cfg_S_PWM1_B);
// 			TCCR1|= T1_FAST_PWM_MODE_ICR1_TOP;
// 			TCCR1|= T1_OC1B_CLEAR;
// 			TCCR1|= PWM_PRESCALER_1024;
// 			TCNT1|=InitialValue;
// 			OCR1A|=InitialValue;
// 			OCR1B|=InitialValue;
// 			ICR1 |=InitialValue;
// 			TIMSK|=T1_POLLING;
// 			Er_Status = E_OK;
		default:
			Er_Status = E_NOK;
	}
	}
	return Er_Status;
}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*********************************************************************************/
uint8_t Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
	uint8_t	Er_Status = 0;
	uint8_t value = 0;
	switch (Channel)
	{
		case PWM_CH0:

			Er_Status = E_OK;
			break;
		case PWM_CH1A:
			//calculate the value of the period of PWM signal
			value=(uint8_t)(F_CPU/((2*1024*Frequncy)))-1;
			ICR1 = value;
			//ICR1 = 125;

			//set duty cycle of the first generated signal
			OCR1A=(uint8_t)value*((float)Duty/100.0);
			OCR1B=(uint8_t)value*((float)Duty/100.0);
			Er_Status = E_OK;
			break;
		case PWM_CH1B:
			//calculate the value of the period of PWM signal
			value=(uint8_t)(F_CPU/((2*1024*Frequncy)))-1;
			ICR1 = value;
			//ICR1 = 125;
			//set duty cycle of the second generated signal
			OCR1A=(uint8_t)value*((float)Duty/100.0);
			OCR1B=(uint8_t)value*((float)Duty/100.0);
			Er_Status = E_OK;
			break;
		case PWM_CH2:
			//OC2 pin for PWm on timer2
			DIO_init(&DIO_Cfg_S_PWM2);
			Er_Status = E_OK;
			break;
			
		case PWM_CH1A_CH1B:
			value=(uint8_t)(F_CPU/((2*1024*Frequncy)))-1;
			//OC2 pin for PWm on timer2
			ICR1 = value;
			//ICR1 = 125;

			//set duty cycle of the first generated signal
			OCR1A=(uint8_t)value*((float)Duty/100.0);
			OCR1B=(uint8_t)value*((float)Duty/100.0);
			//DIO_init(&DIO_Cfg_S_PWM2);
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;
	}
	return Er_Status;
}
/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
uint8_t Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy){
	uint8_t	Er_Status = 0;
	uint8_t value = 0;
	switch (Channel)
	{
		case PWM_CH0:
			Er_Status = E_OK;
			break;
		case PWM_CH1A:
			//calculate the value of the period of PWM signal
			value=(uint8_t)(F_CPU/((2*1024*Frequncy)))-1;
			ICR1 = value;
			//set duty cycle of the first generated signal
			OCR1A=(uint8_t)value*((float)Duty/100.0);
			Er_Status = E_OK;
			break;
		case PWM_CH1B:
			//calculate the value of the period of PWM signal
			value=(uint8_t)(F_CPU/((2*1024*Frequncy)))-1;
			ICR1 = value;
			//set duty cycle of the second generated signal
			OCR1B=(uint8_t)value*((float)Duty/100.0);
			Er_Status = E_OK;
			break;
		case PWM_CH2:
			//OC2 pin for PWm on timer2
			DIO_init(&DIO_Cfg_S_PWM2);
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;
	}
	return Er_Status;
}

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
uint8_t Pwm_Stop(uint8_t Channel){
	uint8_t	Er_Status = 0;
	switch (Channel)
	{
		case PWM_CH0:
			Er_Status = E_OK;
			//Clr_Bit(TCCR0,BIT0);
			TCCR0 &=~(1<<BIT0);
			//Clr_Bit(TCCR0,BIT1);
			TCCR0 &=~(1<<BIT1);
			//Clr_Bit(TCCR0,BIT2);
			TCCR0 &=~(1<<BIT2);
			break;
		case PWM_CH1A:
			OCR1A =0;
			Er_Status = E_OK;
			break;
		case PWM_CH1B:
			OCR1B =0;
			Er_Status = E_OK;
			break;
		case PWM_CH2:
			//Clr_Bit(TCCR2,BIT0);
			TCCR2 &=~(1<<BIT0);
			//Clr_Bit(TCCR2,BIT1);
			TCCR2 &=~(1<<BIT1);
			//Clr_Bit(TCCR2,BIT2);
			TCCR2 &=~(1<<BIT2);
			Er_Status = E_OK;
			break;
		default:
			Er_Status = E_NOK;
	}
	return Er_Status;
}