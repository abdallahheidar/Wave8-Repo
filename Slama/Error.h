/*
 * Error.h
 *
 * Created: 2020-02-25 10:57:28 PM
 *  Author: AHMED_SALAMA
 */ 


#ifndef ERROR_H_
#define ERROR_H_

#define	  BCM_ERROR_BASE			    	 (0)

#define   NO_ERRORS                          (0)

#define   ERROR_NOT_INITIALIZED              (-1)

#define   ERROR_ALREADY_INITIALIZED          (-2)

#define   ERROR_NULL_POINTER                 (-3)

#define   ERROR_EMPTY_BUFFER                 (-4)

#define   ERROR_FULL_BUFFER                  (-5)

#define ID_NOT_MATCHED						 (-6)

#define BUFFER_NOT_FIT					   	 (-7)

#define ERROR_LOCKED_BUFFER			     	 (-8)

#define ERROR_BCM_PROTOCOL_NOT_IMPLEMENTED   (-9)

#define ERROR_BCM_PROTOCOL_LOCKED			(-10)
#endif /* ERROR_H_ */