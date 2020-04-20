/*
 * uart.h
 *
 * Created: 10/02/2020 08:02:37 م
 *  Author: mo
 */


#ifndef UART_H_
#define UART_H_
#include "uartconfig.h"

#define Buffer_Size 10
#define SPIE  7
#define TXCIE 6
#define RXCIE 7
extern uint8_t BufferRequested[];
extern volatile uint8_t u8_Notification_TX;
extern volatile uint8_t gU8_Data_Recieved;
extern volatile uint8_t gU8_Data_transmited;

extern void Uart_Init(En_BAUD_Rate Baud_rate,En_Stop_config Stop_bits_num,
EN_Parity parity_Bit,EN_Data_Size data_num_bits,EN_UartMode uart_mode);
extern void UartTransmitInterrupt(void);
extern void UartRecieveInterrupt(void);
extern void UartTransmitPooling(uint8_t Data);
extern uint8_t UartRecievePooling(void);
extern void Enable_communication_interrupt(void);
extern void UartTransmitdataInt(uint8_t data_to_transmit);
void Uart_tryansmitfirstbyte(uint8_t data);
void Uart_De_Init(void);
#endif /* UART_H_ */
