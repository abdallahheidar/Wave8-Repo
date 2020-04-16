/*
 ============================================================================
 Name        : User_Story2.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


/*********************************includes**********************************/
#include "User_Story2.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TRUE                  1
#define ONE_HANDRED_MS        100
#define ZERO                  0
#define FOUR                  4
#define FIVE                  5
#define SIX                   6
#define SEVEN                 7
#define CLEAR                 0
#define FLAG_LOW              0
#define FLAG_HIGH             1
#define MATCHED               3
#define MISMATCHED            4
#define ENTER                 0
#define ASCII_ADDITION        48
#define ENTRIES_FOR_2_SEC     20
#define ENTRIES_FOR_DEBOUNCE  2
/***************************************************************************/


/******************************global variables*****************************/
static uint8_t arr_passcode[SIX]={1,2,4,3,3,3};
/***************************************************************************/




/************************************************************************************
* Function Name: UserStoryTwoInit
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function is responsible for the initialization of all modules
* used in this file
************************************************************************************/
void UserStoryTwoInit(void)
{
	TaskHandle_t xHandle = NULL;
	LCD_init();
	while(TRUE)
	{
		xHandle=xTaskGetCurrentTaskHandle();
		vTaskDelete(xHandle);
	}
}



/************************************************************************************
* Function Name: UserStoryOne
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
************************************************************************************/
void UserStoryTwo(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = ONE_HANDRED_MS;                    /* to avoid tacking the same input from the user */
	uint8_t au8_Key;
	uint8_t au8_temp_key;
	static uint8_t u8_entry_counter=CLEAR;
	static uint8_t u8_debouncing_counter=CLEAR;
	static uint8_t u8_waiting_flag=FLAG_LOW;
	static uint8_t u8_pass_match_flag=CLEAR;
	static uint8_t u8_counter=CLEAR;

    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		if(u8_waiting_flag == FLAG_HIGH)
		{
			u8_entry_counter++;
			if(u8_entry_counter==ENTRIES_FOR_2_SEC)
			{
				u8_entry_counter=CLEAR;
				u8_waiting_flag=FLAG_LOW;
				LCD_clearScreen();
			}
		}
		else
		{
			/* get the pressed key */
			au8_Key = KeyPad_getPressedKey();

			if(au8_Key != NO_KEY_PRESSED)
			{
				/* Increment the debouncing counter */
				u8_debouncing_counter++;

				/* to prevent any key duplication since the human press is around 100ms */
				if(u8_debouncing_counter==ENTRIES_FOR_DEBOUNCE)
				{
					/* clear the debouncing counter */
					u8_debouncing_counter=CLEAR;

					/* switch on the key value and take the appropriate action */
					au8_temp_key = au8_Key+ASCII_ADDITION;
					LCD_displayCharacter(au8_temp_key);

					/*erase button is pressed */
					if(au8_Key == '#')
					{
						/* clear the LCD */
						LCD_clearScreen();
					}

					  /* enter button is pressed */
					else if(au8_Key == ENTER)
					{
						LCD_clearScreen();
						/* check if 6 digites or more are pressed */
						if(u8_counter >= SIX)
						{
							if(u8_pass_match_flag == MATCHED)
							{
								LCD_displayString("Correct Password");
								u8_waiting_flag = FLAG_HIGH;
							}

						}
						/* reset the matching flag and array counter */
						u8_pass_match_flag = CLEAR;
						u8_counter=CLEAR;
					}

					else if(au8_Key == arr_passcode[u8_counter])
					{
						/* check if the 6 digits entered correctly */
						if(u8_counter==FIVE && u8_pass_match_flag==CLEAR)
						{
							u8_pass_match_flag = MATCHED;
						}
						 /* increment the array counter */
						u8_counter++;
					}

					else
					{
						/* raise a the flag if any mismatch happened */
						u8_pass_match_flag = MISMATCHED;

						/* increment the array counter */
						u8_counter++;
					}
				}

			}

		}

		/* Wait for the next cycle */
		vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}
