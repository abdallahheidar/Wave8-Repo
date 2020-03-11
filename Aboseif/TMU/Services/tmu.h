/*
 * tmu.h
 *
 * Created: 2020-02-24 11:20:47 AM
 *  Author: EbrahimOseif
 */ 


#ifndef TMU_H_
#define TMU_H_

/************************************************************************/
/*				             INCLUDES		                 	        */
/************************************************************************/

#include "../Util/std_types.h"
#include "../Services/tmu_cfg.h"
#include "../MCAL/Timer.h"
#include "../Util/Error.h"


/************************************************************************/
/*				         DEFINES								        */
/************************************************************************/


 /* function state periodic or one shot */
 
#define PERIODIC				(0)
#define ONE_SHOT				(1)

/* timer resolution in ms */

#define TMU_RESOLUTION			(10)

/* pointer to function type */

typedef void (*gptrTMU_Function_t) (void);

/* module state */
#define NOT_INITIALIZED		0
#define INITIALIZED			1

typedef	uint16_t u16_Delay_t;


/************************************************************************/
/*			  Structures Dclarations		                            */
/************************************************************************/


typedef struct strTMU_TCB_t
{
  gptrTMU_Function_t gptrTMU_Function;
  u16_Delay_t u16_Delay;
  u16_Delay_t u16_MilliSecond_Count;
  uint8_t u8_Periodicity;
}strTMU_TCB_t;

/* Create the buffer  of tasks */
strTMU_TCB_t gastrTMU_Buff[MAX_TASK_COUNT];



/************************************************************************/
/*						 FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/

/**
* @brief: TMU Initialization
*		  initialize the timer and buffer
* @param: void
* Input : void
* Output:  
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Init(void);

/**
* @brief: TMU DeInitialization
*			empty the buffer from tasks
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_DeInit(void);

/**
* @brief: add task to the buffer
* @param: gptrTMU_Function: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Start(gptrTMU_Function_t gptrTMU_Function,
						 u16_Delay_t u16_Delay, uint8_t u8_Periodicity);

/**
* @brief: TMU Stop remove the task from buffer
* @param: gptrTMU_Function: pointer to callback function
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Stop(gptrTMU_Function_t gptrTMU_Function);

/**
* @brief: TMU Loops through task list and execute each one as requested
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS status code with error code if one occurred
*/
ERROR_STATUS TMU_Dispatcher(void);


#endif /* TMU_H_ */