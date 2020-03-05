/*
 * Us.c
 *
 * Created: 18-Feb-20 4:43:20 PM
 *  Author: ahmed
 */ 
#include "Us.h"
#include "/carApp/carApp/carApp/MCAL/DIO.h"
#include "/carApp/carApp/carApp/MCAL/ICU.h"

/************************************************************************/
/*				   Defines					                            */
/************************************************************************/
#define LOOP_VAL   (200)

/************************************************************************/
/*					APIS                                                */
/************************************************************************/

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

ERROR_STATUS Us_Init(void){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*create DIO struct to configure it*/
	DIO_Cfg_s st_DioUs_t;
	
	/*create ICU struct to configure it*/
	Icu_cfg_s st_IcuUs_t;
	
	/*configure PC7 as output echo pin*/
	st_DioUs_t.dir = OUTPUT;
	st_DioUs_t.GPIO = GPIOC;
	st_DioUs_t.pins = PIN7;
	
	/*init DIO*/
	error_flag |= DIO_init(&st_DioUs_t);
	
	/*use PB2/IRQ as input && timer 0*/
	st_IcuUs_t.ICU_Ch_No = ICU_CH2;
	st_IcuUs_t.ICU_Ch_Timer = ICU_TIMER_CH2;
	
	/*init ICU*/
	error_flag |= Icu_Init(&st_IcuUs_t);
	
	return error_flag;
}

/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*create loop variable*/
	uint8_t u8_loop = LOW;
	
	/*send pulse on P7 for some time */
	error_flag |= DIO_Write(GPIOC,PIN7,HIGH);
	
	for(u8_loop=0 ; u8_loop<LOOP_VAL ; u8_loop++);
	
	error_flag |= DIO_Write(GPIOC,PIN7,LOW);
	
	return error_flag;
}

/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/

ERROR_STATUS Us_GetDistance(uint16_t *Distance){
	
	/*create status flag*/
	ERROR_STATUS error_status = E_OK;
	
	/*variable to read time*/
	uint32_t u32_time_Us=0;
	
	/*check distance pointer*/
	if(Distance == NULL){
		
		/*null pointer isn't valid*/
		error_status = E_NOK;
	}	
	
	else{
		/*read time value*/
		error_status |= Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&u32_time_Us);
		
		/*calculate distance*/
		*Distance = (u32_time_Us/58);
	}
	
	/*return E_OK*/
	return error_status;
}