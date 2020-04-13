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
	TickType_t UserStoryOne_LastWakeTime;
	 /* to avoid tacking the same input from the user */
	const TickType_t UserStoryOne_Frequency = ONE_HANDRED_MS;

	static uint8_t u8_entry_counter=0;
	static uint8_t u8_toggling_counter=0;
	static uint8_t u8_wait_for_release_flag=FLAG_LOW;
	static uint8_t u8_toggling_flag=FLAG_LOW;
	uint8_t au8_button_status;

    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		au8_button_status = pushButtonGetStatus(BTN_0);
		if(au8_button_status == 1)
		{
			u8_wait_for_release_flag = FLAG_HIGH;
			u8_entry_counter++;
		}
		else
		{
			u8_wait_for_release_flag = FLAG_LOW;
			u8_entry_counter = 0;
		}

		if(u8_entry_counter>20 && u8_entry_counter<40)
		{
			//led toggle 400ms
			if(u8_toggling_counter == 4)
			{
				Led_Toggle(LED_0);
				u8_toggling_counter=0;
			}
		}

		else if(u8_entry_counter>40)
		{
			//led toggle 100ms
			Led_Toggle(LED_0);
		}

		else if(u8_entry_counter<20)
		{
			//led off
			Led_Off(LED_0);
		}

		/* Wait for the next cycle */
		vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}




Pushbuttomtask(void)
{
uint8_t	au8_buttomstate;
uint8_t flag=0;
while(1)
{
	if(gu8_flagdone=0)
	{
			if(flag==0)
			{
					au8_buttomstate=pushButtonGetStatus(BTN_0);
					if(au8_buttomstate==PRESSED)
					{
						flag=1;
					}
			}
			else
			{
				au8_buttomstate=pushButtonGetStatus(BTN_0);
				if(au8_buttomstate==RELEASED)
				{
					flag=0;
					gu8_flagdone=1;
			
				}
				else
				{
			
					gu8_counter++;
			
				}
		
			}
	}
	vTaskDelay(20);
}	
}


void ledtask(void)
{
	gu8_flagdone=0;
	uint8_t au8_delay=0;
	while(1)
	{
		Led_Toggle(LED_0);
		/*if(gu8_counter<led_off_period)
		{
			Led_Off(LED_0);
			au8_delay=20;
		}
		else if((gu8_counter>led_off_period)&&(gu8_counter<led_toggel_period400))
		{
			Led_Toggle(LED_0);
			au8_delay=400;
			
		}
		else
		{
			Led_Toggle(LED_0);
			au8_delay=100;
		}*/
		vTaskDelay(100);
	}
	
	
	
}