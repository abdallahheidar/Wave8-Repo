/*
 * TMU.c
 *
 * Created: 2/24/2020 3:58:24 PM
 *  Author: Hazem 
 */ 


/*- INCLUDES -----------------------------------------------*/

#include "SOS.h"

/*- LOCAL Data types ----------------------------------------*/

typedef  struct  Task_BlockType
{
	uint8_t perodicity;
	uint16_t delay;
	ptrtotask taskfunc;
	uint16_t delay_milistone;
}Task_BlockType;

/*- GLOBAL STATIC VARIABLES -------------------------------*/

static uint8_t gu8_TMUresloution;
static uint8_t gu8_TMUtasks;
static uint8_t gu8_TMUinitflag;
Task_BlockType static gastr_TMUbuffer[BUFFER_SIZE]={CLEAR};
volatile static uint32_t gu32_TMUtick;




	
/*- APIs IMPLEMENTATION -----------------------------------*/

	
/************************************************************************/
/* TMU_Init
EnmTMUError_t TMU_Init (const PtrTMU_Configtype ConfigPtr )
ConfigPtr Pointer to a selected configuration structure*/
/************************************************************************/

EnmTMUError_t TMU_Init (const PtrTMU_Configtype ConfigPtr )
{  
	 /* error variable for init fun*/	 
	EnmTMUError_t au8_TMUiniterror =E_OK;
	  	
	/* check pointer_config is null or not */
	if(ConfigPtr==NULL)
	{
		/*if null return null error from error handling*/
		au8_TMUiniterror =TMU_INIT_NULL_POINTER; 
	}
	else
	{  
		/*INITIALIZED all global variables*/
	    gu8_TMUresloution=CLEAR;
		gu8_TMUtasks=CLEAR;
		/*check TMU is init or not*/
		if(gu8_TMUinitflag==INITIALIZED)
		{
			/*if yes return multiple init error from error handling*/
			au8_TMUiniterror=TMU_MULTIPLE_INIT;
		}
		else
		{   
			/*store Resolution into global static variable*/  
			gu8_TMUresloution=ConfigPtr->u8_res;
			/*config timer according to TMU_TIMERID*/  
			Timer_cfg_s str_TMUtimerconfig={CLEAR};
			switch(ConfigPtr->u8_TMU_timerid)
			{
				case TIMER_0:
				str_TMUtimerconfig.Timer_CH=TIMER_0;
				str_TMUtimerconfig.Timer_Mode=TIMER_MODE;
				str_TMUtimerconfig.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
				str_TMUtimerconfig.Timer_Prescaler=TIMER_PRESCALER_64;
				break;
				case TIMER_1:
				str_TMUtimerconfig.Timer_CH=TIMER_1;
				str_TMUtimerconfig.Timer_Mode=TIMER_MODE;
				str_TMUtimerconfig.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
				str_TMUtimerconfig.Timer_Prescaler=TIMER_PRESCALER_64;
				break;
				case TIMER_2:
				str_TMUtimerconfig.Timer_CH=TIMER_2;
				str_TMUtimerconfig.Timer_Mode=TIMER_MODE;
				str_TMUtimerconfig.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
				str_TMUtimerconfig.Timer_Prescaler=TIMER_PRESCALER_64;
				break;
				default:
				au8_TMUiniterror =E_NOK;
				break;
			}
			/*check timer is init correct or not */  
			if(Timer_Init(&str_TMUtimerconfig)==E_OK)
			{
				
			}
			else
			{
				au8_TMUiniterror=E_NOK;
			}
		}
	}
	/*convert module into INITIALIZED mode*/  
	gu8_TMUinitflag=INITIALIZED;
	
	return au8_TMUiniterror;
}


/*
Function Name 	TMU_Start_Timer
Syntax:     
Sync/Async:   ASYNC  
Parameters (in):
Parameters (out):
Parameters (inOut):
Return:
*/

EnmTMUError_t TMU_Start_Timer(uint16_t u16_time,ptrtotask pf_task,uint8_t u8_periodicORoneshot)
{   
	/* error variable for TMU_start fun initial value no error*/
	EnmTMUError_t au8_TMUstarterror=E_OK;
	
	/*check if module is initialized or not*/
	if(gu8_TMUinitflag==NOTINITIALIZED)
	{
		au8_TMUstarterror=TMU_MODULE_NOTINITIALIZED;
	}
	
	else
	{
		/*check if tasks is less than the maximum number of tasks */
		if(gu8_TMUtasks<MAX_NOTASKS)
		{
			/*check if period is neither one shot or periodic */
			if((u8_periodicORoneshot!=PERIODIC)&&(u8_periodicORoneshot!=ONESHOT))
			{
				au8_TMUstarterror=TMU_NOT_PERODICORONESHOT;
			}
			else
			{
				/*check if fun address is not a null */
				if(pf_task==NULL)
				{
					au8_TMUstarterror=TMU_FUN_NULL_POINTER;
				}
				else
				{
					/*add task to TMU_buffer */
					gastr_TMUbuffer[gu8_TMUtasks].delay=u16_time;
					gastr_TMUbuffer[gu8_TMUtasks].taskfunc=pf_task;
					gastr_TMUbuffer[gu8_TMUtasks].perodicity=u8_periodicORoneshot;
					gastr_TMUbuffer[gu8_TMUtasks].delay_milistone=CLEAR;
                    /*check if task is the first task */
					if(gu8_TMUtasks==FIRST_TASK)
					{
						/*start timer*/
						Timer_Setcallback(TMU_schedulertime);
						if(Timer_Start(TMU_TIMER_ID,TCNT_INITIAL_VALUE)==E_OK)
						{
							
						}
						else
						{
							au8_TMUstarterror=E_NOK;
						}
					}

					gu8_TMUtasks++;
				}
			}
		}
		/*if task not less than max_number_of_tasks return buffer is full */
		else
		{
			au8_TMUstarterror=TMU_BUFFER_IS_FULL;
		}
	}
	return au8_TMUstarterror;
}
/**
* @brief: TMU Stop
* @param: ptrFun: pointer to callback function
* @return: EnmTMUError_t au8_TMUstoperror code with error code if one occurred
*/

EnmTMUError_t TMU_Stop_Timer(ptrtotask ptrtofun)
{	
	/* error variable for TMU_stop fun initial value no error*/
	EnmTMUError_t au8_TMUstoperror=E_OK;
	uint8_t au8_counter;
    /* flag variable to identify the task wanted to stop exist or not */
	uint8_t au8_taskisfound=NOT_FOUND;
	/* if no task is running return TMU_bufferisempty */
	if(gu8_TMUtasks==NOTASKTOSTOP)
	{
		au8_TMUstoperror=TMU_BUFFER_IS_EMPTY;
	}
	else
	{
		/* loop over running tasks */
		for(au8_counter=FIRST_TASK;au8_counter<gu8_TMUtasks;au8_counter++)
		{
             /* task wanted to stop founded  */
			if(gastr_TMUbuffer[au8_counter].taskfunc==ptrtofun)
			{
				/* raise flag*/  
			    au8_taskisfound=FOUND;
			     /* if stooped task equal last task in buffer*/
				if(au8_counter==LAST_TASK)
				{
		            /* just null it to initial state and decrease running task by one*/
					gastr_TMUbuffer[au8_counter].taskfunc=NULL;
					gastr_TMUbuffer[au8_counter].delay_milistone=CLEAR;
					gastr_TMUbuffer[au8_counter].delay=CLEAR;
					gastr_TMUbuffer[au8_counter].perodicity=CLEAR;
				}
				else
				{
				    /* if not swap stooped task by the last task in buffer and null the last one*/
					gastr_TMUbuffer[au8_counter].taskfunc=gastr_TMUbuffer[gu8_TMUtasks].taskfunc;
					gastr_TMUbuffer[au8_counter].delay_milistone=gastr_TMUbuffer[gu8_TMUtasks].delay_milistone;
					gastr_TMUbuffer[au8_counter].delay=gastr_TMUbuffer[gu8_TMUtasks].delay;
					gastr_TMUbuffer[au8_counter].perodicity=gastr_TMUbuffer[gu8_TMUtasks].perodicity;
                    /* and null it to initial state and decrease running task by one*/
					gastr_TMUbuffer[gu8_TMUtasks].taskfunc=NULL;
					gastr_TMUbuffer[gu8_TMUtasks].delay_milistone=CLEAR;
					gastr_TMUbuffer[gu8_TMUtasks].delay=CLEAR;
					gastr_TMUbuffer[gu8_TMUtasks].perodicity=CLEAR;
				}
				gu8_TMUtasks--;
			}

		}
	    /* if task deleted equal last task stop timer*/	
		if(gu8_TMUtasks==LAST_TASK)
		{
			if(Timer_Stop(TMU_TIMER_ID)==E_OK)
			{
				
			}
			else
			{
				au8_TMUstoperror=E_NOK;
			}
		}
	     /* if task deleted not found return no_task to stop_error */
		if(au8_taskisfound==NOT_FOUND)
		{
			au8_TMUstoperror=TMU_NOTASK_FOUND_TO_STOP;
		}
	}
	return au8_TMUstoperror;
}


/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t au8_TMUdiserror code with error code if one occurred
*/


EnmTMUError_t TMU_Dispatch(void)
{
    /* error variable for TMU_stop fun initial value no error*/
	EnmTMUError_t au8_TMUdiserror=E_OK;
	/* pre_load value of timer variable to readjust the system tick*/
	uint8_t au8_preloadtimer=TCNT_INITIAL_VALUE;
	/* if system tick equal to adjust pre_configure resolution start dispatcher */
	if(gu32_TMUtick==RESOLUTION)
	{
		/* clear system tick */
		gu32_TMUtick=CLEAR;
       /* readjust timer to make a system_tick after 1ms(system tick) */
		if(Timer_SetValue(TMU_TIMER_ID,&au8_preloadtimer)==E_OK)
		{
			
		}
		else 
		{
			au8_TMUdiserror=E_NOK;
		}
		/*Loop through Tasks in the array and increment milestones*/
		uint8_t u8_counter=CLEAR;
		for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
		{
			if(gastr_TMUbuffer[u8_counter].taskfunc==NULL)
			{

			}
			else
			{
				gastr_TMUbuffer[u8_counter].delay_milistone++;
			}
		}
		/* Loop through  array of tasks and handle each one */
		for(u8_counter=START;u8_counter<gu8_TMUtasks;u8_counter++)
		{
			if(gastr_TMUbuffer[u8_counter].taskfunc==NULL)
			{

			}
			else
			{
				/* if delay task time_delay is ready  clear milestones ticks of task and serve it*/
				if(gastr_TMUbuffer[u8_counter].delay_milistone==gastr_TMUbuffer[u8_counter].delay)
				{
					gastr_TMUbuffer[u8_counter].delay_milistone=CLEAR;
					gastr_TMUbuffer[u8_counter].taskfunc();
				   /* if task is one shot remove it from scheduler*/
					if(gastr_TMUbuffer[u8_counter].perodicity==ONESHOT)
					{
						if(TMU_Stop_Timer(gastr_TMUbuffer[u8_counter].taskfunc)==E_OK)
						{
							
						}
						else
						{
							au8_TMUdiserror=E_NOK;
						}
					}
				}
				else
				{

				}
			}
		}
	}
	else
	{

	}
	return au8_TMUdiserror;
}

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t au8_TMUdiserror code with error code if one occurred
*/
EnmTMUError_t TMU_DeInit(void)
{
	/* error variable for TMU_dinit fun initial value no error*/
	EnmTMUError_t au8_TMUEROR=E_OK;
   /* clear all global  variable */
	uint8_t u8_counter=CLEAR;
	gu8_TMUresloution=CLEAR;
	gu8_TMUtasks =CLEAR;
	/*if TMU was INITIALIZED */
	if(gu8_TMUinitflag==INITIALIZED)
	{
		/*loop to all tasks and null it and stop system tick by stopped the timer*/
		for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
		{
			gastr_TMUbuffer[u8_counter].taskfunc=NULL;
			gastr_TMUbuffer[u8_counter].delay_milistone=CLEAR;
			gastr_TMUbuffer[u8_counter].delay=CLEAR;
			gastr_TMUbuffer[u8_counter].perodicity=CLEAR;

		}
		if(Timer_Stop(TMU_TIMER_ID)==E_OK)
		{
			
		}
		else
		   au8_TMUEROR=E_NOK;
		  
	}
    /*if TMU WAS NOT_INITIALIZED RETURN TMU_MODULE_NOTINITIALIZED*/
	else
	{
		au8_TMUEROR=TMU_MODULE_NOTINITIALIZED;
	}
	gu8_TMUinitflag = NOTINITIALIZED;
	return au8_TMUEROR;
}


 /*increment system tick variable each interrupt of the timer by this callback function*/
extern void TMU_schedulertime(void)
{
	gu32_TMUtick++;
}