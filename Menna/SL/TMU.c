/*
 * TMU.c
 *
 * Created: 2/24/2020 12:19:35 PM
 *  Author: MENA
 */ 

#include "Timer.h"
#include "TMU.h"


 void ISR_flag_func(void);
static void Remove_task(TMU_tsak_s *TMU_task);




uint8_t g_u8_timer_CH ;
uint8_t g_u8_TMU_reselution ;

TMU_tsak_s *Buffer[TMU_BUFFER_SIZE] = { NULL };

uint8_t g_u8_NO_ELEMNT_BUFFER = ZERO_VALUE ;

uint8_t g_u8_ISR_flag = FALSE ;
uint8_t g_u8_TMU_initialzation = FALSE ;
uint8_t g_u8_first_call_start = FALSE ;


/**
 * Input: Pointer to a structure contains the information needed to initialize the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */


ERROR_STATUS TMU_Init (TMU_Cfg_s *TMU_Cfg){
	
	
	if (TMU_Cfg == NULL)
		return TMU_module_error +NULL_PTR_ERROR ;
	
	/* check if the module is initialized before */
	
	if (g_u8_TMU_initialzation== FALSE )
		g_u8_TMU_initialzation = TRUE ;
	else
		return TMU_module_error + MULTIPLE_INITIALIZATION ;
	
	Timer_cfg_s timer_TMU_cfg ;
	g_u8_timer_CH = TMU_Cfg->Timer_channel;
	
	/* check for available range of resolution */
	
	if (TMU_Cfg->TMU_Reselution<1 || TMU_Cfg->TMU_Reselution>17)
	{
		return TMU_module_error + INVALID__PARAMETER ;
	}
	
	/* set resolution to global to be used in start function */
	
	g_u8_TMU_reselution = TMU_Cfg->TMU_Reselution ;
	
	/*		 switch on timer channel		*/
	
	switch(TMU_Cfg->Timer_channel){
		
		case TMU_TIMER_CH0 :
		
			timer_TMU_cfg.Timer_CH_NO = TMU_TIMER_CH0;
			timer_TMU_cfg.Timer_Mode = TIMER_MODE ;
			timer_TMU_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			timer_TMU_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
			timer_TMU_cfg.Timer_Cbk_ptr = ISR_flag_func ;
			
			/*		initialize timer		 */
			
			Timer_Init(&timer_TMU_cfg);
			
		
			break;
		case TMU_TIMER_CH1 :
		
			timer_TMU_cfg.Timer_CH_NO = TMU_TIMER_CH1;
			timer_TMU_cfg.Timer_Mode = TIMER_MODE ;
			timer_TMU_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			timer_TMU_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
			timer_TMU_cfg.Timer_Cbk_ptr = ISR_flag_func ;
			
			/*		initialize timer		 */
			
			Timer_Init(&timer_TMU_cfg);
		
			break;
		case TMU_TIMER_CH2 :
			PORTA_DATA = 0xFF ;
			timer_TMU_cfg.Timer_CH_NO = TMU_TIMER_CH2;
			timer_TMU_cfg.Timer_Mode = TIMER_MODE ;
			timer_TMU_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			timer_TMU_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
			timer_TMU_cfg.Timer_Cbk_ptr = ISR_flag_func ;
			
			/*		initialize timer		 */
			
			Timer_Init(&timer_TMU_cfg);
		
			break;
		default:
		/*  invalid timer channel */
		
			return TMU_module_error + INVALID__PARAMETER ;
		break;
		
	}
	return E_OK ;
}



/**
 * Input: Pointer to a structure contains the information needed to de-initialize the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: DeInitiates the module.
 * 							
 */


ERROR_STATUS TMU_DeInit (TMU_Cfg_s *TMU_Cfg){
	
	/* check for null pointer error */
	if (TMU_Cfg == NULL)
	return TMU_module_error +NULL_PTR_ERROR ;
	
	
	/* check if the TMU initialized before de-init or not */
	if (g_u8_TMU_initialzation!= TRUE)
	{
		return TMU_module_error + DEINIT_WITHOUT_INIT ;
	}
	/*stop timer */
	
	Timer_Stop(g_u8_timer_CH);
	
	/*free all the buffer */
	
	return E_OK ;
}



/**
 * Input: Pointer to a structure contains the information needed to start the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: start the module.
 * 							
 */


ERROR_STATUS TMU_Start_Timer (TMU_tsak_s *TMU_task){
	
	uint8_t count ;
	/* check for null pointer error */
	
	
	
	
	if (TMU_task == NULL)
	return TMU_module_error +NULL_PTR_ERROR ;
	
	if (TMU_task->Ptr_FunctionCall == NULL)
	return TMU_module_error +NULL_PTR_ERROR ;
	
	TMU_task->N_OVFs=TMU_task->delay_time;
	
	/*check if the buffer is full */
	
	if (TMU_task->TMU_mode!=PERIODIC && TMU_task->TMU_mode!=ONESHOT)
	{return TMU_module_error + INVALID__PARAMETER ;
	}
	
	if (g_u8_NO_ELEMNT_BUFFER<TMU_BUFFER_SIZE)
	{	
		for( count = ZERO_VALUE ; count < TMU_BUFFER_SIZE ; count++)
		{
		if (Buffer[count]==NULL)
		{
			/*		 set struct in buffer		 */
			
			Buffer[count] = TMU_task ;
			
			/* increment the no of element in the buffer */
			
			g_u8_NO_ELEMNT_BUFFER++;
			break;
		}
		
		}
	
		if (g_u8_first_call_start == FALSE )
		{
			Timer_Start(g_u8_timer_CH ,250);
			
			
			g_u8_first_call_start++;
			
		}
	}else
	
		return TMU_module_error + FULL_BUFFER ;
	
	return E_OK ;
	
}



/**
 * Input: Pointer to a structure contains the information needed to stop the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: stop the module.
 * 							
 */



ERROR_STATUS TMU_Stop_Timer (TMU_tsak_s *TMU_task){

	if (g_u8_first_call_start!=1)
	{
		return STOP_WITHOU_SART + TMU_module_error ;
	}
	
	Remove_task(TMU_task);
	
	return E_OK ;
	
}







void Remove_task(TMU_tsak_s *TMU_task){
	
		uint8_t count ;
		
		for (count = ZERO_VALUE ; count<TMU_BUFFER_SIZE ; count++)
		{
			if (Buffer[count]!=NULL&& TMU_task->Task_ID==Buffer[count]->Task_ID)
			{
				Buffer[count] = NULL ;
			}
		}
	
}



/**
 * Input: void. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Run the basic logic code to calculate the timing
 * and call the user function depends on the timeout event for each software timer object.
 * 							
 */


ERROR_STATUS TMU_Dispatch (void){
	uint8_t count ;
	
	if (g_u8_ISR_flag==TRUE)
	{
		
		for (count = ZERO_VALUE ; count<TMU_BUFFER_SIZE ; count++)
		{
			if (Buffer[count]!=NULL)
			{
				Buffer[count] ->N_OVFs-- ;
				if ( Buffer[count] ->N_OVFs == ZERO_VALUE)
				{
					Buffer[count]->Ptr_FunctionCall();
					if (Buffer[count]->TMU_mode== ONESHOT)
					Remove_task(Buffer[count]);
					else 
					Buffer[count]->N_OVFs=Buffer[count]->delay_time ;
					
				
					
				}
			}
		}
		g_u8_ISR_flag = FALSE ;
	}
	return E_OK ;
	
}


 void ISR_flag_func(void){
	
	g_u8_ISR_flag = TRUE ;
	
	
}