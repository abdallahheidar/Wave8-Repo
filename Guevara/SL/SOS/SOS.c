/*
 * TMU.c
 *
 * Created: 24/02/2020 01:22:29 م
 *  Author: mo
 */ 
#include "../../MCAL/PushButtons/pushButton.h"
#include "SOS.h"
#include "../../Infrastructure/Intturpts Manger/Interrupts.h"
#include "../../ECUAL/LCD/LCD.h"
#define Buffer_Size 4
uint8_t u8_Init_finished=0;

uint8_t u8_Is_Intialized=0;
start_status start[Buffer_Size];
uint8_t u8_FUN_index=0;
Buffer_Request Buffer_Array[Buffer_Size];
volatile uint8_t u8Excution_to_be_done=0;
//static uint8_t u8_is_Started=0;
uint8_t Start_status[Buffer_Size];
static uint8_t stu8_increment=0;

ERROR_STATUS SOS_Init (const TMU_ConfigType * ConfigPtr )
{uint8_t u8_channel_ID=ConfigPtr->u8_Timer_channel;
uint8_t ret=E_OK;
/*************************************************************************/
/*			Intializ the required timer identified by the user			 */
/************************************************************************/
u8_Is_Intialized++;

if(ConfigPtr==NULL){ret=TMU_MODULE+NULL_PTR;}
switch(u8_channel_ID)
{
	case TIMER_CH0:
			G_interrupt_Enable();
			Timer_Init(&Timer_Configuration0);
				break;
	case TIMER_CH2:
		G_interrupt_Enable();
		Timer_Init(&Timer_Configuration2);
			break;
	default:
			ret+=E_NOK;
			break;
}	

/*************************************************************************/
/*Intializ the required timer identified by the user using required prescaler  */
/************************************************************************/

switch(ConfigPtr->u8_resolution)
{
	case TIMER_RESOLUTION_1_MS:
	{
		switch(u8_channel_ID)
		{
			case TIMER_CH0 :
		Timer_Start(TIMER_CH0,250);
					//TCNT0=5;
					break;
			case TIMER_CH2 :
				Timer_Start(TIMER_CH2,14);
					break;
			default:
				ret+=E_NOK;
					break;
		}					
	break;
	}	
	
	
	
	default:
	ret+=E_NOK;
	break;

}



/****************************************************************************/
/*      Deal with Errors  to be returned									*/
/***************************************************************************/
return ret;
}



ERROR_STATUS TMU_DeInit( void )
{
	uint8_t ret=E_OK;
	/************************************************************************************************/
	/*1    	De_intialize the timer																	*/
	/*2		make sure this function is not called unless timer was intialized before by  TMU_INIT	*/
	/************************************************************************************************/
if (u8_Is_Intialized==1)
{/*Make the timer without a clk*/
	Timer_Init(&Timer_Deinit_Configuration0);

	u8_Is_Intialized=0;
	
}else if(u8_Is_Intialized>1){ret+=MULTIPLE_INIT;}
	else{
	ret=E_NOK;
	}

	
return ret;	
}

ERROR_STATUS SOS_Create_Task(ptr_to_Fun Function_Consumer,uint8_t  u8_Preodicity,uint8_t u8_function_index,uint16_t u16_Time_delay)
{uint8_t ret=E_OK;
	/*
	this enables interrupt and start the timer with the required configurations
	and provide the request to request buffer (ptr_to_func,delay) Dispatcher with the call back function needed(consumer)
	and make sure this function must not be excuted unless Init happened and De_init not happened
  	*/
	if(u8_Is_Intialized == 1)
	{
		
		
		(Buffer_Array[u8_function_index]).Fuction_consumer=Function_Consumer;
		(Buffer_Array[u8_function_index]).preodic=u8_Preodicity;
		(Buffer_Array[u8_function_index]).u16_time_delay=u16_Time_delay;
		(Buffer_Array[u8_function_index]).u8_flag_is_stopped=1;
		
		
	}
	else if(u8_Is_Intialized>1){ret+=MULTIPLE_INIT;}else{
		ret+=NOT_INIT;
	}

	return ret;
}

ERROR_STATUS SOS_Run(void)
{	uint8_t ret=E_OK;
	/*uint8_t status_flag=0;
	uint8_t preodic_status_flag=0;
	uint16_t u16_Time_needed=0;
	ptr_to_Fun Excuted;
	*//***********************************************************************/
	/*					LOOP upon Buffer Request						*/
	/*********************************************************************/
if (u8Excution_to_be_done==1)
{	u8Excution_to_be_done=0;

		for (u8_FUN_index=0;u8_FUN_index<Buffer_Size;u8_FUN_index++)
			{/*
	Excuted=((Buffer_Array[u8_FUN_index]).Fuction_consumer);
	u16_Time_needed =(Buffer_Array[u8_FUN_index]).u16_time_delay;
	status_flag =(Buffer_Array[u8_FUN_index]).u8_flag_is_stopped;
	preodic_status_flag=(Buffer_Array[u8_FUN_index]).preodic;
*/
/****************************************************************/
/* check if the event is stopped ... do nothing*/
		if((Buffer_Array[u8_FUN_index]).u8_flag_is_stopped==0){ret=E_OK;}
		else{
	/***************************************************************/
	/*if the timer started .. and condition met excute the consumer*/
	/***************************************************************/
		
	/********************************************/
	/*Count up when flag is set**/
	((Buffer_Array[u8_FUN_index]).u16_Counter)++;
	/*make the flag down*/
							
			
/*	u16Excution_to_be_done=100;  ISR*/
	if(((Buffer_Array[u8_FUN_index]).u16_time_delay) == ((Buffer_Array[u8_FUN_index]).u16_Counter) )
	{
		((Buffer_Array[u8_FUN_index]).Fuction_consumer)();
	/******************************************/
	/*Make it zero so that it will work the next time at the required time (to stop it of ovf)*/
		(Buffer_Array[u8_FUN_index]).u16_Counter=0;
		
	}		
		
	/*********************************************************/
	/* if not preodic increment the index after excuteing	*/
	/*********************************************************/

	if((Buffer_Array[u8_FUN_index]).preodic==0)
	{
		/*to make it see the next event in the next time
		Also Status_flag =1 so that this function will be stopped
		*/
		(Buffer_Array[u8_FUN_index]).u8_flag_is_stopped=0;	
	}
			

		}		
	}
}	
return ret;
}


void TMU_Stop_Timer(uint8_t u8_function_index)
{

	/***************************************************/
	/*     Set the stop flag							*/
	/***************************************************/
	(Buffer_Array[u8_function_index]).u8_flag_is_stopped=0;
}

void Task1(void)
{	static uint8_t counter=0;
	static uint8_t u8count=0;
	static uint8_t flag_Null=0;
	static uint8_t twoDarr[][32]={"1.Is 5 + 2 = 7 ?  ","2.IS Earth Flat ?  ",
"3.Do You like Chocolate? "
,"4.Do You like Embedded Systems ? ","5.Do You Know My name ? ","6.NO ","7.YES ","8.False Answer!! ","9.Correct Answer!! ","10.Game Over"};
 static uint8_t X_value=0;
 static uint8_t Y_value=0;
	
	if (u8_Init_finished==1)
	{
	if (stu8_increment<10)
	{
		if (u8count < 16)
		{
			X_value=u8count;
			Y_value=0;
		}
		
		else if(u8count >= 16 || twoDarr[stu8_increment][u8count])
		{
			Y_value=1;
			X_value=u8count-16;
		}
		
		if(twoDarr[stu8_increment][u8count])
		{
			LCD_goto_xy(X_value,Y_value);
			LCD_send_char(twoDarr[stu8_increment][u8count++]);
			
		}
		else if((twoDarr[stu8_increment][u8count]== '\0') && u8count < 32)
		{while(u8count <= 32){
			twoDarr[stu8_increment][u8count]=' ';
			u8count++;
		}
	}else{u8count=0;}
	}else{stu8_increment=0;}			
u8_Init_finished=0;
		
	}

}
void Task2(void){	
	
static uint8_t u8_Counter=0;
static uint8_t u8_Counter1=0;
	if (pushButtonGetStatus(BTN_0))
	{	
		u8_Counter++;
	}
	if (u8_Counter > 20)
	{
	stu8_increment++;
	u8_Counter=0;
	}
	
	if (pushButtonGetStatus(BTN_1))
	{
		u8_Counter1++;
		//stu8_increment++;
	}
	if (u8_Counter1 > 20)
	{
		stu8_increment--;
		u8_Counter1=0;
	}
	

	
}
void Tmu_excute(void){
	
		
}


void timer_interrupt(void)
{
	u8Excution_to_be_done =1;	
}