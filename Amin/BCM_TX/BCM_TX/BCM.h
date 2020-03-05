/*
* BCM.h
*
* Created: 3/2/2020 1:17:48 AM
*  Author: Abdallah & Amin
*/ 


#ifndef BCM_H_
#define BCM_H_

/* inclusions */
#include "std_types.h"
#include "module_retval.h "
#include "ERROR_STORE_CFG.h"
#include "Errors.h"
#include "UART.h"
#include "SPI.h"

/*UART_Channels*/
#define UART_CH		0x01
#define SPI_CH		0x02

/*Buffer Status*/
#define BUFFER_LOCKED		0
#define BUFFER_UNLOCKED		1

/*BCM States*/
#define BCM_IDLE                        0
#define BCM_SENDING_BYTE                1
#define BCM_SENDING_BYTE_COMPLETE       2
#define BCM_RECEIVING_BYTE              3
#define BCM_RECEIVING_BYTE_COMPLETE     4

/*primitive types*/

uint8_t G_BUFF[54];
#define BCM_PAYLOAD_ID 0xA0

/* function declarations*/

/**
 *  @brief BCM Initialization function
 *  
 *  @param [in] bcm_id BCM channel ID
 *  @return ERROR_STATUS
 *  
 *  @details This function initializes the hardware interface and callbacks for the BCM
 */
extern ERROR_STATUS BCM_Init (uint8_t bcm_id);

/**
 *  @brief BCM send function
 *  
 *  @param [in] ptr_Buffer pointer to the buffer containing the payload
 *  @param [in] u16_Size   The size of the payload/message
 *  @param [in] u8_Channel The desired BCM channel
 *  @return ERROR_STATUS
 *  
 *  @details This function creates the whole frame of the message containg the message ID and size and calculates the checksum
 */
extern ERROR_STATUS BCM_Send (uint8_t* ptr_Buffer, uint16_t u16_Size, uint8_t u8_Channel);

/**
 *  @brief BCM receive function
 *  
 *  @param [in] u16_Size   The expected number of character to be reseived
 *  @param [in] bcm_id     The BCM chanel to receive the message from
 *  @return ERROR_STATUS
 *  
 *  @details Callback for received data
 */
extern ERROR_STATUS BCM_Receive (uint16_t u16_Size, uint8_t u8_Channel);

/**
 *  @brief BCM Transmit Dispatcher
 *  
 *  @return void
 */
extern void BCM_TxDispatch(void);

/**
 *  @brief BCM Receive Dispatcher
 *  
 *  @return void
 */
extern void BCM_RxDispatch(void);

/**
 *  @brief BCM UART interface sent callback
 *  
 *  @return void
 *  
 *  @details Callback for sent data
 */
extern void BCM_UART_Tx_Call_Back(void);

/**
 *  @brief BCM UART interface receive callback
 *  
 *  @return void
 *  
 *  @details Callback for received data
 */
extern void BCM_UART_Rx_Call_Back(void);

/**
 *  @brief BCM SPI interface sent callback
 *  
 *  @return void
 *  
 *  @details Callback for sent data
 */
extern void BCM_SPI_Tx_Call_Back(void);

#endif /* BCM_H_ */