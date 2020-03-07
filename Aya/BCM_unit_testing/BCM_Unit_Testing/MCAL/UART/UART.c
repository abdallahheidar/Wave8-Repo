/*
 * UART.c
 *
 * Created: 3/1/2020 9:58:21 PM
 *  Author: A_ayman
 */

/* inclusions */
#include "UART.h"
#include "../../Testing/BCM_unit_Testing.h"

/*LOCAL MACROS*/

/*LOCAL Data types */

/*LOCAL FUNCTIONS PROTOTYPES */

/* GLOBAL STATIC VARIABLES */

//pointer to the call back UART transmit interrupt function
static void (*Ptr_Uart_Tx_INT) (void)=NULL;

//pointer to the call back UART receive interrupt function
static void (*Ptr_Uart_Rx_INT) (void);


/* GLOBAL EXTERN VARIABLES */
volatile uint8_t gu8_Uart_Rec_Data='0';

/*- APIs IMPLEMENTATION --*/
ERROR_STATUS USART_Init2(USART_CFG_t* USART_CFG)
{

	return gu8_UART_Init_Return;
}

void USART_SEND_POLLING(uint8_t Data)
{
	while (!(UCSRA&(1<<UDRE)));  //waiting for the transmit buffer (UDR) to be empty
	UDR=Data;
}

uint8_t USART_Receive_POLLING(void)
{

	while ((UCSRA&(1<<RXC))==0);  //waiting for the data to be received
	gu8_Uart_Rec_Data=UDR;
	return gu8_Uart_Rec_Data;

}

void USART_SEND_NO_POLLING(uint8_t Data)
{
	UDR=Data;
}



void UART_Send_String(uint8_t* str)
{
	uint16_t i=0;
	while(str[i] != '\0')
	USART_SEND_POLLING(str[i++]);
}
uint8_t USART_Receive_NO_POLLING(void)
{

	return UDR;

}

/*
void UART_Send_String_NO_POLLING()
{
	static uint16_t i=0;
	if (str[i] != '\0')
	USART_SEND_NO_POLLING(str[i++]);
}*/

void UART_Tx_CallBack_Set(void (*Ptr_Uart_Tx_CallBack) (void))
{

	Ptr_Uart_Tx_INT=Ptr_Uart_Tx_CallBack;
}

void UART_Rx_CallBack_Set(void (*Ptr_Uart_Rx_CallBack) (void))
{

	Ptr_Uart_Rx_INT=Ptr_Uart_Rx_CallBack;
}
ISR(USART_RXC_vect)
{

	 (*Ptr_Uart_Rx_INT)();

}
ISR (USART_TXC_vect)
{
	(*Ptr_Uart_Tx_INT)();
	//UART_Send_String_NO_POLLING();
}
