/*
 ============================================================================
 Name        : main.c
 Author      : Muhammed Gamal
 Description :
 ============================================================================
 */

/*********************************includes**********************************/
#include "Sprint2_Story1.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define STACK_SIZE1                   		50
#define STACK_SIZE2                   		100
#define STACK_SIZE3                   		150
#define STACK_SIZE4                   		200
#define STACK_SIZE5                   		250
#define NONE_PASSED_PARAMETER               ( void * ) 1
#define INIT_TASK_PRIORITY         	        1
#define STORY1_TASK_PRIORITY                2
/*******Sprint 2 *********/
#define TASK_A_PRIORITY                     3   /* 3 for story-1 ... 2 for story-2 */
#define TASK_B_PRIORITY                     2   /* 2 for story-1 ... 3 for story-2 */
#define TASK_C_PRIORITY                     1   /* 1 for story-1 ... 4 for story-2 */
/***************************************************************************/


/******************************global variables*****************************/
TaskHandle_t InitTask_Handle = NULL;
TaskHandle_t UserStoryOne_Handle = NULL;
/*******Sprint 2 *********/
TaskHandle_t Sprint2_story1_Init_Handle = NULL;
TaskHandle_t Task_A_Handle = NULL;
TaskHandle_t Task_B_Handle = NULL;
TaskHandle_t Task_C_Handle = NULL;
TaskHandle_t Task_D_Handle = NULL;
/***************************************************************************/


/*******************************static APIs*********************************/
void Init_task(void);
void tasks_creation(void);
/***************************************************************************/



/************************************************************************************
* Function Name:main
* Parameters (in):
* Parameters (inout): None
* Parameters (out): None
* Return value: integer value
* Description:this is the main task of the system
************************************************************************************/
int main(void)
{
	Init_task();        /* initialize all needed modules */
	tasks_creation();   /* create all tasks in the system */

	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
}


/************************************************************************************
* Function Name: tasks_creation
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:this task responsible for calling all the initialization functions needed
* in the system.
************************************************************************************/
void Init_task(void)
{
	BaseType_t xReturned;

	/* Create the task and storing the handle */
	xReturned = xTaskCreate(
			       Sprint2_story1_Init,    		 /* Function that implements the task. */
					"Init",                 	 /* Text name for the task. */
					STACK_SIZE1,     	 	     /* Stack size in words, not bytes. */
		         	NONE_PASSED_PARAMETER,       /* Parameter passed into the task. */
					INIT_TASK_PRIORITY,  		 /* Priority at which the task is created. */
				    &InitTask_Handle );          /* Used to pass out the created task's handle. */
}


/************************************************************************************
* Function Name: tasks_creation
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:this task responsible for creating all tasks needed in the system
************************************************************************************/
void tasks_creation(void)
{
	BaseType_t xReturned;

	/* Create the task and storing the handle */
	xReturned = xTaskCreate(
		        	Sprint2_Story1_Task_A,    	 /* Function that implements the task. */
					"Task_A",                    /* Text name for the task. */
					STACK_SIZE1,     			 /* Stack size in words, not bytes. */
					NONE_PASSED_PARAMETER,    	 /* Parameter passed into the task. */
					TASK_A_PRIORITY,  	     	 /* Priority at which the task is created. */
					&Task_A_Handle );            /* Used to pass out the created task's handle. */

	xReturned = xTaskCreate(
		           	Sprint2_Story1_Task_B,    	 /* Function that implements the task. */
					"Task_B",                    /* Text name for the task. */
					STACK_SIZE1,     			 /* Stack size in words, not bytes. */
					NONE_PASSED_PARAMETER,    	 /* Parameter passed into the task. */
					TASK_B_PRIORITY,  	    	 /* Priority at which the task is created. */
					&Task_B_Handle );            /* Used to pass out the created task's handle. */

	xReturned = xTaskCreate(
			       Sprint2_Story1_Task_C,    	 /* Function that implements the task. */
				    "Task_C",                    /* Text name for the task. */
					STACK_SIZE1,     			 /* Stack size in words, not bytes. */
					NONE_PASSED_PARAMETER,    	 /* Parameter passed into the task. */
					TASK_C_PRIORITY,  	    	 /* Priority at which the task is created. */
					&Task_C_Handle );            /* Used to pass out the created task's handle. */
}

