/*
 * SPI.h
 *
 * Created: 2/8/2020 10:15:20 PM
 * Author : EbrahimOseif
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_


#include "../../../Infrastructure/std_types.h"
#include "SPI_Config.h"


/*****************SPCR*************/
#define SPIE 	7
#define SPE 	6
#define DORD 	5
#define MSTR 	4
#define CPOL 	3
#define CPHA 	2
#define SPR1	1
#define SPR0	0
/*****************SPSR*************/
#define SPIF	7
#define WCOL	6
#define SPI2X	0

/*********************************************/
#define OK  1
#define ERR 0
extern volatile uint8_t data_sent;

 void SPI_Init();
 void SPI_Send(uint8_t u8_data);
 uint8_t  SPI_Receive(void);
 uint8_t  SPI_Checks_for_collision(void);
 void SPI_callBackFunc_Assign(void(*PtrToSPI_Isr)(void));
 uint8_t spi_INT_CALLED(void);
void SPI_Transciever_INT(void);
void SPI_De_Init(void);

#endif /* SPI_SPI_H_ */
