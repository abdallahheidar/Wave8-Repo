/*
 ============================================================================
 Name        : Sprint2_Story1.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


/*********************************includes**********************************/
#include "Sprint2_story1.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define HANDRED_MS            100
#define FOUR_HANDRED_MS       400
#define TRUE                  1
#define BUTTON_FLAG	          ( 1 << 0 )
#define STRING_FLAG	          ( 1 << 1 )
#define CLEAR                 0
#define ROW_1                 0
#define ROW_2                 1
#define COLUMN_1              0
#define ENTERY_ONE            1
#define ENTERY_TWO            2
#define ENTERY_THREE          3
#define ENTERY_FOUR           4
#define BTN_PRESSED           1
#define BTN_RELEASED          0
#define HIGH                  1
#define LOW                   0
/***************************************************************************/


/******************************global variables*****************************/
uint8_t *str;

/* Declare a variable to hold the created event group. */
EventGroupHandle_t Sprint2_Task1_EventGroup;
/***************************************************************************/


/************************************************************************************
* Function Name: Sprint2_story1_Init
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
************************************************************************************/
void Sprint2_story1_Init(void)
{
	TaskHandle_t xHandle = NULL;
	LCD_init();
	pushButtonInit(BTN_0);

    /* Attempt to create the event group. */
    Sprint2_Task1_EventGroup = xEventGroupCreate();
	while(TRUE)
	{
		xHandle=xTaskGetCurrentTaskHandle();
		vTaskDelete(xHandle);
	}
}



/************************************************************************************
* Function Name: Sprint2_Story1_Task_A
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function - prints data on LCD
*                            - print “I have been over-written !!!!!!!!!” on row to as long as the button is pressed
*                            - Prints the other string as long as the button is released
************************************************************************************/
void Sprint2_Story1_Task_A(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	static uint8_t u8_entery_counter=CLEAR;
	static uint8_t u8_button_state=CLEAR;
	EventBits_t au8_Bits;

    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		/* read the event flag */
		au8_Bits = xEventGroupGetBits(Sprint2_Task1_EventGroup);

		/* if the BTN is pressed */
		if(au8_Bits&BUTTON_FLAG)
		{
			if(u8_button_state==LOW)
			{
				u8_button_state=HIGH;
				au8_Bits = xEventGroupClearBits(
								Sprint2_Task1_EventGroup,   /* The event group being updated. */
								STRING_FLAG );              /* The bits being cleared. */
				u8_entery_counter=CLEAR;
			}
			LCD_clearScreen();
			LCD_displayStringRowColumn(ROW_1,COLUMN_1,"I have been over-written !!!!!!!!!");
		}
		else
		{
			/* print the string for 200ms then clear the screen for 200ms */
			u8_button_state=CLEAR;
			if(au8_Bits&STRING_FLAG)
			{
				u8_entery_counter++;
				if(u8_entery_counter==ENTERY_ONE)
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,str);
				}
				if(u8_entery_counter==ENTERY_TWO)
				{
					LCD_displayStringRowColumn(0,0,str);
				}
				else if(u8_entery_counter==ENTERY_THREE)
				{
					LCD_clearScreen();
				}
				else if(u8_entery_counter==ENTERY_FOUR)
				{
					LCD_clearScreen();
					au8_Bits = xEventGroupClearBits(
									Sprint2_Task1_EventGroup,   /* The event group being updated. */
									STRING_FLAG );              /* The bits being cleared. */
					u8_entery_counter=CLEAR;
				}
			}
		}
        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}

}



/************************************************************************************
* Function Name: Sprint2_Story1_Task_B
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function - reads the button state
************************************************************************************/
void Sprint2_Story1_Task_B(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	uint8_t au8_btn_status;
	EventBits_t au8_Bits;
    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		au8_btn_status = pushButtonGetStatus(BTN_0);
		if(au8_btn_status)
		{
			au8_Bits = xEventGroupSetBits(
							Sprint2_Task1_EventGroup,    /* The event group being updated. */
							BUTTON_FLAG );               /* The bits being set. */
		}
		else
		{
			au8_Bits = xEventGroupClearBits(
							Sprint2_Task1_EventGroup,   /* The event group being updated. */
							BUTTON_FLAG );              /* The bits being cleared. */
		}
        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}

}



/************************************************************************************
* Function Name: Sprint2_Story1_Task_C
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function -sends data (“Hello LCD !!”) to LCD
*                            -with periodicity 400ms
************************************************************************************/
void Sprint2_Story1_Task_C(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = FOUR_HANDRED_MS;
	EventBits_t au8_Bits;
    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		str = "Hello LCD !!";
		au8_Bits = xEventGroupSetBits(
						Sprint2_Task1_EventGroup,   /* The event group being updated. */
						STRING_FLAG );              /* The bits being cleared. */

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}
