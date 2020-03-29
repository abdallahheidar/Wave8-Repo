/*

 * SPI.c
 *
 * Created: 2/8/2020 10:15:20 PM
 * Author : EbrahimOseif
 */
#include "SPI.h"
#include "../../../Infrastructure/registers.h"
#include "gpio.h"
extern volatile uint8_t u8_DATA;
extern volatile uint8_t u8_interrupt_spi;
/*
volatile uint8_t data_sent;
extern volatile uint8_t gU8_Data_Recieved;
*/
extern ST_SPI_Configuration SPI_Config ;
void SPI_Init()
{

	 ST_SPI_Configuration *gConfig = & SPI_Config;

	/********************Enable SPI Interrupt ******************/

	//SPCR = SPCR | (SPI_INT_ENABLE<<SPIE);
	SPCR |= (gConfig->MASTER_SLAVE_MODE) | (gConfig->DATA_ORDER)
			  | (gConfig->OPERATING_LEVEL) | (gConfig->PRESCALAR)
			 | (gConfig->SAMPLING_EDGE) | (gConfig-> INT_ENABLE) ;

	SPSR |= (gConfig->DOUBLE_SPEED);
			 gpioPinDirection(GPIOB, BIT4 | BIT5 | BIT7, OUTPUT);
			 gpioPinDirection(GPIOB, BIT6, INPUT);


		SPCR |=  (gConfig->ENABLE);



}
void SPI_Transciever_INT(void)
{
	u8_DATA=SPDR;
//SPDR=u8_DATA;
//if(u8_interrupt_spi==0)
	Uart_tryansmitfirstbyte(u8_DATA);
	u8_interrupt_spi=1;
}
void  SPI_Send(uint8_t u8_data)
{
     /* Start transmission */
     SPDR = u8_data;
    if (!(READBIT(SPCR,SPIE)))
    {
	 	/* Wait for transmission complete */
     while(!(SPSR & (1<<SPIF)));
		}
}


uint8_t spi_INT_CALLED(void){
	return SPDR;
}

uint8_t  SPI_Receive(void)
{
	if (!(READBIT(SPCR,SPIE)))
	{
		/* Wait for transmission complete */
		while(!(SPSR & (1<<SPIF)));
		//return SPDR ; // Received data
	}
	return SPDR;
}


 uint8_t SPI_Checks_for_collision(void)
{
	 return READBIT(SPSR, WCOL);
}

void SPI_De_Init(void)
{
SPCR=0;
}
