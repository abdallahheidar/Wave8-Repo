/*
 * uart_config.c
 *
 * Created: 02-Mar-20 11:03:37 AM
 *  Author: ahmed
 */

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
#include "uart.h"


/*create init struct*/
init_uart st_uart_init = {
	PARITY_DISABLE ,
	 DATA_8_BITS ,
	  URSEL_UCSRC ,
	   ONE_STOP ,
	    POLARITY_0 ,
		 ASYNCH ,
		  TX_ENABLE ,
		   BAUD_9600 ,
		   UART_MODE,
		    TX_IRQ_EN,
			 NULL,
			 NULL
			  };

