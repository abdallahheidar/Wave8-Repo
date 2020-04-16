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
#define BUTTON_TASK_DELAY				30		/*Button Task delay in Milli seconds*/
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
	Led_Init(LED_1);
	Led_Init(LED_2);
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
	uint8_t u8_PushButtonStatus = 0;
    uint8_t counter=0;
	uint8_t flag=Released;
	while(1)
	{
		if(gu8_LedToggleTaskReady==0)
		{
		   PORTA_DATA=0x10;	
			/*Get the push button status*/
			 if(flag==RELEASED)
			{
				
					pushButtonGetStatus(BTN_0,&u8_PushButtonStatus);
					PORTA_DATA=u8_PushButtonStatus;
					if(u8_PushButtonStatus==RELEASED)
					{
						counter++;
					}
					if(counter==3)
					{
						flag=PRESSED;
					}
			}
			if(flag==PRESSED)
			{
					
				counter=0;
				pushButtonGetStatus(BTN_0,&u8_PushButtonStatus);
				//PORTA_DATA=u8_PushButtonStatus;
				if(u8_PushButtonStatus==PRESSED)
				{
					
					flag=RELEASED;
					gu8_LedToggleTaskReady=1;
				}
			
			}
		}
		else
		{
			PORTA_DATA=0x40;
		}
		/*delay for 1 Milli second*/
		vTaskDelay(BUTTON_TASK_DELAY);
	}
}	




void ledtask(void)
{
	
uint8_t  au8_counter=0;
while(1)
{
	
	if (gu8_LedToggleTaskReady)
	{
	 if(au8_counter<=15)
	 {	
		Led_On(LED_1);
		Led_Off(LED_0);
		Led_Off(LED_2);
		au8_counter++;
	 }
	 else if((au8_counter<=20)&&(au8_counter>15))
	 {
		Led_Toggle(LED_1);
		Led_Off(LED_0);
		Led_Off(LED_2);
		au8_counter++;  
	 }
	 else if((au8_counter<=60)&&(au8_counter>20))
	 {
		 Led_Off(LED_1);
		 Led_Off(LED_0);
		 Led_On(LED_2);
		 au8_counter++; 
	 }
	 else if((au8_counter<=70)&&(au8_counter>60))
	 {
		 Led_Off(LED_1);
		 Led_Off(LED_0);
		 Led_Toggle(LED_2);
		 au8_counter++;
		 
	 }
	 else
	 {
		 au8_counter=0;
		 gu8_LedToggleTaskReady=0;
	 }
    }
	else
	{
		Led_Off(LED_1);
		Led_On(LED_0);
		Led_Off(LED_2);
	}
	vTaskDelay(200);	
}
}