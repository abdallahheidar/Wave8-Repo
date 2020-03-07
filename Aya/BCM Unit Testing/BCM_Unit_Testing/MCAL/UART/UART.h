/*
 * UART.h
 *
 * Created: 3/1/2020 9:58:38 PM
 *  Author: A_ayman
 */


#ifndef UART_H_
#define UART_H_

/* inclusions */
#include "../DIO/registers.h"
#include "UART_CFG.h"
#include "../../SL/Utilis/std_types.h"
#include "../../SL/Utilis/interrupts.h"
#include "../../SL/Utilis/module_retval.h"

/* Constants */
#define F_CPU                 16000000


typedef enum En_USART_MODE_t{
	USART_ASYNC_MODE=0x00,USART_SYNC_MODE=0x40
}En_USART_MODE_t;

typedef enum En_USART_PARITY_MODE_t{
	USART_PARITY_DIS=0x00,USART_PARITY_EVEN=0x20,USART_PARITY_ODD=0x30
}En_USART_PARITY_MODE_t;

typedef enum En_USART_CLOCK_POLARITY_t{
	USART_RISING_TRANSMIT=0x00,USART_FALLING_TRANSMIT=0x01
}En_USART_CLOCK_POLARITY_t;

typedef enum En_USART_CHAR_DATA_NUMBER_t{
	USART_5BIT_DATA=0x00,USART_6BIT_DATA=0x02,USART_7BIT_DATA=0x04,USART_8BIT_DATA=0x06
}En_USART_CHAR_DATA_NUMBER_t;

typedef enum En_USART_INTERRUPTS_t{
	USART_Interrupt_Disabl=0x00,USART_RX_Complete_Interrupt_Enable=0x80,USART_TX_Complete_Interrupt_Enable=0x40,USART_Data_Register_Empty_Interrupt_Enable=0x20
}En_USART_INTERRUPTS_t;

typedef enum En_USART_RECEIVE_TRANSMIT_t{
	USART_RX_TX_Disable =0x00, USART_RX_TX_Enable=0x18,USART_RX_Enable=0x10,USART_TX_Enable=0x08
}En_USART_RECEIVE_TRANSMIT_t;

typedef enum En_USART_STOP_BIT_SELECT_t{
	USART_1_STOP_BIT=0x00,USART_2_STOP_BIT=0x08
}En_USART_STOP_BIT_SELECT_t;


/*
*** the values of this baud rate are only compatible with FOSC=16MHz and double speed mode is disabled
*/
typedef enum En_USART_BAUD_RATE_SELECT_t{
	USART_9600_BAUD_RATE=0x0067, USART_4800_BAUD_RATE=0x00Cf
}En_USART_BAUD_RATE_SELECT_t;


/*primitive types*/
typedef struct USART_CFG
{
	En_USART_MODE_t USART_MODE;
	En_USART_RECEIVE_TRANSMIT_t USART_RX_TX;
	En_USART_CHAR_DATA_NUMBER_t CHAR_DATA_NUMBER;
	En_USART_PARITY_MODE_t USART_PARITY;
	En_USART_CLOCK_POLARITY_t USART_CLOCK_POLARITY;
	En_USART_STOP_BIT_SELECT_t STOP_BIT_SELECT;
	En_USART_INTERRUPTS_t USART_INTERRUPTS;
	En_USART_BAUD_RATE_SELECT_t USART_BAUD_RATE_SELECT;

}USART_CFG_t;


/* function declarations*/
extern void USART_SEND_POLLING(uint8_t Data);
extern ERROR_STATUS USART_Init2(USART_CFG_t* USART_CFG);
extern uint8_t USART_Receive_POLLING(void);
extern void UART_Send_String(uint8_t str[]);
extern uint8_t USART_Receive_NO_POLLING(void);
extern void USART_SEND_NO_POLLING(uint8_t Data);
extern void UART_Tx_CallBack_Set(void (*Ptr_Uart_Tx_CallBack) (void));
extern void UART_Rx_CallBack_Set(void (*Ptr_Uart_Rx_CallBack) (void));
extern void UART_Send_String_NO_POLLING();
#endif /* UART_H_ */
