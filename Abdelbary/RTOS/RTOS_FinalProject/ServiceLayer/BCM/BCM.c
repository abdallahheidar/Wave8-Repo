
/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "BCM.h"
#include "../../MC_AL/UART/UART.h"
#include "../../COMMON/Errors.h"
/*************************************************************/
/*					 MACROS									 */
/*************************************************************/
#define UART_BAUDRATE_DESIRED					(9600)
#define BCM_TX_RX_FRAME_ID						('#')
#define BCM_NEXT_BYTE_IS_ID						(0)
#define BCM_NEXT_BYTE_IS_SIZE_LOWER_BYTE		(1)
#define BCM_NEXT_BYTE_IS_SIZE_HIGHER_BYTE		(2)
#define BCM_NEXT_BYTE_IS_DATA_BYTE				(3)
#define BCM_NEXT_BYTE_IS_NOTHING				(4)

/*************************************************************/
/*                     NEW TYPES DEFINITIONS                 */
/*************************************************************/
typedef enum enu_BCM_TxStates_t
{
	SEND_IDLE,
	SENDING_BYTE,
	SENDING_COMPLETE
}enu_BCM_TxStates_t;
static enu_BCM_TxStates_t genu_BCM_TxCurrentState;

typedef enum enu_BCM_RxStates_t
{
	RECEIVE_IDLE,
	RECEIVING_BYTE,
	RECEIVING_COMPLETE
}enu_BCM_RxStates_t;
static enu_BCM_RxStates_t genu_BCM_RxCurrentState;


typedef struct str_BCM_Frame_t
{
	uint8_t u8_BCM_Id;
	uint8_t u8_BCM_SizeLower;
	uint8_t u8_BCM_SizeHigher;
	uint8_t* pu8_BCM_Data;
	uint8_t u8_BCM_Checksum;
}str_BCM_Frame_t;

static str_BCM_Frame_t gstr_BCM_TxFrame;
static str_BCM_Frame_t gstr_BCM_RxFrame;

/*************************************************************/
/*                    GOLBAL STATIC VARIABLES                */
/*************************************************************/
UART_cfg_s gstr_UART_Config;
static uint8_t gu8_BCM_IsInitialized = FALSE;
static uint8_t gu8_BCM_IsTxFrameLocked;
static uint8_t gu8_BCM_TxFrameElement;
static uint16_t gu16_BCM_UserTxBufferCounter;
static uint16_t gu16_BCM_UserTxBufferSize;
static gptrfun_User_cbk_t gpfun_UserTxCbk;
volatile static uint8_t gu8_UART_TxFlag;

static uint8_t gu8_BCM_IsRxFrameLocked;
volatile static uint8_t gu8_BCM_RxFrameElement;
volatile static uint32_t gu16_BCM_UserRxBufferCounter;
static uint16_t gu16_BCM_UserRxBufferSize;
static uint16_t gu16_BCM_DataRxBufferSize;
static gptrfun_User_cbk_t gpfun_UserRxCbk;
static uint8_t gu8_BCM_ReceivedData;
volatile static uint8_t gu8_UART_RxFlag;
/*************************************************************/
/*                STATIC FUNCTIONS PROTOTYPES                */
/*************************************************************/
void BCM_UartTxComplete_cbk(void);
void BCM_UartRxComplete_cbk(void);
/*************************************************************/
/*                FUNCTIONS IMPLEMENTATION                   */
/*************************************************************/

ERROR_CODE	BCM_Init(void)
{
	ERROR_CODE u8_ErrorCode = BCM_Base_Error + Error_Success;
	
	/* check if module is initialized before */
	if ( TRUE == gu8_BCM_IsInitialized )
	{
		/* if Initialized, return without re-initialize it again */
		u8_ErrorCode = BCM_Base_Error + Error_Already_Initialized;
	}
	else
	{
		/* initialize uart module */
		gstr_UART_Config.u32_BaudRate = UART_BAUDRATE_DESIRED;
		gstr_UART_Config.u8_DataSize = UART_8_BIT;
		gstr_UART_Config.u8_DesiredOperation = TRANSCEIVER;
		gstr_UART_Config.u8_DoubleSpeed = UART_NO_DOUBLE_SPEED;
		gstr_UART_Config.u8_InterruptMode = UART_INTERRUPT;
		gstr_UART_Config.u8_ParityBit = UART_NO_PARITY;
		gstr_UART_Config.u8_StopBit = UART_ONE_STOP_BIT;
		gstr_UART_Config.ptr_Transmit_CBK = BCM_UartTxComplete_cbk;
		gstr_UART_Config.ptr_Resceive_CBK = BCM_UartRxComplete_cbk;
		gstr_UART_Config.ptr_DataRegEmpty_CBk = NULL;
		u8_ErrorCode = UART_Init(&gstr_UART_Config);
		
		
		/* if uart is failed to be initialized, then other initializations must not be done */
		if ( E_NOK == u8_ErrorCode )
		{
			u8_ErrorCode = BCM_Base_Error + Error_Resource_Not_Found;
		} 
		else
		{
			/* initialize global variables for TX */
			genu_BCM_TxCurrentState = SEND_IDLE;
			gu8_BCM_IsTxFrameLocked = FALSE;
			gu8_UART_TxFlag = FALSE;
			gu8_BCM_TxFrameElement = BCM_NEXT_BYTE_IS_ID;
			gu16_BCM_UserTxBufferCounter = 0;
			gu16_BCM_UserTxBufferSize = 0;
			gpfun_UserTxCbk = NULL;
			
			/* initialize uart Tx frame */
			gstr_BCM_TxFrame.u8_BCM_Id = BCM_TX_RX_FRAME_ID;
			gstr_BCM_TxFrame.u8_BCM_SizeLower = 0;
			gstr_BCM_TxFrame.u8_BCM_SizeHigher = 0;
			gstr_BCM_TxFrame.u8_BCM_Checksum = 0;
			gstr_BCM_TxFrame.pu8_BCM_Data = NULL;
			
			
			/* initialize global variables for RX */
			genu_BCM_RxCurrentState = RECEIVE_IDLE;
			gu8_BCM_IsRxFrameLocked = FALSE;
			gu8_BCM_RxFrameElement = BCM_NEXT_BYTE_IS_ID;
			gu16_BCM_UserRxBufferCounter = 0;
			gu16_BCM_UserRxBufferSize = 0;
			gu16_BCM_DataRxBufferSize = 0;
			gpfun_UserRxCbk = NULL;
			gu8_UART_RxFlag = FALSE;

			/* initialize uart Rx frame */
			gstr_BCM_RxFrame.u8_BCM_Id = BCM_TX_RX_FRAME_ID;
			gstr_BCM_RxFrame.u8_BCM_SizeLower = 0;
			gstr_BCM_RxFrame.u8_BCM_SizeHigher = 0;
			gstr_BCM_RxFrame.u8_BCM_Checksum = 0;
			gstr_BCM_RxFrame.pu8_BCM_Data = NULL;
			
			/* make the initialization flag: TRUE */
			gu8_BCM_IsInitialized = TRUE;
		}
	}
	return u8_ErrorCode;
}


ERROR_CODE BCM_DeInit(void)
{
	ERROR_CODE u8_ErrorCode = BCM_Base_Error + Error_Success;
	
	/* check if module is not initialized */
	if ( FALSE == gu8_BCM_IsInitialized )
	{
		/* error message that module is not Initialized */
		u8_ErrorCode = BCM_Base_Error + Error_Not_Initialized;
	}
	else
	{
		/* de-initialize uart module */
		u8_ErrorCode = UART_Deinit();
						
		/* if uart is failed to be de-initialized, then other de-initializations must not be done */
		if ( E_NOK == u8_ErrorCode )
		{
			u8_ErrorCode = BCM_Base_Error + Error_Resource_Not_Found;
		} 
		else
		{
			/* initialize global variables for TX */
			genu_BCM_TxCurrentState = SEND_IDLE;
			gu8_BCM_IsTxFrameLocked = FALSE;
			gu8_UART_TxFlag = FALSE;
			gu8_BCM_TxFrameElement = BCM_NEXT_BYTE_IS_ID;
			gu16_BCM_UserTxBufferCounter = 0;
			gu16_BCM_UserTxBufferSize = 0;
			gpfun_UserTxCbk = NULL;
			
			/* initialize uart Tx frame */
			gstr_BCM_TxFrame.u8_BCM_Id = BCM_TX_RX_FRAME_ID;
			gstr_BCM_TxFrame.u8_BCM_SizeLower = 0;
			gstr_BCM_TxFrame.u8_BCM_SizeHigher = 0;
			gstr_BCM_TxFrame.u8_BCM_Checksum = 0;
			gstr_BCM_TxFrame.pu8_BCM_Data = NULL;
			
			
			/* initialize global variables for RX */
			genu_BCM_RxCurrentState = RECEIVE_IDLE;
			gu8_BCM_IsRxFrameLocked = FALSE;
			gu8_BCM_RxFrameElement = BCM_NEXT_BYTE_IS_ID;
			gu16_BCM_UserRxBufferCounter = 0;
			gu16_BCM_UserRxBufferSize = 0;
			gu16_BCM_DataRxBufferSize = 0;
			gpfun_UserRxCbk = NULL;
			gu8_UART_RxFlag = FALSE;

			/* initialize uart Rx frame */
			gstr_BCM_RxFrame.u8_BCM_Id = BCM_TX_RX_FRAME_ID;
			gstr_BCM_RxFrame.u8_BCM_SizeLower = 0;
			gstr_BCM_RxFrame.u8_BCM_SizeHigher = 0;
			gstr_BCM_RxFrame.u8_BCM_Checksum = 0;
			gstr_BCM_RxFrame.pu8_BCM_Data = NULL;
			
			/* make the initialization flag: FALSE so means it is de-initialized */
			gu8_BCM_IsInitialized = FALSE;
		}
	}
	return u8_ErrorCode;
}


ERROR_CODE BCM_Send(uint8_t* pu8_data, uint16_t u16_size, gptrfun_User_cbk_t pfun_UserCbk)
{
	ERROR_CODE u8_ErrorCode = BCM_Base_Error + Error_Success;
	uint8_t u8_ChecksumCounter;
	
	/* if tx frame is locked, then never re-assign it and return an error */
	if ( TRUE == gu8_BCM_IsTxFrameLocked )
	{
		u8_ErrorCode = BCM_Base_Error + Error_Resource_Not_Found;
	} 
	else
	{
		/* if any pointer equals NULL, then return an error */
		if ( (NULL == pu8_data) /*| (NULL == pfun_UserCbk )*/ )
		{
			u8_ErrorCode = BCM_Base_Error + Error_Null_Pointer;
		}
		else
		{
			/* make the tx frame locked */
			gu8_BCM_IsTxFrameLocked = TRUE;
			
			/* make all counters equal 0 */
			gu8_BCM_TxFrameElement = 0;
			gu16_BCM_UserTxBufferCounter = 0;
			
			/* assign user data size to the frame lower & higher bytes */
			gu16_BCM_UserTxBufferSize = u16_size;
			gstr_BCM_TxFrame.u8_BCM_SizeLower = (uint8_t)u16_size;
			gstr_BCM_TxFrame.u8_BCM_SizeHigher = (uint8_t) (u16_size >> 8);
			
			/* assign the user data pointer */
			gstr_BCM_TxFrame.pu8_BCM_Data = pu8_data;
			
			/* assign the user's function pointer */
			gpfun_UserTxCbk = pfun_UserCbk;
			
			/* assign frame checksum */
			gstr_BCM_TxFrame.u8_BCM_Checksum = 0;
			for ( u8_ChecksumCounter = 0 ; u8_ChecksumCounter < u16_size ; u8_ChecksumCounter++ )
			{
				gstr_BCM_TxFrame.u8_BCM_Checksum += gstr_BCM_TxFrame.pu8_BCM_Data[u8_ChecksumCounter];
			}
			
			/* make tx state idle */
			genu_BCM_TxCurrentState = SEND_IDLE;
			
			/* send the frame ID */
			UART_SendByte(gstr_BCM_TxFrame.u8_BCM_Id);
			gu8_BCM_TxFrameElement = BCM_NEXT_BYTE_IS_SIZE_LOWER_BYTE;
			
			/* change state to sending_byte */
			genu_BCM_TxCurrentState = SENDING_BYTE;
		}
	}
	return u8_ErrorCode;
}


ERROR_CODE BCM_TxDispatcher(void)
{
	ERROR_CODE u8_ErrorCode = BCM_Base_Error + Error_Success;
	
	/* never start dispatcher if the module is not initialized */
	if (FALSE == gu8_BCM_IsInitialized)
	{
		u8_ErrorCode = TMU_Base_Error + Error_Not_Initialized;
	}
	else
	{
		switch (genu_BCM_TxCurrentState)
		{
			case SEND_IDLE:
				/* make the tx frame unlocked */
				gu8_BCM_IsTxFrameLocked = FALSE;
			break;
			
			case SENDING_BYTE:
				if (TRUE == gu8_UART_TxFlag)
				{
					/* make the flag: FALSE */
					gu8_UART_TxFlag = FALSE;
				
					/* change state to sending_complete */
					genu_BCM_TxCurrentState = SENDING_COMPLETE;
				}
				else
				{
					/* Do Nothing */
				}
			break;
			
			case SENDING_COMPLETE:
				if ( BCM_NEXT_BYTE_IS_SIZE_LOWER_BYTE == gu8_BCM_TxFrameElement )
				{
					/* send the frame size lower byte */
					UART_SendByte(gstr_BCM_TxFrame.u8_BCM_SizeLower);
					gu8_BCM_TxFrameElement = BCM_NEXT_BYTE_IS_SIZE_HIGHER_BYTE;
				
					/* change state to sending_byte */
					genu_BCM_TxCurrentState = SENDING_BYTE;
				}
				else if ( BCM_NEXT_BYTE_IS_SIZE_HIGHER_BYTE == gu8_BCM_TxFrameElement )
				{				
					/* send the frame size higher byte */
					UART_SendByte(gstr_BCM_TxFrame.u8_BCM_SizeHigher);
					gu8_BCM_TxFrameElement = BCM_NEXT_BYTE_IS_DATA_BYTE;
				
					/* change state to sending_byte */
					genu_BCM_TxCurrentState = SENDING_BYTE;
				}
				else if ( BCM_NEXT_BYTE_IS_DATA_BYTE == gu8_BCM_TxFrameElement )
				{
					if ( gu16_BCM_UserTxBufferCounter < gu16_BCM_UserTxBufferSize )
					{
						/* send the user's data bytes */
						UART_SendByte( gstr_BCM_TxFrame.pu8_BCM_Data[gu16_BCM_UserTxBufferCounter] );
						gu16_BCM_UserTxBufferCounter++;
					} 
					else
					{
						/* send the checksum byte */
						UART_SendByte(gstr_BCM_TxFrame.u8_BCM_Checksum);
						gu8_BCM_TxFrameElement = BCM_NEXT_BYTE_IS_NOTHING;
					}
					
					/* change state to sending_byte */
					genu_BCM_TxCurrentState = SENDING_BYTE;
				}
				else if ( BCM_NEXT_BYTE_IS_NOTHING == gu8_BCM_TxFrameElement )
				{
					/* execute user's callback function if not equal NULL */
					if ( NULL == gpfun_UserTxCbk)
					{
						u8_ErrorCode = TMU_Base_Error + Error_Null_Pointer;
					}
					else
					{
						gpfun_UserTxCbk();
					}

					/* change state to IDLE */
					genu_BCM_TxCurrentState = SEND_IDLE;
				}
				else
				{
					/* Do Nothing */
				}
			break;
			
			default: /* Do Nothing */
			break;
		}
	}
	return u8_ErrorCode;
}


void BCM_RxUnlock(void)
{
	/* unlock the RX frame */
	gu8_BCM_IsRxFrameLocked = FALSE;
}

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	---	
 * Description: function to return if the buffer locked
 */
uint8_t BCM_IsBufferLocked(void)
{
	return gu8_BCM_IsRxFrameLocked;
}


ERROR_CODE BCM_SetupReceiveBuffer(uint8_t* pu8_BCM_RxBuffer, uint16_t u16_BCM_RxBufferSize, gptrfun_User_cbk_t pfun_UserCbk)
{
	ERROR_CODE u8_ErrorCode = BCM_Base_Error + Error_Success;
	
	/* if RX frame is locked, then never re-assign it and return an error */
	if ( TRUE == gu8_BCM_IsRxFrameLocked )
	{
		u8_ErrorCode = BCM_Base_Error + Error_Resource_Not_Found;
	}
	else
	{
		/* if any pointer equals NULL, then return an error */
		if ( (NULL == pu8_BCM_RxBuffer) /*| (NULL == pfun_UserCbk )*/ )
		{
			u8_ErrorCode = BCM_Base_Error + Error_Null_Pointer;
		}
		else
		{
			
			/* make all counters equal initial state */
			gu16_BCM_UserRxBufferCounter = 0;
			
			/* assign user data size to the frame size */
			gu16_BCM_UserRxBufferSize = u16_BCM_RxBufferSize;
			
			/* assign the user data pointer */
			gstr_BCM_RxFrame.pu8_BCM_Data = pu8_BCM_RxBuffer;
			
			/* assign the user's function pointer */
			gpfun_UserRxCbk = pfun_UserCbk;
			
			/* make Rx state idle */
			genu_BCM_RxCurrentState = RECEIVE_IDLE;
			
			/* make the frame locked */
			gu8_BCM_IsRxFrameLocked = TRUE;
			
			/* notify dispatcher that the next byte is the ID */
			gu8_BCM_RxFrameElement = BCM_NEXT_BYTE_IS_ID;
		}
	}
	return u8_ErrorCode;
}


ERROR_CODE BCM_RxDispatcher(void)
{
	ERROR_CODE u8_ErrorCode = BCM_Base_Error + Error_Success;
	
	/* never start dispatcher if the module is not initialized */
	if (FALSE == gu8_BCM_IsInitialized)
	{
		u8_ErrorCode = TMU_Base_Error + Error_Not_Initialized;
	}
	else
	{
		switch (genu_BCM_RxCurrentState)
		{
			case RECEIVE_IDLE:
				/* move to state */
				if (TRUE == gu8_BCM_IsRxFrameLocked)
				{
					/* change Rx state */
					genu_BCM_RxCurrentState = RECEIVING_BYTE;					
				} 
				else
				{
					/* Do Nothing */
				}
			break;
			
			case RECEIVING_BYTE:
				if (TRUE == gu8_UART_RxFlag)
				{
					
					/* make the flag: FALSE */
					gu8_UART_RxFlag = FALSE;
					
					/* change Rx state */
					genu_BCM_RxCurrentState = RECEIVING_COMPLETE;
				}
				else
				{
					/* do nothing */
				}
			break;
			
			case RECEIVING_COMPLETE:
			
				/* check received ID */
				if ( BCM_NEXT_BYTE_IS_ID == gu8_BCM_RxFrameElement )
				{
					/* assign the ID byte */
					gstr_BCM_RxFrame.u8_BCM_Id = gu8_BCM_ReceivedData;
					
					/* if received ID is confirmed to be the BCM pre-saved ID */
					if ( BCM_TX_RX_FRAME_ID == gstr_BCM_RxFrame.u8_BCM_Id )
					{
						/* notify the dispatcher what the next byte will be */
						gu8_BCM_RxFrameElement = BCM_NEXT_BYTE_IS_SIZE_LOWER_BYTE;
						
						/* change Rx state */
						genu_BCM_RxCurrentState = RECEIVING_BYTE;
					}
					else
					{
						/* error message */
						u8_ErrorCode = BCM_Base_Error + Error_NotRecognized_ID;
						
						/* change Rx state */
						genu_BCM_RxCurrentState = RECEIVE_IDLE;
					}
				}
				
				/* save the received size lower byte */
				else if ( BCM_NEXT_BYTE_IS_SIZE_LOWER_BYTE == gu8_BCM_RxFrameElement )
				{
					/* assign the size lower byte */
					gstr_BCM_RxFrame.u8_BCM_SizeLower = gu8_BCM_ReceivedData;
					
					/* assign the size lower byte into the lower part of the variable */
					gu16_BCM_DataRxBufferSize = ((uint16_t)gstr_BCM_RxFrame.u8_BCM_SizeLower);
					
					/* notify the dispatcher what the next byte will be */
					gu8_BCM_RxFrameElement = BCM_NEXT_BYTE_IS_SIZE_HIGHER_BYTE;
					
					/* change Rx state */
					genu_BCM_RxCurrentState = RECEIVING_BYTE;
				}
				
				/* save the received size higher byte */
				else if ( BCM_NEXT_BYTE_IS_SIZE_HIGHER_BYTE == gu8_BCM_RxFrameElement )
				{
					/* assign the size higher byte */
					gstr_BCM_RxFrame.u8_BCM_SizeHigher = gu8_BCM_ReceivedData;
					
					/* assign the size higher byte into the higher part of the variable */
					gu16_BCM_DataRxBufferSize |=((uint16_t)gstr_BCM_RxFrame.u8_BCM_SizeHigher<<8);
										
					/* check if (the coming data size + 1 byte for the checksum saving) is <= the user's defined buffer size */
					if ( (gu16_BCM_DataRxBufferSize+1) <= gu16_BCM_UserRxBufferSize )
					{
						/* notify the dispatcher what the next byte will be */
						gu8_BCM_RxFrameElement = BCM_NEXT_BYTE_IS_DATA_BYTE;
						
						/* change Rx state */
						genu_BCM_RxCurrentState = RECEIVING_BYTE;
					}
					else
					{
						/* error message that available resource can not be used */
						u8_ErrorCode = BCM_Base_Error + Error_Resource_Not_Found;
						
						/* change Rx state */
						genu_BCM_RxCurrentState = RECEIVE_IDLE;
					}
				}
				
				/* check if received byte is a data byte */
				else if ( BCM_NEXT_BYTE_IS_DATA_BYTE == gu8_BCM_RxFrameElement )
				{
					/* assign data byte to the user's buffer */
					gstr_BCM_RxFrame.pu8_BCM_Data[gu16_BCM_UserRxBufferCounter] = gu8_BCM_ReceivedData;
					
					/* while the counter is less than the size extracted from the buffer */
					if ( gu16_BCM_UserRxBufferCounter < (gu16_BCM_DataRxBufferSize) )
					{
						/* add the data byte to the checksum */
						gstr_BCM_RxFrame.u8_BCM_Checksum += gstr_BCM_RxFrame.pu8_BCM_Data[gu16_BCM_UserRxBufferCounter];
						gu16_BCM_UserRxBufferCounter++;
						
						/* change Rx state */
						genu_BCM_RxCurrentState = RECEIVING_BYTE;
					}
					else
					{
						/* else means the BCM received the checksum byte */
						if ( gstr_BCM_RxFrame.u8_BCM_Checksum == gstr_BCM_RxFrame.pu8_BCM_Data[gu16_BCM_UserRxBufferCounter] )
						{
							/* execute user's callback function if not equal NULL */
							if ( NULL == gpfun_UserRxCbk)
							{
								u8_ErrorCode = TMU_Base_Error + Error_Null_Pointer;
							}
							else
							{
								gpfun_UserRxCbk();
							}
						}
						else
						{
							/* error message that checksum failed and data is corrupted */
							u8_ErrorCode = BCM_Base_Error + Error_InvalidData;
						}
						
						/* change Rx state */
						genu_BCM_RxCurrentState = RECEIVE_IDLE;
					}
				}			
			break;
			
			default: /* Do Nothing */
			break;
		}
	}
	return u8_ErrorCode;
}

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: callback function for the UART tx complete ISR
 */
void BCM_UartTxComplete_cbk(void)
{
	gu8_UART_TxFlag = TRUE;
}


void BCM_UartRxComplete_cbk(void)
{
	if (TRUE == gu8_BCM_IsRxFrameLocked)
	{
		gu8_UART_RxFlag = TRUE;
		UART_ReceiveByte(&gu8_BCM_ReceivedData);
	}
	else
	{
		/* Do Nothing */
	}
}
