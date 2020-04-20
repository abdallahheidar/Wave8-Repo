/*
 * BCM_Send.h
 *
 * Created: 04/03/2020 04:39:01 م
 *  Author: mo
 */


#ifndef BCM_SEND_H_
#define BCM_SEND_H_
#include "BCM_Config.h"

ERROR_STATUS BCM_Init (const BCM_ConfigType * ConfigPtr );

ERROR_STATUS BCM_DeInit (const BCM_ConfigType * ConfigPtr);

ERROR_STATUS BCM_TxDispatcher(void);

ERROR_STATUS BCM_Send(uint8_t u8_channel_Protcol,uint8_t u8_BCM_ID,uint8_t u8_data_Lenght,uint8_t Num_of_Frames);

#endif /* BCM_SEND_H_ */
