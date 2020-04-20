

#ifndef SPRINTS_ZAYED_AVR_STATICDESIGN_SRC_STD_TYPES_H_
#define SPRINTS_ZAYED_AVR_STATICDESIGN_SRC_STD_TYPES_H_

/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

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
typedef float float32;

typedef void (*gptrfun_User_cbk_t)(void);

/************************************************************************/
/*			 			 defining error status             		        */
/************************************************************************/
#define ERROR_STATUS	 		uint8_t
#define E_OK					0
#define E_NOK					1

#define ERROR_CODE				sint8_t

/************************************************************************/
/*			  			 defining bool values                         	*/
/************************************************************************/
typedef uint8_t bool;
#define FALSE 					0
#define TRUE 					1


/************************************************************************/
/*			    		 LOW/HIGH defines                 	            */
/************************************************************************/
#define LOW  					0
#define HIGH 					0xFF
/************************************************************************/
/*			    		 LOW/HIGH defines                 	            */
/************************************************************************/
#define OUTPUT					0xFF
#define INPUT					0x00

#endif /* SPRINTS_ZAYED_AVR_STATICDESIGN_SRC_STD_TYPES_H_ */
