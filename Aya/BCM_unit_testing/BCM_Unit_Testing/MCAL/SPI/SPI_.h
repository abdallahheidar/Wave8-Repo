/*
 * SPI_.h
 *
 * Created: 10/02/2020 14:18:15
 *  Author: ahmed_pc
 */ 


#ifndef SPI__H_
#define SPI__H_

#include "gpio.h"
#include "SPI_Config.h"
#include "../DIO/registers.h "
#include "../../SL/Utilis/interrupts.h"
#include "../../SL/Utilis/std_types.h"
#include "../../SL/Utilis/module_retval.h"



/************************************************************************/
/*                   typedefs for Timer                        */
/************************************************************************/

typedef void (*SPI_call_back) (void);



typedef enum Interrupt_State{
	Interrupt_Disable=0x00,Interrupt_Enable =0x80
}Interrupt_State;

typedef enum SPI_En_State{
	SPI_Disable=0x00,SPI_Enable =0x40
}SPI_En_State;

typedef enum Data_Order{
	MSB=0x00,LSB =0x20
}Data_Order;

typedef enum SPI_Mode{
	Slave=0x00,Master =0x10
}SPI_Mode;

typedef enum Clock_Polarity{
	Leading_Edge_Rising =0x00,Leading_Edge_Faling =0x08  
}Clock_Polarity;


typedef enum Clock_Phase{
	Leading_Edge_Sample=0x00,Leading_Edge_Setup =0x04
}Clock_Phase;

typedef enum SPI_Clock_Rate{
	Frequency_4 =0x00,Frequency_16 =0x01,Frequency_64 =0x02,Frequency_128 =0x03
}SPI_Clock_Rate;


ERROR_STATUS SPI_Init_(Interrupt_State interrupt_state,SPI_En_State SPI_state , Data_Order data_order ,SPI_Mode SPI_mode ,Clock_Polarity clock_Polarity ,Clock_Phase clock_phase , SPI_Clock_Rate clock_rate);

ERROR_STATUS SPI_Send_(char data);

ERROR_STATUS SPI_Send_Unblock(char data);

char SPI_Recive(void);

ERROR_STATUS SPI_Recive_Unblock(char* data);

void SPI_SET_CallBack(SPI_call_back SPI_Ptr_CallBack);


#endif /* SPI__H_ */