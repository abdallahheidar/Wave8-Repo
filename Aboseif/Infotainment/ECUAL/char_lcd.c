 /*
 * Char_lcd.h
 *
 * Created: 2020-03-13 9:43:14 PM
 * Author : EbrahimOseif
 */


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "char_lcd.h"
#include "softwareDelay.h"
#include "DIO.h"
#include "Error.h"





uint8_t gu8_LCD_InitState;

uint8_t au8_CMD_Buffer[CMD_Buff_Size]; 
uint8_t gu8_CMD_Index;
uint8_t gu8_CMDState;

uint8_t au8_Data_Buffer[Data_Buff_Size];
uint8_t gu8_Data_Index;
uint8_t gu8_DataState;

uint8_t gu8_CMD_Counter = 0;
uint8_t gu8_Data_Counter = 0;

uint8_t gu8_turnState  = CMD_TURN;



/************************************************************************/
/*					 FUNCTIONS implementation		                    */
/************************************************************************/


/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: configure the lcd pins .
 * 							
 */
ERROR_STATUS LCD_configurePins(void){
	
	ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;

	DIO_Cfg_s ST_dio = {0};
	
	/* set LCD RS pins as outputs */

	ST_dio.GPIO = LCD_RS_PORT;
	ST_dio.pins = LCD_RS_PIN;
	ST_dio.dir = OUTPUT;
	ERR_Status = DIO_init(&ST_dio);
	
	/* set LCD RW pins as outputs */
	ST_dio.GPIO = LCD_RW_PORT;
	ST_dio.pins = LCD_RW_PIN;
	ERR_Status = DIO_init(&ST_dio);
	
	/* set LCD ENABLE pin as outputs */
	ST_dio.GPIO = LCD_EN_PORT;
	ST_dio.pins = LCD_EN_PIN;
	ERR_Status = DIO_init(&ST_dio);


	/* set LCD RS pins as outputs */
	
	/*
	ST_dio.GPIO = LCD_D4_PORT;
	ST_dio.pins = LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN;
	DIO_init(&ST_dio);
	*/
	
	ST_dio.GPIO = LCD_D4_PORT;
	ST_dio.pins = LCD_D4_PIN;
	ERR_Status = DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D5_PORT;
	ST_dio.pins = LCD_D5_PIN;
	ERR_Status = DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D6_PORT;
	ST_dio.pins = LCD_D6_PIN;
	ERR_Status = DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D7_PORT;
	ST_dio.pins = LCD_D7_PIN;
	ERR_Status = DIO_init(&ST_dio);
	
	return ERR_Status;
}

/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send enable pulse to the lcd .
 * 							
 */
ERROR_STATUS LCD_enablePulse(void){
	
		ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;


	ERR_Status = DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	softwareDelayMs(1);
	ERR_Status = DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);
	softwareDelayMs(1);
	
	return ERR_Status;
}


/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send 4bits to the lcd .
 * 							
 */
ERROR_STATUS LCD_sendNibble(uint8_t u8_data){
	
	ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;

	uint8_t u8_mask = 1;
	u8_data >>= 4;
	
	if(u8_data & u8_mask)
	     ERR_Status =  DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
	else
	     ERR_Status =  DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

	u8_mask *= 2;
	if(u8_data & u8_mask)
	    ERR_Status =   DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
	else
		ERR_Status =  DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

	u8_mask *= 2;
	if(u8_data & u8_mask)
		ERR_Status =  DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
	else
		ERR_Status =  DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

	u8_mask *= 2;
	if(u8_data & u8_mask)
		ERR_Status =  DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
	else
		ERR_Status =  DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
		  
		 
		 /* WITHOUT SHIFT OR MASK TO REPLACE THE ABOVE LOGIC
		  if(u8_data & LCD_D4_PIN)
		  {
			  DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
		  }
		  else
		  {
			  DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);
		  }

		  if(u8_data & LCD_D5_PIN)
		  {
			  DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
		  }
		  else
		  {
			  DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);
		  }
		  if(u8_data & LCD_D6_PIN)
		  {
			  DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
		  }
		  else
		  {
			  DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);
		  }
		  if( u8_data & LCD_D7_PIN)
		  {
			  DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
		  }
		  else
		  {
			  DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
		  } 
		  */
		 
		 return ERR_Status;
	
}

/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send byte to the lcd .
 * 							
 */
ERROR_STATUS LCD_sendByte(uint8_t u8_data)		
{
	
	/*ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;

	/ * RS is high to send data * /
	ERR_Status = DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);
	
	/ * Higher nibble first * /
	
	ERR_Status = LCD_sendNibble(u8_data); 
	ERR_Status = LCD_enablePulse();
	
	/ * lower nibble next * /
	ERR_Status = LCD_sendNibble(u8_data<<4);
	ERR_Status = LCD_enablePulse();
	
	softwareDelayMs(1);
	
	return ERR_Status;*/
	
	 ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;
	 
	 if (gu8_Data_Index < Data_Buff_Size)
	 {
		 au8_Data_Buffer[gu8_Data_Index] = u8_data;
		 gu8_Data_Index++;
	 }
	 else
	 {
		 ERR_Status = LCD_ERROR_BASE + ERROR_FULL_BUFFER;
	 }
	 return ERR_Status;
 }


/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send command to the lcd .
 * 							
 */
ERROR_STATUS LCD_sendCMD(uint8_t u8_data)	//Sends Command to LCD
{

       ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;
       
       	/* RS is low to send cmd */
       ERR_Status = DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);
       
       /* Higher nibble first */
       
       ERR_Status = LCD_sendNibble(u8_data);
       ERR_Status = LCD_enablePulse();
       
       /* lower nibble next */
       ERR_Status = LCD_sendNibble(u8_data<<4);
       ERR_Status = LCD_enablePulse();
       
       softwareDelayMs(1);
       
	   
       return ERR_Status;
	   
	  /* ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;
	   
		   if (gu8_CMD_Index < CMD_Buff_Size)
		   {
			   au8_CMD_Buffer[gu8_CMD_Index] = u8_data;
			   gu8_CMD_Index++;
		   }
		   else
		   {
				ERR_Status = LCD_ERROR_BASE + ERROR_FULL_BUFFER;
		   }
		   return ERR_Status;*/
	  

}

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Clears LCD .
 * 							
 */
ERROR_STATUS LCD_clear(void)				
{
	       ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;

	ERR_Status = LCD_sendCMD(LCD_CLEAR);
	
	return ERR_Status;
}


/**
 * Input :  u8_DataLength data length 4 bit or 8 bit 
 *			u8_cursorMode	allow cusror on or off 
 *			u8_cursorChange	how cursor changes
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initializes the function of LCD .
 * 							
 */

ERROR_STATUS LCD_FunctionConfigure(uint8_t u8_DataLength, uint8_t u8_cursorMode, uint8_t u8_cursorChange ){
	
	   ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;

	ERR_Status = LCD_sendCMD(0x33);
	ERR_Status = LCD_sendCMD(0x32);
	ERR_Status = LCD_sendCMD(u8_DataLength); 
	ERR_Status = LCD_sendCMD(u8_cursorMode);
	ERR_Status = LCD_sendCMD(u8_cursorChange);
	ERR_Status = LCD_clear();

	return ERR_Status;
}



/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initializes LCD .
 * 							
 */
ERROR_STATUS LCD_init(void)
{
		   ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;
		   gu8_LCD_InitState = NOT_INITIALIZED;

	ERR_Status =  LCD_configurePins();

	softwareDelayMs(10);
	
	ERR_Status = LCD_FunctionConfigure(FOUR_BIT_MODE, CURSOR_ON, CURSOR_INCREMENT);
	
	/*softwareDelayMs(10);*/
	gu8_LCD_InitState = INITIALIZED;
	
	return ERR_Status;
}
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: send  string to LCD the lcd .
 * 							
 */
ERROR_STATUS LCD_sendString(uint8_t* u8_data)	
{
	   ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;
	if (u8_data == NULL)
	{
		ERR_Status = LCD_ERROR_BASE + ERROR_NULL_POINTER;
	}else
	{
		while(*u8_data != '\0'){
			ERR_Status = LCD_sendByte(*u8_data++);
		}
	}
	
	return ERR_Status;
}
/**
 * Input: . 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: move cursor to X Y position .
 * 							
 */
ERROR_STATUS LCD_goto_RowColumn(uint8_t u8_row, uint8_t u16_column)
{
	
		   ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;

	uint8_t DDRAMAddr;
	
	if (u8_row > ROWS_NUMBER || u16_column > COLUMNS_NUMBER)
	{
		ERR_Status = LCD_ERROR_BASE + ERROR_OUT_OF_RANGE;
	}
	else
	{
		/* set the order of lines with DDRAM address */
		
		switch(u8_row)
		{
			case LINE0: DDRAMAddr = LCD_LINE0_DDRAMADDR + u16_column;   break;
			case LINE1: DDRAMAddr = LCD_LINE1_DDRAMADDR + u16_column;   break;
			case LINE2: DDRAMAddr = LCD_LINE2_DDRAMADDR + u16_column;   break;
			case LINE3: DDRAMAddr = LCD_LINE3_DDRAMADDR + u16_column;   break;
			
			default:
				 break;
/*
			DDRAMAddr = LCD_LINE0_DDRAMADDR + u16_column;
*/
			
		}
		
		/* set data address */
		ERR_Status = LCD_sendCMD(1 << LCD_DDRAM | DDRAMAddr);
	
	}
	
	return ERR_Status;
}

ERROR_STATUS LCD_Dispatcher(void)
{
		   ERROR_STATUS ERR_Status = LCD_ERROR_BASE + NO_ERRORS;
		   
	
	
	/*if (gu8_LCD_InitState == NOT_INITIALIZED)
	{
		ERR_Status = LCD_ERROR_BASE + ERROR_NOT_INITIALIZED;
	}
	else
	 if (au8_CMD_Buffer[gu8_CMD_Counter] != 0  / *&& gu8_CMD_Index > gu8_Data_Index* /)
	{
		DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);
		switch (gu8_CMDState)
		{
			case SEND_UPPER_NIBBLE:
			
			LCD_sendNibble(au8_CMD_Buffer[gu8_CMD_Counter]); // Higher nibble first
			LCD_enablePulse();
			gu8_CMDState = SEND_LOWER_NIBBLE;
			break;
			
			case SEND_LOWER_NIBBLE:
			
			LCD_sendNibble((au8_CMD_Buffer[gu8_CMD_Counter])<<4);
			LCD_enablePulse();

			au8_CMD_Buffer[gu8_CMD_Counter]=0;
			gu8_CMD_Counter++;
			
			gu8_CMDState = SEND_UPPER_NIBBLE;
			break;
			
			default:
					break;
		}
		//gu8_turnState == DATA_TURN;
	}
	else */ 
	if (au8_Data_Buffer[gu8_Data_Counter] !=0 /*&& gu8_turnState == DATA_TURN*/)
	{
		DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);
		switch (gu8_DataState)
		{
			case SEND_UPPER_NIBBLE:
			LCD_sendNibble(au8_Data_Buffer[gu8_Data_Counter]); // Higher nibble first
						LCD_enablePulse();

			gu8_DataState = SEND_LOWER_NIBBLE;
			break;
			
			case SEND_LOWER_NIBBLE:
			LCD_sendNibble(((au8_Data_Buffer[gu8_Data_Counter])<<4));
						LCD_enablePulse();

			
			au8_Data_Buffer[gu8_Data_Counter]=0;
			gu8_Data_Counter++;
			
			gu8_DataState = SEND_UPPER_NIBBLE;
			break;
			
			default:
						break;
		}
		//gu8_turnState = CMD_TURN;
	}
	else
	{
		//LCD_sendNibble('a');
		gu8_Data_Index = 0;
		gu8_CMD_Index = 0;
		gu8_CMD_Counter = 0;
		gu8_Data_Counter = 0;
		
	}
	return ERR_Status ;
}
