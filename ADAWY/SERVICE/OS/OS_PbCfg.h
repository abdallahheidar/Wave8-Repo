/*
 * OS_PbCfg.h
 *
 * Created: 2/24/2020 3:05:47 PM
 *  Author: Khaled
 */ 


#ifndef OS_PBCFG_H_
#define OS_PBCFG_H_

 #include "../std_types.h"
 #include "../../MCAL/Timer/timers.h"

 typedef struct str_OS_InitConfig_t
 {
	 uint8_t u8_Timer_Id;
	 uint8_t u8_OS_Res;
 }str_OS_InitConfig_t;

 extern str_OS_InitConfig_t str_OS_InitConf;
 
#endif /* OS_PBCFG_H_ */