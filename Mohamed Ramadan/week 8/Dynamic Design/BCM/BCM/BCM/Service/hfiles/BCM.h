/*
**BCM.h
*	Created on March/2/2020
*		Author:Mohamed Ramadan
*/

#ifndef BCM_H_ 
#define BCM_H_

/*********************************************
 *				Includes  					 *
 ********************************************/
#include "SPI.h"
#include "UART.h"
#include "std_types.h"
/*********************************************
 *				Defines  					 *
 ********************************************/
typedef uint8_t EnmBCMError_t;

/** Potocol ID: clarify the channel used to send or recieve data by BCM **/
#define BCM_UART				0
#define BCM_SPI					1
#define BCM_I2C					2

/** Protocol_Mode: clarify the Mode of sending data is sending or recieving it **/
#define BCM_UART_Send			0
#define BCM_UART_Recieve		1
#define BCM_UART_Send_Recieve	2
#define BCM_SPI_Send			3
#define BCM_SPI_Recieve			4

/** defines of Transmitter States **/
#define	Idle					0
#define SendingByte				1
#define SendingComplete			2

/** defines of Transmitter States **/
#define	Idle					0
#define RecievingByte			1				
#define RecievingComplete		2


/** Element not Defined Yet **/
#define UNDETERMINED			0x00

/************************************************************************/
/*			  Structures Declaration		                            */
/************************************************************************/
typedef struct  
{
	uint8_t Protocol_ID;
	uint8_t Protocol_Mode;
}strBcmConfig_t;


typedef struct  
{
	uint8_t Protocol_ID;
	uint8_t	no_of_bytes;
	uint8_t	CheckSum;
	uint8_t	*PtrAddress;	  
	void (*Bcm_Cbk_Ptr)(void);
	
}strBcmConfigStart_t;


/*********************************************
 *	  	   Function prototypes				 *
 ********************************************/
 
 /**
 * Func			: BCM_Init
 * Input		: Pointer to a structure of type strBcmConfig_t 
 *				contains the BCM_Channel or protocol and the mode sending or receiving.
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (BCM protocol,mode of data[Sending /Recieving])
 */
EnmBCMError_t BCM_Init(strBcmConfig_t *ConfigPtr);

/**
 * Func			: BCM_DeInit
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Uninitialized the Hardware module 
 */
EnmBCMError_t BCM_DeInit(uint8_t Protocol_ID);

/**
 * Func			: BCM_RxDispatch
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Implement BCM_RxDispatch check the flag of ISR and move between Receiving complete
					and Receiving Byte states and reconstruct the packet to extract only the user data. 
**/

EnmBCMError_t BCM_RxDispatch(void);
/**
 * Func			: BCM_TxDispatch
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Implement BCM_TxDispatch check the flag of ISR and move between Transmitting complete 
					and Transmitting Byte states and and construct the packet (Header – Data – Check SUM), 
					and the Header contain Command and the data size..
**/

EnmBCMError_t BCM_TxDispatch(void);

/**
 * Func			: BCM_Send
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Send shall invoked by the user to send the stream of data, it represent event creator.
**/
EnmBCMError_t BCM_Send(strBcmConfigStart_t *ConfigPtr);
/**
 * Func			: BCM_Receive
 * Input		: No Input
 *				
 * Output	
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: function BCM_Receive shall invoked by the user to recieve the stream of data.
**/
EnmBCMError_t BCM_Receive(strBcmConfigStart_t *ConfigPtr); 

#endif  /*BCM_H_*/