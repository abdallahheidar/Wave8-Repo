/*
 * BCM_Send.c
 *
 * Created: 04/03/2020 04:37:48 م
 *  Author: mo
 */
#include "BCM_Send.h"

static uint8_t u8_Is_Intialized=0;
static uint8_t u8_frameID=0;
extern volatile uint8_t Buffer_Array[];
volatile uint8_t u8Index=0;
extern volatile uint8_t u8_DATA;
extern volatile uint8_t u8_DATA_SPI;
extern volatile uint8_t size;
extern volatile uint8_t uartinterruptfinished;
volatile uint8_t u8_interrupt_spi=0;
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
}
u8_frameID=ConfigPtr -> u8_BCM_ID;
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

ERROR_STATUS BCM_TxDispatcher(void)
{
uint8_t ret=E_OK,index=0;
uint8_t Checksum=0;

Checksum+=u8_DATA;

/******Disable SPI int******/
/*while uart is filling buffer*/
/*calculate check sum*/
/*Enable Spi int and disable uart int when buffer is full*/
/*When spi emptys buffer enable uart interrupt*/
if( u8_interrupt_spi && uartinterruptfinished ){
for (index=0;index<size;index++)
{
	SPDR=Buffer_Array[index];
  u8_interrupt_spi=0;
}
}



Buffer_Array[size-1]=Checksum;
return ret;
}
/*BCM SEND Intiate spi connection*/
ERROR_STATUS BCM_Send(
  uint8_t u8_channel_Protcol ,
  uint8_t u8_BCM_ID,
  uint8_t u8_data_Lenght,
  uint8_t Num_of_Frames )
{
  uint8_t ret=E_OK;

/*BCMID  & data length*/
Buffer_Array[0]=u8_BCM_ID;
Buffer_Array[1]=u8_data_Lenght;
u8Index=2;
/*************************************************************/
/*                                                           */
/*************************************************************/

switch (u8_channel_Protcol)
  {
    case SPI:
      spi_send_first(u8_BCM_ID);
      spi_send_first(u8_data_Lenght);
    break;
    case UART:
    	Uart_tryansmitfirstbyte(u8_BCM_ID);
    break;
    case UARTANDSPI:
      spi_send_first(u8_BCM_ID);
    break;
    case I2C:
      ret=INVALID_PARM+BCM_MODULE;
    break;
    default:
    ret=E_NOK+INVALID_PARM+BCM_MODULE;
  }

  return ret;
}


void Uart_Int_RX(void)
{
  u8_DATA=UDR;
  if(u8Index<size-1)
  {
    Buffer_Array[u8Index]=u8_DATA;
    u8Index++;
uartinterruptfinished=0;
  }
    else{
      u8Index=2;
uartinterruptfinished=1;
        }


}
void SPI_int_Master_Send(void)
{
u8_interrupt_spi=1;

}
