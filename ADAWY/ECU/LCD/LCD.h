/*
 * LCD.h
 *
 * Created: 3/12/2020 11:49:22 AM
 *  Author: Khaled
 */ 


#ifndef LCD_H_
#define LCD_H_

/*************************************************************/
/************************* INCLUDES *************************/
/***********************************************************/

#include "../../MCAL/DIO/DIO.h"
#include "../../SERVICE/ERROR/ERROR-STORE.h"
 #include "LCD_Cfg.h"

/*************************************************************/
/*********************** GLOBAL MACROS **********************/
/***********************************************************/







/*************************************************************/
/****************** EXTERN GLOBAL VARIABLES *****************/
/***********************************************************/
extern uint8_t gu8_LCD_InitFlag;
extern uint8_t gu8_LCD_SencCommandFlag;
extern uint8_t gu8_LCD_DisplayCharFlag;
extern uint8_t gu8_LCD_DisplayStringFlag;
extern uint8_t gu8_LCD_DisplayStringRowColumnFlag;
extern  uint8_t gu8_LCD_GoToRowColumFlag;


/*************************************************************/
/***************** APIS FUNCTION PROTOTYPE ******************/
/***********************************************************/

/**
* Input: 
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Initiates the LCD.
*
*/
extern ERROR_STATUS LCD_init (void);

/**
* Input: Command need to execute.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: execute LCD command.
*
*/
extern ERROR_STATUS LCD_SendCommand (uint8_t Command);

/**
* Input: address of needed char in the LCD CGROM (ASCI).
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Display a character on LCD.
*
*/
extern ERROR_STATUS LCD_DisplayChar (uint8_t LCD_Char);

/**
* Input: Pointer to a string and string size.
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Display a string on LCD.
*
*/
extern ERROR_STATUS LCD_DisplayString (uint8_t * LCD_String, uint8_t String_Size);

/**
* Input: Pointer to a string and string size and position (0:31).
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Display a string on LCD on specific position.
*
*/
extern ERROR_STATUS LCD_DisplayStringRowColumn (const uint8_t * LCD_String, uint8_t String_Size, uint8_t Pos);

/**
* Input:
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Clear the LCD.
*
*/
extern ERROR_STATUS LCD_Clear (void);

/**
* Input:  position on the LCD (0:31)
* Output:
* In/Out:
* Return: The error status of the function.
* Description: go to specific position on the LCD.
*
*/
extern ERROR_STATUS LCD_GoToRowColumn (uint8_t Pos);

#endif /* LCD_H_ */