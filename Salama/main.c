/*
 * SEND.c
 *
 *
 * Created: 2020-03-01 9:49:13 PM
 * Author : Ahmed_Sakama
 */ 

#include "bcm.h"
#include "registers.h"
#include "interrupt.h"
#include "uart.h"
#include "uart_config.h"
//extern ptr_Function gptr_BCM_TxC_CBK;

void fun1(){
	
}
char arr[20] ;
int main(void)
{
	
	
	BCM_Cfg.Transmit_Cbk = fun1;
	
	BCM_Init(&BCM_Cfg);
	sei();
	
	

	BCM_SetupReceive(arr,20);

    while (1) 
    {
		BCM_RxDispatcher();
    }
}

void uart_receive_call()
{
	
}
