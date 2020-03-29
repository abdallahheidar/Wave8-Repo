/*
 * BCM_Recieve.h
 *
 * Created: 04/03/2020 05:13:34 م
 *  Author: mo
 */


#ifndef BCM_RECIEVE_H_
#define BCM_RECIEVE_H_
#include "BCM_Config.h"


typedef uint8_t ERROR_STATUS ;
ERROR_STATUS BCM_Init (const BCM_ConfigType * ConfigPtr );
ERROR_STATUS BCM_DeInit (const BCM_ConfigType * ConfigPtr);
ERROR_STATUS BCM_Recieve(  uint8_t u8_channel_Protcol ,uint8_t u8_BCM_ID,uint8_t u8_data_Lenght,uint8_t Num_of_Frames);
ERROR_STATUS BCM_RxDispatcher (void);

extern void Uart_transmit_int(void);
extern void SPI_Receive_int(void);

#endif /* BCM_RECIEVE_H_ */
