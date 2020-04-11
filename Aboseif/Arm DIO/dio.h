/*
 * dio.h
 *
 * Created: 2020-04-10 12:20:42 AM
 *  Author: EbrahimOseif
 */

#ifndef __DIO_H__
#define __DIO_H__



/************************************************************************/
/*				               INCLUDES			                        */
/************************************************************************/


#include "std_types.h"


/************************************************************************/
/*				               typedefs			                        */
/************************************************************************/

typedef enum
{
    STD_low=0,
    STD_high=!STD_low
}STD_levelType;

typedef enum
{
    Dio_Channel_A0,
    Dio_Channel_A1,
    Dio_Channel_A2,
    Dio_Channel_A3,
    Dio_Channel_A4,
    Dio_Channel_A5,
    Dio_Channel_A6,
    Dio_Channel_A7,

    Dio_Channel_B0,
    Dio_Channel_B1,
    Dio_Channel_B2,
    Dio_Channel_B3,
    Dio_Channel_B4,
    Dio_Channel_B5,
    Dio_Channel_B6,
    Dio_Channel_B7,


    Dio_Channel_C0,
    Dio_Channel_C1,
    Dio_Channel_C2,
    Dio_Channel_C3,
    Dio_Channel_C4,
    Dio_Channel_C5,
    Dio_Channel_C6,
    Dio_Channel_C7,


    Dio_Channel_D0,
    Dio_Channel_D1,
    Dio_Channel_D2,
    Dio_Channel_D3,
    Dio_Channel_D4,
    Dio_Channel_D5,
    Dio_Channel_D6,
    Dio_Channel_D7,

    Dio_Channel_E0,
    Dio_Channel_E1,
    Dio_Channel_E2,
    Dio_Channel_E3,
    Dio_Channel_E4,
    Dio_Channel_E5,
    Dio_Channel_E6_NA,
    Dio_Channel_E7_NA,

    Dio_Channel_F0,
    Dio_Channel_F1,
    Dio_Channel_F2,
    Dio_Channel_F3,
    Dio_Channel_F4

}Dio_ChannelType;

typedef enum
{
    Dio_Port_A,
    Dio_Port_B,
    Dio_Port_C,
    Dio_Port_D,
    Dio_Port_E,
    Dio_Port_F
}Dio_PortType;

typedef struct
{
    uint32 GPIODATA    ;
	uint8 REserved[0x3FC];
    uint32 GPIODIR     ;
    uint32 GPIOIS      ;
    uint32 GPIOIBE     ;
    uint32 GPIOIEV     ;
    uint32 GPIOIM      ;
    uint32 GPIORIS     ;
    uint32 GPIOMIS     ;
    uint32 GPIOICR     ;
    uint32 GPIOAFSEL   ; /*offset : 0x420 -> 424 */

    uint8 Reserved_2[0xDC];
    uint32 GPIODR2R    ; /*offset : 0x500 */
    uint32 GPIODR4R    ;
    uint32 GPIODR8R    ;
    uint32 GPIOODR     ;
    uint32 GPIOPUR     ;
    uint32 GPIOPDR     ;
    uint32 GPIOSLR     ;
    uint32 GPIODEN     ;
    uint32 GPIOLOCK    ;
    uint32 GPIOCR      ;
    uint32 GPIOAMSEL   ;
    uint32 GPIOPCTL    ;
    uint32 GPIOADCCTL  ;
    uint32 GPIODMACTL  ;
}PORT_RegType;

#define PORTA_REG     (*((volatile PORT_RegType*)0x400043FC))
#define PORTB_REG     (*((volatile PORT_RegType*)0x400053FC))
#define PORTC_REG     (*((volatile PORT_RegType*)0x400063FC))
#define PORTD_REG     (*((volatile PORT_RegType*)0x400073FC))
#define PORTE_REG     (*((volatile PORT_RegType*)0x400243FC))
#define PORTF_REG     (*((volatile PORT_RegType*)0x400253FC))



/************************************************************************/
/*				   functions' prototypes	                            */
/************************************************************************/


/*
*Input: ChannelId -> to get pin on a port
*					
*Output: 
*In/Out:
*Return STD_level -> the acquired data from a pin
*Description: This function gets the value of a full port
* 			  
*/

STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/*
*Input: ChannelId -> to get pin on a port
*		Level -> level to write 		
*In/Out:
*Description: This function gets the value of a pin 
* 			  
*/
void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level);

/*
*Input: GPIO -> to get PORT name
*					
*Output: 
*In/Out:
*Return:  -> the acquired data wether it was PORT data
*Description: This function gets the value of a full port
* 			  
*/
uint8_t Dio_ReadPort(Dio_PortType PortId );
/*
*Input: PortId -> to get PORT name
*		Level -> level to write 		
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
void Dio_WritePort( Dio_PortType PortId, uint8_t Level);

/*
*Input: ChannelId -> to get ChannelId
*		
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port
* 			  
*/
void Dio_FlipChannel( Dio_ChannelType ChannelId);

/*
*Input: PortId -> to get port num
*		
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a port
* 			  
*/
void Dio_FlipPort(Dio_PortType PortId);
#endif