

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_
/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "../../ServiceLayer/std_types.h"

/*************************************************************/
/*                GLOBAL EXTERN VARIABLES                    */
/*************************************************************/
const extern uint8_t gau8_KeypadArray[3][3];

/*************************************************************/
/*                     MACROS                                */
/*************************************************************/
#define KEYPAD_COLUMNS_GPIO				(GPIOA)
#define KEYPAD_COLUMNS_PINS				(BIT5 | BIT6 | BIT7)

#define KEYPAD_ROWS_GPIO				(GPIOA)
#define KEYPAD_ROWS_PINS				(BIT2 | BIT3 | BIT4)

#define ALL_KEYS_RELEASED_MASK			(0xE0)				/* 0b1110 0000 */

#define COLUMN_0_CHECK_MASK				(0x60)				/* 0b0110 0000 */
#define COLUMN_1_CHECK_MASK				(0xA0)				/* 0b1010 0000 */
#define COLUMN_2_CHECK_MASK				(0xC0)				/* 0b1100 0000 */

#define ROW_0_OTHERS_HIGH_MASK					(0b00011000)
#define ROW_0_LOW_MASK							(0b00000100)
#define ROW_1_OTHERS_HIGH_MASK					(0b00010100)
#define ROW_1_LOW_MASK							(0b00001000)
#define ROW_2_OTHERS_HIGH_MASK					(0b00001100)
#define ROW_2_LOW_MASK							(0b00010000)

#endif /* KEYPAD_CONFIG_H_ */