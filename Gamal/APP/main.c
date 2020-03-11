/*
 ============================================================================
 Name        : main.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


/*********************************includes**********************************/
#include "../MCAL/DIO.h"
#include "../Service/SOS.h"
#include "../MCAL/CPU.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define ID_0 0
#define ID_1 1
#define ID_2 2
#define ID_3 3
#define TRUE 1
#define FALSE 0
#define TEN_MS 10
#define TWENTY_MS 20
/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/

void Task0(void)
{
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT0,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	DIO_Toggle(GPIOA, BIT0);
}

void Task1(void)
{
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT1,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	DIO_Toggle (GPIOA, BIT1);
}

void Task2(void)
{
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT2,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	DIO_Toggle (GPIOA, BIT2);
}

void Task3(void)
{
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT3,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	DIO_Toggle (GPIOA, BIT3);
}

void Task4(void)
{
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT4,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	DIO_Toggle (GPIOA, BIT4);
}


void Idle_Task(void)
{
	 CPU_Sleep(IDLE_MODE);
}



int main(void)
{
	sei();
	SOS_InitRunable(&SOS_Configration);
	SOS_SetIdleTask(Idle_Task);
	Task_Start(Task0,ID_0,PERIODIC,TEN_MS);
	Task_Start(Task1,ID_1,PERIODIC,TWENTY_MS);
	/*SOS_DeInit();*/
	Task_Start(Task2,ID_2,ONE_SHOOT,TEN_MS);
	Task_Stop(ID_1);
	Task_Start(Task3,ID_3,PERIODIC,TEN_MS);
	while(TRUE)
	{
		SOS_Runable();
	}

	return FALSE;
}
