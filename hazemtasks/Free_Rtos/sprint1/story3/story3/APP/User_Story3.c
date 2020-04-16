/*
 ============================================================================
 Name        : User_Story3.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


/*********************************includes**********************************/
#include "User_Story3.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TRUE                  1
#define ONE_HANDRED_MS        100
#define PRESSED               1
#define RELEASED              0
#define FLAG_LOW              0
#define FLAG_HIGH             1
#define ENTRIES_FOR_2_SEC     20
#define ENTRIES_FOR_4_SEC     40
#define led_off_period        100
#define  led_toggel_period400    200

#define INIT_TASK_PRIORITY				0

#define BUTTON_TASK_PRIORITY			1
#define BUTTON_TASK_DELAY				1		/*Button Task delay in Milli seconds*/
#define MINIMUM_BUTTON_PRESS			2000	/*Minimum button press time in Milli Seconds*/
#define MAXIMUM_BUTTON_PRESS			4000	/*Maximum button press time in Milli Seconds*/

#define	LED_TOG_TASK_PRIORITY			2
#define LED_TOG_TASK_400ms_DELAY		400		/*Toggling delay in Milli seconds*/
#define LED_TOG_TASK_100ms_DELAY		100		/*Toggling delay in Milli seconds*/
#define LED_TOG_TASK_NO_DELAY			1		/*Toggling delay in Milli seconds*/

#define INITIAL_COUNT					-1

/*Global Counter to be shared between the tasks*/
sint32_t su32_Counter;

/*Global Flag to be shared between the tasks*/
uint8_t gu8_LedToggleTaskReady;


/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/
uint8_t gu8_flagdone;
uint8_t gu8_counter;



/************************************************************************************
* Function Name: UserStoryTHREEInit
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function is responsible for the initialization of all modules
* used in this file
************************************************************************************/
void UserStoryThreeInit(void)
{
	TaskHandle_t xHandle = NULL;
	pushButtonInit(BTN_0);
	Led_Init(LED_0);
	xHandle=xTaskGetCurrentTaskHandle();
	vTaskDelete(xHandle);
}



/************************************************************************************
* Function Name: UserStoryTwo
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
************************************************************************************/
void UserStoryThree(void)
{
	uint8_t u8_PushButtonStatus = Released;
	while(1)
	{
	pushButtonGetStatus(BTN_0,&u8_PushButtonStatus);
	if(u8_PushButtonStatus)
	Led_Off(LED_0);
	else
	Led_On(LED_0);
	
	vTaskDelay(50);
	}
}




void Pushbuttomtask(void)
{
/*Variable to store the push button status in*/
	uint8_t u8_PushButtonStatus = Released;

	while(1)
	{
		/*Get the push button status*/
		pushButtonGetStatus(BTN_0,&u8_PushButtonStatus);

		/*Check the push button status if it is pressed increment the counter by 1
		and since this task's periodicity is 1 ms so each counter incrementation represents
		1 Milli second press on the button*/
		if (u8_PushButtonStatus == Pressed )
		{
			su32_Counter++;
		}

		/*If the button is pressed again reset the counter to count the pressing time again*/
		if (u8_PushButtonStatus == Pressed && gu8_LedToggleTaskReady)
		{
			su32_Counter = INITIAL_COUNT;
			gu8_LedToggleTaskReady = FALSE;
		}

		/*if the button is released after being pressed set the "ready flag" for the led toggle task*/
		if ((u8_PushButtonStatus) && (su32_Counter > INITIAL_COUNT))
		{
			gu8_LedToggleTaskReady = TRUE;
		}

		/*delay for 1 Milli second*/
		vTaskDelay(BUTTON_TASK_DELAY);
	}
}	




void ledtask(void)
{
	
uint16_t u16_LedTaskDelay = LED_TOG_TASK_NO_DELAY;
while(1)
{
	/*check the "ready flag"*/
	if (gu8_LedToggleTaskReady)
	{
		/*if the button is pressed less than 2000 Milli seconds switch the LED off*/
		if (su32_Counter<=MINIMUM_BUTTON_PRESS)
		{
			Led_Off(LED_0);
		}

		/*if the button is pressed more than 2000 and less than 4000 Milli seconds toggle the led with 400ms periodicity*/
		else if (su32_Counter>MINIMUM_BUTTON_PRESS && su32_Counter<=MAXIMUM_BUTTON_PRESS)
		{
			Led_Toggle(LED_0);
			u16_LedTaskDelay = LED_TOG_TASK_400ms_DELAY;
		}

		/*if the button is pressed more than 4000 Milli seconds toggle the led with 100ms periodicity*/
		else if (su32_Counter>MAXIMUM_BUTTON_PRESS)
		{
			Led_Toggle(LED_0);
			u16_LedTaskDelay = LED_TOG_TASK_100ms_DELAY;
		}

	}

	vTaskDelay(u16_LedTaskDelay);
}

	
	
	
}