/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "std_types.h"

/*
 * General Registers
 */
 extern uint8_t MCUCR;
 extern uint8_t MCUCSR;
 extern uint8_t GICR;
 extern uint8_t GIFR;
 
 /*
 * PORTx registers
 */

 extern uint8_t PORTA_DATA;
 extern uint8_t PORTA_DIR ;
 extern uint8_t PORTA_PIN;
 
 extern uint8_t PORTB_DATA;
 extern uint8_t PORTB_DIR ;
 extern uint8_t PORTB_PIN;
 
 extern uint8_t PORTC_DATA;
 extern uint8_t PORTC_DIR ;
 extern uint8_t PORTC_PIN;
 
 extern uint8_t PORTD_DATA;
 extern uint8_t PORTD_DIR ;
 extern uint8_t PORTD_PIN;
 
/*
 * General Timer registers
 */
 extern uint8_t TIMSK;
 extern uint8_t TIFR;
 /*
 * Timer 0 Registers
 */
 extern uint8_t TCCR0;
 extern uint8_t TCNT0;
 extern uint8_t OCR0;
 /*
 * Timer 1 Registers
 */ 
 extern uint8_t TCCR1A;
 extern uint8_t TCCR1B;
 extern uint16_t TCCR1;
 extern uint8_t TCNT1H;
 extern uint8_t TCNT1L;
 extern uint16_t TCNT1;
 extern uint8_t OCR1AH;
 extern uint8_t OCR1AL;
 extern uint16_t OCR1A;
 extern uint8_t OCR1BH	;
 extern  uint8_t OCR1BL;
 extern uint16_t OCR1B;
 extern uint8_t ICR1H;
 extern uint8_t ICR1L;
 extern uint16_t ICR1;
 
 /*
 * Timer 2 Registers
 */
 extern uint8_t TCCR2;
 extern uint8_t TCNT2;	
 extern uint8_t OCR2;
 extern uint8_t ASSR;
 
 /************************************************************************/
/** USART REGISTERS                                                                     */
/************************************************************************/
 
 extern uint8_t UDR;
 extern uint8_t UCSRA;
 extern uint8_t UCSRB;
 extern uint8_t UCSRC;
 extern uint8_t UBRRL;
 extern uint8_t UBRRH;
 extern uint16_t UBRR;
 
 
 /************************************************************************/
/** SPI REGISTERS                                                                     */
/************************************************************************/

 extern uint8_t SPDR;
 extern uint8_t SPCR ;
 extern uint8_t SPSR;
 
 /*********************/
 extern uint8_t SREG;


#endif /* REGISTERS_H_ */
