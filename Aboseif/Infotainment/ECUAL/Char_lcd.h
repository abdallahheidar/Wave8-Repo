/*
 * Char_lcd.c
 *
 * Created: 2020-03-13 9:43:14 PM
 * Author : EbrahimOseif
 */

#ifndef CHAR_LCD_H_
#define CHAR_LCD_H_

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "DIO.h"

/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/

/* define MCU pin connected to LCD RS */
#define LCD_RS_PIN	    BIT1 	
#define LCD_RS_PORT	    GPIOA
		
/* define MCU pin connected to LCD R/W	*/				    
#define LCD_RW_PIN	    BIT2 	
#define LCD_RW_PORT	    GPIOA

/* define MCU pin connected to LCD E	*/				    
#define LCD_EN_PIN	    BIT3	
#define LCD_EN_PORT	    GPIOA

/* define MCU pin connected to LCD D4	*/				    
#define LCD_D4_PIN	    BIT4	
#define LCD_D4_PORT	    GPIOA

/* define MCU pin connected to LCD D5	*/				    
#define LCD_D5_PIN	    BIT5	
#define LCD_D5_PORT	    GPIOA

/* define MCU pin connected to LCD D6	*/				    
#define LCD_D6_PIN	    BIT6	
#define LCD_D6_PORT	    GPIOA

/* define MCU pin connected to LCD D7 */					    
#define LCD_D7_PIN	    BIT7	
#define LCD_D7_PORT	    GPIOA


/* LCD Commands definition from instruction table */

#define LCD_CLEAR				0x01
#define CURSOR_RETURN_HOME      0x02

#define CURSOR_DECREMENT		0x04
#define CURSOR_INCREMENT		0x06

#define SHIFT_DISPLAY_RIGHT		0x05
#define SHIFT_DISPLAY_LEFT		0x07

#define SHIFT_CURSOR_LEFT		0x10
#define SHIFT_CURSOR_RIGHT		0x14

#define FOUR_BIT_MODE           0x28
#define EIGHT_BIT_MODE          0x38

#define CURSOR_OFF				0x0C
#define CURSOR_ON				0x0E

#define   COLUMNS_NUMBER		16
#define   ROWS_NUMBER			4

/* LCD rows */
#define    LINE0				0
#define    LINE1				1
#define    LINE2				2
#define    LINE3				3

/* DDRAM mapping */
#define  LCD_SET_POSITION      0x60
#define LCD_DDRAM               7	/*bit7 that set the DDRAM Address*/

#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

/* SOS IMPLEMENTATION */
#define  CMD_Buff_Size		64
#define  Data_Buff_Size		64

#define  SEND_UPPER_NIBBLE  0
#define  SEND_LOWER_NIBBLE  1

#define  CMD_TURN	1
#define  DATA_TURN  2




/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/


/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send enable pulse to the lcd .
 * 							
 */
ERROR_STATUS LCD_enablePulse(void);

/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: configure the lcd pins .
 * 							
 */
ERROR_STATUS LCD_configurePins(void); 

/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send 4bits to the lcd .
 * 							
 */
ERROR_STATUS LCD_sendNibble(uint8_t u8_data); 

/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send byte to the lcd .
 * 							
 */
ERROR_STATUS LCD_sendByte(uint8_t u8_data);
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send command to the lcd .
 * 							
 */
ERROR_STATUS LCD_sendCMD(uint8_t u8_data);	
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initializes LCD .
 * 							
 */
ERROR_STATUS LCD_init(void);			
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Clears LCD .
 * 							
 */
ERROR_STATUS LCD_clear(void);				
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send  string to LCD the lcd .
 * 							
 */
ERROR_STATUS LCD_sendString(uint8_t* u8_data);	
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: move cursor to X Y position .
 * 							
 */
ERROR_STATUS LCD_goto_RowColumn(uint8_t u8_row, uint8_t u16_column);

/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: the main function of the lcd  .
 * 							
 */
ERROR_STATUS LCD_Dispatcher(void);



#endif // LCD_H_

