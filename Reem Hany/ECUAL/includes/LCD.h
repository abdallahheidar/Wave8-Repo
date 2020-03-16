/*
 * LCD.h
 *
 * Created: 3/13/2020 5:49:20 PM
 *  Author: Reem
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../Services/includes/std_types.h"
#include "../../Services/includes/common_macros.h"
#include "../../Services/includes/softwareDelay.h"
#include "../../MCAL/includes/DIO.h"

/******************************************************************************/
/*                           DEFINES                                          */
/******************************************************************************/
#define LCD_ERROR
#define LINE_1                             0
#define LINE_2                             1
#define LAST_LCD_COL                       15

extern ERROR_STATUS LCD_Init(void);
extern ERROR_STATUS LCD_ExecuteCommand(uint8_t Command);
extern ERROR_STATUS LCD_WriteData(uint8_t DataByte);
extern ERROR_STATUS LCD_WriteInt(sint32_t Number);
extern void LCD_Runnable(void);
extern ERROR_STATUS LCD_Clear(void);
extern ERROR_STATUS LCD_GoToXY(uint8_t row, uint8_t col);
ERROR_STATUS DisplayData(uint8_t * Data);



#endif /* LCD_H_ */