

#ifndef UART_CFG_H_
#define UART_CFG_H_


/*
 * User Configuration Macros
 */

#define F_CPU 16000000UL

#define USART_BAUDRATE	9600
#define BAUDPRESCALE	((F_CPU / (USART_BAUDRATE * 8UL)) - 1)


#endif /* UART_CFG_H_ */
