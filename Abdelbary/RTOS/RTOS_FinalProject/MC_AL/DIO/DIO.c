
/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "DIO.h"
#include "../../ServiceLayer/std_types.h"
#include "../../MC_AL/registers.h"

/*************************************************************/
/*                    APIs IMPLEMENTATIONS	                 */
/*************************************************************/
/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	ERROR_STATUS Error_Status = E_OK;
		if (NULL != DIO_info)
		{
			if (DIO_info->dir == OUTPUT)
			{
				DIO_info->dir = 0b11111111;
			}
			else if (DIO_info->dir == INPUT)
			{
				DIO_info->dir = 0b00000000;
			}
			switch(DIO_info->GPIO)
			{
				case GPIOA:
					PORTA_DIR = (PORTA_DIR & (~(DIO_info->pins))) | ((DIO_info->pins) & DIO_info->dir);
				break;
				case GPIOB:
					PORTB_DIR = (PORTB_DIR & (~(DIO_info->pins))) | ((DIO_info->pins) & DIO_info->dir);
				break;
				case GPIOC:
					PORTC_DIR = (PORTC_DIR & (~(DIO_info->pins))) | ((DIO_info->pins) & DIO_info->dir);
				break;
				case GPIOD:
					PORTD_DIR = (PORTD_DIR & (~(DIO_info->pins))) | ((DIO_info->pins) & DIO_info->dir);
				break;
				default: Error_Status = E_NOK;
				break;
			}
		}
		else
		{
			Error_Status = E_NOK;
		}
	return Error_Status;
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
	ERROR_STATUS Error_Status = E_OK;
	if (value == HIGH)
	{
		value = 0b11111111;
	}
	else if (value == LOW)
	{
		value = 0b00000000;
	}
	switch(GPIO)
	{
		case GPIOA:
			PORTA_DATA = (PORTA_DATA & (~pins)) | (pins & value);
		break;
		case GPIOB:
			PORTB_DATA = (PORTB_DATA & (~pins)) | (pins & value);
		break;
		case GPIOC:
			PORTC_DATA = (PORTC_DATA & (~pins)) | (pins & value);
		break;
		case GPIOD:
			PORTD_DATA = (PORTD_DATA & (~pins)) | (pins & value);
		break;
		default: Error_Status = E_NOK;
		break;
	}
	return Error_Status;
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
	ERROR_STATUS Error_Status = E_OK;
	switch (GPIO)
	{
		case GPIOA:
			*data = (PORTA_PIN & pins);
		break;
		case GPIOB:
			*data = (PORTB_PIN & pins);
		break;
		case GPIOC:
			*data = (PORTC_PIN & pins);
		break;
		case GPIOD:
			*data = (PORTD_PIN & pins);
		break;
		default: Error_Status = E_NOK;
		break;
	}
	return Error_Status;
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
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	ERROR_STATUS Error_Status = E_OK;
	switch (GPIO)
	{
		case GPIOA:
		PORTA_DATA =  (PORTA_PIN ^ pins);
		break;
		case GPIOB:
		PORTB_DATA =  (PORTB_PIN ^ pins);
		break;
		case GPIOC:
		PORTC_DATA =  (PORTC_PIN ^ pins);
		break;
		case GPIOD:
		PORTD_DATA =  (PORTD_PIN ^ pins);
		break;
		default: Error_Status = E_NOK;
		break;
	}
	return Error_Status;
}
