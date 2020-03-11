/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/
#include "registers.h"
#include "DIO.h"


/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
uint8_t DIO_init (DIO_Cfg_s *DIO_info){
	uint8_t Err_Status = 0;
	uint8_t GPIO_NAME= DIO_info->GPIO;
	uint8_t GPIO_DIR = DIO_info->dir;
	uint8_t GPIO_PINS = DIO_info->pins;
	
	switch (GPIO_NAME)
	{
		case GPIOA:
			if(GPIO_DIR==OUTPUT){
				PORTA_DIR |= GPIO_PINS;
			}else if (GPIO_DIR==INPUT)
			{
				PORTA_DIR &=~ GPIO_PINS;
			}
			Err_Status =E_OK;
			break;
		case GPIOB:
			if(GPIO_DIR==OUTPUT){
				PORTB_DIR |= GPIO_PINS;
			}else if (GPIO_DIR==INPUT)
			{
				PORTB_DIR &=~ GPIO_PINS;
			}
			Err_Status =E_OK;
			break;
		case GPIOC:
			if(GPIO_DIR==OUTPUT){
				PORTC_DIR |= GPIO_PINS;
			}else if (GPIO_DIR==INPUT)
			{
				PORTC_DIR &=~ GPIO_PINS;
			}
			Err_Status =E_OK;
			break;
		case GPIOD:
			if(GPIO_DIR==OUTPUT){
				PORTD_DIR |= GPIO_PINS;
			}else if (GPIO_DIR==INPUT)
			{
				PORTD_DIR &=~ GPIO_PINS;
			}
			Err_Status =E_OK;
			break;
		default:
			Err_Status =E_NOK;
	}
	
return Err_Status;	
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
uint8_t DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value){
	uint8_t Err_Status = 0;
	
	switch (GPIO)
	{
		case GPIOA:
			if(value==HIGH){
				PORTA_DATA |= pins;
			}else if (value==LOW)
			{
				PORTA_DATA &=~ pins;
			}
			Err_Status =E_OK;
			break;
		case GPIOB:
			if(value==HIGH){
				PORTB_DATA |= pins;
			}else if (value==LOW)
			{
				PORTB_DATA &=~ pins;
			}
			Err_Status =E_OK;
			break;
		case GPIOC:
			if(value==HIGH){
				PORTC_DATA |= pins;
			}else if (value==LOW)
			{
				PORTC_DATA &=~ pins;
			}
			Err_Status =E_OK;
			break;
		case GPIOD:
			if(value==HIGH){
				PORTD_DATA |= pins;
			}else if (value==LOW)
			{
				PORTD_DATA &=~ pins;
			}
			Err_Status =E_OK;
			break;
		default:
			Err_Status =E_NOK;
	}
	
	return Err_Status;
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
uint8_t DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data){
	uint8_t Err_Status = 0;
	switch (GPIO)
	{
		case GPIOA:
			 *data = (PORTA_PIN & pins)? 1:0;
			 Err_Status =E_OK;
			 break;
		case GPIOB:
			*data = (PORTB_PIN & pins)? 1:0;
			Err_Status =E_OK;
			break;
		case GPIOC:
			*data = (PORTC_PIN & pins)? 1:0;
			Err_Status =E_OK;
			break;
		case GPIOD:
			*data = (PORTD_PIN & pins)? 1:0;
			Err_Status =E_OK;
			break;
		default:
			Err_Status =E_NOK;
	}
	
	return Err_Status;
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
uint8_t DIO_Toggle (uint8_t GPIO, uint8_t pins){
	uint8_t Err_Status = 0;
	
	switch (GPIO)
	{
		case GPIOA:
			PORTA_DATA ^= pins;
			Err_Status = E_OK;
			break;
		case GPIOB:
			PORTB_DATA ^= pins;
			Err_Status = E_OK;
			break;
		case GPIOC:
			PORTC_DATA ^= pins;
			Err_Status = E_OK;
			break;
		case GPIOD:
			PORTD_DATA ^= pins;
			Err_Status = E_OK;
			break;
		default:
			Err_Status =E_NOK;	
	}
return Err_Status;
}




































