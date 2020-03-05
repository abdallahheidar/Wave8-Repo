/*
 * UART.h
 *
 * Created: 2/9/2020 3:17:06 PM
 *  Author: Khaled
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../HAL/registers.h"
#include "../../SERVICE/std_types.h"
#include "UART_Config.h"
#include "../../HAL/interrupt.h"


#define BIT_0   0x01 	// defines BIT0 in a register
#define BIT_1   0x02 	// defines BIT1 in a register
#define BIT_2   0x04 	// defines BIT2 in a register
#define BIT_3   0x08 	// defines BIT3 in a register
#define BIT_4   0x10 	// defines BIT4 in a register
#define BIT_5   0x20 	// defines BIT5 in a register
#define BIT_6   0x40 	// defines BIT6 in a register
#define BIT_7   0x80 	// defines BIT7 in a register

#define SET_BIT(REG,BIT)    REG |= BIT
#define CLEAR_BIT(REG,BIT)  REG &= ~(BIT)

//UCSRA BIT:
#define RXC  BIT_7
/*
 * set when there are unread data in the receive buffer
 * cleared when the receive buffer is empty (that is, does not contain any unread data)
 * If the receiver is disabled, the receive buffer will be flushed and consequently the RXC bit will become zero.
 */
#define TXC  BIT_6
/*
 * set when the entire frame in the transmit Shift Register has been shifted out and there are no new data
 * currently present in the transmit buffer (UDR).
 * The TXC Flag bit is automatically cleared when a transmit complete interrupt is executed,
 * or it can be cleared by writing a one to its bit location.
 */
#define UDRE BIT_5
/*
 * If UDRE is one, the buffer is empty, and therefore ready to be written.
 */
#define FE   BIT_4
/*
 * set if the next character in the receive buffer had a Frame Error when received.
 */
#define DOR  BIT_3
/*
 * set if a Data OverRun condition is detected.
 */
#define PE   BIT_2
/*
 * set if the next character in the receive buffer had a Parity Error when received and the
 * parity checking was enabled at that point
 */
#define U2X  BIT_1
/*
 * Write this bit to zero when using synchronous operation.
 * Writing this bit to one will reduce the divisor of the baud rate divider from 16 to 8
 * effectively doubling the transfer rate for asynchronous communication.
 */
#define MPCM BIT_0
/*
 * Write this bit to one when using  Multi-processor Communication Mode
 * all the incoming frames received by the USART receiver that do not contain address information will be ignored.
 */

/***************************************************************************************************************************/

//UCSRB BIT:
#define RXCIE  BIT_7
/*
 * Writing this bit to one enables interrupt on the RXC Flag.
 */
#define TXCIE  BIT_6
/*
 * Writing this bit to one enables interrupt on the TXC Flag.
 */
#define UDRIE  BIT_5
/*
 * Writing this bit to one enables interrupt on the UDRE Flag.
 */
#define RXEN   BIT_4
/*
 * Writing this bit to one enables the USART Receiver.
 */
#define TXEN   BIT_3
/*
 * Writing this bit to one enables the USART Transmitter.
 */
#define UCSZ2  BIT_2
/*
 * combined with the UCSZ1:0 bit in UCSRC sets the number
 * of data bits (Character Size) in a frame the receiver and transmitter use.
 */
#define RXB8   BIT_1
/*
 *RXB8 is the ninth data bit of the received character when operating with
 *serial frames with nine data bits.
 *Must be read before reading the low bits from UDR.
 */
#define TXB8   BIT_0
/*
 * TXB8 is the ninth data bit in the character to be transmitted when operating
 * with serial frames with nine data bits.
 * Must be written before writing the low bits to UDR.
 */

/**************************************************************************************************************************/

//UCSRC BIT:
#define URSEL  BIT_7
/*
 * It is read as one when reading UCSRC.
 * The URSEL must be one when writing the UCSRC.
 */
#define UMSEL  BIT_6
/*
 * 0 Asynchronous Operation
 * 1 Synchronous Operation
 */
#define UPM1   BIT_5
#define UPM0   BIT_4
/*
 * UPM1 UPM0 Parity Mode
 *  0    0   Disabled
 *  0    1   Reserved
 *  1    0   Enabled Even Parity
 *  1    1   Enabled Odd Parity
 */
#define USBS   BIT_3
/*
 *This bit selects the number of Stop Bits to be inserted by the Transmitter.
 * 0  1-bit
 * 1  2-bit
 */
#define UCSZ1  BIT_2
#define UCSZ0  BIT_1
/*
 * UCSZ2 UCSZ1 UCSZ0 Character Size
 *   0     0     0   5-bit
 *   0     0     1   6-bit
 *   0     1     0   7-bit
 *   0     1     1   8-bit
 *   1     0     0   Reserved
 *   1     0     1   Reserved
 *   1     1     0   Reserved
 *   1     1     1   9-bit
 */
#define UCPOL  BIT_0
/*
 * Write this bit to zero when Asynchronous mode is used.
 */

/************************************************************************************************************************/

//UBRRL & UBRRH BIT:
/*#define URSEL  BIT15*/
/*
*his bit selects between accessing the UBRRH or the UCSRC Register. It is read as zero when
*reading UBRRH.
**The URSEL must be zero when writing the UBRRH.
*/

/*
Bit 11:0 – UBRR11:0: USART Baud Rate Register
This is a 12-bit register which contains the USART baud rate. The UBRRH contains the four
most significant bits, and the UBRRL contains the 8 least significant bits of the USART baud
rate. Ongoing transmissions by the transmitter and receiver will be corrupted if the baud rate is
changed. Writing UBRRL will trigger an immediate update of the baud rate pre-scaler.
*/
/***********************************************************************************************************************/



void UART_INIT (En_UartParity_t en_parity, En_UartStopBit_t en_stop_bit, En_UartDataFrameSize_t en_data_frame_size, En_UartBaudRate_t en_baud_rate,
                En_UartSpeed_t en_speed,En_UartMultiProcessorCommunication_t en_multi_processor_communication,En_UartInterrupt_t en_interrupt_mode,
                void(* ptr_RCBK)(uint8_t));


void UART_TRANSMIT_Char (uint8_t Data, uint8_t * not);

void UART_TRANSMIT_String (uint8_t * Data);


uint8_t UART_RECEIVE (void);

void UART_RECEIVE_String (uint8_t * Data);

#endif /* UART_H_ */