/*
 * SPI_.c
 *
 * Created: 10/02/2020 14:17:39
 *  Author: ahmed_pc
 */ 

#include "SPI_.h"



/************************************************************************/
/*                GLOBAL STATIC VARIABLES                           */
/************************************************************************/

static volatile SPI_call_back gpfun_SPI_back = NULL ;


ERROR_STATUS SPI_Init_(Interrupt_State interrupt_state,SPI_En_State SPI_state , Data_Order data_order ,SPI_Mode SPI_mode ,Clock_Polarity clock_Polarity ,Clock_Phase clock_phase , SPI_Clock_Rate clock_rate)
{
	ERROR_STATUS u8_Ret_Error = E_OK;
	//SPI_Init_(Interrupt_Enable,SPI_Enable,LSB,Slave,Leading_Edge_Rising,Leading_Edge_Sample,Frequency_16);
	
	//SPCR =0b01010001;
	SPCR = SPCR|(interrupt_state | data_order | SPI_mode | clock_Polarity | clock_phase | clock_rate);	
	//Bit 7 SPIE: SPI Interrupt Enable 
	//Bit 6 SPE: SPI Enable
	//Bit 5  DORD: Data Order  1:LSB 0:MSB
	//Bit 4  MSTR: Master/Slave Select   1:Master 0:slave
	//Bit 3  CPOL: Clock Polarity
	//Bit 2  CPHA: Clock Phase
	//Bits 1, 0  SPR1, SPR0: SPI Clock Rate Select 1 and 0 
    
	if(SPI_mode == Master)
	{gpioPinDirection(SPI_MOSI_PORT, SPI_MOSI_PIN, OUTPUT);
	 gpioPinDirection(SPI_MISO_PORT, SPI_MISO_PIN, INPUT);	 	
	 gpioPinDirection(SPI_SCK_PORT, SPI_SCK_PIN, OUTPUT);
	 gpioPinDirection(SPI_SS_PORT, SPI_SS_PIN, OUTPUT);	
	}else if (SPI_mode == Slave)
	{gpioPinDirection(SPI_MOSI_PORT, SPI_MOSI_PIN, INPUT);
	 gpioPinDirection(SPI_MISO_PORT, SPI_MISO_PIN, OUTPUT);
	 gpioPinDirection(SPI_SCK_PORT, SPI_SCK_PIN, INPUT);
	 gpioPinDirection(SPI_SS_PORT, SPI_SS_PIN, INPUT);
	}
	else
	{
		u8_Ret_Error = E_NOK;
	}
	
	SPCR = SPCR|SPI_state;
   return u8_Ret_Error;  		
}

void SPI_Send_(char data)
{
	SPDR=data;
	while(!(SPSR& 0x80)); // wait until send complete

	
}

ERROR_STATUS SPI_Send_Unblock(char data)
{
	ERROR_STATUS u8_Ret_Error = E_OK;
	/*
	SPDR=data;
	while(!(SPSR& 0x80)); // wait until send complete
	*/
	   // SPSR &= 0x80;
		if ((SPSR& 0x80)==0)
		{
			SPDR=data;
			return 0;
		}else
		{			
			return 1;
		}
		
	return u8_Ret_Error;
}

char SPI_Recive(void)
{
	while(!(SPSR& 0x80)); // wait until receive complete
	  return SPDR ;			
}


ERROR_STATUS SPI_Recive_Unblock(char* data)
{
	ERROR_STATUS u8_Ret_Error = E_OK;
	/*
	while(!(SPSR& 0x80)); // wait until receive complete
	return SPDR ;
	*/
	if ((SPSR& 0x80)==1)
	{
		*data=SPDR;
		return 0;
	}else
	{
		*data=SPDR;//
		return 1;
	}
	return u8_Ret_Error;
}


void SPI_SET_CallBack(SPI_call_back SPI_Ptr_CallBack)
{
  if(SPI_Ptr_CallBack != NULL)
  {
	  gpfun_SPI_back = SPI_Ptr_CallBack;
  }
}


ISR(SPI_STC_vect	)
{
	//PORTC_DATA= 0x01;

	if (gpfun_SPI_back != NULL)
	{
		gpfun_SPI_back();
	}
	
}
