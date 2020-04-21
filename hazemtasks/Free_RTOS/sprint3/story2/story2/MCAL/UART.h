/*
 ============================================================================
 Name        : UART.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef UART_H_
#define UART_H_


#include "../Common/std_types.h"
#include "../Common/common_macros.h"
#include "../MCAL/interrupt.h"
#include "../Hall/lcd.h"

/***************************************************/
/******************************************************************************/


/*******************************************************************************/

/***********************************ENUMs*************************************/

/********************************ENUMs for UBRR************************/
typedef enum En_USART_BAUDRATE_DOUBLE_SPEED_t{
	BAUD100=19999,BAUD200=9999,BAUD300=6666,BAUD1200=1666,BAUD2400=832,BAUD4800=416,
/*UDRR=     19999,    9999    ,     6666   ,     1666    ,      832    ,      416    ,*/
	BAUD9600=207,BAUD19200=103,BAUD38400=51,BAUD57600=34,BAUD115200=16
/*UDRR=   207   ,      103      ,       51      ,       34      ,        16       */
}En_USART_BAUDRATE_DOUBLE_SPEED_t;
/*************************************************************************/

/********************************ENUMs for UCSRC************************/
typedef enum En_USART_SYNCH_MODE_t
{
	USART_ASYNCH =0 ,
	USART_SYNC = (1<<UMSEL)
}En_USART_SYNCH_MODE_t;

typedef enum En_USART_PARITY_MODE_t
{
	USART_NO_PARITY =0,
	USART_EVEN_PARITY =(1<<UPM1),
	USART_ODD_PARITY = (1<<UPM1) | (1<<UPM0)
}En_USART_PARITY_MODE_t;

typedef enum En_USART_STOPBIT_t
{
	USART_1_STOPBIT =0,
	USART_2_STOPBIT =(1<<USBS)
}En_USART_STOPBIT_t;

typedef enum En_USART_CLK_POLARITY_t
{
	TX_RISING_RX_FALLING =0,
	TX_FALLING_RX_RISING =(1<<UCPOL)
}En_USART_CLK_POLARITY_t;

typedef enum En_USART_CHAR_SIZE_t
{
	USART_5_Bit_CHAR =0,
	USART_6_Bit_CHAR =(1<<UCSZ0),
	USART_7_Bit_CHAR =(1<<UCSZ1),
	USART_8_Bit_CHAR =(1<<UCSZ0) | (1<<UCSZ1),
	USART_9_Bit_CHAR_UCSRC =(1<<UCSZ0) | (1<<UCSZ1),  /*this mode activates by two registers*/
	USART_9_Bit_CHAR_UCSRB =(1<<UCSZ2)
}En_USART_CHAR_SIZE_t;

/****************************************************************************/

/********************************UCSRB**********************************/

typedef enum En_USART_RX_COMPLETE_INTER_t
{
	RX_COMPLETE_INTER_DISABLE=0,
	RX_COMPLETE_INTER_ENABLE=(1<<RXCIE)
}En_USART_RX_COMPLETE_INTER_t;

typedef enum En_USART_TX_COMPLETE_INTER_t
{
	TX_COMPLETE_INTER_DISABLE=0,
	TX_COMPLETE_INTER_ENABLE=(1<<TXCIE)
}En_USART_TX_COMPLETE_INTER_t;

typedef enum En_USART_DATA_REG_EMPTY_INTER_t
{
	DATA_REG_EMPTY_INTER_DISABLE=0,
	DATA_REG_EMPTY_INTER_ENABLE=(1<<UDRIE)
}En_USART_DATA_REG_EMPTY_INTER_t;

typedef enum En_USART_RECIEVE_t
{
	USART_RECIEVE_DISABLE=0,
	USART_RECIEVE_ENABLE=(1<<RXEN)
}En_USART_RECEIVE_t;

typedef enum En_USART_TRANSMIT_t
{
	USART_TRANSMIT_DISABLE=0,
	USART_TRANSMIT_ENABLE=(1<<TXEN)
}En_USART_TRANSMIT_T;

typedef enum En_USART_NINE_BITS_RECEIVE_t
{
	USART_NINE_BITS_RECEIVE_DISABLE=0,
	USART_NINE_BITS_RECEIVE_ENABLE=(1<<TXB8)
}En_USART_NINE_BITS_RECEIVE_t;

typedef enum En_USART_NINE_BITS_TRANSMIT_t
{
	USART_NINE_BITS_TRANSMIT_DISABLE=0,
	USART_NINE_BITS_TRANSMIT_ENABLE=(1<<RXB8)
}En_USART_NINE_BITS_TRANSMIT_t;

/***************************************************************************/

/********************************UCSRA**********************************/
typedef enum En_USART_SPEED_MODE_t
{
	USART_NORMAL_SPEED=0,
	USART_DOUBLE_SPEED=(1<<U2X)
}En_USART_SPEED_MODE_t;

typedef enum En_USART_MULTI_PROCESSOR_COMM_t
{
	MULTI_PROCESSOR_COMM_DISABLE=0,
	MULTI_PROCESSOR_COMM_ENABLE=(1<<MPCM)
}En_USART_MULTI_PROCESSOR_COMM_t;

 /****************************************************************************/

/********************************structures*********************************/
typedef struct
{
	En_USART_SYNCH_MODE_t Synch_Mode;
	En_USART_PARITY_MODE_t Parity_Mode;
	En_USART_STOPBIT_t Stop_Bit_Mode;
	En_USART_CLK_POLARITY_t Clk_Polarity_Mode;
	En_USART_CHAR_SIZE_t Char_Size;
	En_USART_RX_COMPLETE_INTER_t Receive_Complete_Inter;
	En_USART_TX_COMPLETE_INTER_t Transmit_Complete_Inter;
	En_USART_DATA_REG_EMPTY_INTER_t Data_Reg_Empty_Inter;
	En_USART_RECEIVE_t Receive_Mode;
	En_USART_TRANSMIT_T Transmit_Mode;
	En_USART_NINE_BITS_RECEIVE_t Nine_Bits_Receive_Mode;
	En_USART_NINE_BITS_TRANSMIT_t Nine_Bits_Transmit_Mode;
	En_USART_SPEED_MODE_t Speed_Mode;
	En_USART_MULTI_PROCESSOR_COMM_t Multi_Processor_Comm_Mode;
	En_USART_BAUDRATE_DOUBLE_SPEED_t Double_Speed_Baud_Rate;
}UART_Config_Structure;
/***************************************************************************/

/****************************Functions Prototypes****************************/
void UART_init(const UART_Config_Structure * UART_Init_Structure);
void UART_sendByte(const uint8_t data);
void UART_sendByte_INT(const uint8_t data);
uint8_t UART_recieveByte(void);
void UART_sendString(const uint8_t *Str);
void UART_receiveString(uint8_t *Str);
void UART_set_UDR(void);
/****************************************************************************/



/****************************Global variables****************************/
extern volatile uint8_t g8_udr_data[16];
extern volatile uint8_t gu8_counterrec;
extern volatile uint8_t g8_UART_RX_FLAG;
extern volatile void (*g_UART_sender_CallBackPtr)(void);
volatile void (*g_UART_receiver_CallBackPtr)(void);
/****************************************************************************/
#endif /* UART_H_ */


