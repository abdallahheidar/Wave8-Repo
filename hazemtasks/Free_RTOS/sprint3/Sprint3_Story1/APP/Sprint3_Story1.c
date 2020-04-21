/*
 ============================================================================
 Name        : Sprint3_Story1.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


/*********************************includes**********************************/
#include "Sprint3_story1.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define HANDRED_MS            100
#define HALF_SEC              500
#define TRUE                  1
#define CLEAR                 0
#define ROW_1                 0
#define ROW_2                 1
#define COLUMN_1              0
#define FLAG_LOW              0
#define FLAG_HIGH             1
#define ASCII_VALUE           48
/***************************************************************************/


/******************************global variables*****************************/
uint8_t au8_key;
uint8_t au8_BTN_status;
/***************************************************************************/


/************************************************************************************
* Function Name: Sprint3_story1_Init
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this task initializes all modules needed for this system
************************************************************************************/
void Sprint3_story1_Init(void)
{
	TaskHandle_t xHandle = NULL;
	/* initialize LCD, pushbutton and UART*/
	LCD_init();
	pushButtonInit(BTN_1);

	UART_Config_Structure uart_initialization_structure;
	uart_initialization_structure.Char_Size=USART_8_Bit_CHAR;
	uart_initialization_structure.Clk_Polarity_Mode=TX_RISING_RX_FALLING;
	uart_initialization_structure.Speed_Mode=USART_DOUBLE_SPEED;
	uart_initialization_structure.Parity_Mode=USART_NO_PARITY;
	uart_initialization_structure.Stop_Bit_Mode=USART_1_STOPBIT;
	uart_initialization_structure.Receive_Mode=USART_RECIEVE_ENABLE;
	uart_initialization_structure.Transmit_Mode=USART_TRANSMIT_ENABLE;
	uart_initialization_structure.Double_Speed_Baud_Rate=BAUD9600;
	uart_initialization_structure.Transmit_Complete_Inter=TX_COMPLETE_INTER_ENABLE;
	uart_initialization_structure.Receive_Complete_Inter=RX_COMPLETE_INTER_ENABLE;
	UART_init(&uart_initialization_structure);

	/* initialize all global variables */
	au8_key=CLEAR;
	au8_BTN_status=CLEAR;

	while(TRUE)
	{
		/* delete the task to no be called any more */
		xHandle=xTaskGetCurrentTaskHandle();
		vTaskDelete(xHandle);
	}
}



/************************************************************************************
* Function Name: Sprint3_Story1_Task_A
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this task is responsible for outputting data on LCD
************************************************************************************/
void Sprint3_Story1_Task_A(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HALF_SEC;

    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		/* check the button status */
		if(au8_BTN_status == HIGH)
		{
			LCD_clearScreen();
		}
		else
		{
			/* print the pressed key on LCD on first row */
			au8_key=au8_key+ASCII_VALUE;
			LCD_clearScreen();
			LCD_displayString("PRESSED KEY IS ");
			LCD_displayCharacter(au8_key);

			/* print the received data form UART on LCD */
			LCD_displayStringRowColumn(ROW_2,COLUMN_1,"UART DATA IS ");
			LCD_displayCharacter(g8_udr_data);
		}

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}

}



/************************************************************************************
* Function Name: Sprint3_Story1_Task_B
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this task is responsible for monitoring keypad and sending reading to LCD
************************************************************************************/
void Sprint3_Story1_Task_B(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
	static uint8_t u8_pevious_key_value;
    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		/* get the pressed digit if any and save it into a global variable*/
		au8_key = KeyPad_getPressedKey();
		if(au8_key==NO_KEY_PRESSED)
		{
			/* in case no digit is pressed the global variable take the value of the previous digit */
			au8_key = u8_pevious_key_value;
		}
		else
		{
			/* save the previous value */
			u8_pevious_key_value = au8_key;
		}
        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}

}



/************************************************************************************
* Function Name: Sprint3_Story1_Task_C
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this task is responsible for sending any received data form UART to LCD
************************************************************************************/
void Sprint3_Story1_Task_C(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;

    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
        /* check if the previous receiving is complete or not */
        if(g8_UART_RX_FLAG==FLAG_HIGH)
        {
        	/* low the flag and save the data in a global variable */
        	g8_UART_RX_FLAG=FLAG_LOW;
        	UART_sendByte_INT(g8_udr_data);
        }
	}
}



/************************************************************************************
* Function Name: Sprint3_Story1_Task_D
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this task is responsible for sending push button state to LCD
************************************************************************************/
void Sprint3_Story1_Task_D(void)
{
	TickType_t UserStoryOne_LastWakeTime;
	const TickType_t UserStoryOne_Frequency = HANDRED_MS;
    /* Initialize the xLastWakeTime variable with the current time */
	UserStoryOne_LastWakeTime = xTaskGetTickCount();
	while(TRUE)
	{
		/* get the button status and save it in a global variable */
		au8_BTN_status=pushButtonGetStatus(BTN_1);

        /* Wait for the next cycle */
        vTaskDelayUntil( &UserStoryOne_LastWakeTime, UserStoryOne_Frequency);
	}
}

