/*
 * UART.c
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "UART.h"
#include "UART_cfg.h"


/*- PREPROCESSOR MACROS -------------------------------------*/

#define MPCM	0
#define U2X		1
#define PE		2
#define DOR		3
#define FE		4
#define UDRE	5
#define TXC		6
#define RXC		7

#define TXB8	0
#define RXB8	1
#define UCSZ2	2
#define TXEN	3
#define RXEN	4
#define UDRIE	5
#define TXCIE	6
#define RXCIE	7

#define UCPOL	0
#define UCSZ0	1
#define UCSZ1	2
#define USBS	3
#define UPM0	4
#define UPM1	5
#define UMSEL	6
#define URSEL	7


/*- GLOBAL STATIC VARIABLES --------------------------------*/

static volatile void (*g_TXC_callBackPtr)(void) = NULL;
static volatile void (*g_RXC_callBackPtr)(void) = NULL;
static volatile void (*g_UDRE_callBackPtr)(void) = NULL;


/*- INTERRUPT SERVICE ROUTINES -----------------------------*/

ISR(USART_RXC_vect)
{
	if(g_RXC_callBackPtr != NULL)
	{
		g_RXC_callBackPtr();
	}
}

ISR(USART_UDRE_vect)
{
	if(g_UDRE_callBackPtr != NULL)
	{
		g_UDRE_callBackPtr();
	}
}

ISR(USART_TXC_vect)
{
	if(g_TXC_callBackPtr != NULL)
	{
		g_TXC_callBackPtr();
	}
}


/************************** UCSRA Register Description **************************
 * Abbreviated form of USART Control and Status Register A.						*
 *------------------------------------------------------------------------------*
 * RXC		: USART Receive Complete Flag (Set when there are unread data in	*
 * the receive buffer, and is cleared when the receive buffer is empty).		*
 * TXC		: USART Transmit Complete Flag (Set when the entire frame in the	*
 * transmit shift register has been shifted out and there is no new data		*
 * currently present in the transmit buffer (UDR), and cleared when ISR is		*
 * executed, In case of Polling, It can be cleared by writing a logical			*
 * one to it).																	*
 * UDRE		: USART Data Register Empty Flag (Set as long as the transmit		*
 * buffer (UDR) is empty, and therefore ready to be written, It is set after	*
 * a reset to indicate that the transmitter is ready).							*
 *------------------------------------------------------------------------------*
 * FE	= 0	: Frame Error (written as zero when writing to UCSRA).				*
 * DOR	= 0	: Data Overrun Error (written as zero when writing to UCSRA).		*
 * PE	= 0 : Parity Error (written as zero when writing to UCSRA).				*
 * U2X	= 0 : Double Transmission Speed (for asynchronous operation only).		*
 *------------------------------------------------------------------------------*
 * MPCM = 0 : Set when the receiver is exposed to more than one transmitter		*
 * and hence must use the address information to extract the correct			*
 * information, then, all the incoming frames received by the USART receiver	*
 * that do not contain address information will be ignored.						*
 * NOTE: The transmitter is unaffected by the MPCM setting 						*
 ********************************************************************************/

/*************************** UCSRB Register Description *************************
 * Abbreviated form of USART Control and Status Register B.						*
 *------------------------------------------------------------------------------*
 * RXCIE = 1/0	: Enable/Disable RX Complete Interrupt.							*
 * TXCIE = 1/0	: Enable/Disable TX Complete Interrupt.							*
 * UDRIE = 1/0	: Enable/Disable Data Register Empty Interrupt.					*
 *------------------------------------------------------------------------------*
 * RXEN			: Receiver Enable.												*
 * TXEN 		: Transmitter Enable.											*
 *------------------------------------------------------------------------------*
 * UCSZ2		: Character Size (combined with UCSZ1:0 bits in UCSRC Register).*
 * RXB8 & TXB8	: Receive/Transmit Data Bit 8 (This is the 9th data bit of the	*
 * received character when operating with serial frames with nine data bits, It	*
 * must be read/written before reading/writing the low bits from UDR).			*
 ********************************************************************************/

/*************************** UCSRC Register Description *************************
 * Abbreviated form of USART Control and Status Register C.						*
 *------------------------------------------------------------------------------*
 * URSEL = 1: USART Register Select (must be one when writing the UCSRC).		*
 * UMSEL = 0: USART Mode Select (0 for asynchronous operation and 1 for synch.)	*
 * UPM1:0	: Parity Mode.			(Table)										*
 * USBS		: Stop Bit Selection (0 for 1-bit and 1 for 2-bits).				*
 * UCSZ1:0	: Character Size.		(Table)										*
 * UCPOL 	: Clock Polarity. check data sheet									*
 ********************************************************************************/

/************************ UBRR(H & L) Register Description **********************
 * Abbreviated form of USART Baud Rate Registers.								*
 *------------------------------------------------------------------------------*
 * URSEL = 0: USART Register Select (must be zero when writing the UBRRH).		*
 * UBRRH:L	: The value entered to those two registers will determine the Baud	*
 * Rate at which the operation will occur.										*
 ********************************************************************************/


/*- APIs IMPLEMENTATION ------------------------------------*/

void UART_TXC_setCallBack(void(*local_ptr)(void))
{
	g_TXC_callBackPtr = (volatile void(*)(void))local_ptr;
}

void UART_RXC_setCallBack(void(*local_ptr)(void))
{
	g_RXC_callBackPtr = (volatile void(*)(void))local_ptr;
}

void UART_UDRE_setCallBack(void(*local_ptr)(void))
{
	g_UDRE_callBackPtr = (volatile void(*)(void))local_ptr;
}

void UART_init(const UART_ConfigType* ConfigPtr)
{
	/* Activating double speed mode */
	SET_BIT(UCSRA_R, U2X);

	/* Deciding whether the MCU will operate as a sender/receiver/sender and receiver */
	switch(ConfigPtr->communicationMode)
	{
	case UART_SENDER_MODE:
		SET_BIT(UCSRB_R, TXEN);
		if(ConfigPtr->interruptMode == UART_INTERRUPT_ENABLED)
			SET_BIT(UCSRB_R, TXCIE);
		break;
	case UART_RECEIVER_MODE:
		SET_BIT(UCSRB_R, RXEN);
		if(ConfigPtr->interruptMode == UART_INTERRUPT_ENABLED)
			SET_BIT(UCSRB_R, RXCIE);
		break;
	case UART_SENDER_RECEIVER_MODE:
		SET_BIT(UCSRB_R, TXEN);
		SET_BIT(UCSRB_R, RXEN);
		if(ConfigPtr->interruptMode == UART_INTERRUPT_ENABLED)
		{
			SET_BIT(UCSRB_R, TXCIE);
			SET_BIT(UCSRB_R, RXCIE);
		}
		break;
	}

	/* Selecting the character size (for the bits in UCSRB register) */
	UCSRB_R = (UCSRB_R & 0xFB) | (ConfigPtr->charSize & 0x04);

	UCSRC_R |= ConfigPtr->mode | ((ConfigPtr->charSize & 0x03) << UCSZ0) |
			(1 << URSEL) | ConfigPtr->parityMode | ConfigPtr->stopBits;

	/* Choosing the baud rate of the process */
	UBRRH_R = BAUDPRESCALE >> 8;
	UBRRL_R = BAUDPRESCALE;
}

void UART_deInit(void)
{
	UCSRA_R = 0x20;
	UCSRB_R = 0x00;
	UCSRC_R = 0x06;
	UBRRL_R = 0x00;
}

void UART_transmit(const uint8_t data)
{
	/* busy-waiting the UDRE bit in the UCSRA register in case interrupt is disabled */
	if(BIT_IS_CLEAR(UCSRB_R, TXCIE))
		while(BIT_IS_CLEAR(UCSRA_R, UDRE));
	/* sending the data */
	UDR = data;
}

uint8_t UART_receive(void)
{
	/* busy-waiting the RXC bit in the UCSRA register in case interrupt is disabled */
	if(BIT_IS_CLEAR(UCSRB_R, RXCIE))
		while(BIT_IS_CLEAR(UCSRA_R, RXC));
	/* read the received data */
	return UDR;
}

void UART_Send_String(char* str)
{
	uint8_t index = 0;
	uint8_t data = 0;

	while(str[index])
	{
		data=str[index++];
		UART_transmit(data);
	}
}


void UART_receiveString(sint8_t* Str)
{
	uint8_t i = 0;
	Str[i] = UART_receive();
	while(Str[i] != '\r')
	{
		i++;
		Str[i] = UART_receive();
	}
	Str[i] = '\0';
}
