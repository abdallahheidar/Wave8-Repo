/*
 * SPI.c
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "SPI.h"
#include "SPI_cfg.h"


/*- GLOBAL STATIC VARIABLES --------------------------------*/

  void (*g_SPI_callBackPtr)(void) = NULL;
volatile uint8_t gu8spidata;


/*- INTERRUPT SERVICE ROUTINES -----------------------------*/





/*- APIs IMPLEMENTATION ------------------------------------*/

/*
 * Description : A Function to Initialize the SPI Driver.
 */
void SPI_init(const SPI_ConfigType* ConfigPtr)
{
	/* In case the MCU will be configured as a slave */
	if(ConfigPtr->MasterSlaveSelect == SPI_SLAVE)
	{
		/* select the slave mode and set the pins accordingly */
      DIO_Cfg_s instance={SPI_GPIO,SS,INPUT};
     DIO_init(&instance);
      instance.pins=MOSI;
      DIO_init(&instance);
      instance.pins=SCK;
      DIO_init(&instance);
      instance.pins=MISO;
      instance.dir=OUTPUT;
      DIO_init(&instance);
		Clear_BIT(SPCR, MSTR);
	}
	/* In case the MCU will be configured as a master */
	else if(ConfigPtr->MasterSlaveSelect == SPI_MASTER)
	{
		/* select the master mode and set the pins accordingly */
       DIO_Cfg_s instance={SPI_GPIO,SS,OUTPUT};
       DIO_init(&instance);
       instance.pins=MOSI;
       DIO_init(&instance);
       instance.pins=SCK;
       DIO_init(&instance);
       instance.pins=MISO;
       instance.dir=INPUT;
         DIO_init(&instance);
         DIO_Write(SPI_GPIO,SS,LOW);
		 Set_BIT(SPCR, MSTR);
	}
	/* Selecting the interrupt mode (enabled of disabled) */
	SPCR = (SPCR & 0x7F) | ConfigPtr->Mode;
	/* Selecting the clock rate */
	SPCR = (SPCR & 0xFC) | ((ConfigPtr->ClockRateSelect) & 0x03);
	SPSR = (SPSR & 0xFE) | ((ConfigPtr->ClockRateSelect) >> 2);
   SREG=0X80;
   /* Enable the SPI module */
   Set_BIT(SPCR, SPE);
}

/*
 * Description : A Function to set the call back function.
 */
void SPI_setCallBack(void(*a_ptr)(void))
{
	g_SPI_callBackPtr = a_ptr;
}




void SPI_sendByte(uint8_t data)
{
   
   SPDR=data;
  
   
}

 uint8_t SPI_receivebyte(void)
{
 return SPDR;   
   
}

/*
ISR(SPI_STC_vect)
{
g_SPI_callBackPtr();
}*/
ISR(SPI_STC_vect)
{    
	g_SPI_callBackPtr();
}