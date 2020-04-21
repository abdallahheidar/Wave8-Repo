/*
 ============================================================================
 Name        : DIO.h
 Author      : Muhammed Gamal
 Description :
 ============================================================================
 */

#ifndef	DIO_H
#define DIO_H

#include "../Common/common_macros.h"
#include "../Common/std_types.h"
#include "registers.h"
/************************************************************************/
/*						PINS/BITS defines                               */
/************************************************************************/
/*
#define PIN0			0x01
#define PIN1			0x02
#define PIN2			0x04
#define PIN3			0x08
#define PIN4	        0x10
#define PIN5			0x20
#define PIN6			0x40
#define PIN7			0x80
*/

#define BIT0			0x01
#define BIT1			0x02
#define BIT2			0x04
#define BIT3			0x08
#define BIT4			0x10
#define BIT5			0x20
#define BIT6			0x40
#define BIT7			0x80

#define UPPER_NIBBLE	0xF0
#define LOWER_NIBBLE	0x0F
#define FULL_PORT		0xFF

#define GPIOA			0
#define GPIOB			1
#define GPIOC			2
#define GPIOD			3

#define OUTPUT			0xFF
#define INPUT			0x00


/************************************************************************/
/*						Typedefs defines                               	*/
/************************************************************************/


typedef struct DIO_Cfg_s
{
	uint8_t GPIO;
	uint8_t pins;
	uint8_t dir;
}DIO_Cfg_s;

/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info);


/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value);

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data);

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins);

/****************************************************************************/

/********************************************************
 * PORTx registers
 *******************************************************/

#define PORTA_DATA 	*((reg_type8_t)(0X3B))
#define PORTA_DIR  	*((reg_type8_t)(0X3A))
#define PORTA_PIN	*((reg_type8_t)(0X39))

#define PORTB_DATA 	*((reg_type8_t)(0X38))
#define PORTB_DIR  	*((reg_type8_t)(0X37))
#define PORTB_PIN	*((reg_type8_t)(0X36))

#define PORTC_DATA 	*((reg_type8_t)(0X35))
#define PORTC_DIR  	*((reg_type8_t)(0X34))
#define PORTC_PIN	*((reg_type8_t)(0X33))


#define PORTD_DATA 	*((reg_type8_t)(0X32))
#define PORTD_DIR  	*((reg_type8_t)(0X31))
#define PORTD_PIN	*((reg_type8_t)(0X30))
/******************************************************************************/

#endif

