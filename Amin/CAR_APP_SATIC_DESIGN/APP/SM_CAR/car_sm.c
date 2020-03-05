#include "car_sm.h"
#include "Steering.h"
#define F_CPU 16000000UL
#include "util\delay.h"
volatile static uint16 u16_distance = 0;
volatile static	uint8 flag=0;
/*Describtion: this function initialize the ultrasonic and steering*/
ERROR_STATUS Car_SM_Init(void){
uint8 eror =0;
eror=Steering_Init();
eror=Us_Init();
	return eror;
	}
	
	
/*Describtion: this function update the diurection and speed of motor*/
ERROR_STATUS Car_SM_Update(void){
	uint8 eror=0;
eror=Us_GetDistance(&u16_distance);
if(u16_distance>=30){
	flag=1;
	}
	else if(u16_distance>10&&u16_distance<30){
		flag=2;
	}
	else if(u16_distance<=10){
		flag=3;
	}
	switch(flag){
		case 1:
		eror=Steering_SteerCar(CAR_FORWARD,30);  
		break;
		case 2:
		eror=Steering_SteerCar(CAR_RIGHT,30);  
		_delay_ms(100);
		break;
		case 3:
		eror=Steering_SteerCar(CAR_BACKWARD,50); 
		_delay_ms(100);
	}
	flag=0;
	return eror;
	}