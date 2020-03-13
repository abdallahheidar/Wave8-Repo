/*
 * Car_App_Static_Arch.c
 *
 * Created: 2/15/2020 4:41:06 PM
 * Author : Ahmed Amin
 */ 
#define F_CPU 16000000UL
#include "util\delay.h"
#include "DIO.h"
#include "Timer.h"
#include "PWM.h"
#include "motor.h"
#include "Steering.h"
#include "car_sm.h"




int main(void)
{
	uint8 eror=0;
/*pwm test 
Pwm_Cfg_s pwmmm;
pwmmm.Channel=PWM_CH0;
pwmmm.Prescaler=TIMER_PRESCALER_256;
DIO_Cfg_s dioo;
dioo.GPIO=GPIOD;
dioo.dir=OUTPUT;
dioo.pins=BIT4|BIT5;
eror=DIO_init (&dioo);
eror=Pwm_Init(&pwmmm);
eror=Pwm_Start(PWM_CH0,50,1);
_delay_ms(3000);
eror=Pwm_Stop(PWM_CH0);*/


/* motor test
eror= Motor_Init(MOTOR_1);
eror= Motor_Init(MOTOR_2);
eror=Motor_Direction(MOTOR_1,MOTOR_FORWARD);
eror=Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
eror=Motor_Start(MOTOR_1,50);
eror=Motor_Start(MOTOR_2,50);
_delay_ms(5000);
eror=Motor_Stop(MOTOR_1);
eror=Motor_Stop(MOTOR_2);*/


/* steering test
eror=Steering_Init();
eror=Steering_SteerCar(CAR_FORWARD,50);
_delay_ms(3000);
eror=Steering_SteerCar(CAR_BACKWARD,70);
_delay_ms(3000);
eror=Steering_SteerCar(CAR_RIGHT,30);
_delay_ms(3000);
eror=Steering_SteerCar(CAR_LEFT,80);*/



eror=Car_SM_Init();

    while (1) 
    {
		eror=Car_SM_Update();
		_delay_ms(100);
    }
}

