 

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "../../ServiceLayer/std_types.h"

/*************************************************************/
/*                       MACROS                              */
/*************************************************************/
#define NO_KEY_IS_PRESSED				(0xFF)
#define ENTER_KEY						(0xFE)
#define ERASE_KEY						(0xFD)

/*************************************************************/
/*                     NEW TYPES DEFINITIONS                 */
/*************************************************************/
typedef enum enu_Keys_States_t
{
	Key_PreReleased_State,
	Keys_Released_State,
	Key_PrePressed_State,
	Key_Pressed_State
}enu_Keys_States_t;

/*************************************************************/
/*                     FUNCTIONS PROTOTYPES                  */
/*************************************************************/
/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: initialize the keypad module
 */
void Keypad_Init(void);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: task to update the pressed key if any pressed
 */
void Keypad_Update(void);


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
uint8_t Keypad_GetPressedKey( enu_Keys_States_t enu_KeyAtState);

#endif /* KEYPAD_H_ */