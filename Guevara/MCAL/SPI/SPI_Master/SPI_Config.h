/*
 * SPI_Config.h
 *
 * Created: 2020-02-10 10:31:57 PM
 *  Author: EbrahimOseif
 */


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_
#include  "../../../Infrastructure/std_types.h"

/*SPI_MASTER_SLAVE_MODE*/
#define	SPI_MASTER  0x10
#define	SPI_SLAVE   0x00

/* SPI_PRESCALAR*/
#define	SPI_Fosc4	 0x00
#define	SPI_Fosc16   0x01
#define	SPI_Fosc64   0x02
#define	SPI_Fosc128  0x03

/*  SPI_ENABLE*/
#define	SPI_ENABLE_ON	 0x40
#define	SPI_ENABLE_OFF   0x00

/* SPI_DOUBLE_SPEED*/
#define	SPI_DOUBLE_SPEED_MODE_OFF  0x00
#define	SPI_DOUBLE_SPEED_MODE_ON   0x01


/*SPI_OPERATING_LEVEL*/
#define	SPI_IDLE_LOW   0x00
#define	SPI_IDLE_HIGH  0x08

/*SPI_SAMPLING_EDGE*/
#define	SPI_LEADING   0x00
#define	SPI_TRAILING  0x04


 /*SPI_INT_ENABLE*/
#define	SPI_INT_OFF  0x00
#define	SPI_INT_ON	 0x80
/* SPI_DATA_ORDER */
#define	SPI_LSB_FISRT  0x20
#define	SPI_MSB_FISRT  0x00


typedef struct ST_SPI_Configuration
{
	uint8_t MASTER_SLAVE_MODE;
	uint8_t  PRESCALAR;
	uint8_t  ENABLE;
	uint8_t  DOUBLE_SPEED;
	uint8_t  OPERATING_LEVEL;
	uint8_t   SAMPLING_EDGE;
	uint8_t    INT_ENABLE;
	uint8_t  DATA_ORDER ;
}ST_SPI_Configuration;




#endif /* SPI_CONFIG_H_ */
