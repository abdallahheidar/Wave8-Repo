/*
 * BCM.h
 *
 * Created: 3/3/2020 1:45:44 AM
 *  Author: Ema
 */ 


#ifndef BCM_H_
#define BCM_H_

#include "BCM_cfg.h"
#include "..\Mcal\spi.h"
#include "..\Mcal\USART.h"

extern uint8_t bcm_Id;

typedef void (*BCM_SEND_CBKFUNCOMP)(void);
extern void BCM_init(Bcm_Cfg_ST *Bcm_cfg_ST);

extern void BCM_recieve(uint8_t *Buffer_ptr);
extern void BCM_RX_dispatcher(void);
extern void BCM_Send(BCM_SEND_CBKFUNCOMP CBKFUN,uint8_t* BUFFER,uint16_t size);
extern void BCM_TX_dispatcher(void);
extern 



#endif /* BCM_H_ */