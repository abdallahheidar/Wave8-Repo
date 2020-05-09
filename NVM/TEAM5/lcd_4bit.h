
#ifndef _LCD_4BIT_H

	#define _LCD_4BIT_H

#define LCD_LINE0		         0x00
#define LCD_LINE1	             0x40
#define LCD_DDRAM                  7
#define LCD_CLEAR           	 0x01
void lcd_sendCommand(unsigned char cmd);
void lcd_displayChar(unsigned char data);
void lcd_init(void);
void lcd_gotoxy(unsigned char x , unsigned char y );
void lcd_clrScreen(void);
void lcd_dispString(char * ptr);
void lcd_disp_string_xy(char * ptr , int y , int x);


#endif  

