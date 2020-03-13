#include "ICU.h"


/*- DEFINES ------------------------------------------------*/

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

#define	TIMER2_1024_PRESCALER	0x07

#define	TIMER_PRESCALER_MASK	0xF8


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	uint8 au8_Ret = NO_ERROR;

	/* Configure pin2 of portB as an input pin and activate the internal pull-up resistor option */
	PORTB_DIR &= ~BIT2;
	PORTB_DATA |= BIT2;

	switch(Icu_Cfg->ICU_Ch_Timer)
	{
		case ICU_TIMER_CH2:
		/* Choose the prescaler of 1024 */
		TCCR2 = (TCCR2 & TIMER_PRESCALER_MASK) | TIMER2_1024_PRESCALER;
		break;
		default:
		au8_Ret = ERROR;
		break;
	}
	return au8_Ret;
}

ERROR_STATUS Icu_ReadTime(uint8 Icu_Channel, uint8 Icu_EdgeToEdge, uint32* Icu_Time)
{
	uint8 au8_Ret = NO_ERROR;

	/* A switch case to determine the edge detection mode */
	switch(Icu_EdgeToEdge)
	{
		case ICU_FALE_TO_RISE:
		/* A busy-wait until the rising edge is met */
		while(!(PORTB_PIN & BIT2));
		/* A busy-wait until the falling edge is met */
		while(PORTB_PIN & BIT2);
		TCNT2 = 0;
		/* A busy-wait until the rising edge is met */
		while(!(PORTB_PIN & BIT2));
		*Icu_Time = TCNT2;
		break;
		case ICU_RISE_TO_FALL:
		/* A busy-wait until the falling edge is met */
		while(PORTB_PIN & BIT2);
		/* A busy-wait until the rising edge is met */
		while(!(PORTB_PIN & BIT2));
		TCNT2 = 0;
		/* A busy-wait until the falling edge is met */
		while(PORTB_PIN & BIT2);
		*Icu_Time = TCNT2;
		break;
		case ICU_RISE_TO_RISE:
		/* A busy-wait until the falling edge is met */
		while(PORTB_PIN & BIT2);
		/* A busy-wait until the rising edge is met */
		while(!(PORTB_PIN & BIT2));
		TCNT2 = 0;
		/* A busy-wait until the falling edge is met */
		while(PORTB_PIN & BIT2);
		/* A busy-wait until the rising edge is met */
		while(!(PORTB_PIN & BIT2));
		*Icu_Time = TCNT2;
		break;
		default:
		au8_Ret = ERROR;
		break;
	}

	return au8_Ret;
}
