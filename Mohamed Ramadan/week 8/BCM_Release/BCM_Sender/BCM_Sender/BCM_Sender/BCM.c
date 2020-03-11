/*
 * BCMTx.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Youssef Harby & Mohamed Ramadan
 */


/*- INCLUDES -----------------------------------------------*/

#include "BCM.h"
#include "BCM_cfg.h"
#include "util/delay.h"

/*- DEFINITIONS --------------------------------------------*/

#define UNDETERMINED		0x00


/*- GLOBAL STATIC VARIABLES --------------------------------*/

static volatile uint8_t gu8_BCM_SENDING_SM = BCM_SENDER_IDLE;
static volatile uint8_t gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;

static volatile uint8_t gu8_BCM_BufferState = BCM_BUFFER_UNLOCKED;

static strBcmSendConfig_t TxCfg;
static strBcmSendConfig_t RxCfg;

static volatile uint8_t gu8_TxDispatchCounter = 255;
static volatile uint8_t gu8_RxDispatchCounter = 255;

static uint8_t gu8_TxCheckSum = 0;


// locals to globals

static uint8_t gu8_RxCheckSum = 0;
static uint8_t gu8_TxCounter = 0;
static uint8_t gu8_RxCounter = 0;


/*- CALL BACK FUNCTIONS ------------------------------------*/

void RxApp(void)
{
	gu8_BCM_Receiving_SM = BCM_RECEIVING_BYTE;
	BCM_Receive(&RxCfg);
	gu8_BCM_Receiving_SM = BCM_RECEIVING_COMPLETE;
	gu8_RxDispatchCounter++;
}

void TxApp(void)
{
	gu8_BCM_SENDING_SM = 1;
	
}


/*- APIs IMPLEMENTATION ------------------------------------*/

EnmBCMError_t BCM_Init(const strBcmConfig_t* ConfigPtr)
{
	_delay_ms(100);
	//_delay_ms(500);
	uint8_t au8_Ret = E_OK;

	UART_ConfigType UART_cfg = {
			UART_ASYNCHRONOUS_MODE,
			UNDETERMINED,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_ENABLED
	};

	SPI_ConfigType SPI_cfg = {
			UNDETERMINED,
			SPI_INTERRUPT_ENABLED,
			SPI_F_OSC_4
	};
	
 //TCNT2 = SPI_cfg.ClockRateSelect;

	switch(ConfigPtr->BCM_DataDirection)
	{
	case BCM_TRANSMIT:
		UART_cfg.communicationMode = UART_SENDER_MODE;
		SPI_cfg.MasterSlaveSelect = SPI_MASTER;
		break;
	case BCM_RECEIVE:
		UART_cfg.communicationMode = UART_RECEIVER_MODE;
		SPI_cfg.MasterSlaveSelect = SPI_SLAVE;
		break;
	case BCM_TRANSMIT_RECEIVE:
		UART_cfg.communicationMode = UART_SENDER_RECEIVER_MODE;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	switch(ConfigPtr->BCM_ProtocolID)
	{
	case BCM_UART_ID:
		UART_init(&UART_cfg);
		break;
	case BCM_SPI_ID:
		SPI_init(&SPI_cfg);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

EnmBCMError_t BCM_DeInit(uint8_t BCM_ProtocolID)
{
	uint8_t au8_Ret = E_OK;

	switch(BCM_ProtocolID)
	{
	case BCM_UART_ID:
		UART_deInit();
		UART_RXC_setCallBack(NULL);
		UART_TXC_setCallBack(NULL);
		break;
	case BCM_SPI_ID:
		SPI_deInit();
		SPI_setCallBack(NULL);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

EnmBCMError_t BCM_RxDispatch(void)
{
	uint8_t au8_Ret = E_OK;

	if(gu8_BCM_Receiving_SM == BCM_RECEIVING_COMPLETE && gu8_RxDispatchCounter < (RxCfg.BCM_ArraySize - 1) && gu8_RxDispatchCounter >= 3)
	{
		gu8_RxCheckSum += RxCfg.BCM_ArrayStartAddress[gu8_RxDispatchCounter];

		gu8_BCM_Receiving_SM = BCM_RECEIVING_BYTE;
	}

	if(gu8_RxDispatchCounter == RxCfg.BCM_ArraySize - 1)
	{
		if(gu8_RxCheckSum != RxCfg.BCM_ArrayStartAddress[gu8_RxDispatchCounter])
			au8_Ret = E_NOK;
		gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;
		gu8_RxCounter = 0;
		gu8_RxDispatchCounter = 255;
		gu8_RxCheckSum = 0;
	}

	return au8_Ret;
}

EnmBCMError_t BCM_TxDispatch(void)
{
	uint8_t au8_Ret = E_OK;



if (gu8_BCM_SENDING_SM == 1)
{
	BCM_Send(&TxCfg);
}
		
		
gu8_BCM_SENDING_SM = 0;
		
	return au8_Ret;
}

EnmBCMError_t BCM_Send(strBcmSendConfig_t* ConfigPtr)
{
	uint8_t au8_Ret = E_OK;
	static uint8_t i= 0;
	
	switch(ConfigPtr->BCM_ProtocolID)
	{
		case BCM_SPI_ID:
		SPI_setCallBack(&TxApp);
		SPI_sendByte(ConfigPtr->BCM_ArrayStartAddress[i]);
		break;
		default:
		au8_Ret = E_NOK;
		break;
	}
	
//i++;

	TxCfg = *ConfigPtr;
	return au8_Ret;
}

EnmBCMError_t BCM_SetupRxBuffer(uint8_t ProtocolID, uint8_t* ArrayFirstElementAddress, uint16_t ArraySize)
{
	uint8_t au8_Ret = E_OK;

	RxCfg.BCM_ArraySize = ArraySize;
	RxCfg.BCM_ArrayStartAddress = ArrayFirstElementAddress;
	RxCfg.BCM_ProtocolID = ProtocolID;

	switch(ProtocolID)
	{
	case BCM_UART_ID:
		UART_RXC_setCallBack(&RxApp);
		break;
	case BCM_SPI_ID:
		SPI_setCallBack(&RxApp);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

EnmBCMError_t BCM_Receive(strBcmSendConfig_t* ConfigPtr)
{
	static uint8_t au8_Ret = E_OK;
	PointerToReceiverFunction apf_ReceiverFunction = NULL;

	switch(ConfigPtr->BCM_ProtocolID)
	{
	case BCM_UART_ID:
		UART_RXC_setCallBack(&RxApp);
		apf_ReceiverFunction = UART_receive;
		break;
	case BCM_SPI_ID:
		SPI_setCallBack(&RxApp);
		apf_ReceiverFunction = SPI_receiveByte;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	if(gu8_RxCounter < ConfigPtr->BCM_ArraySize && au8_Ret == E_OK)
	{
		ConfigPtr->BCM_ArrayStartAddress[gu8_RxCounter] = apf_ReceiverFunction();

		if(ConfigPtr->BCM_ArrayStartAddress[0] != BCM_ID)
		{
			au8_Ret = E_NOK;
			gu8_BCM_Receiving_SM = BCM_RECEIVER_IDLE;
			gu8_RxCounter = 0;
			gu8_RxDispatchCounter = 255;
			gu8_RxCheckSum = 0;
		}else
		{
			gu8_BCM_BufferState = BCM_BUFFER_LOCKED;
		}

		PORTD_DIR = ConfigPtr->BCM_ArrayStartAddress[gu8_RxCounter];
		gu8_RxCounter++;
	}

	return au8_Ret;
}
