

/**************************** PreProcessors ******************************/
#ifndef LCD_H_
#define LCD_H_

#define RIGHT									0		// just indicator number make cursor/display shift right
#define LEFT									1		// just indicator number make cursor/display shift left

#include "../../ServiceLayer/std_types.h"

/*LCD commands as hex */
typedef enum
{
	LCD_CMD_CLEAR = 0x01,
	LCD_CMD_RETURN_HOME = 0x02,
	LCD_CMD_4BIT_MODE_2LINE_DISPLAY_5X8FONT = 0x28,
	LCD_CMD_DISPLAY_ON_CURSOR_OFF = 0x0c,
	LCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_ON = 0x0f,
	LCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_OFF = 0x0e,
	LCD_CMD_SHIFT_CURSOR_RIGHT = 0x14,
	LCD_CMD_SHIFT_CURSOR_LEFT = 0x10,
	LCD_CMD_SHIFT_DISPLAY_RIGHT = 0x1c,
	LCD_CMD_SHIFT_DISPLAY_LEFT = 0x18
}t_LCD_CMD;

typedef enum
{
	SHIFR_RIGHT,
	SHIFT_LEFT
}t_LCD_SHIFT_DIR;
/******************* Prototypes and Global variables *********************/
// function to send H-to-L enable pulse to LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: minimum delay is 450ns, so 1us here is good
void LCD_Latch(void);

// function to send command to LCD
// INPUT: cmd>command in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteCMD(uint8_t cmd);

// function to send command to LCD
// INPUT: data>ascii character in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteData(uint8_t data);

// function to send string to LCD
// INPUT: pointer to the first element of the character array
// OUTPUT: ...
// NOTES: ...
void LCD_WriteString(uint8_t *str);

// function to clear the LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Clear(void);

// function to shift cursor 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift cursor 1 step to right
//				LEFT: shift cursor 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_CursorShift(t_LCD_SHIFT_DIR direction);

// function to shift data on LCD 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift data on LCD 1 step to right
//				LEFT: shift data on LCD 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_DisplayShift(t_LCD_SHIFT_DIR direction);

// function to move LCD AC(address counter of the LCD DDRAM) to a certain position
// INPUT: line> allowed values are: 1 to move AC to the first horizontal line
//									2 to move AC to the second horizontal line
//		  column> allowed values are from 1:16 to move the AC to any position
// OUTPUT: ...
// NOTES: any values other than 1 OR 2 for line .. 1-16 for column will be ignored
void LCD_GoToLineColumn(uint8_t , uint8_t);

// function to initialize the 16x2 LCD in 4-bits mode and also initialize micro controller port pins
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Init(void);

#endif /* LCD_H_ */