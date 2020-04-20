
#include "Motor_Config.h"

DIO_Cfg_s Motorone= {
	GPIOD,
	BIT4|BIT3|BIT2,
	OUTPUT
};


DIO_Cfg_s Motortwo= {
	GPIOD,
	BIT5|BIT6|BIT7,
	OUTPUT
};


DIO_Cfg_s ALL_Motor= {
	GPIOD,
	BIT4|BIT3|BIT2|BIT5|BIT6|BIT7,
	OUTPUT
};
