/*
 ============================================================================
 Name        : LCD.c
 Author      : Muhammed Gamal
 Description : This File Includes The Functions Implementation Of The LCD Driver
 ============================================================================
 */


#include "lcd.h"

uint8_t gu8_String_CompleteFlag=0;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */

	#if (DATA_BITS_MODE == 4)

		LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8_t command)
{
	/*NOTE THAT:
	 * ALL The LCD Delays Has Been Removed Since It's Too Small
	 * And The SOS Tick Is 1ms
	 */

	CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits  */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif

	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */

	/* out the lowest 4 bits  */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif

	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* out the required command  */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
#endif
}

void LCD_displayCharacter(uint8_t data)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	SET_BIT(LCD_CTRL_PORT,E);

#if (DATA_BITS_MODE == 4)

#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif

	CLEAR_BIT(LCD_CTRL_PORT,E);
	SET_BIT(LCD_CTRL_PORT,E);

	/* out the lowest 4 bits  */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif

	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* out the required command  */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
#endif
}

void LCD_displayString(const char *Str)
{
	static uint8_t i = 0;
	if(Str[i] != '\0')
	{
		gu8_String_CompleteFlag=0;
		LCD_displayCharacter(Str[i]);
		i++;
	}
	else
	{
		gu8_String_CompleteFlag=1;
	}
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t Address;

	/* calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}
	/* to write to a specific address in the LCD
	 * I need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}


void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); /*clear display*/
}
