/*
 * SPI.c
 *
 * Created: 10-Feb-20 6:11:46 PM
 *  Author: ahmed
 */
#include "SPI.h"
#include "SPI_CONFIG.h"
#include "interrupt.h"
#include "registers.h"

volatile uint8_t spi_myflag =0;
volatile uint8_t data=0;

static volatile config_spi st_spi = {0};
ERROR_STATUS spi_init(config_spi *sp_inits){
	
	uint8_t loop=ZERO;
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*save structure*/
	st_spi = *sp_inits;
	
	/*configure spi*/
	SPCR = ((sp_inits->spi_irq)  | (sp_inits->bit_first) | (sp_inits->smp) | (sp_inits->spi_prescal) |(sp_inits->spi_en));

	switch(sp_inits->master_slave)
	{
		case MASTER_SELECT:
		/*set MOSI as OUT*/
		
			/*make some time delay if master selected*/
			for(loop=0 ; loop<5 ; loop++);
			PORTB_DIR |= (MOSI);
			PORTB_DIR &= ~(MISO);
		
			PORTB_DIR |= (SS);
			/*set ck as out*/
			PORTB_DIR |= (SCK);
		
		break;
		
		case SLAVE_SELECT:
		
			/*set MOSI as IN*/
			PORTB_DIR &= ~(MOSI);
			PORTB_DIR |= (MISO);
		
			PORTB_DIR &= ~(SS);
			/*set ck as in*/
			PORTB_DIR &= ~(SCK);
		
		break;
		
		default:
			/*save error status*/
			error_flag = E_NOK;
		break;
	}
	
	/*set master or slave bit*/
	SPCR |=(sp_inits->master_slave);
	/*return error status*/
	return error_flag;
}

uint8_t spi_receiver(void){
	
	/*write spdr at spi*/	
	return SPDR;
}

ERROR_STATUS spi_transmitter(uint8_t u8_spi_sender)
{
	/*create error flag*/
	ERROR_STATUS error_flag = E_NOK;
	
	/*write the value at spdr*/
	SPDR = u8_spi_sender;
	
	return error_flag;
}


ISR(SPI_STC_vect)
{
	st_spi.spi_callback();
}