#ifndef SOS_H_
#define SOS_H_
/*
 * File		: Sos.h
 * Author	: M.Ramadan
 */

/*********************************************
 *				Includes  					 *
 ********************************************/
 #include "Timer.h"
 #include "Sos_cfg.h"


/*********************************************
 *				Defines  					 *
 ********************************************/
 #define No_of_CBK    3
 
 #define E_OK    0
 #define E_NOK   1
 
 #define NULL_PTR					 2
 #define MODULE_UNITIALIZED			 3
 #define MULTIPLE_INIYIALIZATION	 4
 #define STOP_WITH_START			 5
 #define INVALID_PARAMETER			 6
 #define MULTIPLE_STOP				 7
 #define MULTIPLE_START				 8
 #define FULL_BUFFER				 9
 #define EMPTY_BUFFER				 10

 
/************************************************************************/
/*			  Structures Declaration		                            */
/************************************************************************/
typedef struct Sos_cfg_start
{
	uint16_t Sos_delay;
	uint16_t Sos_periodicity;
	uint16_t Sos_Counter;
	
	//typedef Sos_Cbk_ptr then use data type
	void (*Sos_Cbk_ptr)(void);
}Sos_Cfg_start;
 
/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/ 
extern Sos_Cfg_start Sos_Cfg_start_Fun1;
extern Sos_Cfg_start Sos_Cfg_start_Fun2;
extern Sos_Cfg_start Sos_Cfg_start_Fun3; 
 
typedef enum EnmSosError_t{
	Null_ptr=0, Module_Not_Initialized = 1, Multiple_Initialization = 2, Stop_Without_start =3, Invalid_Parameter = 4, Multiple_Stop =5, Multiple_Start =6, Full_Buffer= 7
}EnmSosError_t;
 
 

 /*********************************************
 *	  	   Function prototypes				 *
 ********************************************/
 
 /**
 * Func			: Sos_Init
 * Input		: Pointer to a structure of type Sos_cfg_Init contains the Sos channel timer and resolution
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (timer channel ,resolution of the Sos)
 */
 
 
 uint8_t Sos_Init(const Sos_ConfigType * ConfigPtr );
 
/**
 * Func			: Sos_Start
 * Input		: Pointer to a structure of type contains the Sos_delay ,Sos_periodicity and call back function
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (timer channel ,resolution of the Sos)
 */

uint8_t Sos_Start(Sos_Cfg_start * SosStartPtr); 


 /**
 * Func			: Sos_Stop
 * Input		: Pointer to a structure of type  call back function
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: stop(call back function)
 */
 
 void Sos_Stop_Timer ();
 
 /**
 * Func			: Sos_Dispatch
 * Input		: Pointer to a pointer to array of Call Back Structure functions
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: 
 */
 
 uint8_t Sos_Dispatch();
 
 /**
 * Func			: Sos_Deinit
 * Input		: Pointer to a structure of type Sos_cfg_Init contains the Sos channel timer and resolution
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Deinitialize (timer channel ,resolution of the Sos)
 */
 
 
 void Sos_DeInit(void);
 
 
 #endif