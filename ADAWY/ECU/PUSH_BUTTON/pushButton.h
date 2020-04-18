/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_
#include "pushButtonConfig.h"
#include "../../MCAL/DIO/DIO.h"


#define BUTTONDELAYA 5
/*button Id*/
#define 	BTN_0  0
#define 	BTN_1  BTN_0 + 1
#define 	BTN_2  BTN_1 + 1
#define 	BTN_3  BTN_2 + 1

 /* En_buttonStatus */
#define 	Released    5
#define 	Prepressed  Released + 1
#define 	Pressed     Prepressed + 1
#define 	Prereleased Pressed + 1


/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
ERROR_STATUS pushButtonInit(uint8_t en_butotn_id);
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
ERROR_STATUS pushButtonUpdate(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
ERROR_STATUS pushButtonGetStatus(uint8_t en_butotn_id, uint8_t * ButtonStatus);

#endif /* PUSHBUTTON_H_ */