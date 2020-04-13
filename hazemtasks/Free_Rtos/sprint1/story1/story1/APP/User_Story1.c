/*
 ============================================================================
 Name        : User_Story1.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

/*********************************includes**********************************/
#include "User_Story1.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define ONE_MS                1000
#define TRUE                  1
/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/




/************************************************************************************
* Function Name: UserStoryOneInit
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function is responsible for the initialization of all modules
* used in this file
************************************************************************************/
void UserStoryOneInit(void)
{
	TaskHandle_t xHandle = NULL;
	 /* initialize the LED */
	Led_Init(LED_0); 
	
		
		xHandle=xTaskGetCurrentTaskHandle();
		vTaskDelete(xHandle);
		  		

}



/************************************************************************************
* Function Name: UserStoryOne
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function toggles LED number zero
************************************************************************************/
void UserStoryOne(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = ONE_MS;

    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		Led_Toggle(LED_0);		 /* toggle the LED */
        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}
