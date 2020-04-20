


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../../MC_AL/registers.h"

/* LCD ports, pins definitions */

#define LCD_RS_GPIO						GPIOC
#define LCD_RS_PIN						BIT6

#define LCD_EN_GPIO						GPIOC
#define LCD_EN_PIN						BIT7

#define LCD_RW_GPIO						GPIOC
#define LCD_RW_PIN						BIT5

#define LCD_DATA_GPIO					GPIOB

#define LCD_D4_GPIO						GPIOB
#define LCD_D4_PIN						BIT4

#define LCD_D5_GPIO						GPIOB
#define LCD_D5_PIN						BIT5

#define LCD_D6_GPIO						GPIOB
#define LCD_D6_PIN						BIT6

#define LCD_D7_GPIO						GPIOB
#define LCD_D7_PIN						BIT7

#endif /* LCD_CONFIG_H_ */