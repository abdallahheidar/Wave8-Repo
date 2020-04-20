

#include "../../ServiceLayer/std_types.h"
#include "../../MC_AL/DIO/DIO.h"
#include "ledConfig.h"
#include "led.h"
/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Init(En_LedNumber_t led_id)
{
	DIO_Cfg_s str_DioCfg;
	str_DioCfg.dir = OUTPUT;
	
	switch (led_id)
	{
		case LED_0:
			str_DioCfg.GPIO = LED_0_GPIO;
			str_DioCfg.pins = LED_0_BIT;
			DIO_init(&str_DioCfg);
			break;
		case LED_1:
			str_DioCfg.GPIO = LED_1_GPIO;
			str_DioCfg.pins = LED_1_BIT;
			DIO_init(&str_DioCfg);
			break;
		case LED_2:
			str_DioCfg.GPIO = LED_2_GPIO;
			str_DioCfg.pins = LED_2_BIT;
			DIO_init(&str_DioCfg);
			break;
		case LED_3:
			str_DioCfg.GPIO = LED_3_GPIO;
			str_DioCfg.pins = LED_3_BIT;
			DIO_init(&str_DioCfg);
			break;
		default:
		break;
	}
}
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_On(En_LedNumber_t led_id)
{
	switch (led_id)
	{
		case LED_0:
			DIO_Write(LED_0_GPIO, LED_0_BIT, LED_ON_LEVEL);
			break;
		case LED_1:
			DIO_Write(LED_1_GPIO, LED_1_BIT, LED_ON_LEVEL);
			break;
		case LED_2:
			DIO_Write(LED_2_GPIO, LED_2_BIT, LED_ON_LEVEL);
			break;
		case LED_3:
			DIO_Write(LED_3_GPIO, LED_3_BIT, LED_ON_LEVEL);
			break;
		default:
			break;
	}
}
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Off(En_LedNumber_t led_id)
{
	switch (led_id)
	{
		case LED_0:
			DIO_Write(LED_0_GPIO, LED_0_BIT, LED_OFF_LEVEL);
			break;
		case LED_1:
			DIO_Write(LED_1_GPIO, LED_1_BIT, LED_OFF_LEVEL);
			break;
		case LED_2:
			DIO_Write(LED_2_GPIO, LED_2_BIT, LED_OFF_LEVEL);
			break;
		case LED_3:
			DIO_Write(LED_3_GPIO, LED_3_BIT, LED_OFF_LEVEL);
			break;
		default:
		break;
	}
}
/**
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Toggle(En_LedNumber_t led_id)
{
	switch (led_id)
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
		default:
		break;
	}
}
