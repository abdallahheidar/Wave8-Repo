/*
 * BCM_Recieve.c
 *
 * Created: 04/03/2020 05:13:17 م
 *  Author: mo
 */
#include "BCM_Recieve.h"
volatile uint8_t u8_ChecksumR=0;
uint8_t u8_Is_Intialized=0;
uint8_t u8Index=0;
extern uint8_t u8_DATA;
extern volatile uint8_t size;
extern volatile uint8_t SPI_size;
extern volatile uint8_t u8_DATA_SPI;
extern volatile uint8_t SPIu8Index;
uint8_t bcm_id=0;
extern volatile uint8_t Buffer_Array[];

ERROR_STATUS BCM_Init (const BCM_ConfigType * ConfigPtr )
{
  uint8_t ret=E_OK;
if(ConfigPtr == NULL){ret=NULL_PTR+BCM_MODULE;}
else{
/*Intialize SPI..*/
switch (ConfigPtr->u8_channel_Protcol) {
  case SPI:
  u8_Is_Intialized++;
	SPI_Init();
  Enable_communication_interrupt();
  break;
  case UART:
u8_Is_Intialized++;
  Uart_Init(Baud9600,OneStopBit,NoParity,EightBits,ASynchronous);
	Enable_communication_interrupt();
  break;
  case UARTANDSPI:
  u8_Is_Intialized++;
  SPI_Init();
  Uart_Init(Baud9600,OneStopBit,NoParity,EightBits,ASynchronous);
	Enable_communication_interrupt();
  break;
  case I2C:
  ret=INVALID_PARM+BCM_MODULE;
  break;
  default:
  ret=INVALID_PARM+BCM_MODULE;
  break;
  }
  bcm_id=ConfigPtr->u8_BCM_ID;
}
return ret;
}
ERROR_STATUS BCM_DeInit (const BCM_ConfigType * ConfigPtr)
{
uint8_t ret=E_OK;
    if(u8_Is_Intialized==1)
      {
      switch (ConfigPtr->u8_channel_Protcol)
        {
          case SPI:
            u8_Is_Intialized--;
	           SPI_De_Init();
          break;
          case UART:
            u8_Is_Intialized--;
             Uart_De_Init();
          break;
          case UARTANDSPI:
            u8_Is_Intialized--;
            SPI_De_Init();
            Uart_De_Init();
          break;
          case I2C:
            ret=INVALID_PARM+BCM_MODULE;
          break;
        }
    }else if(u8_Is_Intialized > 1)
      {
        ret=MULTIPLE_INIT+BCM_MODULE;
      }else
      {
        ret = NOT_INIT+BCM_MODULE;
      }
return ret;
}
ERROR_STATUS BCM_Recieve(  uint8_t u8_channel_Protcol ,uint8_t u8_BCM_ID,uint8_t u8_data_Lenght,uint8_t Num_of_Frames)
{uint8_t ret =0;
  Buffer_Array[0]=u8_BCM_ID;
  Buffer_Array[1]=u8_data_Lenght;
  u8Index=2;


return ret;
}
ERROR_STATUS BCM_RxDispatcher (void)
{
  uint8_t ret=E_OK;
  uint8_t Checksum=0;/*
CLEAR_BIT(UCSRB,TXCIE);
if(u8Index<size-1)
Checksum+=u8_DATA;*/
/******Disable SPI int******/
/*while uart is filling buffer*/
/*calculate check sum*/
/*Enable Spi int and disable uart int when buffer is full*/
/*When spi emptys buffer enable uart interrupt*/
/*
if(u8_ChecksumR==Checksum)
{
	SET_BIT(UCSRB,TXCIE);
	Uart_tryansmitfirstbyte(bcm_id);
}
*/
  return ret;
}
void Uart_transmit_int(void)
{
    UDR=u8_DATA;
    if(u8Index<size-1)
    {
	    u8_DATA=Buffer_Array[u8Index];
	    u8Index++;
    }
    else{
	    u8Index=2;
    }
}
void SPI_Receive_int(void)
{

	u8_DATA=SPDR;
	u8_ChecksumR+=u8_DATA;
	if(u8_DATA < (size-1))
	{
		Buffer_Array[u8Index]=u8_DATA;
		u8Index++;
	}
	else{
		u8Index=2;
		}

}
