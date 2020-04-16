/*
 ============================================================================
 Name        : Sprint2_Story2.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


/*********************************includes**********************************/
#include "Sprint2_story2.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TRUE                  1
#define BTN0_FLAG	          ( 1 << 0 )
#define BTN1_FLAG	          ( 1 << 1 )
#define LED0_FLAG	          ( 1 << 2 )
#define HANDRED_MS            100
#define ROW_1                 0
#define ROW_2                 1
#define COLUMN_1              0
/***************************************************************************/


/******************************global variables*****************************/

/* Declare a variable to hold the created event group. */
EventGroupHandle_t Sprint2_Task2_EventGroup;
/***************************************************************************/

void Sprint2_story2_Init(void)
{
	TaskHandle_t xHandle = NULL;
	LCD_init();
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	Led_Init(LED_0);
    /* Attempt to create the event group. */
    Sprint2_Task2_EventGroup = xEventGroupCreate();
	while(TRUE)
	{
		xHandle=xTaskGetCurrentTaskHandle();
		vTaskDelete(xHandle);
	}
}

void Sprint2_Story2_Task_A(void)
{
	/* monitor button one state */
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	uint8_t au8_btn_status;
	EventBits_t au8_Bits;
	while(TRUE)
	{
		au8_btn_status = pushButtonGetStatus(BTN_0);
		if(au8_btn_status)
		{
			au8_Bits = xEventGroupSetBits(
							Sprint2_Task2_EventGroup,    /* The event group being updated. */
							BTN0_FLAG );               /* The bits being set. */
		}
		else
		{
			au8_Bits = xEventGroupClearBits(
							Sprint2_Task2_EventGroup,   /* The event group being updated. */
							BTN0_FLAG );              /* The bits being cleared. */
		}

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}

}

void Sprint2_Story2_Task_B(void)
{
	/* monitor button two state */
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	uint8_t au8_btn_status;
	EventBits_t au8_Bits;
	while(TRUE)
	{
		au8_btn_status = pushButtonGetStatus(BTN_1);
		if(au8_btn_status)
		{
			au8_Bits = xEventGroupSetBits(
							Sprint2_Task2_EventGroup,    /* The event group being updated. */
							BTN1_FLAG );               /* The bits being set. */
		}
		else
		{
			au8_Bits = xEventGroupClearBits(
							Sprint2_Task2_EventGroup,   /* The event group being updated. */
							BTN1_FLAG );              /* The bits being cleared. */
		}

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}

void Sprint2_Story2_Task_C(void)
{
	/* switching led on/off */
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	EventBits_t au8_Bits;
	au8_Bits = xEventGroupGetBits(Sprint2_Task2_EventGroup);
	while(TRUE)
	{
		if((au8_Bits&BTN0_FLAG) || (au8_Bits&BTN1_FLAG))
		{
			Led_On(LED_0);
			au8_Bits = xEventGroupSetBits(
							Sprint2_Task2_EventGroup,    /* The event group being updated. */
							LED0_FLAG );               /* The bits being set. */
		}
		else
		{
			Led_Off(LED_0);
			au8_Bits = xEventGroupClearBits(
							Sprint2_Task2_EventGroup,   /* The event group being updated. */
							LED0_FLAG );              /* The bits being cleared. */
		}

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}


void Sprint2_Story2_Task_D(void)
{
	/* print the led state and which button is currently active */
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	EventBits_t au8_Bits;
	while(TRUE)
	{
		/* read the event flag */
		au8_Bits = xEventGroupGetBits(Sprint2_Task2_EventGroup);
		LCD_clearScreen();
		if(au8_Bits&LED0_FLAG)
		{
			if(au8_Bits&BTN0_FLAG)
			{
				LCD_displayStringRowColumn(ROW_1,COLUMN_1,"LED ON");
				LCD_displayStringRowColumn(ROW_2,COLUMN_1,"BTN 1 ACTIVE");
			}
			else
			{
				LCD_displayStringRowColumn(ROW_1,COLUMN_1,"LED ON");
				LCD_displayStringRowColumn(ROW_2,COLUMN_1,"BTN 2 ACTIVE");
			}
		}
		else
		{
			LCD_displayStringRowColumn(ROW_1,COLUMN_1,"LED OFF");
			LCD_displayStringRowColumn(ROW_2,COLUMN_1,"NO BTN ACTIVE");
		}

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}
