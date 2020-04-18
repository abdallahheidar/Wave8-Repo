/*
* pushBotton.c
*
* Created: 1/18/2020 11:05:12 AM
*  Author: 3dawy
*/
#include "pushButton.h"
#include "pushButtonConfig.h"

#define ZERO_VALUE 0

ERROR_STATUS pushButtonInit(uint8_t en_butotn_id)
{
	uint8_t au8_Error = E_OK;

	DIO_Cfg_s DIO_Info;
	DIO_Info.dir = INPUT;
	
	switch(en_butotn_id)
	{
		case BTN_0:
		DIO_Info.GPIO = BTN_0_GPIO;
		DIO_Info.pins = BTN_0_BIT;
		break;

		case BTN_1:
		DIO_Info.GPIO = BTN_1_GPIO;
		DIO_Info.pins = BTN_1_BIT;
		break;

		default:
		au8_Error = E_NOK;
	}

	au8_Error |= DIO_init(&DIO_Info);

	return au8_Error;

}

ERROR_STATUS pushButtonGetStatus(uint8_t en_butotn_id, uint8_t * ButtonStatus)
{
	uint8_t au8_Error = E_OK;
	uint8_t PinValue = ZERO_VALUE;


	switch(en_butotn_id)
	{
		case BTN_0:
		au8_Error = DIO_Read(BTN_0_GPIO,BTN_0_BIT, &PinValue);
		break;
		
		case BTN_1:
		au8_Error |= DIO_Read(BTN_1_GPIO,BTN_1_BIT, &PinValue);
		break;
		
		default:
		au8_Error = E_NOK;
	}

			if (PinValue)
			*ButtonStatus = Pressed;
			else
			*ButtonStatus = Released;



	return au8_Error;
}