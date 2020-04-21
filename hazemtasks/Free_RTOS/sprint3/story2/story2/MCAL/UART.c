/*
 ============================================================================
 Name        : UART.c
 Author      : Muhammed Gamal
 Description : this file includes the implementation of all UART functions
 ============================================================================
 */

/********************************includes***************************************/
#include "UART.h"
/*******************************************************************************/

/********************************definitions********************************/
//#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
#define NULL_PTR ((void*)0)
#define FLAG_LOW              0
#define FLAG_HIGH             1
/********************************************************************************/

/********************************global variables********************************/
volatile uint8_t g8_udr_data[16];
volatile uint8_t g8_UART_TX_FLAG=FLAG_LOW;
volatile uint8_t g8_UART_RX_FLAG=FLAG_LOW;
volatile uint8_t gu8_counterrec=0;
/* Global variables to hold the address of the call back function in the application */
volatile void (*g_UART_sender_CallBackPtr)(void) = NULL_PTR;
volatile void (*g_UART_receiver_CallBackPtr)(void) = NULL_PTR;
/********************************************************************************/


//static UART_Config_Structure * UART_Init_Structure = NULL_PTR;


/********************************Functions Definitions***********************************/
void UART_init(const UART_Config_Structure * UART_Init_Structure)
{
	uint8_t UCSRC_Value;
	//uint8_t UBRRH_Value;
	/****************************UCSRA Description************************
	 * U2X => double transmission speed
	 * MPCM =>Multi processor communication
	 *********************************************************************/
    sei();
	UCSRA = UART_Init_Structure->Speed_Mode | UART_Init_Structure->Multi_Processor_Comm_Mode;

	/************************** UCSRB Description **************************
	 * RXCIE => USART RX Complete Interrupt
	 * TXCIE => USART Tx Complete Interrupt
	 * UDRIE => USART Data Register Empty Interrupt
	 * RXEN  => Receiver Enable
	 * RXEN  => Transmitter Enable
	 * UCSZ2 => 9-bit data mode... bit number nine used as identify the frame as data frame or address frame
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/

	UCSRB = UART_Init_Structure->Receive_Complete_Inter | UART_Init_Structure->Transmit_Complete_Inter |
			UART_Init_Structure->Data_Reg_Empty_Inter | UART_Init_Structure->Receive_Mode |
			UART_Init_Structure->Transmit_Mode | UART_Init_Structure->Nine_Bits_Receive_Mode |
			UART_Init_Structure->Nine_Bits_Transmit_Mode;

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   => Asynchronous Operation
	 * UPM1:0  => parity mode
	 * USBS    => stop bit mode
	 * UCSZ1:0 => data mode
	 * UCPOL   => Clk Polarity... Used with the Synchronous operation only
	 ***********************************************************************/

	UCSRC_Value = (1<<URSEL) | UART_Init_Structure->Synch_Mode | UART_Init_Structure->Parity_Mode |
			UART_Init_Structure->Stop_Bit_Mode | UART_Init_Structure->Clk_Polarity_Mode |
			UART_Init_Structure->Char_Size;


	UCSRC = UCSRC_Value;
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	//UBRRH_Value = (0X0F) & (UART_Init_Structure->Double_Speed_Baud_Rate>>8);
	//UBRRH = UBRRH_Value;
	UBRRH = (UART_Init_Structure->Double_Speed_Baud_Rate>>8);
	UBRRL = UART_Init_Structure->Double_Speed_Baud_Rate;

}


void UART_sendByte(const uint8_t data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = data;
}


void UART_sendByte_INT(const uint8_t data)
{
	if(g8_UART_TX_FLAG==FLAG_LOW)
	{
		g8_UART_TX_FLAG=FLAG_HIGH;
		UDR = data;
	}
}


uint8_t UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
    return UDR;
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
/****************************************************************************************/

/***************************UART interrupt functions*************************************/
ISR(USART_TXC_vect)
{
	g8_UART_TX_FLAG = FLAG_LOW;
}

ISR(USART_RXC_vect)
{
	g8_udr_data[gu8_counterrec] = UDR;
	gu8_counterrec++;
	g8_UART_RX_FLAG = FLAG_HIGH;
	if(gu8_counterrec==1)
	{
		LCD_goToRowColumn(1,0);
	}
	LCD_displayCharacter(gu8_counterrec+48);
	if(gu8_counterrec==5)
	{
		
		LCD_goToRowColumn(0,0);
	}
		
	
}
