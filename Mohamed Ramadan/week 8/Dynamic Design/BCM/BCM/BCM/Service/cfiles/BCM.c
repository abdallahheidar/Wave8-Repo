/*
 * File		: BCM.c
 * Author	: M.Ramadan
 */

/*********************************************
 *				Includes  					 *
 ********************************************/
#include "BCM.h"
#include "avr/interrupt.h"

/************************************************************************/
/*			  global variable Declaration		                        */
/************************************************************************/
uint8_t gu8_StateMode;
uint8_t UART_TXC_Flag;

static strBcmConfigStart_t BCM_St_Send;
/********************************************
 *			  Function Implementation        *
 *********************************************/

/** Call Back function **/
void UART_TXC(void){
	UART_TXC_Flag = 1;
}



/**
 * Func			: BCM_Init
 * Input		: Pointer to a structure of type strBcmConfig_t 
 *				contains the BCM_Channel or protocol and the mode sending or receiving.
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (BCM protocol,mode of data[Sending /Recieving])
 */
EnmBCMError_t BCM_Init(strBcmConfig_t *ConfigPtr){
	
	/** Declare the Error Status of the function **/
	uint8_t au8_ErrStatus = E_OK;
	
	/** UART Structure Definition **/
	UART_ConfigType UART_Cfg = {UART_SYNCHRONOUS_MODE, UNDETERMINED, UART_EIGHT_BITS,
						 UART_PARITY_DISABLED, UART_ONE_STOP_BIT, UART_INTERRUPT_ENABLED};
	
	
	/** SPI Structure Definition **/
	SPI_ConfigType SPI_Cfg ={UNDETERMINED,SPI_INTERRUPT_ENABLED,SPI_F_OSC_4};
	
	/** choose the mode of the uart and spi **/	
	switch (ConfigPtr->Protocol_Mode)
	{
	case BCM_UART_Send:
		UART_Cfg.communicationMode = UART_SENDER_MODE;
		break;
	case BCM_UART_Recieve:
		UART_Cfg.communicationMode = UART_RECEIVER_MODE;
		break;
	case BCM_UART_Send_Recieve:
		UART_Cfg.communicationMode = UART_SENDER_RECEIVER_MODE;
		break;
	case BCM_SPI_Send:
		SPI_Cfg.MasterSlaveSelect = SPI_MASTER;
		break;	
	case BCM_SPI_Recieve:
		SPI_Cfg.MasterSlaveSelect = SPI_SLAVE;
		break;	
	default:
		au8_ErrStatus = E_NOK;		
	}
	 
	/** move between and initialize BCM channels UART or SPI or I2C **/
	switch (ConfigPtr->Protocol_ID)
	{
		case BCM_UART:
			UART_init(&UART_Cfg);
			gu8_StateMode = Idle;
			break;
		case BCM_SPI:
			SPI_init(&SPI_Cfg);
			gu8_StateMode = Idle;
			break;
		case BCM_I2C:
			/** Can be used to add feature of using I2C channel **/
			break;
		default:
			au8_ErrStatus = E_NOK;	
	}
	
	return au8_ErrStatus;
}

/**
 * Func			: BCM_DeInit
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Uninitialized the Hardware module 
 */
EnmBCMError_t BCM_DeInit(uint8_t Protocol_ID){
	
	/** Declare the Error Status of the function **/
	uint8_t au8_ErrStatus = E_OK;
	
	switch (Protocol_ID)
	{
	case BCM_UART:
		UART_deInit();
		gu8_StateMode = Idle;
		break;
	case BCM_SPI:
		SPI_deInit();
		gu8_StateMode = Idle;
		break;	
	case BCM_I2C:
		/** Can be used to add feature of using I2C channel **/
		break;
	default:
		au8_ErrStatus=E_NOK;	
	}
	
	return au8_ErrStatus;
}


/**
 * Func			: BCM_TxDispatch
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Implement BCM_TxDispatch check the flag of ISR and move between Transmitting complete 
					and Transmitting Byte states and and construct the packet (Header – Data – Check SUM), 
					and the Header contain Command and the data size..
**/
EnmBCMError_t BCM_TxDispatch(void){
	/** Declare the Error Status of the function **/
	uint8_t au8_ErrStatus = E_OK;
	
	if (UART_TXC_Flag==1)
	{
		BCM_Send(&BCM_St_Send);
		gu8_StateMode = SendingByte;
	} 
	else
	{
		//do Nothing
	}
	
	return au8_ErrStatus;
}


/**
 * Func			: BCM_DeInit
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Implement BCM_RxDispatch check the flag of ISR and move between Receiving complete
					and Receiving Byte states and reconstruct the packet to extract only the user data. 
**/

EnmBCMError_t BCM_RxDispatch(void){
		
		/** Declare the Error Status of the function **/
		uint8_t au8_ErrStatus = E_OK;	
		
			
	
}


/**
 * Func			: BCM_Send
 * Input		:  Pointer to a structure of type strBcmConfig_t 
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Send shall invoked by the user to send the stream of data, it represent event creator.
**/
EnmBCMError_t BCM_Send(strBcmConfigStart_t *ConfigPtr){
			/** static counter for data **/
			static uint8_t DataCounter = 0;
			/** Declare the Error Status of the function **/
			uint8_t au8_ErrStatus = E_OK;
		
		switch (ConfigPtr->Protocol_ID)
		{
		case BCM_UART:
			UART_transmit(ConfigPtr->PtrAddress[DataCounter++]);
			UART_TXC_setCallBack(ConfigPtr->Bcm_Cbk_Ptr);
			gu8_StateMode = SendingByte;
			break;
		case BCM_SPI:
			SPI_sendByte(ConfigPtr->PtrAddress[DataCounter++]);
			gu8_StateMode = SendingByte;
			break;
		case BCM_I2C:
			/** Can be used to add feature of using I2C channel **/
			break;	
		default:
			au8_ErrStatus = E_NOK;	
		}
	/** store the structure content in the global BCM_St_Send structure to ease using it in Dispature **/
	BCM_St_Send = *ConfigPtr;	
	return au8_ErrStatus;
}

/**
 * Func			: BCM_Receive
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Receive shall invoked by the user to receive the stream of data.
**/
EnmBCMError_t BCM_Receive(strBcmConfigStart_t *ConfigPtr){
			/** static counter for data **/
			static uint8_t DataCounter = 0;
			/** Declare the Error Status of the function **/
			uint8_t au8_ErrStatus = E_OK;
			
		switch (ConfigPtr->Protocol_ID)
		{
		case BCM_UART:
			ConfigPtr->PtrAddress[DataCounter] = UART_receive();
			gu8_StateMode = RecievingComplete;
			break;
		case BCM_SPI:
			ConfigPtr->PtrAddress[DataCounter] = SPI_receiveByte();
			gu8_StateMode = RecievingComplete;
			break;	
		
		case BCM_I2C:
			/** Can be used to add feature of using I2C channel **/
			break;
			
		default:
			au8_ErrStatus = E_NOK;	
		}
		
		DataCounter++;
		return 	au8_ErrStatus;
}
