/*
 * DynamicDesign_Challenge.c
 *
 * Created: 2020-02-24 11:20:22 AM
 * Author : EbrahimOseif
 */ 

#include "tmu.h"
#include "DIO.h"
#include "sleep.h"


void led0_toggle(void){
	
	/*PORTA_DATA ^= HIGH;
	//_delay_ms(1000);*/
	
	DIO_Toggle(GPIOB, BIT5);
}
void led1_toggle(void){
	
	/*PORTC_DATA ^= HIGH;
	//_delay_ms(1000);
	*/
		DIO_Toggle(GPIOB, BIT6);
		
		/*	related to test case two
		TMU_Stop(led0_toggle);
		*/

}
void led2_toggle(void){
	
	/*PORTD_DATA ^= HIGH;
	//_delay_ms(1000);
	*/
		DIO_Toggle(GPIOB, BIT7);

}


int main(void)
{	
	
	/* normal way */
	
	DIO_Cfg_s Leds ={
		GPIOB,
		BIT5 |BIT6 |BIT7,
		OUTPUT
	};
	
	DIO_init(&Leds);
	
	TMU_Init();
	
	/* 	TMU_Start(funcPtr, delay_ms , periodicity) */
	TMU_Start(led0_toggle, 1000, PERIODIC);
	
	
	/*TMU_Start(led1_toggle, 500, ONE_SHOT);
	TMU_Start(led2_toggle, 2000, PERIODIC);*/
	
	Sleep_SetMode(IDLE_MODE);

	/* enable global interrupts */
	sei();

	
	while (1)
	{
		//fun();
		
		TMU_Dispatcher();
		
		Sleep_Enable();
	}
	
	
	/* test case 1: adding to full buffer 
		
	DIO_Cfg_s Leds ={
		GPIOB,
		BIT5 |BIT6 |BIT7,
		OUTPUT
	};
	
	DIO_init(&Leds);
	
	TMU_Init();
	
	TMU_Start(led0_toggle, 1000, PERIODIC);
	TMU_Start(led1_toggle, 500, ONE_SHOT);
	
	PORTC_DIR = 0xff;
	PORTC_DATA =  TMU_Start(led2_toggle, 2000, PERIODIC)+ 6 ;

	sei();

	
	while (1)
	{
		//fun();
		TMU_Dispatcher();
		
	}*/
	
	
	/* test case 2 stopping while empty buffer 
	
	TMU_Init();
	PORTC_DIR = 0xff;
	/ * it will print 1 as return is -4 * /
	PORTC_DATA = TMU_Stop(led2_toggle) + 5;
	
	*/
	
	/*test case 3 
	
	DIO_Cfg_s Leds ={
		GPIOB,
		BIT5 |BIT6 |BIT7,
		OUTPUT
	};
	
	DIO_init(&Leds);
	
	TMU_Init();
	
	TMU_Start(led0_toggle, 1000, PERIODIC);
	TMU_Start(led1_toggle, 500, ONE_SHOT);
	TMU_Start(led2_toggle, 2000, PERIODIC);

	sei();

    
    while (1) 
    {
				//fun();
		   TMU_Dispatcher();
    }*/
	
	/*	test case 4 
	
	DIO_Cfg_s Leds ={
		GPIOB,
		BIT5 |BIT6 |BIT7,
		OUTPUT
	};
	
	DIO_init(&Leds);
	
	TMU_Init();
	
	TMU_Start(led0_toggle, 1000, PERIODIC);
	TMU_Start(led1_toggle, 500, ONE_SHOT);
	TMU_Start(led2_toggle, 2000, PERIODIC);

	sei();

    / * Replace with your application code * /
    while (1) 
    {
				//fun();
		   TMU_Dispatcher();
    }*/
	
	/*	test case 5 
	
	DIO_Cfg_s Leds ={
		GPIOB,
		BIT5 |BIT6 |BIT7,
		OUTPUT
	};
	
	DIO_init(&Leds);
	
	TMU_Init();
	
	TMU_Start(led0_toggle, 1000, PERIODIC);
	TMU_Start(led1_toggle, 500, ONE_SHOT);
	TMU_Start(led2_toggle, 2000, PERIODIC);

	sei();

    / * Replace with your application code * /
    while (1) 
    {
				//fun();
		   TMU_Dispatcher();
		   PORTC_DIR = 0xff;
		   PORTC_DATA = TMU_Stop(NULL) + 4;
    }*/
	
	
	
	      /* testing timers
	   struct Timer_cfg_s st_Timer_cfg={
       	TIMER_CH0,
       	TIMER_MODE,
       	TIMER_INTERRUPT_MODE,
       	TIMER_PRESCALER_1024
       };
	Timer_Init(&st_Timer_cfg);
	Timer_Start(0,100);
	*/
	/*PORTA_DIR = 0xff;
	PORTC_DIR = 0xff;
	PORTD_DIR = 0xff;*/
	
	
	
}




