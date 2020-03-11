/*
 * tmu.c
 *
 * Created: 2020-02-24 11:21:04 AM
 *  Author: EbrahimOseif
 */ 



/************************************************************************/
/*				             INCLUDES		                 	        */
/************************************************************************/

#include "tmu.h"


/************************************************************************/
/*				         DEFINES								        */
/************************************************************************/

#define OVF_NOT_TRIGGERED	(0)
#define OVF_TRIGGERED		(1)

/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/


/* static functions prototype */

static void TMU_TimerOvf_CBK(void);
static void TMU_ClearTask(uint8_t u8_index);
static void TMU_ShiftTasks(uint8_t newIndex, uint8_t oldIndex);



/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/

static uint16_t gu16_PRELOAD = 0;
static uint8_t gsu8_TMUInitStatus = NOT_INITIALIZED;
static volatile uint8_t gu8_TMU_TimerOvf_Flag = OVF_NOT_TRIGGERED;
static volatile uint8_t gu8_OvfCounter = 0;
static uint8_t gu8_Index = 0;
Timer_cfg_s gstr_Timer_Cfg;

/************************************************************************/
/*		                FUNCTIONS' implementation				        */
/************************************************************************/

/**
* @brief: TMU Initialize
*		  initialize the timer and buffer
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Init(void)
{
		
/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = TMU_ERROR_BASE + NO_ERRORS;
		
		if (gsu8_TMUInitStatus == INITIALIZED)
		{
			u8_status = TMU_ERROR_BASE + ERROR_ALREADY_INITIALIZED;
		}
		else{
			
			uint8_t u8_counter;
			
			for(u8_counter = 0; u8_counter < MAX_TASK_COUNT; u8_counter++)
			{
				gastrTMU_Buff[u8_counter].gptrTMU_Function = NULL;
				gastrTMU_Buff[u8_counter].u16_Delay = 0;
				gastrTMU_Buff[u8_counter].u8_Periodicity = 0;
			}


			/* switch on timer channel */
			
			#if TMU_TIMER_CH0
			
			gstr_Timer_Cfg.Timer_CH_NO = TIMER_CH0;
			gstr_Timer_Cfg.Timer_Prescaler = TIMER_PRESCALER_64; /* preload = 256 - 250 */
			gu16_PRELOAD = 256 - 250;
			
			#elif TMU_TIMER_CH1
			
			gstr_Timer_Cfg.Timer_CH_NO = TIMER_CH1;
			gstr_Timer_Cfg.Timer_Prescaler = TIMER_PRESCALER_1024; /* preload = 65536 - 156 */
			gu16_PRELOAD = 65536 - 15;
			
			#elif TMU_TIMER_CH2
			
			gstr_Timer_Cfg.Timer_CH_NO = TIMER_CH2;
			gstr_Timer_Cfg.Timer_Prescaler = TIMER_PRESCALER_1024; /* preload = 65536 - 156 */
			gu16_PRELOAD = 256 - 15;
			
			#endif
			
			
			gstr_Timer_Cfg.Timer_Mode = TIMER_MODE;
			gstr_Timer_Cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			gstr_Timer_Cfg.Timer_Cbk_Fun = TMU_TimerOvf_CBK;
			
			/* Initializing the  timer */
			
			u8_status = Timer_Init(&gstr_Timer_Cfg);
					
			/* set TMU module is initialized */
			
			gsu8_TMUInitStatus = INITIALIZED;
		}
		
	return u8_status;
}

/**
* @brief: TMU DeInitialization
*			empty the buffer from tasks
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_DeInit(void)
{	
		
		/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = TMU_ERROR_BASE + NO_ERRORS;
		
		if (gsu8_TMUInitStatus == NOT_INITIALIZED)
		{
			u8_status = TMU_ERROR_BASE + ERROR_NOT_INITIALIZED;
		}
		else
		{
			/* empty the buffer */
			uint8_t u8_counter;
			for(u8_counter = 0; u8_counter < MAX_TASK_COUNT; u8_counter++)
			{
				gastrTMU_Buff[u8_counter].gptrTMU_Function = NULL;
				gastrTMU_Buff[u8_counter].u16_Delay = 0;
				gastrTMU_Buff[u8_counter].u16_MilliSecond_Count = 0;
				gastrTMU_Buff[u8_counter].u8_Periodicity = 0;
			}

			/*  TMU module is not initialized */
			gsu8_TMUInitStatus = NOT_INITIALIZED;
			
		}
	
	return u8_status;
}

/**
* @brief: add task to the buffer
* @param: gptrTMU_Function: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Start(gptrTMU_Function_t gptrTMU_Function,
					   u16_Delay_t u16_Delay,
					   uint8_t u8_Periodicity)
{
	
	/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = TMU_ERROR_BASE + NO_ERRORS;
		
		
	if(gsu8_TMUInitStatus == NOT_INITIALIZED)
	{
		u8_status = TMU_ERROR_BASE + ERROR_NOT_INITIALIZED;
	}
	else
	{
		if(NULL == gptrTMU_Function)
		{
			u8_status = TMU_ERROR_BASE + ERROR_NULL_POINTER;
		}
		else
		{
			if (gu8_Index == MAX_TASK_COUNT)
			{
				u8_status = TMU_ERROR_BASE + ERROR_FULL_BUFFER;
			}
			else{
			/* add the task to the buffer */
			gastrTMU_Buff[gu8_Index].gptrTMU_Function		= gptrTMU_Function;
			gastrTMU_Buff[gu8_Index].u16_Delay				= u16_Delay;
			gastrTMU_Buff[gu8_Index].u16_MilliSecond_Count  = 0;
			gastrTMU_Buff[gu8_Index].u8_Periodicity         = u8_Periodicity;

			/*start the timer for the first time */
			
			if(gu8_Index == 0)
			{
				#if  TMU_TIMER_CH0
								
				Timer_Start(TIMER_CH0, gu16_PRELOAD);

				#elif  TMU_TIMER_CH1
				Timer_Start(TIMER_CH1, gu16_PRELOAD);
				#elif  TMU_TIMER_CH2
				Timer_Start(TIMER_CH2, gu16_PRELOAD);
				#endif
			}

			gu8_Index++;
		} /* end of else */
	}
  } /* end of outer else */

	return u8_status;
}

/**
* @brief: TMU Stop remove the task from buffer
* @param: gptrTMU_Function: pointer to callback function
* @return: ERROR_STATUS status code with error code if one occurred
*/
 
ERROR_STATUS TMU_Stop(gptrTMU_Function_t gptrTMU_Function)
{
		/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = TMU_ERROR_BASE + NO_ERRORS;
		

	if(gsu8_TMUInitStatus == NOT_INITIALIZED)
	{
		u8_status = TMU_ERROR_BASE + ERROR_NOT_INITIALIZED;
	}
	else
	{
		uint8_t u8_Counter;

		if(gu8_Index == 0)
		{
			u8_status = TMU_ERROR_BASE + ERROR_EMPTY_BUFFER;
		}
		else
		{
			if (NULL == gptrTMU_Function)
			{
			u8_status = TMU_ERROR_BASE + ERROR_NULL_POINTER;
			}
			else
			{
			
			for(u8_Counter = 0; u8_Counter < MAX_TASK_COUNT; u8_Counter++)
				{
					if(gastrTMU_Buff[u8_Counter].gptrTMU_Function == gptrTMU_Function)
					{
					/* Check if one task exist or full */
					if((gu8_Index == 1) || (gu8_Index == MAX_TASK_COUNT))
						{
						TMU_ClearTask(gu8_Index);
						gu8_Index--;
						}
						else
						{
						TMU_ShiftTasks(u8_Counter , (gu8_Index-1));

						TMU_ClearTask((gu8_Index-1));
						gu8_Index--;
						}
				   }
			  }
		  }
		}

		/*  if buffer is empty so stop the timer */
		
		if(gu8_Index == 0)
		{
			#if  TMU_TIMER_CH0
			Timer_Stop(TIMER_CH0);
			
			#elif  TMU_TIMER_CH1
			Timer_Stop(TIMER_CH1); 
			#elif  TMU_TIMER_CH2
			Timer_Stop(TIMER_CH2);
			#endif
		}
	}
	return u8_status;
}

/**
* @brief: TMU Loops through task list and execute each one as requested
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Dispatcher(void)
{
		/*
		ERROR_STATUS u8_status = E_OK;
*/
		ERROR_STATUS u8_status = TMU_ERROR_BASE + NO_ERRORS;
		

	if(gu8_TMU_TimerOvf_Flag == OVF_TRIGGERED)
	{
		uint8_t u8_Counter;
			
		for(u8_Counter = 0; u8_Counter < gu8_Index; u8_Counter++)
		{
			if(NULL == gastrTMU_Buff[u8_Counter].gptrTMU_Function)
			{
				/* skip for now until making circular buffer */
				u8_status = TMU_ERROR_BASE + ERROR_NULL_POINTER;

			}
			else
			{
				gastrTMU_Buff[u8_Counter].u16_MilliSecond_Count++;
			}
		}


		/* Loop through TCB buffer and execute the tasks */
		
		for(u8_Counter = 0; u8_Counter < gu8_Index; u8_Counter++)
		{
			if(NULL == gastrTMU_Buff[u8_Counter].gptrTMU_Function)
			{
				/* skip for now until making circular buffer */
				u8_status = TMU_ERROR_BASE + ERROR_NULL_POINTER;

			}
			else
			{
				/* if the delay is complete */
				
			if(gastrTMU_Buff[u8_Counter].u16_MilliSecond_Count >= gastrTMU_Buff[u8_Counter].u16_Delay)
				{
					gastrTMU_Buff[u8_Counter].u16_MilliSecond_Count = 0;

					gastrTMU_Buff[u8_Counter].gptrTMU_Function();
								
					if(gastrTMU_Buff[u8_Counter].u8_Periodicity == ONE_SHOT)
					{
						TMU_Stop(gastrTMU_Buff[u8_Counter].gptrTMU_Function);
					}
				}	
			} /* end of else */
		} /* end of for */
	} /*check the ovf flag */
	
	else
	{
		/*u8_status = E_NOK;*/
	}
	return u8_status;
}

static void TMU_TimerOvf_CBK(void)
{
	gu8_OvfCounter++;
	
	if(gu8_OvfCounter == TMU_RESOLUTION)
	{
		gu8_TMU_TimerOvf_Flag = OVF_TRIGGERED;

		gu8_OvfCounter = 0;
	}
		
	/* Restart and pre-load timer */
	#if  TMU_TIMER_CH0
	
	Timer_Start(TIMER_CH0, gu16_PRELOAD);
	
	#elif  TMU_TIMER_CH1
	Timer_Start(TIMER_CH1, 65286);
	#elif  TMU_TIMER_CH2
	Timer_Start(TIMER_CH2, 6);
	#endif
}

static void TMU_ClearTask(uint8_t u8_index){
	
	  gastrTMU_Buff[gu8_Index].gptrTMU_Function			= NULL;
	  gastrTMU_Buff[gu8_Index].u16_Delay				= 0;
	  gastrTMU_Buff[gu8_Index].u16_MilliSecond_Count    = 0;
	  gastrTMU_Buff[gu8_Index].u8_Periodicity			= 0;
}

static void TMU_ShiftTasks(uint8_t newIndex, uint8_t oldIndex){
	
	
	  gastrTMU_Buff[newIndex].gptrTMU_Function		= gastrTMU_Buff[oldIndex].gptrTMU_Function;
	  gastrTMU_Buff[newIndex].u16_Delay				= gastrTMU_Buff[oldIndex].u16_Delay;
	  gastrTMU_Buff[newIndex].u16_MilliSecond_Count = gastrTMU_Buff[oldIndex].u16_MilliSecond_Count;
	  gastrTMU_Buff[newIndex].u8_Periodicity		= gastrTMU_Buff[oldIndex].u8_Periodicity;

}