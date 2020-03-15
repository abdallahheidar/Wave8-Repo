//*****************************************************************************
//
// File Name	: 'lcd_lib.c'
// Title		: 4-bit LCd interface
// Author		: Ahmed Osama
// Date			: Mar 5 2019
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#include "char_lcd.h"
#include "softwareDelay.h"
#include <stdlib.h>
#include "../../MCAL/DIO/DIO.h"
/*lcd states*/
#define LCD_IDLE			0
#define LCD_INIT_CMD0		1
#define LCD_INIT_CMD1		2
#define LCD_INIT_CMD2		3
#define LCD_INIT_CMD3		4
#define LCD_INIT_CMD4		5
#define LCD_INIT_CMD5		6
#define LCD_INIT_CMD6		7
#define LCD_INIT_FIN		8
#define LCD_READY			9
#define LCD_POSITION_UPDATE 10
#define LCD_CLEAR			11

static uint8_t row = 0;
static uint8_t colum = 0;

#define FIRST_RAW			0
#define SECOND_RAW			1
#define LCD_MAX_CLUM			16/*LCD END OF LINE*/
#define LCD_MAX_RAW			2/*LCD END OF ROWS*/
uint8_t gu8_lcdBuffer[LCD_ROWS][LCD_COLUMS] = {{"Hellow World!"},{"End of the world"}};
static	uint8_t gu8_lcdState;

void LCD_EN_pulse(void){
	DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);
}

void LCD_config_pins(void){

	/* set LCD pins as outputs */
	gpioPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	gpioPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
	gpioPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);

	gpioPinDirection(LCD_D4_PORT, LCD_D4_PIN, OUTPUT);
	gpioPinDirection(LCD_D5_PORT, LCD_D5_PIN, OUTPUT);
	gpioPinDirection(LCD_D6_PORT, LCD_D6_PIN, OUTPUT);
	gpioPinDirection(LCD_D7_PORT, LCD_D7_PIN, OUTPUT);
}

void LCD_send_nibble(uint8_t data){
	uint8_t mask = 1;
	data >>= 4;
	if(data&mask)
		DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
	else
		DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

	mask *= 2;
	if(data&mask)
		DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
	else
		DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

	mask *= 2;
	if(data&mask)
		DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
	else
		DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

	mask *= 2;
	if(data&mask)
		DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
	else
		DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
}

void LCD_send_char(uint8_t data)		//Sends Char to LCD
{
	DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
}
void LCD_send_command(uint8_t data)	//Sends Command to LCD
{
	DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();
	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
}
void LCD_init(void)//Initializes LCD
{
	//uint8_t u8_funStatus = OK;
	static uint8_t u8_LCD_initState = LCD_INIT_CMD0;
	switch(u8_LCD_initState)
	{
		case LCD_INIT_CMD0:
			LCD_config_pins();
			LCD_send_command(0x33);
			u8_LCD_initState = LCD_INIT_CMD1;
		break;
		case LCD_INIT_CMD1:
			LCD_send_command(0x32);
			u8_LCD_initState = LCD_INIT_CMD2;
		break;
		case LCD_INIT_CMD2:
			LCD_send_command(Four_bit); // 4-bit
			u8_LCD_initState = LCD_INIT_CMD3;
		break;
		case LCD_INIT_CMD3:
			LCD_send_command(Cursor_on);
			u8_LCD_initState = LCD_INIT_CMD4;
		break;
		case LCD_INIT_CMD4:
			LCD_send_command(Lcd_clear);
			u8_LCD_initState = LCD_INIT_CMD5;
		break;
		case LCD_INIT_CMD5:
			LCD_send_command(Increment_cursor);
			u8_LCD_initState = LCD_INIT_CMD6;
		break;
		case LCD_INIT_CMD6:
			LCD_send_command(Cursor_off); // Cursor of
			gu8_lcdState = LCD_READY;
		break;
	}

}
void LCD_clear(void)				//Clears LCD
{
	/*after clearing go to postion zero and zero and go to state update position*/
	LCD_send_command(Lcd_clear);
	row = ZERO;
	colum = ZERO;
	gu8_lcdState = LCD_POSITION_UPDATE;
}
void LCD_send_string(uint8_t* data)	//Outputs string to LCD
{
	
	while(*data){
		LCD_send_char(*data++);
	}
}

void LCD_goto_xy(uint8_t row, uint8_t colum)	//Cursor to X Y position
{
	uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(row)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+colum; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+colum; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+colum; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+colum; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+colum;
	}
	// set data address
	LCD_send_command(1<<LCD_DDRAM | DDRAMAddr);

}


ERROR_STATUS lcd_dispatcher(void)
{
	uint8_t u8_funStatus= OK;
	TCNT1L = gu8_lcdState;
	switch(gu8_lcdState)
	{
		case LCD_IDLE:
			LCD_init();
		break;
		case LCD_READY:
			LCD_send_char(gu8_lcdBuffer[row][colum]);
			++colum;
			if (colum == LCD_MAX_CLUM)
			{
				/*go to first culm in next line*/
				colum = ZERO;
				++row;
				/*if line > max lcd lines zero line*/
				if (row == LCD_MAX_RAW)
					row = ZERO;
				/*change state to update curser*/
				gu8_lcdState = LCD_POSITION_UPDATE;
			}
		break;
		
		case LCD_POSITION_UPDATE:
			LCD_goto_xy(row,colum);
			/*if (row == ZERO && colum == ZERO) / *first place clear lcd* /
				gu8_lcdState = LCD_CLEAR;
			else*/
				gu8_lcdState = LCD_READY;
		break;
		
		/*case LCD_CLEAR: / *clear lcd and go to LCD_READY STATE* /
			LCD_clear();
			gu8_lcdState = LCD_READY;
		break;*/
	}
	return u8_funStatus;
}
/*---Modification----------------------------------------------------------------------------------------------*/

// inline function to swap two numbers
inline void swap(uint8_t *x, uint8_t *y) {
   uint8_t t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
uint8_t* reverse(uint8_t *buffer, uint32_t i, uint32_t j)
{
   while (i < j)
   swap(&buffer[i++], &buffer[j--]);

   return buffer;
}

// Iterative function to implement itoa() function in C
uint8_t* itoa_(uint32_t value, uint8_t* buffer, uint32_t base)
{
   // invalid input
   if (base < 2 || base > 32)
   return buffer;

   // consider absolute value of number
   int n = abs(value);

   int i = 0;
   while (n)
   {
      int r = n % base;

      if (r >= 10)
      buffer[i++] = 65 + (r - 10);
      else
      buffer[i++] = 48 + r;

      n = n / base;
   }

   // if number is 0
   if (i == 0)
   buffer[i++] = '0';

   // If base is 10 and value is negative, the resulting string
   // is preceded with a minus sign (-)
   // With any other base, value is always considered unsigned
   if (value < 0 && base == 10)
   buffer[i++] = '-';

   buffer[i] = '\0'; // null terminate string

   // reverse the string and return it
   return reverse(buffer, 0, i - 1);
}

ERROR_STATUS LCD_setNewBuffer(uint8_t * u8_firstRow,uint8_t * u8_secondRow)
{
	ERROR_STATUS U8_funStatus = OK;
	uint8_t u8_counter = 0 ;
	
	/*
	*	1-set new data to buffer.
	*	2-clear LCD.
	*
	*/
	while(u8_counter < LCD_MAX_CLUM)
	{
		TCNT2 = 5;
		gu8_lcdBuffer[FIRST_RAW][u8_counter] = u8_firstRow[u8_counter];
		gu8_lcdBuffer[SECOND_RAW][u8_counter] = u8_secondRow[u8_counter];
		u8_counter++;
	}
	//LCD_clear();
	return U8_funStatus;
}
