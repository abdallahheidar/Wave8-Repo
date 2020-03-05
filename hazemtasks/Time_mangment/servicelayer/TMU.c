/*
 * TMU.c
 *
 * Created: 2/24/2020 3:58:24 PM
 *  Author: Hazem 
 */ 

#include "TMU.h"

static uint8_t g_res;
static uint8_t gs_arraycount;

Task_BlockType gstr_arrayoftasks[BUFFER_SIZE]={0};


/************************************************************************/
/* TMU_Init
EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr )
Synchronous
Non Reentrant
ConfigPtr Pointer to a selected configuration structure*/
/************************************************************************/
EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr )
{
   EnmTMUError_t status =E_OK;
   g_res=ConfigPtr->RES;
   Timer_cfg_s instance={0};
   switch(ConfigPtr->TIMER_ID)
   {    
     case TIMER_0:
            instance.Timer_CH=TIMER_0;
            instance.Timer_Mode=TIMER_MODE;
            instance.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
            instance.Timer_Prescaler=TIMER_PRESCALER_64;
            Timer_Init(&instance);
            break;
      case TIMER_1:
            instance.Timer_CH=TIMER_1;
            instance.Timer_Mode=TIMER_MODE;
            instance.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
            instance.Timer_Prescaler=TIMER_PRESCALER_64;
            Timer_Init(&instance);
            break;
      case TIMER_2:
             instance.Timer_CH=TIMER_2;
             instance.Timer_Mode=TIMER_MODE;
             instance.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
             instance.Timer_Prescaler=TIMER_PRESCALER_64;
             Timer_Init(&instance);
             break;
      default:
             status =E_NOK;
             break;
   }
   return status;
}


/*
Function Name 	TMU_Start_Timer
Syntax:
Sync/Async:
Reentrancy:
Parameters (in):
Parameters (out):
Parameters (inOut):
Return:*/

EnmTMUError_t TMU_Start_Timer(uint16_t time,ptrtotask_CBK_FUNC ptrtofun,uint8_t periodicORoneshot)
{   EnmTMUError_t status=E_OK;
   if(gs_arraycount<BUFFER_SIZE)
   {
      
   
  gstr_arrayoftasks[gs_arraycount].delay=time;
  gstr_arrayoftasks[gs_arraycount].Ptrtotask=ptrtofun;
  gstr_arrayoftasks[gs_arraycount].perodicity=periodicORoneshot;
  gstr_arrayoftasks[gs_arraycount].delay_milistone=0;
  
  if(gs_arraycount==0)
  {
     Timer_Start(TMU_TIMER_ID,6);  
  }

gs_arraycount++;
   }
   else
   {
      status=E_NOK;
   }
return status;
}
/**
* @brief: TMU Stop
* @param: ptrFun: pointer to callback function
* @return: EnmTMUError_t status code with error code if one occurred
*/
EnmTMUError_t TMU_Stop_Timer(void (*ptrtofun)(void))
{
   EnmTMUError_t status=E_OK;
   uint8_t au8_counter=0; 
   uint8_t Flag=0;
   for(au8_counter=0;au8_counter<BUFFER_SIZE;au8_counter++)
   {
      if(gstr_arrayoftasks[au8_counter].Ptrtotask==ptrtofun)
      {   Flag=1;
         if(au8_counter==BUFFER_SIZE-1)
         {
            gstr_arrayoftasks[au8_counter].Ptrtotask=NULL;
            gstr_arrayoftasks[au8_counter].delay_milistone=0;
            gstr_arrayoftasks[au8_counter].delay=0;
            gstr_arrayoftasks[au8_counter].perodicity=0;
         }
         else
         {
            gstr_arrayoftasks[au8_counter].Ptrtotask=gstr_arrayoftasks[BUFFER_SIZE-1].Ptrtotask;
            gstr_arrayoftasks[au8_counter].delay_milistone=gstr_arrayoftasks[BUFFER_SIZE-1].delay_milistone;
            gstr_arrayoftasks[au8_counter].delay=gstr_arrayoftasks[BUFFER_SIZE-1].delay;
            gstr_arrayoftasks[au8_counter].perodicity=gstr_arrayoftasks[BUFFER_SIZE-1].perodicity;
            
            gstr_arrayoftasks[BUFFER_SIZE-1].Ptrtotask=NULL;
            gstr_arrayoftasks[BUFFER_SIZE-1].delay_milistone=0;
            gstr_arrayoftasks[BUFFER_SIZE-1].delay=0;
            gstr_arrayoftasks[BUFFER_SIZE-1].perodicity=0;
         }
         gs_arraycount--;
      }
      
   }
   if(gs_arraycount==0)
   {
      Timer_Stop(TMU_TIMER_ID);
   }
  if(Flag==0)
  {
   status=E_NOK;
  }   
   return status;
}


/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/


EnmTMUError_t TMU_Dispatch(void)
{
   EnmTMUError_t status=E_OK;
   uint8_t u8_preloadtimer=6;
   
   if(gu_timer_count1>=RESOLUTION)
   { 
      gu_timer_count1=0;
      
      Timer_SetValue(TMU_TIMER_ID,&u8_preloadtimer);
      	/*Loop through Tasks in the array and increment milestones*/
      uint8_t u8_counter=0;
      for(u8_counter=0;u8_counter<BUFFER_SIZE;u8_counter++)
      {
         if(gstr_arrayoftasks[u8_counter].Ptrtotask==NULL)
         {
            
         }
         else
         {
            gstr_arrayoftasks[u8_counter].delay_milistone++;
         }
      }
      /* Loop through  array of structure and handle each one */
      for(u8_counter=0;u8_counter<BUFFER_SIZE;u8_counter++)
      {
         if(gstr_arrayoftasks[u8_counter].Ptrtotask==NULL)
         {
            
         }
         else
         {
            if(gstr_arrayoftasks[u8_counter].delay_milistone>=gstr_arrayoftasks[u8_counter].delay)
             {
                gstr_arrayoftasks[u8_counter].delay_milistone=0;
                gstr_arrayoftasks[u8_counter].Ptrtotask();
                if(gstr_arrayoftasks[u8_counter].perodicity==ONESHOT)
                {
                   TMU_Stop_Timer(gstr_arrayoftasks[u8_counter].Ptrtotask);
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
   return status;
}

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/
EnmTMUError_t TMU_DeInit(void)
{
   EnmTMUError_t u8_status=E_OK;
   uint8_t u8_counter=0;
   for(u8_counter=0;u8_counter<BUFFER_SIZE;u8_counter++)
   {
       gstr_arrayoftasks[u8_counter].Ptrtotask=NULL;
       gstr_arrayoftasks[u8_counter].delay_milistone=0;
       gstr_arrayoftasks[u8_counter].delay=0;
       gstr_arrayoftasks[u8_counter].perodicity=0;
      
   }
   Timer_Stop(TMU_TIMER_ID);
   
   return u8_status;
}
