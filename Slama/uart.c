/*
 * uart.c
 *

 * Created: 10-Feb-20 2:21:06 PM
 *  Author: ahmed
 */ 
#include "uart.h"
#include "interrupt.h"
#include "registers.h"



volatile static ptr_Function UART_Callback_TxC_Function;
volatile static ptr_Function UART_Callback_RxC_Function;

/************************************************************************/
/*			Uart_init, takes a structure of inits                       */
/************************************************************************/
ERROR_STATUS uart_init(init_uart *uart){
	
	/*clear all flags*/
	UCSRA =0;
	
	/*init all values*/
	UCSRC = ((uart->ur_sel) | ( uart->parity) | (uart->stop) | (uart->uart_mode) | (uart->frame_size) | (uart->polarity) |(uart->synch));
	
	/*write baud rate val*/
	UBRRL = (uart->baud);
	
	/*enable or disable "Tx/Rx" pins & interrupts*/
	UCSRB = ((uart->tx_rx_en) | (uart->tx_rx_irq));
	
	/*set transmiter and receiver callback*/
	UART_Callback_TxC_Function = uart->UART_TxC_Cbk_Function;
	UART_Callback_RxC_Function = uart->UART_RxC_Cbk_Function;
	
	return E_OK;
}

/*send a byte to tx pin*/
void uart_tx_send(uint8_t data_send){
	
	/*wait for the data register to be empty*/
	if((UCSRA & UDRE_EMPTY)){
	
	/*write your data in udr*/
	UDR = data_send;
	}
	/*wait till transmission completed*/
	//while(!(UCSRA & 0x40));
}

/*Rec byte from uart receive*/
uint8_t uart_rx(void){
	
	while(!(UCSRA & RX_COMP_FLAG));
	/*return the value of udr*/
	return UDR;
}

/*void set_callback(void (*local_ptr)(void))
{
	global_ptr = (volatile void(*)(void))local_ptr;
}
*/

ISR(USART_RXC_vect){
	

	UART_Callback_RxC_Function();
}