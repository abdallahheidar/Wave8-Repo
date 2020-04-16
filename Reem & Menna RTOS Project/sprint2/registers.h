/*
 * registers.h
 *
 * Created: 2/15/2020 11:07:24 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "std_types.h"




/************************************************************************/
/*		                     PORTS REGISTERS		                        */
/************************************************************************/
#define PORTA_DATA      *((reg_type8_t)0x3B)
#define PORTA_DIR       *((reg_type8_t)0x3A)
#define PORTA_PIN	      *((reg_type8_t)0x39)

#define PORTB_DATA 	    *((reg_type8_t)0x38)
#define PORTB_DIR  	    *((reg_type8_t)0x37)
#define PORTB_PIN	       *((reg_type8_t)0x36)

#define PORTC_DATA 	    *((reg_type8_t)0x35)
#define PORTC_DIR  	    *((reg_type8_t)0x34)
#define PORTC_PIN	       *((reg_type8_t)0x33)


#define PORTD_DATA 	    *((reg_type8_t)0x32)
#define PORTD_DIR  	    *((reg_type8_t)0x31)
#define PORTD_PIN	       *((reg_type8_t)0x30)




#endif /* REGISTERS_H_ */