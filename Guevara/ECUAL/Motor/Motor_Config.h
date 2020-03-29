
/*********************************************
 *				Includes  					 *
 ********************************************/
#include "../../MCAL/PWM/PWM.h"
#include "../../MCAL/DIO/DIO.h"

/*********************************************
 *				Defines  					 *
 ********************************************/

#define MOTOR_1		       	1
#define MOTOR_2 	       	2
#define ALL_MOTOR         3
#define MOTOR_STOP 	    	0
#define MOTOR_FORWARD   	1
#define MOTOR_BACKWARD 	  2



#define MOTOR_EN_1_GPIO		(GPIOD)
#define MOTOR_EN_1_BIT		(BIT4)

#define MOTOR_OUT_1A_GPIO	(GPIOD)
#define MOTOR_OUT_1B_GPIO	(GPIOD)
#define MOTOR_OUT_1A_BIT	(BIT2)
#define MOTOR_OUT_1B_BIT	(BIT3)


#define MOTOR_EN_2_GPIO		(GPIOD)
#define MOTOR_EN_2_BIT		(BIT5)

#define MOTOR_OUT_2A_GPIO	(GPIOD)
#define MOTOR_OUT_2B_GPIO	(GPIOD)
#define MOTOR_OUT_2A_BIT	(BIT6)
#define MOTOR_OUT_2B_BIT	(BIT7)






/*********************************************************/
extern DIO_Cfg_s Motorone;
extern DIO_Cfg_s Motortwo;
extern DIO_Cfg_s ALL_Motor;
/***********************************************/
