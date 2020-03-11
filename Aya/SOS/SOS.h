/*
 * SOS.h
 *
 * Created: 3/11/2020 5:10:22 PM
 * Author : A_ayman
 */ 


#ifndef SOS_H_
#define SOS_H_

/* Inclusions */
#include "../../MCAL/TIMERS/timers.h"
#include "../Utilis/std_types.h"
#include "SOS_CFG.h"
#include "SOS_PbCFG.h"
#include "../ERROR_HANDLING/ERROR-STORE.h"
#include "../ERROR_HANDLING/Errors.h"



/* Constants */

/*
*** this macro determine whether the task would be repeated or happen only once
*/

#define ONE_SHOT 0 
#define PERIODIC 1

/*macro to select timer id*/
#define  Timer_0      0
#define  Timer_1      1
#define  Timer_2      2





/* function declarations*/


/******************************************************************************
* Function        : ERROR_STATUS SOS_Init (const str_SOS_InitConfig_t * pstr_SOS_ConfigPtr );
* Type            : public
* Input parameters: SOSCfg Structure (u8_Timer_Id, u8_SOS_Res)
* Return type     : ERROR_STATUS
* Reentrancy	   : Non Reentrant
* Description     : initialize the SOS configuration, which initialize the Timer.
*****************************************************************************/
extern ERROR_STATUS Sos_Init (const str_SOS_InitConfig_t * pstr_SOS_ConfigPtr );

/******************************************************************************
* Function        : ERROR_STATUS SOS_Dispatch(void);
* Type            : public
* Input parameters: none
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : check timing to serve the consumer function.
*****************************************************************************/
extern ERROR_STATUS Sos_Dispatch(void);

/******************************************************************************
* Function        : ERROR_STATUS SOS_Stop(uint8_t Task_Id, void(* Ptr_Func)(void));
* Type            : public
* Input parameters: Task_Id, void(* Ptr_Func)(void)
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : stop SOS for a specific task
*****************************************************************************/
extern ERROR_STATUS Sos_Stop(uint8_t Task_Id);

/******************************************************************************
* Function        : ERROR_STATUS SOS_Start (uint16_t Time_Delay,uint8_t Task_Id, uint8_t Repeat, void(* Ptr_Func)(void));
* Type            : public
* Input parameters: Time_Delay(0 : 65536), Task_Id(0 : 255), Repeat (one shot or periodic), void(* Ptr_Func)(void))
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : start SOS for a specific task
*****************************************************************************/
extern ERROR_STATUS Sos_Start (gstr_Task_Info_t);


/******************************************************************************
* Function        : ERROR_STATUS SOS_DeInit (void);
* Type            : public
* Input parameters: none
* Return type     : ERROR_STATUS
* Reentrancy	   : Non Reentrant
* Description     : start SOS
*****************************************************************************/
extern ERROR_STATUS Sos_DeInit (void);

#endif /* SOS_H_ */