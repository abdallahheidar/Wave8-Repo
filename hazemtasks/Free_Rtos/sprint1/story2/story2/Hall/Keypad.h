/*
 ============================================================================
 Name        : Keypad.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "../Common/std_types.h"
#include "../Common/common_macros.h"
#include "../MCAL/DIO.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC_DATA
#define KEYPAD_PORT_IN  PORTC_PIN
#define KEYPAD_PORT_DIR PORTC_DIR

#define NO_KEY_PRESSED             99
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8_t KeyPad_getPressedKey(void);


#endif /* HAL_KEYPAD_H_ */
