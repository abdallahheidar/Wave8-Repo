/*
 * TMU.h
 *
 * Created: 2/24/2020 12:19:58 PM
 *  Author: MENA
 */ 


#ifndef TMU_H_
#define TMU_H_

/************************************************************************/
/*							 INCLUDES							        */
/************************************************************************/

#include "std_types.h"
#include "registers.h"


/************************************************************************/
/*							 DEFINES							        */
/************************************************************************/

#define PERIODIC 0 
#define  ONESHOT 1

#define TMU_TIMER_CH0 0
#define TMU_TIMER_CH1 1
#define TMU_TIMER_CH2 2


#define TMU_BUFFER_SIZE 100


#define reselution_one_mili 1


/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct TMU_Cfg_s{
	
	uint8_t Timer_channel ;
	uint8_t TMU_Reselution ;
	
	
	}TMU_Cfg_s;
	
	
typedef struct TMU_tsak_s{
	
	uint8_t Task_ID;
	void (* Ptr_FunctionCall)(void) ; 
	uint16_t delay_time ;
	uint8_t TMU_mode ;/* periodic or one shot*/
	uint16_t N_OVFs ;
	
	}TMU_tsak_s;



/************************************************************************/
/*				    TMU FUNCTIONS' PROTOTYPES				        */
/************************************************************************/


/**
 * Input: Pointer to a structure contains the information needed to initialize the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */


ERROR_STATUS TMU_Init (TMU_Cfg_s *TMU_Cfg);




/**
 * Input: Pointer to a structure contains the information needed to deinitialize the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: DeInitiates the module.
 * 							
 */


ERROR_STATUS TMU_DeInit (TMU_Cfg_s *TMU_Cfg);


/**
 * Input: Pointer to a structure contains the information needed to start the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: start the module.
 * 							
 */


ERROR_STATUS TMU_Start_Timer (TMU_tsak_s *TMU_task);


/**
 * Input: Pointer to a structure contains the information needed to stop the TMU. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: stop the module.
 * 							
 */


ERROR_STATUS TMU_Stop_Timer (TMU_tsak_s *TMU_task);


/**
 * Input: void. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Run the basic logic code to calculate the timing
 * and call the user function depends on the timeout event for each software timer object.
 * 							
 */


ERROR_STATUS TMU_Dispatch (void);









#endif /* TMU_H_ */