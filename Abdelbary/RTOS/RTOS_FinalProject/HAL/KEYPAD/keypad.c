 

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "keypad.h"
#include "Keypad_Config.h"
#include "../../MC_AL/DIO/DIO.h"

/*************************************************************/
/*                    GOLBAL STATIC VARIABLES                */
/*************************************************************/
static enu_Keys_States_t genu_Key_CurrentState = Keys_Released_State;
static uint8_t gau8_KeySamples[2] = {ALL_KEYS_RELEASED_MASK, ALL_KEYS_RELEASED_MASK};
static uint8_t gu8_KeyRow;
static uint8_t gu8_KeyColumn;

/*************************************************************/
/*                STATIC FUNCTIONS PROTOTYPES                */
/*************************************************************/
/**
 * Input:	----
  * Output:	----
 * In/Out:	----			
 * Return:	internal function for detecting which key is pressed
 * Description: 
 */
static void Key_Detection(void);

/*************************************************************/
/*                FUNCTIONS IMPLEMENTATION                   */
/*************************************************************/
			
/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: initialize the keypad module
 */
void Keypad_Init(void)
{
	DIO_Cfg_s str_Columns_Cfg;
	str_Columns_Cfg.dir = INPUT;
	str_Columns_Cfg.GPIO = KEYPAD_COLUMNS_GPIO;
	str_Columns_Cfg.pins = KEYPAD_COLUMNS_PINS;
	DIO_init(&str_Columns_Cfg);
	/* pull up all columns input pullups */
	DIO_Write(KEYPAD_COLUMNS_GPIO, KEYPAD_COLUMNS_PINS, HIGH);
	
	DIO_Cfg_s str_Rows_Cfg;
	str_Rows_Cfg.dir = OUTPUT;
	str_Rows_Cfg.GPIO = KEYPAD_ROWS_GPIO;
	str_Rows_Cfg.pins = KEYPAD_ROWS_PINS;
	DIO_init(&str_Rows_Cfg);
	/* make all rows output HIGH */
	DIO_Write(KEYPAD_ROWS_GPIO, KEYPAD_ROWS_PINS, HIGH);
}

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: task to update the pressed key if any pressed
 */
void Keypad_Update(void)
{
	uint8_t u8_ReadValue;
	
	/* make all rows low */
	DIO_Write(KEYPAD_ROWS_GPIO, KEYPAD_ROWS_PINS, LOW);
	
	/* read all columns */
	DIO_Read(KEYPAD_COLUMNS_GPIO, KEYPAD_COLUMNS_PINS, &u8_ReadValue);
	
	gau8_KeySamples[0] = gau8_KeySamples[1];
	gau8_KeySamples[1] = u8_ReadValue;
	
	switch (genu_Key_CurrentState)
	{
		case Keys_Released_State:
			/* if any column reads low twice, means a key is pressed */
			if ( ALL_KEYS_RELEASED_MASK != gau8_KeySamples[0] && ALL_KEYS_RELEASED_MASK != gau8_KeySamples[1] )
			{
				/* check witch key is pressed */
				asm("NOP");
				Key_Detection();
				
				/* change state to confirm a key is PrePressed */
				genu_Key_CurrentState = Key_PrePressed_State;
			} 
			else
			{
				/* Do Nothing */
			}
			break;
		
		case Key_PrePressed_State:
			/* if any column reads low again, then the key is still pressed so move the state from PrePressed To pressed */
			if ( ALL_KEYS_RELEASED_MASK != gau8_KeySamples[1] )
			{
				/* change state to confirm a key is Pressed */
				genu_Key_CurrentState = Key_Pressed_State;
			} 
			else
			{
				/* Do Nothing */
			}
			break;
		
		case Key_Pressed_State:
			/* if no column reads low, means a key has just released */
			if ( ALL_KEYS_RELEASED_MASK == gau8_KeySamples[0] && ALL_KEYS_RELEASED_MASK == gau8_KeySamples[1] )
			{
				/* change state to confirm all keys are released */
				genu_Key_CurrentState = Key_PreReleased_State;
			}
			else
			{
				/* Do Nothing */
			}
			break;
			
		case Key_PreReleased_State:
			/* if no column reads low while it was already released */
			if ( ALL_KEYS_RELEASED_MASK == gau8_KeySamples[1] )
			{
				/* change state to released */
				genu_Key_CurrentState = Keys_Released_State;
			}
			else
			{
				/* Do Nothing */
			}
			break;
		default:	/* Do Nothing */
		break;
	}
}

/**
 * Input:	state of the key that user want to detect on:
 *			-> Key_PreReleased_State
 *			-> Keys_Released_State
 *			-> Key_PrePressed_State
 *			-> Key_Pressed_State
 * Output:	----
 * In/Out:	----			
 * Return:	the key pressed from the keys array	
 * Description: 
 */
uint8_t Keypad_GetPressedKey( enu_Keys_States_t enu_KeyAtState)
{
	uint8_t u8_PressedKey;
	switch ( enu_KeyAtState )
	{
	case Key_PrePressed_State:
		/* if the module current state is the same as user's requested state */
		if ( Key_PrePressed_State == genu_Key_CurrentState )
		{
			u8_PressedKey = gau8_KeypadArray[gu8_KeyRow][gu8_KeyColumn];
		} 
		else
		{
			u8_PressedKey = NO_KEY_IS_PRESSED;
		}
		break;
	case Key_Pressed_State:
		/* if the module current state is the same as user's requested state */
		if ( Key_Pressed_State == genu_Key_CurrentState )
		{
			u8_PressedKey = gau8_KeypadArray[gu8_KeyRow][gu8_KeyColumn];
		}
		else
		{
			u8_PressedKey = NO_KEY_IS_PRESSED;
		}
		break;
	case Key_PreReleased_State:
		/* if the module current state is the same as user's requested state */
		if ( Key_PreReleased_State == genu_Key_CurrentState )
		{
			u8_PressedKey = gau8_KeypadArray[gu8_KeyRow][gu8_KeyColumn];
		}
		else
		{
			u8_PressedKey = NO_KEY_IS_PRESSED;
		}
		break;
	default:	u8_PressedKey = NO_KEY_IS_PRESSED; 
	}
	return u8_PressedKey;
}

/**
 * Input:	----
  * Output:	----
 * In/Out:	----			
 * Return:	internal function for detecting which key is pressed
 * Description: 
 */
static void Key_Detection(void)
{
	uint8_t u8_ReadValue;
		
	/* First: save the column caused the press */
	/* make all rows low */
	DIO_Write(KEYPAD_ROWS_GPIO, KEYPAD_ROWS_PINS, LOW);
	
	/* read all columns */
	DIO_Read(KEYPAD_COLUMNS_GPIO, KEYPAD_COLUMNS_PINS, &u8_ReadValue);
	
	if ( COLUMN_0_CHECK_MASK == u8_ReadValue )
	{
		gu8_KeyColumn = 0;
	} 
	else if ( COLUMN_1_CHECK_MASK == u8_ReadValue )
	{
		gu8_KeyColumn = 1;
	}
	else if ( COLUMN_2_CHECK_MASK == u8_ReadValue )
	{
		gu8_KeyColumn = 2;
	}
	else
	{
		/* Do Nothing */
	}
	
	/* Second: find the row caused the press and save it by setting one row : 0, and all others: 1*/
	
	/* ROW0: */
	DIO_Write(KEYPAD_ROWS_GPIO, (ROW_0_OTHERS_HIGH_MASK), HIGH);
	DIO_Write(KEYPAD_ROWS_GPIO, (ROW_0_LOW_MASK), LOW);
		
	/* read all columns */
	DIO_Read(KEYPAD_COLUMNS_GPIO, KEYPAD_COLUMNS_PINS, &u8_ReadValue);
		
	/* check if this is the right row that caused the press */
	if ( ALL_KEYS_RELEASED_MASK != u8_ReadValue )
	{
		gu8_KeyRow = 0;
	}
	else
	{
		/* ROW1: */
		DIO_Write(KEYPAD_ROWS_GPIO, (ROW_1_OTHERS_HIGH_MASK), HIGH);
		DIO_Write(KEYPAD_ROWS_GPIO, (ROW_1_LOW_MASK), LOW);
		
		/* read all columns */
		DIO_Read(KEYPAD_COLUMNS_GPIO, KEYPAD_COLUMNS_PINS, &u8_ReadValue);
		
		/* check if this is the right row that caused the press */
		if ( ALL_KEYS_RELEASED_MASK != u8_ReadValue )
		{
			gu8_KeyRow = 1;
		}
		else
		{
			/* ROW0: */
			DIO_Write(KEYPAD_ROWS_GPIO, (ROW_2_OTHERS_HIGH_MASK), HIGH);
			DIO_Write(KEYPAD_ROWS_GPIO, (ROW_2_LOW_MASK), LOW);
			
			/* read all columns */
			DIO_Read(KEYPAD_COLUMNS_GPIO, KEYPAD_COLUMNS_PINS, &u8_ReadValue);
			
			/* check if this is the right row that caused the press */
			if ( ALL_KEYS_RELEASED_MASK != u8_ReadValue )
			{
				gu8_KeyRow = 2;
			}
			else
			{
				/* Do Nothing */
			}
		}
	}
}



