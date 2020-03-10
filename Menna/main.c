/*
 * TMU.c
 *
 * Created: 2/23/2020 9:32:04 PM
 * Author : Khaled Magdy
 */ 
#include "SL/BCM.h"
#include "MCAL/UART.h"
#include "util/softwareDelay.h"

#include "DIO.h"
#include "TMU.h"
#include "avr/interrupt.h"


/**=========================================================================*
 *								Defines & Globals							*
 *==========================================================================*/

#define TRANSMIT_MAX 255
#define RECEIVE_MAX  255
#define ENTER_KEY	 0x0D

BCM_cfg_s BCM1;
UART_cfg UART1;

uint8_t rxBuffer[RECEIVE_MAX];
uint8_t txBuffer[TRANSMIT_MAX];

volatile uint8_t a_index        = ZERO;
volatile uint8_t msg_len        = ZERO;
volatile uint8_t g_TxBuffer_Len = ZERO;
volatile uint8_t g_UART_TXindex = ZERO;
volatile uint8_t BCM_sending    = FALSE;


/**=========================================================================*
 *							TMU TASKS				                    	*
 *==========================================================================*/

void toggle1(void){
	DDRA = 0x0F ;
	PORTA_DATA ^= 0x0F ;
	
}

void toggle2(void){
	DDRA = 0xFF ;
	PORTA_DATA ^= 0xF0 ;
	
}

/**=========================================================================*
 *							BCM Notification Functions						*
 *==========================================================================*/

/* TX Completion Notification Routine */
void txnotify(enum_BcmStatus st)
{
	BCM_sending = FALSE ;
	g_UART_TXindex = ZERO;
	BCM_DeInit(&BCM1);
	BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);
}
	
/* RX Completion Notification Routine */
void rxnotify(enum_BcmStatus st)
{	
	msg_len = BCM_Get_msgLEN();
	UART_Write(rxBuffer[a_index++]);
}

/**=========================================================================*
 *							UART TX / RX ISR Handlers						*
 *==========================================================================*/

/* UART Reception Completion ISR Handler*/
void UART_ISR_RXcbf(void)
{
	if (BCM_sending==FALSE)
	{
		if(g_UART_TXindex < TRANSMIT_MAX)
		{
			txBuffer[g_UART_TXindex++] = UART_Read();
			if(txBuffer[g_UART_TXindex-1] == ENTER_KEY)
			{
				BCM_Send(txBuffer, g_UART_TXindex, &BCM1, txnotify);
				g_UART_TXindex = ZERO;
			}
		}
		else
		{
			BCM_Send(txBuffer, g_UART_TXindex, &BCM1, txnotify);
			BCM_sending = TRUE;
			g_UART_TXindex = ZERO;	
		}
	}
	
}

/* UART Transmission Completion ISR Handler */
void UART_ISR_TXcbf(void)
{
	if(a_index < msg_len)
	{	
		UART_Write(rxBuffer[a_index++]);	
	}
	else if(a_index == msg_len)
	{
		UART_Write('\n');
		a_index++;
	}
	else
	{
		a_index = ZERO;
	}
}

/**=========================================================================*
 *					BCM Applications For ECU1 & ECU2						*
 *==========================================================================*/

void ECU1_Application(void)
{
	/*-------------[ BCM Initialization ]-------------*/
	BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Tx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);
	
	/*-------------[ UART Initialization ]-------------*/
	UART1.baudrate   = 9600;
	UART1.dataBits   = UART_Bits_8;
	UART1.stopBits   = StopBits_1;
	UART1.parity     = No_Parity;
	UART1.sampleEdge = RisingEdg;
	UART1.uartSync   = UART_Async;
	UART1.mode       = UART_RX;
	UART1.uartInterrupts = OnRx;
	UART_SetRX(UART_ISR_RXcbf);
	UART_Init(&UART1);
	
	/*-------------[ SUPER LOOP ]-------------*/
	while (1)
	{
		BCM_Tx_Dispatcher();
	}
}

void ECU2_Application(void)
{
	/*-------------[ BCM Initialization ]-------------*/
	BCM1.BCM_CH_ID = 1;
	BCM1.Mode = BCM_Rx_Mode;
	BCM1.Protocol = SPI_Protocol;
	BCM_Init(&BCM1);
	BCM_Setup_RxBuffer(&BCM1, RECEIVE_MAX, rxBuffer, rxnotify);
	
	/*-------------[ UART Initialization ]-------------*/
	UART1.baudrate   = 9600;
	UART1.dataBits   = UART_Bits_8;
	UART1.stopBits   = StopBits_1;
	UART1.parity     = No_Parity;
	UART1.sampleEdge = RisingEdg;
	UART1.uartSync   = UART_Async;
	UART1.mode       = UART_TX;
	UART1.uartInterrupts = OnTx;
	UART_SetTX(UART_ISR_TXcbf);
	UART_Init(&UART1);
	
	/*-------------[ SUPER LOOP ]-------------*/
	while (1)
	{
		BCM_Rx_Dispatcher();
	}
}

/**=========================================================================*
 *								Main Function								*
 *==========================================================================*/

int main(void)
{
	//ECU2_Application();
	//ECU1_Application();
	
	
	
	
/**=========================================================================*
 *								TMU TEST CODE								*
 *==========================================================================*/
	
	
	sei();
	
	TMU_Cfg_s TMU_cfg1 ;
	TMU_cfg1.Timer_channel = TMU_TIMER_CH2 ;
	TMU_cfg1.TMU_Reselution = reselution_one_mili ;
	
	TMU_Init(&TMU_cfg1);
	
	TMU_tsak_s TMU_task1 ;
	TMU_task1.delay_time = 1000;
	TMU_task1.Ptr_FunctionCall = toggle1;
	TMU_task1.Task_ID = 1;
	TMU_task1.TMU_mode = PERIODIC ;
	
	TMU_Start_Timer(&TMU_task1) ;
	
	TMU_tsak_s TMU_task2 ;
	TMU_task2.delay_time = 500;
	TMU_task2.Ptr_FunctionCall = toggle2;
	TMU_task2.Task_ID = 2;
	TMU_task2.TMU_mode = PERIODIC ;
	
	TMU_Start_Timer(&TMU_task2) ;
	
    while (1) 
    {
		TMU_Dispatch();
    }
	
	
}
