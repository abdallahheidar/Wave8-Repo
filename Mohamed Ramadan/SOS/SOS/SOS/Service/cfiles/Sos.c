
 
 /*********************************************
 *				Includes  					 *
 ********************************************/
 #include "std_types.h"
 #include "Sos.h"
 
 /*********************************************
 *				Defines  					 *
 ********************************************/
#define	FIRSTPIN	0x01
#define	SECONDPIN	0x02
#define	THIRDPIN	0x04

#define	Task1Delay	250
#define	Task2Delay	500
#define	Task3Delay	750

#define	Task1Priodicity		1
#define	Task2Priodicity		1
#define	Task3Priodicity		1

#define	Task1InitCNTValue	0
#define	Task2InitCNTValue	0
#define	Task3InitCNTValue	0

#define Zero	0
#define ONE		1
#define TWO		2	
 /*********************************************
 *	   Function Implementation  	       	  *
 ********************************************/

void func1(void)
{
	
	PORTA_DATA^=FIRSTPIN;
}

void func2(void)
{
	PORTA_DATA^=THIRDPIN;
}

void func3(void)
{
	PORTA_DATA^=SECONDPIN;
}

/********************************************
 *				CBK_Functions               *
*********************************************/
 
Sos_Cfg_start Sos_Cfg_start_Fun1 = {Task1Delay,Task1Priodicity,Task1InitCNTValue,func1};
 
Sos_Cfg_start Sos_Cfg_start_Fun2 = {Task2Delay,Task1Priodicity,Task1InitCNTValue,func2};
 
Sos_Cfg_start Sos_Cfg_start_Fun3 = {Task3Delay,Task1Priodicity,Task1InitCNTValue,func3};
 
/******static global Array of Call Back Structure functions*******/
 static Sos_Cfg_start Sos_CBK_Arr_Struct[No_of_CBK];
 
 /*{Sos_Cfg_start_Fun1,Sos_Cfg_start_Fun2,Sos_Cfg_start_Fun3};*/
 
 /*******Sos_Ch_TimerNo to store the channel timer********/
 static uint8_t Sos_Ch_TimerNo = Zero;
 /************index of the array of structure***************/
 static uint8_t arr_counter=Zero;
 
 /********* Sos_FLag_Fun variable store no of timer ticks************/
 volatile uint16_t Sos_FLag_Fun = ONE;
 /********* Sos_FLag_Fun Array store no of timer ticks************/
 volatile uint16_t Sos_Flag_Arr[No_of_CBK]={Zero};
	 
 uint8_t x= Zero;	 
 /********************************************
 *			  Function Implementation        *
 *********************************************/
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
 uint8_t Sos_Init(const Sos_ConfigType * ConfigPtr){
	 uint8_t Err_status  = E_OK;
	
	 if (ConfigPtr == NULL)
	 {
		 Err_status = NULL_PTR;
	 } 
	 else
	 {
		 //create an object for timer structure
		 Timer_Cfg_S Timer_Cfg;
		 
		 //Declaring Sos_Ch_TimerNo to store timer channel
		 Sos_Ch_TimerNo  = ConfigPtr->Sos_Ch_Timer;
		 
		 //Definition of timer
		 Timer_Cfg.Timer_CH_NO = Sos_Ch_TimerNo;
		 Timer_Cfg.Timer_Mode  = Zero;
		 Timer_Cfg.Timer_Polling_Or_Interrupt = T2_INTERRUPT_NORMAL;   
		 Timer_Cfg.Timer_Prescaler = T2_PRESCALER_64;
		 Timer_Init(&Timer_Cfg);
	 }
	return Err_status;
 }
 
 
 /**
 * Func			: Sos_Start
 * Input		: Pointer to a structure of type contains the Sos_delay ,Sos_periodicity and call back function
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Start the Sos (one shot or period , delay time, call back function)
 */

uint8_t Sos_Start(Sos_Cfg_start * SosStartPtr){
	uint8_t Err_Status =E_OK;
	if (SosStartPtr==NULL)
	{
		Err_Status=NULL_PTR;
	} 
	else
	{
	/*****Fill  the elements of the array to start the  tasks ******/
	Sos_CBK_Arr_Struct[arr_counter] = *SosStartPtr;
	
	/*******Increment the arr_counter to move to the next elemnt of the array and reinitialized in Deinit function****/
	arr_counter++;
	
	//start timer to count delay
	Timer_Start(Sos_Ch_TimerNo,Zero);
	}
	return Err_Status;
}
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
 
 uint8_t Sos_Dispatch(){
		
		uint8_t Err_Status = E_OK;
		
		/**check if the flag of the SOS is raised to one that mean 1 ms dpassed **/
		if (Sos_FLag_Fun == ONE)
		{
			/**Increment the SOS counter**/
			Sos_CBK_Arr_Struct[Zero].Sos_Counter++;
			Sos_CBK_Arr_Struct[ONE].Sos_Counter++;
			Sos_CBK_Arr_Struct[TWO].Sos_Counter++;
			/**DeInitialize the ISR flag**/
			Sos_FLag_Fun=Zero;
		} 
		else
		{
			//do Nothing
		}
		
		if (arr_counter==Zero)
		{
			/**if there is no tasks in the buffer **/
			Err_Status = EMPTY_BUFFER;
		} 
		else
		{
			/**loop the created tasks to perform it**/
		for (uint8_t i=Zero; i<arr_counter ; i++)
		{
				/**check if the delay of the task is matched**/
			if (Sos_CBK_Arr_Struct[i].Sos_Counter==Sos_CBK_Arr_Struct[i].Sos_delay)
			{
					/**call the call back function of the task **/				
				Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr();
					/**Reinitialize the counter of the task**/
				Sos_CBK_Arr_Struct[i].Sos_Counter=Zero;
					/**check the priodicity of the task if priodic or one shot**/
				if (Sos_CBK_Arr_Struct[i].Sos_periodicity == Zero)
				{
					/** delete the task from the buffer **/
					Sos_Stop_Timer(Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr);
				} 
				else
				{
					//do Nothing
				}
			} 
			else
			{
				//do Nothing
			}
		}
			}
			
			/**return the error status of the function**/
	  return Err_Status;
 }

 
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
 
void Sos_Stop_Timer (void(*ptr)(void)){
	
	/***********initilaize arr_counter**********/
	 uint8_t S_Arr_counter; 
	 //arr_counter
	 for(S_Arr_counter = Zero;S_Arr_counter<arr_counter;S_Arr_counter++){
		 
		/**check if the passing pointer is matching one of the tasks in the array**/
		if(Sos_CBK_Arr_Struct[S_Arr_counter].Sos_Cbk_ptr==ptr){
			
			/**change the location of the task to the last position of the buffer**/
			Sos_CBK_Arr_Struct[S_Arr_counter] = Sos_CBK_Arr_Struct[arr_counter-ONE];
			
			Sos_CBK_Arr_Struct[arr_counter-1].Sos_Cbk_ptr = NULL;
			Sos_CBK_Arr_Struct[arr_counter-1].Sos_delay = Zero;
			Sos_CBK_Arr_Struct[arr_counter-1].Sos_periodicity =Zero;
			
			/*************Decrement the structures of the array*******************/
			arr_counter--;
			
		} 
	 }
 }
 
/**
 * Func			: Sos_Deinit
 * Input		: Pointer to a structure of type Sos_cfg_Init contains the Sos channel timer and resolution
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Deinitialize shall uninitialized the hardware timer module.
 */
 
 
void Sos_DeInit( ){
	 
	//Timer_Stop(Sos_Ch_TimerNo); 
	 x=Zero;
	for(uint8_t i=Zero;i<arr_counter-ONE;i++){
	
		Sos_CBK_Arr_Struct[i].Sos_delay = Zero;
		Sos_CBK_Arr_Struct[i].Sos_periodicity = Zero;
		Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr = NULL;
	}
 }

 
 

 