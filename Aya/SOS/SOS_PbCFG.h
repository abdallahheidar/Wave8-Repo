/*
 * TMU_PbCfg.h
 *
 * Created: 2/24/2020 3:05:47 PM
 *  Author: Khaled
 */ 


#ifndef TMU_PBCFG_H_
#define TMU_PBCFG_H_

 #include "../Utilis/std_types.h"
 #include "../../MCAL/TIMERS/timers.h"


 typedef struct str_TMU_InitConfig_t
 {
	 uint8_t u8_Timer_Id;
	 uint8_t u8_Tmu_Res;
 }str_TMU_InitConfig_t;
 
 typedef struct gstr_Task_Info_t
 {
	 uint8_t Task_Id;
	 uint16_t Time_Delay;
	 uint8_t Repeat;
	  void(* Ptr_Func)(void);
 }gstr_Task_Info_t;
 
extern str_TMU_InitConfig_t init;
 
#endif /* TMU_PBCFG_H_ */