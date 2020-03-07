/*
 * UART_CFG.h
 *
 * Created: 3/1/2020 10:47:12 PM
 *  Author: A_ayman
 */ 



#ifndef UART_CFG_H_
#define UART_CFG_H_

#include "UART.h"

#define USART_TX_GPIO   GPIOD
#define USART_TX_BIT   BIT1

#define USART_RX_GPIO   GPIOD
#define USART_RX_BIT   BIT0



/*primitive types*/
// typedef struct 
// {
// 	uint8_t USART_MODE;
// 	uint8_t USART_RX_TX;
// 	uint8_t CHAR_DATA_NUMBER;
// 	uint8_t USART_PARITY;
// 	uint8_t USART_CLOCK_POLARITY;
// 	uint8_t STOP_BIT_SELECT;
// 	uint8_t USART_INTERRUPTS;
// 	uint8_t USART_BAUD_RATE_SELECT;
// 	
// }USART_CFG_t;
// 
// extern USART_CFG_t UART1_CFG;






#endif /* UART_CFG_H_ */