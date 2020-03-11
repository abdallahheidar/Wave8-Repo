/*
 * SPI.h
 *
 * Created: 10-Feb-20 6:04:17 PM
 *  Author: ahmed
 */ 


#ifndef SPI_H_
#define SPI_H_

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
#include "std_types.h"
#include "SPI_CONFIG.h"
#include "registers.h"

/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/
#define UNLOCKED	(0)
#define LOCKED		(1)

/************************************************************************/
/*							Declarations                                */
/************************************************************************/
ERROR_STATUS spi_init(config_spi *sp_inits);
ERROR_STATUS spi_transmitter(uint8_t u8_spi_sender);
uint8_t spi_receiver(void);
#endif /* SPI_H_ */