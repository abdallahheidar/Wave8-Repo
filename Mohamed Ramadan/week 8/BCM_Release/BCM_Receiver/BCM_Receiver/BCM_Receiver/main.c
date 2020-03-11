// /*
//  * BCM_Receiver.c
//  *
//  * Created: 3/5/2020 12:20:12 PM
//  * Author : Mohamed Ramadan
//  */ 
// 
// /*- INCLUDES ----------------------------------------*/
// //#include <avr/io.h>
// //#include "util/delay.h"
// #include "BCM.h"
// 
// 
// /*- DEFINITIONS --------------------------------------------*/
// 
// #define OVERHEAD 		4
// #define ELEMENTS(X)		(X + OVERHEAD)
// 
// #define BCM_DONE		1
// #define BCM_NOT_DONE	0
// 
// 
// volatile sint8_t SendingString[ELEMENTS(20)];
// 
// //volatile uint8_t uart_counter = 0;
// 
// //volatile uint8_t uart_flag = 1;
// 
// volatile uint8_t bcm_flag = BCM_NOT_DONE;
// 
// // void Uart_SendingApp(void)
// // {
// // 	uart_flag = 1;
// // }
// 
// void Bcm_CallBack(void)
// {
// 	bcm_flag = BCM_DONE;
// }
// 
// int main(void)
// {
// 	
// 	//static uint8_t i =0;
// // 	UART_ConfigType UART_cfg = {
// // 		UART_ASYNCHRONOUS_MODE,
// // 		UART_SENDER_MODE,
// // 		UART_EIGHT_BITS,
// // 		UART_PARITY_DISABLED,
// // 		UART_ONE_STOP_BIT,
// // 		UART_INTERRUPT_ENABLED
// // 	};
// 
// 	strBcmConfig_t BCM_cfg = {
// 		BCM_SPI_ID,
// 		BCM_RECEIVE
// 	};
// 	
// 	BCM_Init(&BCM_cfg);
// 	BCM_SetCallBack(Bcm_CallBack);
// 	
// 	
// 	sei();
// 	BCM_SetupRxBuffer(BCM_SPI_ID, (uint8_t*)SendingString, ELEMENTS(20));
// 
// 	while(1)
// 	{	
// 			BCM_RxDispatch();	
// 	}
// }


//#include <avr/io.h>
//#include "util/delay.h"
#include "BCM.h"


#define OVERHEAD 		4
#define ELEMENTS(X)		(X + OVERHEAD)

uint8_t Buffer[5];

strBcmConfig_t cfg = {
		BCM_SPI_ID,
		BCM_RECEIVE
};

int main(void)
{
BCM_Init(&cfg);

sei();

BCM_SetupRxBuffer(BCM_SPI_ID, (uint8_t*)Buffer, sizeof(Buffer));

while(1)
{
	BCM_RxDispatch();
}

}