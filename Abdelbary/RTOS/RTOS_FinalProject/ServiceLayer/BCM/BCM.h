


#ifndef BCM_H_
#define BCM_H_


/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#include "../../ServiceLayer/std_types.h"
#include "../../COMMON/Errors.h"

/*************************************************************/
/*				        	 MACROS	                		 */
/*************************************************************/


/*************************************************************/
/*                     NEW TYPES DEFINITIONS                 */
/*************************************************************/


/*************************************************************/
/*						API PROTOTYPES		                 */
/*************************************************************/
/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: initialize the BCM module
 */
ERROR_CODE	BCM_Init(void);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: de-initialize the BCM module
 */
ERROR_CODE BCM_DeInit(void);

/**
 * Input:
 *			pu8_data: pointer to the user's array of bytes to be send
 *			u16_size: size of the user's array of bytes to be send
 *			pfun_UserCbk: function pointer to be executed when sending is complete
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: start the BCM module by initiating the send state
 */
ERROR_CODE BCM_Send(uint8_t* pu8_data, uint16_t u16_size, gptrfun_User_cbk_t pfun_UserCbk);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	----	
 * Description: start the BCM module by initiating the send state
 */
ERROR_CODE BCM_TxDispatcher(void);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: BCM manager for the RX functionality
 */
ERROR_CODE BCM_RxDispatcher(void);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	Error Code		
 * Description: function to get the receive buffer from the user
 */
ERROR_CODE BCM_SetupReceiveBuffer(uint8_t* pu8_BCM_RxBuffer, uint16_t u16_BCM_RxBufferSize, gptrfun_User_cbk_t pfun_UserCbk);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	---	
 * Description: function to unlock the RX locker by the user
 */
void BCM_RxUnlock(void);

/**
 * Input:	----
 * Output:	----
 * In/Out:	----			
 * Return:	---	
 * Description: function to return if the buffer locked
 */
uint8_t BCM_IsBufferLocked(void);

#endif /* BCM_H_ */