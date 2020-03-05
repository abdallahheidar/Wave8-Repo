/*
* UART.c
*
* Created: 2/9/2020 3:17:33 PM
*  Author: Khaled
*/

#include "UART.h"

#define	NINTH           0x0100
#define  GETRXB8         (UCSRB >> 1) & 0x01
#define  NINTHBITVALUE   (Ninth_Bit << 8)

#define  BAUD_RATE_9600_NORMAL_SPEED    103
#define  BAUD_RATE_9600_DOUBLE_SPEED    0xCF
#define  BAUD_RATE_115200_NORMAL_SPEED  0x08
#define  BAUD_RATE_115200_DOUBLE_SPEED  0x10
#define  UCSRC_INITAIL_VALUE            0x00


static volatile uint8_t gu8_Data;
static volatile uint8_t gu8_interrupt;
volatile uint8_t * Transmit_complet = NULL;
volatile void(* ptr_CBK)(uint8_t); 


static void CBK_Send (void);



void UART_INIT (En_UartParity_t en_parity, En_UartStopBit_t en_stop_bit, En_UartDataFrameSize_t en_data_frame_size, En_UartBaudRate_t en_baud_rate, 
					 En_UartSpeed_t en_speed,En_UartMultiProcessorCommunication_t en_multi_processor_communication,En_UartInterrupt_t en_interrupt_mode,
					 void(* ptr_RCBK)(uint8_t))
{
	uint8_t UCSRC_Value = UCSRC_INITAIL_VALUE;
	

		
	/*Disable global interrupt*/
	CLEAR_BIT (SREG, BIT_7);

	/*set Tx as output bit*/
	SET_BIT (PORTD_DIR, BIT_1);

	/*set Rx as input bit*/
	CLEAR_BIT (PORTD_DIR, BIT_0);
	
	CLEAR_BIT (UCSRA, UDRE);

	CLEAR_BIT (UCSRA, FE);
	
	CLEAR_BIT (UCSRA, DOR);

	CLEAR_BIT (UCSRA, PE);

	switch(en_speed)
	{
		case Uart_Async_Normal_Speed:
		CLEAR_BIT (UCSRA,U2X);
		break;

		case Uart_Async_Double_Speed:
		SET_BIT (UCSRA,U2X);
		break;
	}

	switch (en_multi_processor_communication)
	{
	   case Uart_Multi_Processor_Communication_Disable:
		CLEAR_BIT (UCSRA, MPCM);
		break;

		case Uart_Multi_Processor_Communication_Enable:
		SET_BIT (UCSRA, MPCM);
	}


	/*set ninth bit low as a initial value*/
	CLEAR_BIT (UCSRB, TXB8);
	/*set ninth bit low as a initial value*/
	CLEAR_BIT (UCSRB, RXB8);
	/*disable UDR interrupt*/
	CLEAR_BIT (UCSRB, UDRIE);
	/*disable TX interrupt*/
	CLEAR_BIT (UCSRB, TXCIE);
	/*disable RX interrupt*/
	CLEAR_BIT (UCSRB, RXCIE);
	 /*Enable UART Transmitter*/
	 SET_BIT (UCSRB, TXEN);
	 /*Enable UART Reception*/
	 SET_BIT (UCSRB, RXEN);
	 	/*set URSEL bit to select UCSRC reg during writing operation*/
	SET_BIT (UCSRC_Value, URSEL);
/*	UCSRC |= 0x80;*/
	/*select Asynchronous Operation*/
	CLEAR_BIT (UCSRC_Value, UMSEL);

	switch (en_parity)
	{
		case Uart_Parity_no:
		CLEAR_BIT (UCSRC_Value, UPM0);
		CLEAR_BIT (UCSRC_Value, UPM1);
		break;

		case Uart_Parity_Even:
		CLEAR_BIT (UCSRC_Value, UPM0);
		SET_BIT (UCSRC_Value, UPM1);
		break;

		case Uart_Parity_Odd:
		SET_BIT (UCSRC_Value, UPM0);
		SET_BIT (UCSRC_Value, UPM1);
		break;
	}

	switch (en_stop_bit)
	{
		case Uart_Stop_Bit_One:
		CLEAR_BIT (UCSRC_Value, USBS);
		break;

		case Uart_Stop_Bit_Two:
		SET_BIT (UCSRC_Value, USBS);
		break;
	}

	switch(en_data_frame_size)
	{
		case Uart_Data_5_Bit:
		CLEAR_BIT (UCSRB, UCSZ2);
		CLEAR_BIT (UCSRC_Value, UCSZ1);
		CLEAR_BIT (UCSRC_Value, UCSZ0);
		break;

		case Uart_Data_6_Bit:
		CLEAR_BIT (UCSRB, UCSZ2);
		CLEAR_BIT (UCSRC_Value, UCSZ1);
		SET_BIT (UCSRC_Value, UCSZ0);
		break;

		case Uart_Data_7_Bit:
		CLEAR_BIT (UCSRB, UCSZ2);
		SET_BIT (UCSRC_Value, UCSZ1);
		CLEAR_BIT (UCSRC_Value, UCSZ0);
		break;

		case Uart_Data_8_Bit:
		CLEAR_BIT (UCSRB, UCSZ2);
		SET_BIT (UCSRC_Value, UCSZ1);
		SET_BIT (UCSRC_Value, UCSZ0);
		break;

		case Uart_Data_9_Bit:
		SET_BIT (UCSRB, UCSZ2);
		SET_BIT (UCSRC_Value, UCSZ1);
		SET_BIT (UCSRC_Value, UCSZ0);
		break;
	}
	
	/*CLEAR Clock polarity during asynchronous mode*/
	CLEAR_BIT (UCSRC_Value,UCPOL);
	UCSRC = UCSRC_Value;
	switch(en_baud_rate)
	{
	   /*clear URSEL bit to select UBRRH register in writing operation*/
		//CLEAR_BIT (UBRRH, URSEL);

		case Uart_Baud_Rate_9600:
		if (Uart_Async_Normal_Speed == en_speed)
		{
		   UBRRL = BAUD_RATE_9600_NORMAL_SPEED;
			//UBRRH = 0x00;
		}
		else if (Uart_Async_Double_Speed == en_speed)
		{
		   UBRRL = BAUD_RATE_9600_DOUBLE_SPEED;
		//	UBRRH = 0x00;
		}
		break;

		case Uart_Baud_Rate_115200:
		if (Uart_Async_Normal_Speed == en_speed)
		{
			UBRRL = BAUD_RATE_115200_NORMAL_SPEED;
			//UBRRH = 0x00;
		}
		else if (Uart_Async_Double_Speed == en_speed)
		{
			UBRRL = BAUD_RATE_115200_DOUBLE_SPEED;
		//	UBRRH = 0x00;
		}
		break;
	}
	
		gu8_interrupt = en_interrupt_mode;
		ptr_CBK = ptr_RCBK;
		if (en_interrupt_mode == Uart_Interrupt)
		{
			SET_BIT(UCSRB,RXCIE);

			SET_BIT(SREG, BIT_7);
		}
		
	
}


void UART_TRANSMIT_Char (uint8_t Data, uint8_t * not)
{
   switch(gu8_interrupt)
	{
	case Uart_Polling:
	/*check if transmit buffer register is empty to write Data to UDR*/
	while (!(UCSRA & UDRE)) ;

	/* Copy 9th bit to TXB8 */
	UCSRB &= ~(TXB8);

	if ( Data & NINTH )
	
	UCSRB |= (TXB8);

	/* Put data into buffer, sends the data*/
	UDR = Data;
	break;

	case Uart_Interrupt:
	gu8_Data = Data;

	Transmit_complet = not;
	*Transmit_complet = 0;

	/*enable interrupt*/
	SET_BIT(SREG,BIT_7);
	
	SET_BIT (UCSRB,UDRIE);

	SET_BIT(UCSRB,TXCIE);
	break;
	}
}


/*transmit call back function*/
void CBK_Send (void)
{
   UDR = gu8_Data;
	
	/*disable UDRE interrupt*/
	CLEAR_BIT(UCSRB,UDRIE);
	
}

/*UDRE ISR*/
_ISR__ (USART_UDRE_vect)
{
   CBK_Send();

}

/*end sending notification*/
_ISR__ (USART_TXC_vect)
{
   *Transmit_complet = 0xFF;
	CLEAR_BIT(UCSRB,TXCIE);
}



uint8_t UART_RECEIVE (void)
{
   uint8_t Error_Check, Ninth_Bit;

	

	/* Wait for data to be received*/
	while (!(UCSRA & RXC));

	/* Get error*/ 
	Error_Check = (FE)|(DOR)|(PE);

	/* Get 9th bit*/ 
	Ninth_Bit = GETRXB8;
	       
	/* Check errors*/
	if (Error_Check & UCSRA);
	/* THIS MEAN THERE IS ERROR IN RECEVED FRAME*/

	/* Filter the 9th bit, then return*/
	return (NINTHBITVALUE | UDR);
}


void UART_RECEIVE_String (uint8_t * Data)
{
   uint8_t au8_Char_Poition = 0;

   Data[au8_Char_Poition] = UART_RECEIVE();
   
	while (Data[au8_Char_Poition] != '\r')
	{
	   au8_Char_Poition++;
		Data[au8_Char_Poition] = UART_RECEIVE();
	}
	
}


void UART_TRANSMIT_String (uint8_t * Data)
{
	uint8_t au8_Char_Poition = 0;
	
	while (Data[au8_Char_Poition] != '\0')
	{
		UART_TRANSMIT_Char(Data[au8_Char_Poition],NULL);
		 au8_Char_Poition ++;
	}
	
}


_ISR__(USART_RXC_vect)
{
   ptr_CBK(UDR);
  
}