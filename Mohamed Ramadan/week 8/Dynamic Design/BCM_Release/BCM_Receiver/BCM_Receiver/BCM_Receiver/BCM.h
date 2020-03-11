/*
 * BCM.h
 *
 *  Created on: Mar 2, 2020
 *      Author: Youssef Harby & Mohamed Ramadan
 */

#ifndef BCM_H_
#define BCM_H_


/*- INCLUDES -----------------------------------------------*/

#include "SPI.h"
#include "UART.h"


/*- DEFINITIONS --------------------------------------------*/

#define BCM_ID					0x5A

#define BCM_UART_ID				0xA0
#define BCM_SPI_ID				0xA1
#define BCM_I2C_ID				0xA2

#define BCM_TRANSMIT			0x00
#define BCM_RECEIVE				0x01
#define BCM_TRANSMIT_RECEIVE	0x02


typedef void (*PointerToSenderFunction)(const uint8_t);
typedef uint8_t (*PointerToReceiverFunction)(void);
typedef void (*PointerToSetCallBackFunction)(void(*ptr)(void));
typedef void (*PointerToApplicationFunction)(void);

typedef uint8_t EnmBCMError_t;

typedef struct BCM_ConfigType{
	uint8_t BCM_ProtocolID;
	uint8_t BCM_DataDirection;
}strBcmConfig_t;

typedef struct BCM_SendConfigType{
	uint8_t BCM_ProtocolID;
	uint8_t* BCM_ArrayStartAddress;
	uint16_t BCM_ArraySize;
}strBcmSendConfig_t;


extern EnmBCMError_t BCM_Init(const strBcmConfig_t* ConfigPtr);
extern EnmBCMError_t BCM_DeInit(uint8_t BCM_ProtocolID);

extern EnmBCMError_t BCM_Send(strBcmSendConfig_t* ConfigPtr);
extern EnmBCMError_t BCM_Receive(strBcmSendConfig_t* ConfigPtr);

extern EnmBCMError_t BCM_SetupRxBuffer(uint8_t ProtocolID, uint8_t* ArrayFirstElementAddress, uint16_t ArraySize);
extern EnmBCMError_t BCM_RxDispatch(void);
extern EnmBCMError_t BCM_TxDispatch(void);

extern void BCM_SetCallBack(void (*a_ptr)(void));

#endif /* BCM_H_ */
