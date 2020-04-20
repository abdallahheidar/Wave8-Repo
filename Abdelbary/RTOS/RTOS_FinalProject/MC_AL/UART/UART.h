

#ifndef UART_H_
#define UART_H_


#include "../../ServiceLayer/std_types.h"


/*
*	Definition of UART register's bits
*/
/*CSRA*/
#define UART_MPCM  (0x01)
#define UART_U2X   (0x02)
#define UART_PE    (0x04)
#define UART_DOR   (0x08)
#define UART_FE    (0x10)
#define UART_DRE   (0x20)
#define UART_TXC   (0x40)
#define UART_RXC   (0x80)

/*CSRB*/
#define UART_TXB8  (0x01)
#define UART_RXB8  (0x02)
#define UART_CSZ2 (0x04)
#define UART_TXEN  (0x08)
#define UART_RXEN  (0x10)
#define UART_DRIE  (0x20)
#define UART_TXCIE (0x40)
#define UART_RXCIE (0x80)

/*CSRC*/
#define UART_CPOL  (0x01)
#define UART_CSZ0  (0x02)
#define UART_CSZ1  (0x04)
#define UART_SBS   (0x08)
#define UART_PM0   (0x10)
#define UART_PM1   (0x20)
#define UART_MSEL  (0x40)
#define UART_RSEL  (0x80)

/*
*	Used macros 
*/
#define UART_POLLING					(0U)
#define UART_INTERRUPT					(1U)

#define TRANSMITTER						(0U)
#define RECEIVER						(1U)
#define TRANSCEIVER						(2U)

#define UART_NO_DOUBLE_SPEED			(0U)
#define UART_DOUBLE_SPEED				(1U)

#define UART_ONE_STOP_BIT				(0U)
#define UART_TWO_STOP_BIT				(1U)

#define UART_NO_PARITY					(0U)
#define UART_EVEN_PARITY				(2U)
#define UART_ODD_PARITY					(3U)

#define UART_5_BIT						(0U)
#define UART_6_BIT						(1U)
#define UART_7_BIT						(2U)
#define UART_8_BIT						(3U)
#define UART_9_BIT						(7U)
/*
*	Used Pins
*/

#define UART_TX_GPIO					GPIOD
#define UART_TX_BIT						BIT1

#define UART_RX_GPIO					GPIOD
#define UART_RX_BIT						BIT0

typedef struct 
{
	uint8_t u8_InterruptMode;
	uint8_t u8_DesiredOperation;	
	uint8_t u8_DoubleSpeed;
	uint8_t u8_StopBit;
	uint8_t u8_ParityBit;
	uint8_t u8_DataSize;
	uint32_t u32_BaudRate;
	void (*ptr_Transmit_CBK)(void);
	void (*ptr_Resceive_CBK)(void);
	void (*ptr_DataRegEmpty_CBk)(void);
}UART_cfg_s;
/** 
 * \brief UART_Init : 
 *
 * \param *pUART_cfg_s : A pointer to a struct that holds the desired UART configuration
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/     
extern ERROR_STATUS UART_Init(UART_cfg_s *pUART_cfg_s);

/** 
 * \brief UART_Deinit : Deinitialize the UART module
 *
 * \param void
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/     
extern ERROR_STATUS UART_Deinit(void);


/**
 * \brief  UART_SendByte : Sends a certain byte
 *
 * \param u8_Data : The byte the user wants to send
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
extern ERROR_STATUS UART_SendByte(uint8_t u8_Data);

/** 
 * \brief  UART_ReceiveByte : Receives a certain byte
 *
 * \param pu8_ReceivedData : The sent byte will be stored in the passed pointer 
 * \return ERROR_STATUS : Indication to the function execution 
 *
 **/  
extern ERROR_STATUS UART_ReceiveByte(uint8_t *pu8_ReceivedData);
   
#endif /* UART_H_ */
