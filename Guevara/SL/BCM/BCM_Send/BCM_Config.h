/*
 * BCM_Config.h
 *
 * Created: 04/03/2020 04:38:32 م
 *  Author: mo
 */


#ifndef BCM_CONFIG_H_
#define BCM_CONFIG_H_
#include "../../../MCAL/SPI/SPI_Master/SPI.h"
#include "../../../MCAL/UART/UART_Recieve/uart.h"
#include "../../../Infrastructure/Intturpts Manger/Interrupts.h"
#include "../../../MCAL/Timer/Timer.h"
#include "../../../Infrastructure/Error.h"
/*u8_channel_Protcol*/
#define   UART  1
#define   SPI   2
#define   UARTANDSPI   3
#define   I2C   4

/*u8_BCM_ID*/
#define TASK1_ID  'A'
#define TASK2_ID  'B'
#define TASK3_ID  'C'
/* u8_data_Lenght*/
typedef struct ST_BCM_ConfigType
{
uint8_t u8_channel_Protcol;
uint8_t u8_BCM_ID;
uint16_t u16_data_Lenght;
uint8_t Num_of_Frames;
}BCM_ConfigType;

extern const BCM_ConfigType BCM_Configuration;
#endif /* BCM_CONFIG_H_ */
