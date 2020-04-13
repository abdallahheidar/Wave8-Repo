/*
 * std_types.h
 *
 *  *  Author: Ehab & Reem
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/************************************************************************/
/*			   			 INITIAL VALUES DIFINITION                           */
/************************************************************************/
#define INITIALLY_STARTING_WITH_ZERO						0
#define NULL_CHARACTER										 '\0'
#define NULL											((void *)0)

/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char sint8_t;
typedef signed int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;


typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;

typedef uint16_t ERROR_STATUS;


/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	 /*defines boolean false*/
#define TRUE 	1	 /*defines boolean true*/


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0		/*defines LOW value for a bit*/
#define HIGH 0xFF	/*defines HIGH value for a bit*/

/************************************************************************/
/*						Function Status Macros                          */
/************************************************************************/

#define E_OK	0
#define E_NOK	0

#define OUTPUT 0xFF
#define INPUT 0x00

/************************************************************************/
/*				 COMMAN MACROS                               */
/************************************************************************/

#define GET_BIT(Reg, BitNo)      ( (Reg>>BitNo) & 1 )
#define CLEAR_BIT(Reg, BitNo)    (  Reg &=~ (1<<BitNo) )
#define SET_BIT(Reg, BitNo)      (  Reg |=  (1<<BitNo)   )
#define TOOGLE_BIT(Reg, BitNo)   (  Reg ^=  (1<<BitNo)   )


#endif /* STD_TYPES_H_ */