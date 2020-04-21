/*
 ============================================================================
 Name        : User_Story1.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

/*********************************includes**********************************/
#include "User_Story2.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define ONE_MS                1000
#define TRUE                  1
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

/***************************************************************************/

uint8_t gau8_datatosend[16];
volatile uint8_t gu8_sendflag;


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
	 /* initialize the sytem*/
	Led_Init(LED_0); 
	pushButtonInit(BTN_1);
	LCD_init();
	
	UART_Config_Structure uart_initialization_structure;
	uart_initialization_structure.Char_Size=USART_8_Bit_CHAR;
	uart_initialization_structure.Clk_Polarity_Mode=TX_RISING_RX_FALLING;
	uart_initialization_structure.Speed_Mode=USART_DOUBLE_SPEED;
	uart_initialization_structure.Parity_Mode=USART_NO_PARITY;
	uart_initialization_structure.Stop_Bit_Mode=USART_1_STOPBIT;
	uart_initialization_structure.Receive_Mode=USART_RECIEVE_ENABLE;
	uart_initialization_structure.Transmit_Mode=USART_TRANSMIT_ENABLE;
	uart_initialization_structure.Double_Speed_Baud_Rate=BAUD9600;
	uart_initialization_structure.Transmit_Complete_Inter=TX_COMPLETE_INTER_DISABLE;
	uart_initialization_structure.Receive_Complete_Inter=RX_COMPLETE_INTER_ENABLE;
	UART_init(&uart_initialization_structure);
	
	
	
		xHandle=xTaskGetCurrentTaskHandle();
		vTaskSuspend(xHandle);
		  		

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
	uint8_t au8_getbtnstatue=Released;
    static uint8_t au8_counter;
	static uint8_t au8_counter2;
	uint8_t flag=0;
	while(TRUE)
	{
		pushButtonGetStatus(BTN_1,&au8_getbtnstatue);
		if(au8_getbtnstatue==Pressed)
		{
			au8_counter++;
			if(au8_counter==2)
			{
				gu8_sendflag=1;
				flag=1;
				au8_counter=0;
			    
			}
		}
		if(flag==1)
		{
           au8_counter2++;
		   Led_On(LED_0);
		   if(au8_counter2==10)
		   {
			   au8_counter2=0;
			   flag=0;
			   Led_Off(LED_0);
		   }

		}
		if(g8_UART_RX_FLAG==FLAG_HIGH)
		{
			
			flag=1;
			g8_UART_RX_FLAG=FLAG_LOW;
		}	 
		
        /* Wait for the next cycle */
        vTaskDelay(40);
	}
}

void keypadtask(void)
{
		TickType_t UserStoryOne_LastWakeTime;
		const TickType_t UserStoryOne_Frequency = ONE_HANDRED_MS;                 
		   /* to avoid tacking the same input from the user */
		   uint8_t i=0;
		uint8_t au8_Key;
		uint8_t au8_temp_key;
		static uint8_t u8_entry_counter=CLEAR;
		static uint8_t u8_debouncing_counter=CLEAR;
		static uint8_t u8_waiting_flag=FLAG_LOW;
		static uint8_t u8_pass_match_flag=CLEAR;
		static uint8_t u8_counter=CLEAR;
		static uint8_t au8_counter=0;

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
						gau8_datatosend[au8_counter]=au8_temp_key;
						au8_counter++;			
					}

				}

			}
				if(gu8_sendflag==1)
				{
					
					for(i=0;i<au8_counter;i++)
					{
						UART_sendByte(gau8_datatosend[i]);
						gau8_datatosend[i]=0;
					}
					au8_counter=0;
					gu8_sendflag=0;
					
				}
				
				
			/* Wait for the next cycle */
			vTaskDelay(30);
		}
	
	
}