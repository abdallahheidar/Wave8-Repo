#include "pushButton.h"
void pushButtonInit(En_buttonId_t en_butotn_id)
{
	DIO_Cfg_s BTN0_init=
	{
			BTN0_init.GPIO=BTN_0_GPIO,
			BTN0_init.pins=BTN_0_BIT,
			BTN0_init.dir=INPUT,
	};

	DIO_Cfg_s BTN1_init=
	{
			BTN1_init.GPIO=BTN_1_GPIO,
			BTN1_init.pins=BTN_1_BIT,
			BTN1_init.dir=INPUT,
	};

	DIO_Cfg_s BTN2_init=
	{
			BTN2_init.GPIO=BTN_2_GPIO,
			BTN2_init.pins=BTN_2_BIT,
			BTN2_init.dir=INPUT,
	};

	DIO_Cfg_s BTN3_init=
	{
			BTN2_init.GPIO=BTN_3_GPIO,
			BTN2_init.pins=BTN_3_BIT,
			BTN2_init.dir=INPUT,
	};


	switch(en_butotn_id)
	{
		case BTN_0:
			DIO_init (&BTN0_init);
			break;
		case BTN_1:
			DIO_init (&BTN1_init);
			break;
		case BTN_2:
			DIO_init (&BTN2_init);
			break;
		case BTN_3:
			DIO_init (&BTN3_init);
			break;
	}
}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id)
{
	unsigned char current_status=0;
	uint8_t au8_BTN0_Pin;
	uint8_t au8_BTN1_Pin;
	uint8_t au8_BTN2_Pin;
	uint8_t au8_BTN3_Pin;
	switch(en_butotn_id)
	{
		case BTN_0:
			DIO_Read(BTN_0_GPIO, BTN_0_BIT, &au8_BTN0_Pin);
			if(au8_BTN0_Pin)
			{
				/*check due to switch de-bouncing*/
				do
				{
					DIO_Read(BTN_0_GPIO, BTN_0_BIT, &au8_BTN0_Pin);
				}
				while(au8_BTN0_Pin);
				current_status=au8_BTN0_Pin;
			}
			break;

		case BTN_1:
			DIO_Read(BTN_1_GPIO, BTN_1_BIT, &au8_BTN1_Pin);
			if(au8_BTN1_Pin)
			{
				/*check due to switch de-bouncing*/
				do
				{
					DIO_Read(BTN_1_GPIO, BTN_1_BIT, &au8_BTN1_Pin);
				}
				while(au8_BTN1_Pin);
				current_status=au8_BTN1_Pin;
			}
			break;

		case BTN_2:
			DIO_Read(BTN_2_GPIO, BTN_2_BIT, &au8_BTN2_Pin);
			if(au8_BTN2_Pin)
			{
				/*check due to switch de-bouncing*/
				do
				{
					DIO_Read(BTN_2_GPIO, BTN_2_BIT, &au8_BTN2_Pin);
				}
				while(au8_BTN2_Pin);
				current_status=au8_BTN2_Pin;
			}
			break;

		case BTN_3:
			DIO_Read(BTN_3_GPIO, BTN_3_BIT, &au8_BTN3_Pin);
			if(au8_BTN3_Pin)
			{
				/*check due to switch de-bouncing*/
				do
				{
					DIO_Read(BTN_3_GPIO, BTN_3_BIT, &au8_BTN3_Pin);
				}
				while(au8_BTN3_Pin);
				current_status=au8_BTN3_Pin;
			}
			break;

	}
	return current_status;
}
