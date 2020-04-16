/*
 ============================================================================
 Name        : Keypad.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "keypad.h"

#define KEYPAD_MASK                0b00010000
#define INITIAL_VALUE              0
#define ONE                        1
/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/


/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t button_number);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8_t KeyPad_getPressedKey(void)
{
	uint8_t col,row;
	uint8_t key=NO_KEY_PRESSED;
	for(col=INITIAL_VALUE;col<N_col;col++) /* loop for columns */
	{
		/*
		 * each time only one of the column pins will be output and
		 * the rest will be input pins include the row pins
		 */
		KEYPAD_PORT_DIR = (KEYPAD_MASK<<col);

		/*
		 * clear the output pin column in this trace and enable the internal
		 * pull up resistors for the rows pins
		 */
		KEYPAD_PORT_OUT = (~(KEYPAD_MASK<<col));
		for(row=INITIAL_VALUE;row<N_row;row++) /* loop for rows */
		{
			if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row)) /* if the switch is press in this row */
			{
				//while(BIT_IS_CLEAR(KEYPAD_PORT_IN,row));  /* for button debouncing */
				key = KeyPad_4x3_adjustKeyNumber((row*N_col)+col+ONE);

			}
		}
	}
	return key;
}



static uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of =
				 break;
		case 11: return 0;
				 break;
		case 12: return '#'; // ASCII Code of +
				 break;
		default: return button_number;
	}
}

