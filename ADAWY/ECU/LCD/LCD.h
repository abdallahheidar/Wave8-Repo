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
#include "../../Delay.h"
#include "../../SERVICE/ERROR/ERROR-STORE.h"

/*************************************************************/
/*********************** GLOBAL MACROS **********************/
/***********************************************************/







/*************************************************************/
/********************** STRUCT TYPEDEF **********************/
/***********************************************************/






/*************************************************************/
/***************** APIS FUNCTION PROTOTYPE ******************/
/***********************************************************/
extern ERROR_STATUS LCD_init (void);
extern ERROR_STATUS LCD_SendCommand (uint8_t Command);
extern ERROR_STATUS LCD_DisplayChar (uint8_t LCD_Char);
extern ERROR_STATUS LCD_DisplayString (uint8_t * LCD_String, uint8_t String_Size);
extern ERROR_STATUS LCD_DisplayStringRowColumn (uint8_t * LCD_String, uint8_t String_Size, uint8_t Pos);
extern ERROR_STATUS LCD_Clear (void);
extern ERROR_STATUS LCD_GoToRowColumn (uint8_t Pos);

#endif /* LCD_H_ */