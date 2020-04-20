
/************************ Preprocessors **************************/
#define F_CPU		16000000UL
#include <util/delay.h>
#include "../../MC_AL/DIO/DIO.h"
#include "lcd.h"
#include "lcd_Config.h"

/************************ Functions Definitions **************************/
void LCD_SendNibble(uint8_t u8_DataNibble);


// function to send H-to-L enable pulse to LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: minimum delay is 450ns, so 1us here is good
void LCD_Latch(void)
{
	DIO_Write(LCD_EN_GPIO, LCD_EN_PIN, HIGH);				/*make EN high*/
	_delay_us(20);											/*delay 20us*/
	DIO_Write(LCD_EN_GPIO, LCD_EN_PIN, LOW);				/*make EN low*/
	_delay_us(20);											/*delay 20us*/
}

// function to initialize the 16x2 LCD in 4-bits mode and also initialize micro controller port pins
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Init(void)
{
	DIO_Cfg_s str_DioCfg_EN;
	str_DioCfg_EN.dir = OUTPUT;
	str_DioCfg_EN.GPIO = LCD_EN_GPIO;
	str_DioCfg_EN.pins = LCD_EN_PIN;
	DIO_init(&str_DioCfg_EN);
	
	DIO_Cfg_s str_DioCfg_RS;
	str_DioCfg_RS.dir = OUTPUT;
	str_DioCfg_RS.GPIO = LCD_RS_GPIO;
	str_DioCfg_RS.pins = LCD_RS_PIN;
	DIO_init(&str_DioCfg_RS);
	
	DIO_Cfg_s str_DioCfg_RW;
	str_DioCfg_RW.dir = OUTPUT;
	str_DioCfg_RW.GPIO = LCD_RW_GPIO;
	str_DioCfg_RW.pins = LCD_RW_PIN;
	DIO_init(&str_DioCfg_RW);
	
	DIO_Cfg_s str_DioCfg_Data;
	str_DioCfg_Data.dir = OUTPUT;
	str_DioCfg_Data.GPIO = LCD_DATA_GPIO;
	str_DioCfg_Data.pins = LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;;
	DIO_init(&str_DioCfg_Data);
	
	LCD_WriteCMD(0x33);											/*4 bit sequence for LCD 4-bits initializing*/
	LCD_WriteCMD(0x32);											/*4 bit sequence for LCD 4-bits initializing*/
	LCD_WriteCMD(LCD_CMD_4BIT_MODE_2LINE_DISPLAY_5X8FONT);	    /*mode:4 bit , display:2Lines , font:5x8 dots*/
	LCD_WriteCMD(LCD_CMD_DISPLAY_ON_CURSOR_OFF);		/*display on .. cursor on .. blinking off*/
	LCD_Clear();												/*clear LCD , set LCD cursor to 0 (display address counter = 0)*/
}

// function to send command to LCD
// INPUT: cmd>command in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteCMD(t_LCD_CMD cmd)
{
	
	DIO_Write(LCD_RW_GPIO, LCD_RW_PIN, LOW);
	DIO_Write(LCD_RS_GPIO, LCD_RS_PIN, LOW);
	LCD_SendNibble(cmd>>4);
	LCD_Latch();
	
	LCD_SendNibble(cmd);
	LCD_Latch();
	
	// all commands need delay of minimum 39us, so 50us is good enough
	_delay_us(50);
}


// function to send command to LCD
// INPUT: data>ascii character in 8bits
// OUTPUT: ...
// NOTES: using preprocessor #if here to allow user compile this code
//	if LCD D4-D7 are connected to micro controller port pins 4-7 OR pins 0-3
void LCD_WriteData(uint8_t u8_DataByte)
{
	DIO_Write(LCD_RW_GPIO, LCD_RW_PIN, LOW);
	DIO_Write(LCD_RS_GPIO, LCD_RS_PIN, HIGH);
	LCD_SendNibble(u8_DataByte>>4);
	LCD_Latch();
	
	LCD_SendNibble(u8_DataByte);
	LCD_Latch();
	
	// all data writing need delay of minimum 40us, so 50us is good enough
	_delay_us(50);																								// delay 100us for data to be processed by LCD before sending any other data
}

// function to send string to LCD
// INPUT: pointer to the first element of the character array
// OUTPUT: ...
// NOTES: ...
void LCD_WriteString(uint8_t *str)
{
	// loop until pointer dereference = '\0'
	while(*str)
	{
		LCD_WriteData(*str);				// send current array character to the LCD
		str++;								// point to the next character address
	}
}

// function to clear the LCD
// INPUT: ...
// OUTPUT: ...
// NOTES: ...
void LCD_Clear(void)
{
	LCD_WriteCMD(LCD_CMD_CLEAR);						// send clear command to the LCD
}

// function to shift cursor 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift cursor 1 step to right
//				LEFT: shift cursor 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_CursorShift(t_LCD_SHIFT_DIR u8_Direction)
{
	if (u8_Direction == RIGHT)
	{
		LCD_WriteCMD(0x14);				// shift cursor 1 step to right
	}
	else if (u8_Direction == LEFT)
	{
		LCD_WriteCMD(0x10);				// shift cursor 1 step to left
	}
}

// function to shift data on LCD 1 step right OR left
// INPUT: direction> 2 directions available as follow:
//				RIGHT: shift data on LCD 1 step to right
//				LEFT: shift data on LCD 1 step to left
// OUTPUT: ...
// NOTES: ...
void LCD_DisplayShift(t_LCD_SHIFT_DIR u8_Direction)
{
	if (u8_Direction == RIGHT)
	{
		LCD_WriteCMD(0x1c);				// shift data on LCD 1 step to right
	}
	else if (u8_Direction == LEFT)
	{
		LCD_WriteCMD(0x18);				// shift data on LCD 1 step to left
	}
}

// function to move LCD AC(address counter of the LCD DDRAM) to a certain position
// INPUT: line> allowed values are: 1 to move AC to the first horizontal line
//									2 to move AC to the second horizontal line
//		  column> allowed values are from 1:16 to move the AC to any position
// OUTPUT: ...
// NOTES: any values other than 1 OR 2 for line .. 1-16 for column will be ignored
void LCD_GoToLineColumn(uint8_t line , uint8_t column)
{
	if (line == 1 && column >= 1 && column <= 16)
	{
		LCD_WriteCMD( 0x80 | (0x00 +     column - 1 ) );			// move AC to line 1 , column's position
	}
	else if (line == 2 && column >= 1 && column <= 16)
	{
		LCD_WriteCMD( 0x80 | (0x40 +     column - 1 ) );			// move AC to line 2 , column's position
	}
}

void LCD_SendNibble(uint8_t u8_DataNibble)
{
	uint8_t u8_Mask;
	
	u8_Mask = 0x01;
	if ( u8_DataNibble & u8_Mask )
	{
		DIO_Write(LCD_D4_GPIO, LCD_D4_PIN, HIGH );
	}
	else
	{
		DIO_Write(LCD_D4_GPIO, LCD_D4_PIN, LOW );
	}
	
	u8_Mask = 0x02;
	if ( u8_DataNibble & u8_Mask )
	{
		DIO_Write(LCD_D5_GPIO, LCD_D5_PIN, HIGH );
	}
	else
	{
		DIO_Write(LCD_D5_GPIO, LCD_D5_PIN, LOW );
	}
	
	u8_Mask = 0x04;
	if ( u8_DataNibble & u8_Mask )
	{
		DIO_Write(LCD_D6_GPIO, LCD_D6_PIN, HIGH );
	}
	else
	{
		DIO_Write(LCD_D6_GPIO, LCD_D6_PIN, LOW );
	}
	
	u8_Mask = 0x08;
	if ( u8_DataNibble & u8_Mask )
	{
		DIO_Write(LCD_D7_GPIO, LCD_D7_PIN, HIGH );
	}
	else
	{
		DIO_Write(LCD_D7_GPIO, LCD_D7_PIN, LOW );
	}
}
