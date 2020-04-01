/*
 * sleep.c
 *
 * Created: 09/03/2020 07:11:16 م
 *  Author: TOSHIBA
 */ 

/* INCLUDE*/

#include "sleep.h"

/* DEFINE*/

#define SLEEP_EN_BIT  (0x80)
#define SLEEP_DIS_EN_BIT  (0x7F)
#define MCUCR_CLEAR_SLEEP_MODE_BITS_MASK 0x0f
#define INIT_MODULE			1
#define UNINIT_MODULE		0
static uint8_t u8_SleepModeInit;

/*					FUNCTION IMPLEMENTAION				*/ 

u8_ERROR_STATUS_t Sleep_Mode(uint8_t u8_SleepMode)
{	u8_ERROR_STATUS_t u8_ErroeStatus = E_OK;
	if(u8_SleepModeInit == UNINIT_MODULE)
	{
		switch(u8_SleepMode)
		{
			case IDLE:
			//MCUCR &= MCUCR_CLEAR_SLEEP_MODE_BITS_MASK; //need to try it
			MCUCR |= u8_SleepMode;
			break;
			
			default:
			u8_ErroeStatus= SLEEP_MODE_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR ;
			break;
		}
		u8_SleepModeInit = INIT_MODULE ;
	}
	else 
	{
		u8_ErroeStatus = SLEEP_MODE_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT ;
	}
	return u8_ErroeStatus;
}
u8_ERROR_STATUS_t EN_Sleep(void)
{
	u8_ERROR_STATUS_t u8_ErroeStatus = E_OK;
	if(u8_SleepModeInit == INIT_MODULE)
	{
		MCUCR |= SLEEP_EN_BIT;
	
		/* Assembly code that turn sleep mode */
	
		__asm__ __volatile__( "sleep" "\n\t" :: );
	}
	else
	{
		u8_ErroeStatus = SLEEP_MODE_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE ;
	}

	return u8_ErroeStatus;
}
u8_ERROR_STATUS_t DIS_EN_Sleep(void)
{
	u8_ERROR_STATUS_t u8_ErroeStatus = E_OK;
	if(u8_SleepModeInit == INIT_MODULE)
	{
		MCUCR &= SLEEP_DIS_EN_BIT;
	}
	else
	{
		u8_ErroeStatus = SLEEP_MODE_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE ;
	}
	return u8_ErroeStatus;
}