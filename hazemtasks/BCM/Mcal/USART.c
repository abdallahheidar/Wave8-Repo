/*
 * USART.c
 *
 * Created: 2/9/2020 2:01:56 PM
 *  Author: Ema
 */ 

#include "USART.h"

usart_cbk_ptr guUsart_RX_Cbk;

static uint8_t guUSART_Mode;

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void USART_init(USART_Config * UART_config)
{
	uint8_t UCSRC_URSEL_Value= 128;
	guUSART_Mode = UART_config->Intrrupt;
	
	if (guUSART_Mode == InterruptRX_EN)
	{
		
		guUsart_RX_Cbk = UART_config->usart_cbk_ptr;
	}
	
	
	//guUsart_RX_Cbk = UART_config->Usart_Cbk_ptr;			//set RX_ISR call back
	
	UCSRA.B.U2X1 = UART_config->Speed;
	UCSRB.UCSRB_ST.TXEN1 = UART_config->Tx_enable;
	UCSRB.UCSRB_ST.RXEN1 = UART_config->Rx_enable;
	UCSRB.UCSRB_ST.RXCIE1 = UART_config->Intrrupt;
	
	UCSRC.UCSRC_B = UCSRC_URSEL_Value|(UART_config->Parity)|(UART_config->Stop)|(UART_config->Mode)|(UART_config->DataSize); 
	
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
	
}

void UART_sendByte(const uint8_t data)
{UDR = data;
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	
	
	while(BIT_IS_CLEAR(UCSRA.UCSRA_B,UDRE)){
	
	}
		
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	
}

uint8_t UART_recieveByte(void)
{
	volatile uint8_t RX_Data = 0;
	
	if (guUSART_Mode == InterruptRX_EN)
	{
		RX_Data = UDR;
	}
	else
	{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA.UCSRA_B,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    RX_Data = UDR;
	}
	return RX_Data;
}

uint8_t UART_Tx_getStatus(void)
{
	return (UCSRA.B.TXC1);
}

void UART_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}

ISR(USART_RXC_vect)
{
	guUsart_RX_Cbk();
}