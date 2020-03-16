/*
 * LCD.c
 *
 * Created: 3/13/2020 5:49:37 PM
 *  Author: Reem
 */ 

#include "../includes/LCD_preCfg.h"
#include "../includes/LCD.h"
#include "../../Services/includes/softwareDelay.h"

#define LCD_BUFFER_SIZE     500

static uint8_t gau8LCDBuffer[LCD_BUFFER_SIZE]={0};
static uint8_t gu8LCD_BufferSize;
static uint8_t gu8LCD_BufferLockState;
// These variables should be initialized here because it will be checked in the beginning of the init function
static uint8_t gu8LCD_InitSTATE = _LCD_INIT_STATE1;
static uint8_t gu8_WriteState;
static uint8_t gu8LCDInitFlag = FALSE;
static uint8_t gu8LCDState = _LCD_IDLE;

/*****************************************************************/
/*                    Static prototype functions                 */
/*****************************************************************/


static ERROR_STATUS LCD_Enable(void);
static ERROR_STATUS LCD_SendingInfo(uint8_t InfoNibble);
static ERROR_STATUS LCD_WriteStr(uint8_t * DataStr);

static ERROR_STATUS LCD_SendingInfo(uint8_t InfoNibble)
{
	ERROR_STATUS ERR;
	
	if(InfoNibble%2)
	ERR = DIO_Write(LCD_PORT,LCD_DATA_4,HIGH);
	else
	ERR = DIO_Write(LCD_PORT,LCD_DATA_4,LOW);
	
	InfoNibble>>=1;
	
	if(InfoNibble%2)
	ERR = DIO_Write(LCD_PORT,LCD_DATA_5,HIGH);
	else
	ERR = DIO_Write(LCD_PORT,LCD_DATA_5,LOW);
	
	InfoNibble>>=1;
	
	if(InfoNibble%2)
	ERR = DIO_Write(LCD_PORT,LCD_DATA_6,HIGH);
	else
	ERR = DIO_Write(LCD_PORT,LCD_DATA_6,LOW);
	
	InfoNibble>>=1;
	
	if(InfoNibble%2)
	ERR = DIO_Write(LCD_PORT,LCD_DATA_7,HIGH);
	else
	ERR = DIO_Write(LCD_PORT,LCD_DATA_7,LOW);
//	ERR = LCD_Enable();
	
	return ERR;
	
}

static ERROR_STATUS LCD_Enable(void)
{
	ERROR_STATUS ERR = LCD_ERROR + E_INVALID_PARAMETER;;
	
	ERR = DIO_Write(LCD_PORT,LCD_EN,HIGH);
	ERR = DIO_Write(LCD_PORT,LCD_EN,LOW);
	return ERR;
}

ERROR_STATUS LCD_Init(void)
{
	ERROR_STATUS ERR = LCD_ERROR + E_INVALID_PARAMETER;
	if (gu8LCDInitFlag)
	{
		ERR = LCD_ERROR + E_MULTIPLE_INITIALIZION;
	}
	else
	{
		#if _4_BIT_MODE == ENABLE
		
		strDIO_Cfg_s astr_DIOcfg={ LCD_PORT,
			(LCD_RS|LCD_RW|LCD_EN|LCD_DATA_4|LCD_DATA_5|LCD_DATA_6|LCD_DATA_7),
		OUTPUT};
		
		switch(gu8LCD_InitSTATE)
		{
			case _LCD_INIT_STATE1:
		
			ERR = DIO_init(&astr_DIOcfg);
			gu8LCD_InitSTATE = _LCD_INIT_STATE2;
			break;
			
			case _LCD_INIT_STATE2:
			
			ERR = LCD_ExecuteCommand(_LCD_4BIT_INIT_CMD);
			ERR = LCD_ExecuteCommand(_LCD_2_LINE_CMD);
			ERR = LCD_ExecuteCommand(_LCD_CURSOR_OFF_CMD);
			ERR = LCD_ExecuteCommand(_LCD_CURSOR_SHIFT_TO_RIGHT_CMD);
			ERR = LCD_Clear();
			
			gu8LCD_InitSTATE = _LCD_INIT_STATE3;
			
			break;
			case _LCD_INIT_STATE3:
			
			gu8LCD_InitSTATE = _LCD_INIT_STATE4;
			break;
			
			case _LCD_INIT_STATE4:
			
			gu8LCD_BufferSize =0;
			gu8LCD_BufferLockState = _LCD_BUFFER_UNLOCKED;
			gu8LCDInitFlag = TRUE;
			ERR =E_TASK_DONE;
			break;
		}	
		#else
		ERR = LCD_ERROR + E_INVALID_PARAMETER;
		#endif
	}
	
	return ERR;
}

ERROR_STATUS LCD_ExecuteCommand(uint8_t Command)
{
	ERROR_STATUS ERR;
	
	
	#if _4_BIT_MODE == ENABLE
	
	uint8_t commandHigherNibble = GET_NIBBLE_HIGH(Command);
	uint8_t commandLowerNibble  = GET_NIBBLE_LOW(Command);

		
	//Command Register selection
	DIO_Write(LCD_PORT,LCD_RS, LOW);
	//Write option selection
	DIO_Write(LCD_PORT,LCD_RW, LOW);
		
	//Sending the higher nibble first
		
	//Load Higher command nibble on the 4 bit data pins
		
		
	ERR = LCD_SendingInfo(commandHigherNibble);
	ERR =LCD_Enable();
		
	//Sending the lower nibble
		
	//Load Lower command nibble on the 4 bit data pins

	ERR = LCD_SendingInfo(commandLowerNibble);
	ERR = LCD_Enable();
	#endif
	return ERR;
	
}

ERROR_STATUS LCD_WriteData(uint8_t DataByte)
{
	ERROR_STATUS ERR =E_NOK;
	
	if (gu8LCDInitFlag)
	{
		static uint8_t au8_counter;
		#if _4_BIT_MODE == ENABLE
		uint8_t dataHigherNibble = GET_NIBBLE_HIGH(DataByte);
		uint8_t dataLowerNibble  = GET_NIBBLE_LOW(DataByte);
		switch(gu8_WriteState)
		{
			case _LCD_WRITE_STATE1:
			//Data Register selection
			ERR=DIO_Write(LCD_PORT,LCD_RS, HIGH);
			//Write option selection
			ERR=DIO_Write(LCD_PORT,LCD_RW, LOW);
			
			/*Sending the higher nibble first*/
			
			//Load Higher data nibble on the 4 bit data pins
			ERR=LCD_SendingInfo(dataHigherNibble);
			LCD_Enable();
			
			/*Sending the lower nibble*/
			
			//Load Lower data nibble on the 4 bit data pins

			ERR=LCD_SendingInfo(dataLowerNibble);
			LCD_Enable();
			gu8_WriteState = _LCD_WRITE_STATE2;
			break;
			case _LCD_WRITE_STATE2:
			au8_counter++;
			if (au8_counter ==5)
			{
				ERR = _LCD_WRITE_DONE;
				gu8_WriteState = _LCD_WRITE_STATE1;
			}
			break;
		}
		
	
		//softwareDelayMs(5);
		
		
		#endif
	}
	else
	{
		ERR = LCD_ERROR + E_UNINITIALIZED_MODULE;
	}
	return ERR;
}

static ERROR_STATUS LCD_WriteStr(uint8_t * DataStr)
{
	ERROR_STATUS ERR;
	uint8_t* str = NULL;
	static uint8_t au8_BufferIterator_i,au8_BufferIterator_j;
	
	if(gu8LCDInitFlag)
	{
		str = DataStr;
	
		if(DataStr == NULL)
		{
			ERR =LCD_ERROR + E_NULL_PTR;
		}
		else
		{
			ERR = LCD_ERROR + E_INVALID_PARAMETER;
			while(au8_BufferIterator_i<gu8LCD_BufferSize)
			{
				
				if (au8_BufferIterator_j == LINE_1_LAST_CHAR_POS+ONE)
				{
					LCD_GoToXY(LINE_2,ZERO);
					softwareDelayMs(5);
				}
				else if (au8_BufferIterator_j ==LINE_2_LAST_CHAR_POS+ONE)
				{
					LCD_Clear();
					LCD_GoToXY(LINE_1,ZERO);
					au8_BufferIterator_j=0;
				}
				ERR = LCD_WriteData(str[au8_BufferIterator_i]);
				
				if (ERR == _LCD_WRITE_DONE)
				{
					au8_BufferIterator_i++;
					au8_BufferIterator_j++;
				}
				
			}
			ERR = E_TASK_DONE;
			gu8LCD_BufferLockState = _LCD_BUFFER_UNLOCKED;
			au8_BufferIterator_i=0;
			au8_BufferIterator_j=0;
			gu8LCD_BufferSize=0;
		}
	}
	else
	{
		ERR = LCD_ERROR + E_UNINITIALIZED_MODULE;
	}
	
	return ERR;
}
ERROR_STATUS LCD_Clear(void)
{
	ERROR_STATUS ERR = LCD_ExecuteCommand(_LCD_CLR);
	return ERR;
}
//ERROR_STATUS LCD_WriteInt(sint32_t Number);
void LCD_Runnable(void)
{
	ERROR_STATUS ERR =E_NOK;
	switch(gu8LCDState)
	{
		case _LCD_IDLE:
		ERR = LCD_Init();
		
		if (ERR ==E_TASK_DONE)
		{
			gu8LCDState = _LCD_BUSY;
		}
		
		break;
		case _LCD_BUSY:
		
		if (gu8LCDState == _LCD_BUFFER_LOCKED)
		{
			
			gu8_WriteState = _LCD_WRITE_STATE1;
			ERR =LCD_WriteStr(gau8LCDBuffer);
		}
		break;
	}
	
}
ERROR_STATUS DisplayData(uint8_t * Data)
{
	ERROR_STATUS ERR;
	if (gu8LCDInitFlag == FALSE)
	{
		ERR = LCD_ERROR + E_NULL_PTR;
	}
	else
	{
		uint8_t * str = Data;
		static uint8_t xFlag;
		
		if (gu8LCD_BufferLockState == _LCD_BUFFER_UNLOCKED)
		{
			
			while((*str) != '\0')
			{
				gau8LCDBuffer[gu8LCD_BufferSize] = (*str);
				gu8LCD_BufferSize++;
				str++;
			}
			gu8LCD_BufferLockState = _LCD_BUFFER_LOCKED;
			ERR= E_OK;
			LCD_Clear();
		}
		
		
	}
	return ERR;
}
ERROR_STATUS LCD_GoToXY(uint8_t row, uint8_t col)
{
	ERROR_STATUS ERR;
	if(gu8LCDInitFlag == FALSE)
	{
		ERR = LCD_ERROR + E_UNINITIALIZED_MODULE;
	}
	else
	{
		if ((row != LINE_1 && row != LINE_2 )||(col > LAST_LCD_COL))
		{
			ERR = LCD_ERROR + E_INVALID_PARAMETER;
		}
		else
		{
			if(row == LINE_1)
				ERR = LCD_ExecuteCommand(DDRAM+LINE_1_FIRST_CHAR+col);
			else
				ERR = LCD_ExecuteCommand(DDRAM+LINE_2_FIRST_CHAR+col);
		}
	}
	return ERR;
}