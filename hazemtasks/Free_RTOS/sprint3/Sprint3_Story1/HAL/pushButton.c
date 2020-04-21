#include "pushButton.h"
void pushButtonInit(En_buttonId_t en_butotn_id)
{
	uint8_t au8_BTN_port;
	uint8_t au8_BTN_pin;

	switch(en_butotn_id)
	{
		case BTN_0:
			au8_BTN_port = BTN_0_GPIO;
			au8_BTN_pin = BTN_0_BIT;
			break;
		case BTN_1:
			au8_BTN_port = BTN_1_GPIO;
			au8_BTN_pin = BTN_1_BIT;
			break;
		case BTN_2:
			au8_BTN_port = BTN_2_GPIO;
			au8_BTN_pin = BTN_2_BIT;
			break;
		case BTN_3:
			au8_BTN_port = BTN_3_GPIO;
			au8_BTN_pin = BTN_3_BIT;
			break;
	}
	DIO_Cfg_s BTN_init=
	{
			BTN_init.GPIO=BTN_0_GPIO,
			BTN_init.pins=BTN_0_BIT,
			BTN_init.dir=INPUT,
	};
	DIO_init (&BTN_init);
}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id)
{
	uint8_t current_status=0;
	uint8_t au8_BTN0_Pin;
	uint8_t au8_BTN1_Pin;
	uint8_t au8_BTN2_Pin;
	uint8_t au8_BTN3_Pin;
	switch(en_butotn_id)
	{
		case BTN_0:
			DIO_Read(BTN_0_GPIO, BTN_0_BIT, &au8_BTN0_Pin);
			current_status=au8_BTN0_Pin;
			break;

		case BTN_1:
			DIO_Read(BTN_1_GPIO, BTN_1_BIT, &au8_BTN1_Pin);
			current_status=au8_BTN1_Pin;
			break;

		case BTN_2:
			DIO_Read(BTN_2_GPIO, BTN_2_BIT, &au8_BTN2_Pin);
			current_status=au8_BTN2_Pin;
			break;

		case BTN_3:
			DIO_Read(BTN_3_GPIO, BTN_3_BIT, &au8_BTN3_Pin);
			current_status=au8_BTN3_Pin;
			break;

	}
	return current_status;
}
