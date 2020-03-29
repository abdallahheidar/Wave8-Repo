/*
 * US.c
 *
 * Created: 18/02/2020 11:34:13 م
 *  Author: mo
 */ 
#include "Us.h"
#include "UsConfig.h"

/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/

ERROR_STATUS Us_Init(void)
{uint8_t Ret;
Ret=DIO_init(&US_Configuration);
Ret=Icu_Init(&ICU_Configuration);
return Ret;
}
ERROR_STATUS Us_Trigger(void)
{uint8_t Ret=0;
Ret=DIO_Write(GPIOC,BIT4,HIGH);
/***********************************************/
Timer_Start(TIMER_CH0,10);
/**********************************************/
Ret=DIO_Write(GPIOC,BIT4,LOW);
return Ret;	
}


ERROR_STATUS Us_GetDistance(uint16_t *Distance)
{uint8_t Ret=0;
	uint32_t u32l_Time;
	Ret=Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&u32l_Time);
	*Distance=u32l_Time;
	return Ret;
}

