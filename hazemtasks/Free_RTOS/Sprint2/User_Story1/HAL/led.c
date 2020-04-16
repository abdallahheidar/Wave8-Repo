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
	uint8_t au8_led_port;
	uint8_t au8_led_pin;
	switch(en_led_id)
	{
	case LED_0:
		au8_led_port = LED_0_GPIO;
		au8_led_pin = LED_0_BIT;
		break;
	case LED_1:
		au8_led_port = LED_1_GPIO;
		au8_led_pin = LED_1_BIT;
		break;
	case LED_2:
		au8_led_port = LED_2_GPIO;
		au8_led_pin = LED_2_BIT;
		break;
	case LED_3:
		au8_led_port = LED_3_GPIO;
		au8_led_pin = LED_3_BIT;
		break;
	}
	DIO_Cfg_s LED_init=
	{
			LED_init.GPIO=au8_led_port,
			LED_init.pins=au8_led_pin,
			LED_init.dir=OUTPUT,
	};
	DIO_init(&LED_init);
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

