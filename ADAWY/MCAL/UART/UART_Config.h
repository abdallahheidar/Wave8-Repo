/*
 * UART_Config.h
 *
 * Created: 2/9/2020 3:20:26 PM
 *  Author: Khaled
 */ 


 #ifndef UARTCONFIG_H_
 #define UARTCONFIG_H_
/*
 * Asyn operation mode: normal speed or double speed mode
 */
 typedef enum En_UartSpeed_t{
	 Uart_Async_Normal_Speed, Uart_Async_Double_Speed
 }En_UartSpeed_t;

  typedef enum En_UartMultiProcessorCommunication_t{
	  Uart_Multi_Processor_Communication_Disable, Uart_Multi_Processor_Communication_Enable
  }En_UartMultiProcessorCommunication_t;
/*
 * Operating baud rate
 */
 typedef enum En_UartBaudRate_t{
	 Uart_Baud_Rate_9600, Uart_Baud_Rate_115200
 }En_UartBaudRate_t;

/*
 * Data size 5,6,7,8 or 9 bits in the frame
 */
 typedef enum En_UartDataFrameSize_t{
	 Uart_Data_5_Bit, Uart_Data_6_Bit, Uart_Data_7_Bit, Uart_Data_8_Bit, Uart_Data_9_Bit
 }En_UartDataFrameSize_t;
 
/*
 *  Stop bit condition: one or two bits
 */
 typedef enum En_UartStopBit_t{
	 Uart_Stop_Bit_One, Uart_Stop_Bit_Two
 }En_UartStopBit_t;
 
/*
 * Parity operating mode 
 */
 typedef enum En_UartParity_t{
	 Uart_Parity_no, Uart_Parity_Odd, Uart_Parity_Even
 }En_UartParity_t;

 typedef enum En_UartInterrupt_t{
	 Uart_Interrupt, Uart_Polling
 }En_UartInterrupt_t;


 /*#define  UART_SPEED (Normal_Speed)*/

 #endif /* UART_CFG_H_ */