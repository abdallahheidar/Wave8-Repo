/*
 * uart_config.h
 *
 * Created: 10-Feb-20 10:46:38 PM
 *  Author: ahmed
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_



typedef volatile void (*ptr_Function) (void);

/*structure of UART*/
typedef struct init_uart{
	
	uint8_t parity;
	uint8_t frame_size;
	uint8_t ur_sel;
	uint8_t stop;
	uint8_t polarity;
	uint8_t synch;
	uint8_t tx_rx_en;
	uint16_t baud;
	uint8_t uart_mode;
	uint8_t tx_rx_irq;
	ptr_Function UART_TxC_Cbk_Function;
	ptr_Function UART_RxC_Cbk_Function;
	}init_uart;

/*extern uart struct to be used anywhere at upper layers*/
extern init_uart st_uart_init;

#endif /* UART_CONFIG_H_ */