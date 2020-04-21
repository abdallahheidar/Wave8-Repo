
#include "APP/User_Story2.h"

#define  STACK_SIZE   100
void vOtherFunction(void);
void vTaskCode( void * pvParameters );

int main(void)
{

	 vOtherFunction();
	/*start scheduler*/
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0;
}



/* Function that creates a task. */
void vOtherFunction( void )
{

TaskHandle_t xHandle = NULL;

    /* Create the task, storing the handle. */
    xTaskCreate(UserStoryOneInit,       /* Function that implements the task. */
                    "INIT",          /* Text name for the task. */
                    STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &xHandle );      /* Used to pass out the created task's handle. */

 xTaskCreate(
 UserStoryOne,       /* Function that implements the task. */
 "toggelled",          /* Text name for the task. */
 STACK_SIZE,      /* Stack size in words, not bytes. */
 ( void * ) 1,    /* Parameter passed into the task. */
 tskIDLE_PRIORITY,/* Priority at which the task is created. */
 &xHandle );      /* Used to pass out the created task's handle. */
 
 
  xTaskCreate(
  keypadtask,       /* Function that implements the task. */
  "keypad",          /* Text name for the task. */
  STACK_SIZE,      /* Stack size in words, not bytes. */
  ( void * ) 1,    /* Parameter passed into the task. */
  tskIDLE_PRIORITY,/* Priority at which the task is created. */
  &xHandle );      /* Used to pass out the created task's handle. */

}

