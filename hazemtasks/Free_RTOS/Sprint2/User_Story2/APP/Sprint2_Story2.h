/*
 ============================================================================
 Name        : Sprint2_Story2.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef APP_SPRINT2_STORY2_H_
#define APP_SPRINT2_STORY2_H_

/*********************************includes**********************************/
#include "../Service/FreeRTOS.h"
#include "../Service/task.h"
#include "../Service/event_groups.h"
#include "../HAL/LCD.h"
#include "../HAL/pushButton.h"
#include "../HAL/led.h"
/***************************************************************************/


/*********************************definitions*******************************/

/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/


/***********************************APIs************************************/
void Sprint2_story2_Init(void);
void Sprint2_Story2_Task_A(void);
void Sprint2_Story2_Task_B(void);
void Sprint2_Story2_Task_C(void);
void Sprint2_Story2_Task_D(void);
/***************************************************************************/

#endif /* APP_SPRINT2_STORY2_H_ */
