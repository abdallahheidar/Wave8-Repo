/*
 * Dynamic Design.c
 *
 * Created: 2/24/2020 9:35:01 AM
 * Author : Khaled
 */ 

#include "SERVICE/TMU/TMU.h"
#include "MCAL/DIO/DIO.h"

void Test3 (void);
void Test2 (void);
void Test1 (void);
void consumer1 (void);
void consumer2 (void);
void consumer3 (void);
void consumer4 (void);


extern str_TMU_InitConfig_t init;
int main(void)
{
     DIO_Cfg_s DIO_Init;
	 DIO_Init.dir = OUTPUT;
	 DIO_Init.GPIO = GPIOA;
	 DIO_Init.pins = LOWER_NIBBLE;

	 DIO_init (&DIO_Init);
	 TMU_Init(&init);
	 
	 Test3();
	 while(1)
	 {
	    TMU_Dispatch();
	 }
	 
}

//call creator more(4) that buffer size(3)
void Test1 (void)
{
   TMU_Start(2,1,PERIODIC,consumer1);
	TMU_Start(3,2,PERIODIC,consumer2);
	TMU_Start(4,3,PERIODIC,consumer3);
	TMU_Start(5,4,PERIODIC,consumer4);

}

void Test2 (void)
{
   TMU_Stop(1,consumer1);
}


//call and stop during run time 
void Test3 (void)
{
   static uint8_t au8_Counter = ZERO;
	if (ZERO == au8_Counter)
	{
	   TMU_Start(100,1,PERIODIC,Test3);
	}

	au8_Counter++;
	if (10 == au8_Counter)
	{
	   TMU_Start(2,2,PERIODIC,consumer1);
	}

	if (15 == au8_Counter)
	{
		TMU_Start(3,3,PERIODIC,consumer2);
	}

	if (20 == au8_Counter)
	{
		TMU_Start(6,4,PERIODIC,consumer3);
	}

	if (35 == au8_Counter)
	{
		TMU_Stop(2,consumer1);
	}

	if (40 == au8_Counter)
	{
		TMU_Stop(3,consumer2);
	}

	if (50 == au8_Counter)
	{
		TMU_Start(3,4,PERIODIC,consumer4);
	}

	if (60 == au8_Counter)
	{
		TMU_Stop(4,consumer3);
	}

	if (70 == au8_Counter)
	{
		TMU_Stop(4,consumer4);
	}

	if (100 == au8_Counter)
	{
		TMU_Stop(1,Test3);
	}
}

void consumer1 (void)
{
   DIO_Toggle(GPIOA, BIT0);
}
void consumer2 (void)
{
	DIO_Toggle(GPIOA,BIT1);
}
void consumer3 (void)
{
	DIO_Toggle(GPIOA,BIT2);
}
void consumer4 (void)
{
	DIO_Toggle(GPIOA,BIT3);
}
