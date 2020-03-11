/*
 * SPI_cfg.h
 *
 *  Created on: Feb 10, 2020
 *      Author: Youssef Harby
 */

#ifndef SPI_CFG_H_
#define SPI_CFG_H_


/*
 * User Configuration Macros
 */

#define SPI_GPIO	PORTB_DIR

#define SS 			0x10
#define MOSI 		0x20
#define MISO 		0x40
#define SCK 		0x80

#define SPR0		0
#define SPR1		1
#define CPHA		2
#define CPOL		3
#define MSTR		4
#define DORD		5
#define SPE			6
#define SPIE		7

#define SPI2X		0
#define WCOL		6
#define SPIF		7


#endif /* SPI_CFG_H_ */
