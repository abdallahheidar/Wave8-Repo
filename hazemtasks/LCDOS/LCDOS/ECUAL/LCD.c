/*
 * LCD.c
 *
 * Created: 3/15/2020 11:16:04 AM
 *  Author: hazem
 */ 
/*- INCLUDES ----------------------------------------------*/
#include "LCD.h"

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
static void LCD_EN_pulse(void);
static void LCD_send_nibble(uint8_t data);
/*- LOCAL FUNCTIONS implementation ----------------------------*/

 static void LCD_EN_pulse(void)
{
	DIO_Write(str_lcdEnconfig.GPIO, str_lcdEnconfig.pins, HIGH);
	DIO_Write(str_lcdEnconfig.GPIO, str_lcdEnconfig.pins, LOW);
}

static void LCD_send_nibble(uint8_t data)
{
	uint8_t u8_mask = 1;
	data >>= 4;
	if(data&u8_mask)
	DIO_Write(LCD_D4_GPIO, LCD_D4_PIN, HIGH);
	else
	DIO_Write(LCD_D4_GPIO, LCD_D4_PIN, LOW);
	u8_mask *= 2;
	if(data&u8_mask)
	DIO_Write(LCD_D5_GPIO, LCD_D5_PIN, HIGH);
	else
	DIO_Write(LCD_D5_GPIO, LCD_D5_PIN, LOW);
	u8_mask *= 2;
	if(data&u8_mask)
	DIO_Write(LCD_D6_GPIO, LCD_D6_PIN, HIGH);
	else
	DIO_Write(LCD_D6_GPIO, LCD_D6_PIN, LOW);
	u8_mask *= 2;
	if(data&u8_mask)
	DIO_Write(LCD_D7_GPIO, LCD_D7_PIN, HIGH);
	else
	DIO_Write(LCD_D7_GPIO, LCD_D7_PIN, LOW);
}

/*- APIs IMPLEMENTATION -----------------------------------*/
ENMULCDERROR  LCD_init(void)
{
	DIO_init(&str_lcddataconfig);
	DIO_init(&str_lcdEnconfig);
	DIO_init(&str_lcdRSconfig);
	DIO_init(&str_lcdRWconfig);	
	DIO_Write(str_lcdRSconfig.GPIO, str_lcdRSconfig.pins, LOW);
	DIO_Write(str_lcdRWconfig.GPIO, str_lcdRWconfig.pins, LOW);
	DIO_Write(str_lcdEnconfig.GPIO, str_lcdEnconfig.pins, LOW);
	LCD_sendCommand(LCD_ST);
	LCD_sendCommand(gu8_lcdmode); 
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR);	
}


ENMULCDERROR  LCD_sendCommand(uint8_t u8_command)
{
	DIO_Write(str_lcdRSconfig.GPIO, str_lcdRSconfig.pins, LOW);
    LCD_send_nibble(u8_command);	
    LCD_EN_pulse();
    softwareDelayMs(1);
    LCD_send_nibble(u8_command<<4);
	LCD_EN_pulse();
    softwareDelayMs(1);
}



ENMULCDERROR LCD_displayChar(uint8_t u8_char)
{
	 DIO_Write(str_lcdRSconfig.GPIO, str_lcdRSconfig.pins, HIGH);
     LCD_send_nibble(u8_char);
	 LCD_EN_pulse();
     LCD_send_nibble(u8_char<<4);
	 LCD_EN_pulse();
}


ENMULCDERROR  LCD_displayString(uint8_t au8_char[])
{
	uint8_t u8_counter=0;
	while(au8_char[u8_counter]!='\0')
	{
		LCD_displayChar(au8_char[u8_counter]);
		u8_counter++;
		softwareDelayMs(1);
	}
}