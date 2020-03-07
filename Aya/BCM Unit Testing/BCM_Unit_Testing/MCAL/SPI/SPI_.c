/*
 * SPI_.c
 *
 * Created: 10/02/2020 14:17:39
 *  Author: ahmed_pc
 */

#include "SPI_.h"
#include "../../Testing/BCM_unit_Testing.h"


/************************************************************************/
/*                GLOBAL STATIC VARIABLES                           */
/************************************************************************/

static volatile SPI_call_back gpfun_SPI_back = NULL ;


ERROR_STATUS SPI_Init_(Interrupt_State interrupt_state,SPI_En_State SPI_state , Data_Order data_order ,SPI_Mode SPI_mode ,Clock_Polarity clock_Polarity ,Clock_Phase clock_phase , SPI_Clock_Rate clock_rate)
{

   return gu8_SPI_Init_Return;
}

ERROR_STATUS SPI_Send_(char data)
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
