
#ifndef LEDCONFIG_H_
#define LEDCONFIG_H_

/*
 * This macro define the maximum used leds
 */
#define LED_MAX_NUM			(4)

#define LED_ON_LEVEL		LOW
#define LED_OFF_LEVEL		HIGH
/*
 * LED_x_GPIO and LED_x_BIT
 * where x is the led identifier
 */

#define LED_0_GPIO	(GPIOD)
#define LED_0_BIT	(BIT4)

#define LED_1_GPIO	(GPIOD)
#define LED_1_BIT	(BIT5)

#define LED_2_GPIO	(GPIOD)
#define LED_2_BIT	(BIT6)

#define LED_3_GPIO	(GPIOD)
#define LED_3_BIT	(BIT7)


#endif /* LEDCONFIG_H_ */
