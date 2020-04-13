/*
 ============================================================================
 Name        : led.c
 Author      : Muhammed Gamal
 Description :
 ============================================================================
 */

/*********************************includes**********************************/
#include "led.h"
/***************************************************************************/


/*********************************definitions*******************************/

/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/
void Led_Init(En_LedNumber_t en_led_id)
{
	DIO_Cfg_s LED0_init=
	{
			LED0_init.GPIO=LED_0_GPIO,
			LED0_init.pins=LED_0_BIT,
			LED0_init.dir=OUTPUT,
	};

	DIO_Cfg_s LED1_init=
	{
			LED0_init.GPIO=LED_1_GPIO,
			LED0_init.pins=LED_1_BIT,
			LED0_init.dir=OUTPUT,
	};

	DIO_Cfg_s LED2_init=
	{
			LED0_init.GPIO=LED_2_GPIO,
			LED0_init.pins=LED_2_BIT,
			LED0_init.dir=OUTPUT,
	};

	DIO_Cfg_s LED3_init=
	{
			LED0_init.GPIO=LED_3_GPIO,
			LED0_init.pins=LED_3_BIT,
			LED0_init.dir=OUTPUT,
	};

	switch(en_led_id)
	{
	case LED_0:
		DIO_init(&LED0_init);
		break;
	case LED_1:
		DIO_init(&LED1_init);
		break;
	case LED_2:
		DIO_init(&LED2_init);
		break;
	case LED_3:
		DIO_init(&LED3_init);
		break;

	}
}

void Led_On(En_LedNumber_t en_led_id)
{
	switch(en_led_id)
	{
	case LED_0:
		DIO_Write(LED_0_GPIO, LED_0_BIT, HIGH);
		break;
	case LED_1:
		DIO_Write(LED_1_GPIO, LED_1_BIT, HIGH);
		break;
	case LED_2:
		DIO_Write(LED_2_GPIO, LED_2_BIT, HIGH);
		break;
	case LED_3:
		DIO_Write(LED_3_GPIO, LED_3_BIT, HIGH);
		break;

	}
}

void Led_Off(En_LedNumber_t en_led_id)
{
	switch(en_led_id)
	{
	case LED_0:
		DIO_Write(LED_0_GPIO, LED_0_BIT, LOW);
		break;
	case LED_1:
		DIO_Write(LED_1_GPIO, LED_1_BIT, LOW);
		break;
	case LED_2:
		DIO_Write(LED_2_GPIO, LED_2_BIT, LOW);
		break;
	case LED_3:
		DIO_Write(LED_3_GPIO, LED_3_BIT, LOW);
		break;

	}
}

void Led_Toggle(En_LedNumber_t en_led_id)
{
	switch(en_led_id)
	{
	case LED_0:
		DIO_Toggle(LED_0_GPIO, LED_0_BIT);
		break;
	case LED_1:
		DIO_Toggle(LED_1_GPIO, LED_1_BIT);
		break;
	case LED_2:
		DIO_Toggle(LED_2_GPIO, LED_2_BIT);
		break;
	case LED_3:
		DIO_Toggle(LED_3_GPIO, LED_3_BIT);
		break;

	}
}

