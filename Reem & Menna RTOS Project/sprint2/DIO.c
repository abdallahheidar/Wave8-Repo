/*
 * DIO.c
 *
 * Created: 2/15/2020 10:42:57 PM
 *  Author: Reem el-Areeny
 */ 

#include "DIO.h"

/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_t *DIO_info)
{
	ERROR_STATUS  aenum_status = ERROR_DIO_MODULE + E_OK;
	if(DIO_info == NULL)
	{
		aenum_status = ERROR_DIO_MODULE + ERROR_NULL_POINTER;
	}
	else
	{
		if(DIO_info->dir == OUTPUT){
			switch(DIO_info->GPIO)
			{
				case GPIOA:
					PORTA_DIR |= DIO_info->pins;
					break;
				case GPIOB:
					PORTB_DIR |= DIO_info->pins;
					break;
				case GPIOC:
					PORTC_DIR |= DIO_info->pins;
					break;
				case GPIOD:
					PORTD_DIR |= DIO_info->pins;
					break;
				default:
					aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_PORT;
					break;
			}
		}
		else if(DIO_info->dir == INPUT)
		{
			switch(DIO_info->GPIO)
			{
				case GPIOA:
					PORTA_DIR &= ~(DIO_info->pins);
					break;
				case GPIOB:
					PORTB_DIR &= ~(DIO_info->pins);
					break;
				case GPIOC:
					PORTC_DIR &= ~(DIO_info->pins);
					break;
				case GPIOD:
					PORTD_DIR &= ~(DIO_info->pins);
					break;
				default:
					aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_PORT;
					break;
			}
		}
		else
		{
			aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_DIR;
		}
	}
	return aenum_status;
}

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
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	ERROR_STATUS  aenum_status = ERROR_DIO_MODULE + E_OK;
	if(value == HIGH)
	{
		switch(GPIO)
		{
			case GPIOA:
				PORTA_DATA |= pins;
				break;
			case GPIOB:
				PORTB_DATA |= pins;
				break;
			case GPIOC:
				PORTC_DATA |= pins;
				break;
			case GPIOD:
				PORTD_DATA |= pins;
				break;
			default:
				aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_PORT;
				break;
			}
		}
		else if(value == LOW)
		{
			switch(GPIO)
			{
				case GPIOA:
					PORTA_DATA &= ~(pins);
					break;
				case GPIOB:
					PORTB_DATA &= ~(pins);
					break;
				case GPIOC:
					PORTC_DATA &= ~(pins);
					break;
				case GPIOD:
					PORTD_DATA &= ~(pins);
					break;
				default:
					aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_PORT;
					break;
			}
		}
		else
		{
			aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_VALUE;
		
	}
	return aenum_status;
}

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
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{
	ERROR_STATUS aenum_status = ERROR_DIO_MODULE + E_OK;
	if(data  == NULL)
	{
		aenum_status = ERROR_DIO_MODULE + ERROR_NULL_POINTER;
	}
	else
	{
		switch(GPIO){
			case GPIOA:
			//	*data = (PORTA_PIN & pins);
				*data = (PORTA_PIN & pins)?HIGH:LOW;
				break;
			case GPIOB:
// 				*data = (PORTB_PIN & pins);
				*data = (PORTB_PIN & pins)?HIGH:LOW;

				break;
			case GPIOC:
// 				*data = (PORTC_PIN & pins);
				*data = (PORTC_PIN & pins)?HIGH:LOW;

				break;
			case GPIOD:
// 				*data = (PORTD_PIN & pins);
				*data = (PORTD_PIN & pins)?HIGH:LOW;
				break;
			default:
				aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_PORT;
				break;
		}
	}
	return aenum_status;
}

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
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins){
	ERROR_STATUS  aenum_status = ERROR_DIO_MODULE + E_OK;
	switch(GPIO){
		case GPIOA:
			PORTA_DATA ^= pins;
			break;
		case GPIOB:
			PORTB_DATA ^= pins;
			break;
		case GPIOC:
			PORTC_DATA ^= pins;
			break;
		case GPIOD:
			PORTD_DATA ^= pins;
			break;
		default:
			aenum_status = ERROR_DIO_MODULE + ERROR_INVALID_PORT;
			break;
	}
	return aenum_status;
}