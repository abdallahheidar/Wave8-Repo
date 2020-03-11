/*
 * SOS.h
 *
 * Created: 2020-02-24 11:20:47 AM
 *  Author: EbrahimOseif
 */ 


#ifndef SOS_H_
#define SOS_H_

/************************************************************************/
/*				             INCLUDES		                 	        */
/************************************************************************/

#include "std_types.h"
#include "SOS_cfg.h"
#include "Timer.h"
#include "Error.h"


/************************************************************************/
/*				         DEFINES								        */
/************************************************************************/


 /* function state periodic or one shot */
 
#define PERIODIC				(0)
#define ONE_SHOT				(1)

/* timer resolution in ms */

#define SOS_RESOLUTION			(10)

/* pointer to function type */

typedef void (*gptrSOS_Function_t) (void);

/* module state */
#define NOT_INITIALIZED		0
#define INITIALIZED			1

typedef	uint16_t u16_Delay_t;


/************************************************************************/
/*			  Structures Dclarations		                            */
/************************************************************************/


typedef struct strSOS_TCB_t
{
  gptrSOS_Function_t gptrSOS_Function;
  u16_Delay_t u16_Delay;
  u16_Delay_t u16_MilliSecond_Count;
  uint8_t u8_Periodicity;
}strSOS_TCB_t;

/* Create the buffer  of tasks */
strSOS_TCB_t gastrSOS_Buff[MAX_TASK_COUNT];



/************************************************************************/
/*						 FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/

/**
* @brief: SOS Initialization
*		  initialize the timer and buffer
* @param: void
* Input : void
* Output:  
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Init(void);

/**
* @brief: SOS DeInitialization
*			empty the buffer from tasks
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_DeInit(void);

/**
* @brief: add task to the buffer
* @param: gptrSOS_Function: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Start(gptrSOS_Function_t gptrSOS_Function,
						 u16_Delay_t u16_Delay, uint8_t u8_Periodicity);

/**
* @brief: SOS Stop remove the task from buffer
* @param: gptrSOS_Function: pointer to callback function
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Stop(gptrSOS_Function_t gptrSOS_Function);

/**
* @brief: SOS Loops through task list and execute each one as requested
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS SOS_Dispatcher(void);


#endif /* SOS_H_ */