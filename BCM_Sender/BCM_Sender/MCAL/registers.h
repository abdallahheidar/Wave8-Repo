/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#define F_CPU 16000000UL

/*- INCLUDES ------------------------------------------------*/

#include "std_types.h"
#include "avr/interrupt.h"
#include "common_macros.h"


/*
 * General Registers
 */

#define MCUCR_R		(*((reg_type8_t)(0x55)))
#define MCUCSR_R	(*((reg_type8_t)(0x54)))
#define GICR_R		(*((reg_type8_t)(0x5B)))
#define GIFR_R		(*((reg_type8_t)(0x5A)))

/*
 * PORTx registers
 */

#define PORTA_DATA 	(*((reg_type8_t)(0x3B)))
#define PORTA_DIR  	(*((reg_type8_t)(0x3A)))
#define PORTA_PIN	(*((reg_type8_t)(0x39)))

#define PORTB_DATA 	(*((reg_type8_t)(0x38)))
#define PORTB_DIR  	(*((reg_type8_t)(0x37)))
#define PORTB_PIN	(*((reg_type8_t)(0x36)))

#define PORTC_DATA 	(*((reg_type8_t)(0x35)))
#define PORTC_DIR  	(*((reg_type8_t)(0x34)))
#define PORTC_PIN	(*((reg_type8_t)(0x33)))


#define PORTD_DATA 	(*((reg_type8_t)(0x32)))
#define PORTD_DIR  	(*((reg_type8_t)(0x31)))
#define PORTD_PIN	(*((reg_type8_t)(0x30)))


/*
 * General Timer registers
 */

#define TIMSK_R		*((reg_type8_t)(0x59))
#define TIFR_R		*((reg_type8_t)(0x58))


/*
 * Timer 0 Registers
 */

#define TCCR0_R		*((reg_type8_t)(0x53))
#define TCNT0_R		*((reg_type8_t)(0x52))
#define OCR0_R		*((reg_type8_t)(0x5C))


/*
 * Timer 1 Registers
 */

#define TCCR1A_R	*((reg_type8_t)(0x4F))
#define TCCR1B_R	*((reg_type8_t)(0x4E))
#define TCCR1_R		*((reg_type16_t)(0x4E))
#define TCNT1H_R	*((reg_type8_t)(0x4D))
#define TCNT1L_R	*((reg_type8_t)(0x4C))
#define TCNT1_R		*((reg_type16_t)(0x4C))
#define OCR1AH_R	*((reg_type8_t)(0x4B))
#define OCR1AL_R	*((reg_type8_t)(0x4A))
#define OCR1A_R		*((reg_type16_t)(0x4A))
#define OCR1BH_R	*((reg_type8_t)(0x49))
#define OCR1BL_R	*((reg_type8_t)(0x48))
#define OCR1B_R		*((reg_type16_t)(0x48))
#define ICR1H_R		*((reg_type8_t)(0x47))
#define ICR1L_R		*((reg_type8_t)(0x46))
#define ICR1_R		*((reg_type16_t)(0x46))


/*
 * Timer 2 Registers
 */

#define TCCR2_R		*((reg_type8_t)(0x45))
#define TCNT2_R		*((reg_type8_t)(0x44))
#define OCR2_R		*((reg_type8_t)(0x43))


/*
 * USART Registers
 */

#define UDR_R		*((reg_type8_t)(0x2C))
#define UCSRA_R		*((reg_type8_t)(0x2B))
#define UCSRB_R		*((reg_type8_t)(0x2A))
#define UCSRC_R		*((reg_type8_t)(0x40))
#define UBRRH_R		*((reg_type8_t)(0x40))
#define UBRRL_R		*((reg_type8_t)(0x29))


/*
 * SPI Registers
 */

#define SPCR_R		*((reg_type8_t)(0x2D))
#define SPSR_R		*((reg_type8_t)(0x2E))
#define SPDR_R		*((reg_type8_t)(0x2F))


#endif /* REGISTERS_H_ */
