/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */
#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "pushButtonConfig.h"
#include "..\MCAL\DIO.h"


#define BTN_0		0
#define BTN_1		1
#define BTN_2		2
#define BTN_3		3


#define Pressed		0
#define Released	1

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
extern ERROR_STATUS pushButtonInit(uint8_t u8_butotn_id);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
extern ERROR_STATUS pushButtonGetStatus(uint8_t u8_butotn_id , uint8_t* pu8_ButtonStatus);

#endif /* PUSHBUTTON_H_ */ 