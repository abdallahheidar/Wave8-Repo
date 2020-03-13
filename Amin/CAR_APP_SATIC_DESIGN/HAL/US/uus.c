#include "Us.h"


#define US_TRIGGER_GPIO		GPIOD
#define US_TRIGGER_BIT		BIT0

#define US_CONSTANT_PRESCALER_1024		1.088


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Us_Init(void)
{
	uint8_t au8_Ret =NO_ERROR;

	/* A structure to initialize the DIO trigger bit as output */
	DIO_Cfg_s Dio_InitializationConfig = {US_TRIGGER_GPIO, US_TRIGGER_BIT, OUTPUT};
	/* A structure to initialize the ICU module */
	Icu_cfg_s Icu_InitializationConfig = {ICU_CH2, ICU_TIMER_CH2};

	/* Initialization */
	au8_Ret |= DIO_init(&Dio_InitializationConfig);
	au8_Ret |= Icu_Init(&Icu_InitializationConfig);

	return au8_Ret;
}

ERROR_STATUS Us_Trigger(void)
{
	uint8_t au8_Ret = NO_ERROR;

	/* Sending trigger by putting the pin to high level then to low level after >1 msec delay */
	au8_Ret |= DIO_Write(US_TRIGGER_GPIO, US_TRIGGER_BIT, HIGH);
	_delay_ms(5);
	au8_Ret |= DIO_Write(US_TRIGGER_GPIO, US_TRIGGER_BIT, LOW);

	return au8_Ret;
}

ERROR_STATUS Us_GetDistance(uint16_t* Distance)
{
	uint8_t au8_Ret = NO_ERROR;

	/* The value to be returned from the Icu_ReadTime function and contains the timer counter value */
	uint32_t au32_CounterValue = 0;

	/* Reading the timer counter value required to calculate the edge detection time */
	au8_Ret |= Icu_ReadTime(ICU_CH2, ICU_RISE_TO_FALL, &au32_CounterValue);

	*Distance = (uint16_t)((au32_CounterValue) * US_CONSTANT_PRESCALER_1024);

	return au8_Ret;
}
