/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//#include <asf.h>
#include "gpio.h"
#include "pushButton.h"
#include "led.h"
#define F_CPU 8000000UL
int main (void)
{
		

	/* Insert system clock initialization code here (sysclk_init()). */
				/*Testing GPIO Functions*/
	gpioPinDirection(LED_0_GPIO,LED_0_BIT|LED_1_BIT|LED_2_BIT|LED_3_BIT,OUTPUT);
	gpioPinDirection(BTN_0_GPIO,BTN_0_BIT|BTN_1_BIT,INPUT);
	gpioPinDirection(BTN_1_GPIO,BTN_1_BIT,INPUT);
				
				/*Testing LED Driver Functions*/
	Led_Init(LED_0);
	pushButtonInit(BTN_0);
	En_buttonStatus_t status = pushButtonGetStatus(BTN_0);			
	if (status==Pressed)
	{
		Led_On(LED_0);
	} 
	else
	{
		Led_Off(LED_0);
	}
	
	
	
	//board_init();

	/* Insert application code here, after the board has been initialized. */
	
}
