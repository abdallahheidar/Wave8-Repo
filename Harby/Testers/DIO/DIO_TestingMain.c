/*
 * main.c
 *
 *  Created on: Mar 26, 2020
 *      Author: Youssef Harby
 */


#include <stdio.h>
#include "MCAL/DIO.h"


/*- PREPROCESSOR MACROS ------------------------------------*/

#define SKIP_LINE		printf("\n")


/*- STATIC GLOBAL VARIABLES --------------------------------*/

static uint8_t gu8_ReadFunctionTarget;


/*- APIs PROTOTYPES ----------------------------------------*/

void DIO_Init_Tester(uint8_t GPIO, uint8_t Pins, uint8_t Direction);
void DIO_Write_Tester(uint8_t GPIO, uint8_t pins, uint8_t value);
void DIO_Read_Tester(uint8_t GPIO, uint8_t pins, uint8_t* DataAddress);
void DIO_Toggle_Tester(uint8_t GPIO, uint8_t pins);


/*- MAIN FUNCTION ------------------------------------------*/

int main(void)
{
//	REMOVE "//" FOR DIO_INIT FUNCTION TEST SCENARIOS

	//DIO_INIT_1
	DIO_Init_Tester(GPIOA, BIT0 | BIT3, OUTPUT);
	SKIP_LINE;

	//DIO_INIT_2
	DIO_Init_Tester(GPIOB, BIT0 | BIT3, 0x65);
	SKIP_LINE;

	//DIO_INIT_3
	DIO_Init_Tester(5, BIT0 | BIT3, INPUT);
	SKIP_LINE;

	//DIO_INIT_4
	DIO_Init_Tester(5, BIT0 | BIT3, 0x65);
	SKIP_LINE;

	//DIO_INIT_5
	DIO_Init_Tester(GPIOC, BIT4 | BIT2, INPUT);
	DIO_Init_Tester(GPIOC, BIT7 | BIT6, OUTPUT);
	SKIP_LINE;

		SKIP_LINE;
		SKIP_LINE;

//	REMOVE "//" FOR DIO_WRITE FUNCTION TEST SCENARIOS

	//DIO_WRITE_1
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Write_Tester(GPIOC, BIT0 | BIT3, HIGH);
	SKIP_LINE;

	//DIO_WRITE_2
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Write_Tester(GPIOC, BIT0 | BIT3, 0x54);
	SKIP_LINE;

	//DIO_WRITE_3
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Write_Tester(6, BIT0 | BIT3, HIGH);
	SKIP_LINE;

	//DIO_WRITE_4
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Write_Tester(6, BIT0 | BIT3, 0x54);
	SKIP_LINE;

	//DIO_WRITE_5
	DIO_DeInit(GPIOC);
	DIO_Write_Tester(GPIOC, BIT0 | BIT3, HIGH);
	SKIP_LINE;

		SKIP_LINE;
		SKIP_LINE;

//	REMOVE "//" FOR DIO_READ FUNCTION TEST SCENARIOS

	//DIO_READ_1
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Read_Tester(GPIOC, BIT0 | BIT3, &gu8_ReadFunctionTarget);
	SKIP_LINE;

	//DIO_READ_2
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Read_Tester(6, BIT0 | BIT3, &gu8_ReadFunctionTarget);
	SKIP_LINE;

	//DIO_READ_3
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Read_Tester(GPIOC, BIT0 | BIT3, NULL);
	SKIP_LINE;

	//DIO_READ_4
	DIO_DeInit(GPIOC);
	DIO_Read_Tester(GPIOC, BIT0 | BIT3, &gu8_ReadFunctionTarget);
	SKIP_LINE;

		SKIP_LINE;
		SKIP_LINE;

//	REMOVE "//" FOR DIO_TOGGLE FUNCTION TEST SCENARIOS

	//DIO_TOGGLE_1
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Toggle_Tester(GPIOC, BIT0 | BIT3);
	SKIP_LINE;

	//DIO_TOGGLE_2
	DIO_DeInit(GPIOC);
	DIO_Init_Tester(GPIOC, BIT0 | BIT3, OUTPUT);
	DIO_Toggle_Tester(6, BIT0 | BIT3);
	SKIP_LINE;

	//DIO_TOGGLE_3
	DIO_DeInit(GPIOC);
	DIO_Toggle_Tester(GPIOC, BIT0 | BIT3);
	SKIP_LINE;

	return 0;
}


/*- APIs IMPLEMENTATION ------------------------------------*/

void DIO_Init_Tester(uint8_t GPIO, uint8_t Pins, uint8_t Direction)
{
	DIO_Cfg_s astr_DioTesterCfg = {GPIO, Pins, Direction};
	sint8_t as8_ErrorValue = DIO_Init(&astr_DioTesterCfg);

	if(as8_ErrorValue == DIO_E_INVALID_PORT)
	{
		printf("DIO Init Error Detected - Invalid Port\n");
	}else if(as8_ErrorValue == DIO_E_INVALID_DIRECTION)
	{
		printf("DIO Init Error Detected - Invalid Direction\n");
	}else if(as8_ErrorValue == DIO_E_ALREADY_INIT)
	{
		printf("DIO Init Error Detected - Port Already Initialized\n");
	}else if(as8_ErrorValue == DIO_E_OK)
	{
		printf("DIO Init Error-Free\n");
	}
}


void DIO_Write_Tester(uint8_t GPIO, uint8_t pins, uint8_t value)
{
	sint8_t as8_ErrorValue = DIO_Write(GPIO, pins, value);

	if(as8_ErrorValue == DIO_E_INVALID_PORT)
	{
		printf("DIO Write Error Detected - Invalid Port\n");
	}else if(as8_ErrorValue == DIO_E_INVALID_VALUE)
	{
		printf("DIO Write Error Detected - Invalid Value\n");
	}else if(as8_ErrorValue == DIO_E_NOT_INIT)
	{
		printf("DIO Write Error Detected - Port Not Initialized\n");
	}else if(as8_ErrorValue == DIO_E_OK)
	{
		printf("DIO Write Error-Free\n");
	}
}


void DIO_Read_Tester(uint8_t GPIO, uint8_t pins, uint8_t* DataAddress)
{
	sint8_t as8_ErrorValue = DIO_Read(GPIO, pins, DataAddress);

	if(as8_ErrorValue == DIO_E_INVALID_PORT)
	{
		printf("DIO Read Error Detected - Invalid Port\n");
	}else if(as8_ErrorValue == DIO_E_NULL_POINTER)
	{
		printf("DIO Read Error Detected - Null Pointer\n");
	}else if(as8_ErrorValue == DIO_E_NOT_INIT)
	{
		printf("DIO Read Error Detected - Port Not Initialized\n");
	}else if(as8_ErrorValue == DIO_E_OK)
	{
		printf("DIO Read Error-Free\n");
	}
}

void DIO_Toggle_Tester(uint8_t GPIO, uint8_t pins)
{
	sint8_t as8_ErrorValue = DIO_Toggle(GPIO, pins);

	if(as8_ErrorValue == DIO_E_INVALID_PORT)
	{
		printf("DIO Toggle Error Detected - Invalid Port\n");
	}else if(as8_ErrorValue == DIO_E_NOT_INIT)
	{
		printf("DIO Toggle Error Detected - Port Not Initialized\n");
	}else if(as8_ErrorValue == DIO_E_OK)
	{
		printf("DIO Toggle Error-Free\n");
	}
}
