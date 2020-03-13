
 
 /*********************************************
 *				Includes  					 *
 ********************************************/
 #include "std_types.h"
 #include "Sos.h"
 
 

 /*********************************************
 *	   Function Implementation  	       	  *
 ********************************************/

void func1(void)
{
	
	PORTA_DATA^=0x01;
}

void func2(void)
{
	PORTA_DATA^=0x04;
}

void func3(void)
{
	PORTA_DATA^=0x02;
}

/********************************************
 *				CBK_Functions                *
 *********************************************/
 
Sos_Cfg_start Sos_Cfg_start_Fun1 = {250,1,0,func1};
 
Sos_Cfg_start Sos_Cfg_start_Fun2 = {250,1,0,func2};
 
Sos_Cfg_start Sos_Cfg_start_Fun3 = {250,1,0,func3};
 
/******static global Array of Call Back Structure functions*******/
 static Sos_Cfg_start Sos_CBK_Arr_Struct[No_of_CBK];
 
 /*{Sos_Cfg_start_Fun1,Sos_Cfg_start_Fun2,Sos_Cfg_start_Fun3};*/
 
 /*******Sos_Ch_TimerNo to store the channel timer********/
 static uint8_t Sos_Ch_TimerNo = 0;
 /************index of the array of structure***************/
 static uint8_t arr_counter=0;
 
 /********* Sos_FLag_Fun variable store no of timer ticks************/
 volatile uint16_t Sos_FLag_Fun = 1;
 /********* Sos_FLag_Fun Array store no of timer ticks************/
 volatile uint16_t Sos_Flag_Arr[No_of_CBK]={0};
	 
 uint8_t x= 0;	 
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
		 Timer_Cfg.Timer_Mode  = 0;
		 Timer_Cfg.Timer_Polling_Or_Interrupt = 0x40;   //T2_INTERRUPT_NORMAL=0x40;
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
	Timer_Start(Sos_Ch_TimerNo,0);
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
		
		if (Sos_FLag_Fun == 1)
		{
			
			Sos_CBK_Arr_Struct[0].Sos_Counter++;
			Sos_CBK_Arr_Struct[1].Sos_Counter++;
			Sos_CBK_Arr_Struct[2].Sos_Counter++;
			Sos_FLag_Fun=0;
		} 
		else
		{
			//do Nothing
		}
		
		if (arr_counter==0)
		{
			
			Err_Status = EMPTY_BUFFER;
		} 
		else
		{
		for (uint8_t i=0; i<arr_counter ; i++)
		{
			
			if (Sos_CBK_Arr_Struct[i].Sos_Counter==Sos_CBK_Arr_Struct[i].Sos_delay)
			{
								
				Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr();
				Sos_CBK_Arr_Struct[i].Sos_Counter=0;
				
				if (Sos_CBK_Arr_Struct[i].Sos_periodicity == 0)
				{
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
	  return Err_Status;
 }
 /*
uint8_t Sos_Dispatch(){
	// static uint8_t arr[No_of_CBK]={0};
	uint8_t Err_Status = E_OK;	 
	for (uint8_t i=0; i<arr_counter ; i++)
     {
         //Passing addresses of array elements
		  //if(Sos_FLag_Fun ==Sos_FLag_Fun % Sos_CBK_Arr_Struct[i].Sos_delay){
			  if(!(Sos_FLag_Fun % Sos_CBK_Arr_Struct[i].Sos_delay)){
			  Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr();
			  x++;
			  //PORTA_DATA=0x01; 
		  } 
		  if (x == Sos_CBK_Arr_Struct[i].Sos_periodicity)
		  {
			  Sos_Stop_Timer(Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr);	 
		  }
		  
     }
	 
	 
	 if (arr_counter== 0)
	 {
		 
		 Sos_DeInit();
	 }
	 return Err_Status;
 }
 */
 
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
	 for(S_Arr_counter = 0;S_Arr_counter<arr_counter;S_Arr_counter++){
		
		if(Sos_CBK_Arr_Struct[S_Arr_counter].Sos_Cbk_ptr==ptr){
			
			Sos_CBK_Arr_Struct[S_Arr_counter] = Sos_CBK_Arr_Struct[arr_counter-1];
			
			Sos_CBK_Arr_Struct[arr_counter-1].Sos_Cbk_ptr = NULL;
			Sos_CBK_Arr_Struct[arr_counter-1].Sos_delay = 0;
			Sos_CBK_Arr_Struct[arr_counter-1].Sos_periodicity = 0;
			
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
	 x=0;
	for(uint8_t i=0;i<arr_counter-1;i++){
	
		Sos_CBK_Arr_Struct[i].Sos_delay = 0;
		Sos_CBK_Arr_Struct[i].Sos_periodicity = 0;
		Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr = NULL;
	}
 }

 
 

 