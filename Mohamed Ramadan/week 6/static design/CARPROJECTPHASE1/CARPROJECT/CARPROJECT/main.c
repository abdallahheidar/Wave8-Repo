/*
 * CARPROJECT.c
 *
 * Created: 2/17/2020 10:14:40 AM
 * Author : Mohamed Ramadan
 */ 
/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Timer.h"
#include "DIO.h"
#include "util/delay.h"
#include "PWM.h"
#include "motor.h"
#include "ICU.h"
#include "Us.h"
#include "car_sm.h"
#include "Steering.h"


//Timer structures
Timer_Cfg_S Cfg_S_T2;
Timer_Cfg_S Cfg_S_T0;
Timer_Cfg_S Cfg_S_T1;

//DIO structures
DIO_Cfg_s DIO_Cfg_B_Test;
DIO_Cfg_s DIO_Cfg_L_Test;
DIO_Cfg_s DIO_Cfg_L2_Test;


//PWM Structures
Pwm_Cfg_s  Pwm_Cfg_PWM_1A;
Pwm_Cfg_s  Pwm_Cfg_PWM_1B;

//ICU structures
Icu_cfg_s Icu_cfg_INT2;

//Timer_Init(&Timer_Cfg_S);
int main(void)
{
	
	
// 	uint16_t Distance;
// 
// 	Us_Init();
// 	while(1)
// 	{
// 		Us_Trigger();
// 		Us_GetDistance(&Distance);
// 		TCNT0=Distance;
// 	}
	
	//Pwm_Cfg_s instans={PWM_CH1A,PWM_PRESCALER_1024};
	//Pwm_Init(&instans);
	//instans.Channel=PWM_CH1B;
	//Pwm_Init(&instans);
// 	DIO_Cfg_S_PWM1_A.GPIO = T1A_PWM_GPIO;
// 	DIO_Cfg_S_PWM1_A.dir  = OUTPUT;
// 	DIO_Cfg_S_PWM1_A.pins = T1A_PWM_BIT;
// 	DIO_init(&DIO_Cfg_S_PWM1_A);
// 	TCCR1|= T1_FAST_PWM_MODE_ICR1_TOP;
// 	TCCR1|=	T1_OC1A_CLEAR;
// 	TCCR1|= PWM_PRESCALER_1024;
// 	TCNT1|=InitialValue;
// 	OCR1A|=InitialValue;
// 	OCR1B|=InitialValue;
// 	ICR1 |=InitialValue;
// 	TIMSK|=T1_POLLING;
// 	Pwm_Start(PWM_CH1A,20,250);
	//Pwm_Start(PWM_CH1B,30,T1_PHASE_CORRECT_FREQUENCY_50HZ);

/*	while(1)
	{

	}*/
/*	 uint8_t  *Check_B = NULL;
	 uint32_t *ICU_Catch_Value = NULL;
	 uint16_t *Get_Distance = NULL;
	 uint16_t US_Distance = 0;
	 
	 */

	// uint8_t ch_value = 0;
	uint32_t Value_Timer_Catched = 0;
	volatile uint16_t Distance_Value_Catched = 0;
/*	
	//Initialize Dio structure 
	DIO_Cfg_B_Test.GPIO = GPIOC;
	DIO_Cfg_B_Test.dir  = INPUT;
	DIO_Cfg_B_Test.pins = BIT4;
	
	DIO_Cfg_L_Test.GPIO = GPIOA;
	DIO_Cfg_L_Test.dir  = OUTPUT;
	DIO_Cfg_L_Test.pins = BIT0;
	
	DIO_Cfg_L2_Test.GPIO = GPIOA;
	DIO_Cfg_L2_Test.dir  = OUTPUT;
	DIO_Cfg_L2_Test.pins = BIT1;
	
	//Initialize Timer structure
	Cfg_S_T2.Timer_CH_NO =TIMER_CH2;
	Cfg_S_T2.Timer_Mode  =TIMER_MODE;
	Cfg_S_T2.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	Cfg_S_T2.Timer_Prescaler =  T2_PRESCALER_256;
	
	Cfg_S_T0.Timer_CH_NO =TIMER_CH0;
	Cfg_S_T0.Timer_Mode  =TIMER_MODE;
	Cfg_S_T0.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	Cfg_S_T0.Timer_Prescaler =  T0_PRESCALER_256;
	
	Cfg_S_T1.Timer_CH_NO =TIMER_CH1;
	Cfg_S_T1.Timer_Mode  =TIMER_MODE;
	Cfg_S_T1.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	Cfg_S_T1.Timer_Prescaler =  T1_PRESCALER_1024;
	
	//initialize PWM structure
	Pwm_Cfg_PWM_1A.Channel   = PWM_CH1A;
	Pwm_Cfg_PWM_1A.Prescaler = T1_PRESCALER_1024;
	
	Pwm_Cfg_PWM_1B.Channel   = PWM_CH1B;
	Pwm_Cfg_PWM_1B.Prescaler = T1_PRESCALER_1024;
	
	//Initialize  ICU structure
	Icu_cfg_INT2.ICU_Ch_No = ICU_CH2;
	Icu_cfg_INT2.ICU_Ch_Timer = ICU_TIMER_CH2;
	
	//PORTB_DIR = 0xFF;
	//PORTC_DIR = 0x00;
	
	//DIO_init(&DIO_Cfg_B_Test);
	  //DIO_init(&DIO_Cfg_L_Test);
	  //DIO_init(&DIO_Cfg_L2_Test);
	

	//ICU Initialization structure
	  //Icu_Init(&Icu_cfg_INT2);
	//Initialize PWM
    Pwm_Init(&Pwm_Cfg_PWM_1A);
	Pwm_Init(&Pwm_Cfg_PWM_1B);
	
	//Initialize Motor
	Motor_Init(MOTOR_1);
	Motor_Init(MOTOR_2);
	
	Motor_Start(MOTOR_1,30);
	Motor_Start(MOTOR_2,30);
	//Motor Direction
	
	
	//Ultrasonic Initialization
	Us_Init();
	
	
	
	//Us_Trigger();
	//Icu_ReadTime(ICU_TIMER_CH2,ICU_FALE_TO_RISE,ICU_Catch_Value);
	while(1){
		//Icu_ReadTime(ICU_TIMER_CH2,ICU_RISE_TO_FALL,ICU_Catch_Value);
		Us_Trigger();
		Us_GetDistance(ICU_Catch_Value);
		US_Distance = *ICU_Catch_Value;
		//US_Distance = 30;
		//Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		//Motor_Direction(MOTOR_2,MOTOR_FORWARD);
		PORTC_DIR=US_Distance;
		if (US_Distance<10)
		{
			
			Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
			Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
			//DIO_Write(PORTA_DATA,PIN0,HIGH);
		} 
		else if(10<US_Distance<40)
		{
			Motor_Direction(MOTOR_1,MOTOR_FORWARD);
			Motor_Direction(MOTOR_2,MOTOR_FORWARD);
			
			//Motor_Start(MOTOR_1);
			//MOTOR_BACKWARD(MOTOR_2);
			//DIO_Write(PORTA_DATA,PIN1,HIGH);
		}
		else{
			
			Motor_Direction(MOTOR_1,MOTOR_STOP);
			Motor_Direction(MOTOR_2,MOTOR_STOP);
		}
		
//TCNT2 =*ICU_Catch_Value;

	}*/


/*********************************** Car Application *****************************************/

Car_SM_Init();

while(1)
{
	Car_SM_Update();
}

	return 0;
}

