// /*Sender 20 Element*/
// 
// /*
//  * BCM_Sender.c
//  *
//  * Created: 3/5/2020 12:29:02 PM
//  * Author : Mohamed Ramadan & Harby
//  */ 
// 
// 
// /*- INCLUDES -----------------------------------------------*/
// 
// //#include <avr/io.h>
// #include "BCM.h"
// #include "util/delay.h"
// 
// 
// 
// /*- DEFINITIONS --------------------------------------------*/
// 
// #define OVERHEAD 		4
// #define ELEMENTS(X)		(X + OVERHEAD)
// 
// #define UART_DONE		1
// #define UART_NOT_DONE	0
// 
// /*- GLOBAL STATIC VARIABLES --------------------------------*/
// 
// //static uint8_t testing_arr[ELEMENTS(21)] = {1, 2, 3, 4, 5, 6, 7,
// //		8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
// 
// volatile sint8_t ReceivedString[ELEMENTS(20)];
// 
// volatile uint8_t uart_counter = 0;
// 
// static uint8_t i = 0;
// 
// void Uart_receivingApp(void)
// {
// 	ReceivedString[i] = UART_receive();
// 	PORTA_DIR = ReceivedString[i];
// 	uart_counter++;
// 	i++;
// }
// 
// int main(void)
// {
// 	uint8_t UART_status = 0;
// 	
// 	UART_ConfigType UART_cfg = {
// 		UART_ASYNCHRONOUS_MODE,
// 		UART_RECEIVER_MODE,
// 		UART_EIGHT_BITS,
// 		UART_PARITY_DISABLED,
// 		UART_ONE_STOP_BIT,
// 		UART_INTERRUPT_ENABLED
// 	};
// 
// 	strBcmConfig_t BCM_cfg = {
// 		BCM_SPI_ID,
// 		BCM_TRANSMIT
// 	};
// 
// 	strBcmSendConfig_t BCM_startCfg = {
// 		BCM_SPI_ID,
// 		(uint8_t*)ReceivedString,
// 		ELEMENTS(20)
// 	};
// 
// 	BCM_Init(&BCM_cfg);
// 	UART_init(&UART_cfg);
// 	
// 	UART_RXC_setCallBack(Uart_receivingApp);
// 	
// 	sei();
// 
// 	while(1)
// 	{
// 		
// 		if(uart_counter == ELEMENTS(20))
// 		UART_status = UART_DONE;
// 
// 		if(UART_status == UART_DONE)
// 		{
// 			if(uart_counter == ELEMENTS(20))
// 			{
// 				BCM_Send(&BCM_startCfg);
// 			
// 				uart_counter++;
// 			}
// 			
// 			
// 			BCM_TxDispatch();
// 
// 		}
// 		
// 		
// 	}
// }


/*- INCLUDES -----------------------------------------------*/

//#include <avr/io.h>
#include "BCM.h"
#include "util/delay.h"


 #define OVERHEAD 			4
 #define ELEMENTS(X)		(X + OVERHEAD)

static uint8_t testing_arr[5] = {'A', 'B', 7, 8, 9};

strBcmConfig_t BCM_cfg = {
		BCM_SPI_ID,
		BCM_TRANSMIT
};

strBcmSendConfig_t BCM_startCfg = {
		BCM_SPI_ID,
		(uint8_t*)testing_arr,
		5
};

int main(void){
	
BCM_Init(&BCM_cfg);

sei();

BCM_Send(&BCM_startCfg);

while(1)
{
	
		BCM_TxDispatch();
	
}

}