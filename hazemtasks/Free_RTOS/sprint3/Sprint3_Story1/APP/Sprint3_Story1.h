/*
 ============================================================================
 Name        : Sprint3_Story1.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef APP_SPRINT3_STORY1_H_
#define APP_SPRINT3_STORY1_H_

/*********************************includes**********************************/
#include "../Service/FreeRTOS.h"
#include "../Service/task.h"
#include "../Service/event_groups.h"
#include "../HAL/LCD.h"
#include "../HAL/pushButton.h"
#include "../HAL/Keypad.h"
#include "../HAL/UART.h"
/***************************************************************************/


/*********************************definitions*******************************/

/***************************************************************************/


/******************************global variables*****************************/

/***************************************************************************/


/***********************************APIs************************************/
void Sprint3_story1_Init(void);
void Sprint3_Story1_Task_A(void);
void Sprint3_Story1_Task_B(void);
void Sprint3_Story1_Task_C(void);
void Sprint3_Story1_Task_D(void);
/***************************************************************************/

#endif /* APP_SPRINT3_STORY1_H_ */
