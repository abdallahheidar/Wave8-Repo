/*
 * DIO.c
 *
 *  Created on: Feb 17, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "DIO.h"


/*- PREPROCESSOR MACROS ------------------------------------*/

#define		PORT_NOT_INITIALIZED		0
#define		PORT_INITIALIZED			1

/*- STATIC GLOBAL VARIABLES --------------------------------*/

static uint8_t gu8_PortA_InitStatus;
static uint8_t gu8_PortB_InitStatus;
static uint8_t gu8_PortC_InitStatus;
static uint8_t gu8_PortD_InitStatus;


/*- APIs IMPLEMENTATION ------------------------------------*/

static void DIO_ParsVarsDefault(void)
{
	gu8_PortA_InitStatus = PORT_NOT_INITIALIZED;
	gu8_PortB_InitStatus = PORT_NOT_INITIALIZED;
	gu8_PortC_InitStatus = PORT_NOT_INITIALIZED;
	gu8_PortD_InitStatus = PORT_NOT_INITIALIZED;
}

ERROR_STATUS DIO_Init (DIO_Cfg_s *DIO_info)
{
	sint8_t as8_Ret = DIO_E_OK;
	static uint8_t au8_InitializeGlobalVariablesOnce = NOT_DONE;
	/* A local pointer to register in which the required register address will be stored */
	uint8_t* pau8_gpioDirectionPointer = NULL;

	if(au8_InitializeGlobalVariablesOnce == NOT_DONE)
	{
		DIO_ParsVarsDefault();

		au8_InitializeGlobalVariablesOnce = DONE;
	}

	/* A switch case to determine which Port to change its direction */
	switch(DIO_info->GPIO)
	{
	case GPIOA:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTA_DIR);
		if(gu8_PortA_InitStatus == PORT_INITIALIZED)
		{
			as8_Ret = DIO_E_ALREADY_INIT;
		}else
		{
			gu8_PortA_InitStatus = PORT_INITIALIZED;
		}
		break;
	case GPIOB:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTB_DIR);
		if(gu8_PortB_InitStatus == PORT_INITIALIZED)
		{
			as8_Ret = DIO_E_ALREADY_INIT;
		}else
		{
			gu8_PortB_InitStatus = PORT_INITIALIZED;
		}
		break;
	case GPIOC:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTC_DIR);
		if(gu8_PortC_InitStatus == PORT_INITIALIZED)
		{
			as8_Ret = DIO_E_ALREADY_INIT;
		}else
		{
			gu8_PortC_InitStatus = PORT_INITIALIZED;
		}
		break;
	case GPIOD:
		pau8_gpioDirectionPointer = (uint8_t*)(&PORTD_DIR);
		if(gu8_PortD_InitStatus == PORT_INITIALIZED)
		{
			as8_Ret = DIO_E_ALREADY_INIT;
		}else
		{
			gu8_PortD_InitStatus = PORT_INITIALIZED;
		}
		break;
	default:
		as8_Ret = DIO_E_INVALID_PORT;
		break;
	}

	if(as8_Ret == DIO_E_OK)
	{
		/* A switch case to determine which direction to be configured in the port */
		switch(DIO_info->dir)
		{
		case INPUT:
			*pau8_gpioDirectionPointer &= ~(DIO_info->pins);
			break;
		case OUTPUT:
			*pau8_gpioDirectionPointer |= (DIO_info->pins);
			break;
		default:
			as8_Ret = DIO_E_INVALID_DIRECTION;
			break;
		}
	}

	return as8_Ret;
}

ERROR_STATUS DIO_DeInit (uint8_t GPIO)
{
	sint8_t as8_Ret = DIO_E_OK;

	switch(GPIO)
	{
	case GPIOA:
		gu8_PortA_InitStatus = PORT_NOT_INITIALIZED;
		break;
	case GPIOB:
		gu8_PortB_InitStatus = PORT_NOT_INITIALIZED;
		break;
	case GPIOC:
		gu8_PortC_InitStatus = PORT_NOT_INITIALIZED;
		break;
	case GPIOD:
		gu8_PortD_InitStatus = PORT_NOT_INITIALIZED;
		break;
	default:
		as8_Ret = DIO_E_INVALID_PORT;
		break;
	}

	return as8_Ret;
}


ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	sint8_t as8_Ret = DIO_E_OK;
	/* A pointer to register in which the required register address will be stored */
	uint8_t* pau8_gpioDataPointer = NULL;

	/* A switch case to determine which Port to change its data */
	switch(GPIO)
	{
	case GPIOA:
		pau8_gpioDataPointer = (uint8_t*)(&PORTA_DATA);
		if(gu8_PortA_InitStatus == PORT_NOT_INITIALIZED)
			as8_Ret = DIO_E_NOT_INIT;
		break;
	case GPIOB:
		pau8_gpioDataPointer = (uint8_t*)(&PORTB_DATA);
		if(gu8_PortB_InitStatus == PORT_NOT_INITIALIZED)
			as8_Ret = DIO_E_NOT_INIT;
		break;
	case GPIOC:
		pau8_gpioDataPointer = (uint8_t*)(&PORTC_DATA);
		if(gu8_PortC_InitStatus == PORT_NOT_INITIALIZED)
			as8_Ret = DIO_E_NOT_INIT;
		break;
	case GPIOD:
		pau8_gpioDataPointer = (uint8_t*)(&PORTD_DATA);
		if(gu8_PortD_InitStatus == PORT_NOT_INITIALIZED)
			as8_Ret = DIO_E_NOT_INIT;
		break;
	default:
		as8_Ret = DIO_E_INVALID_PORT;
		break;
	}

	if(as8_Ret == DIO_E_OK)
	{
		/* A switch case to determine which value to be configured in the port */
		switch(value)
		{
		case LOW:
			*pau8_gpioDataPointer &= ~(pins);
			break;
		case HIGH:
			*pau8_gpioDataPointer |= (pins);
			break;
		default:
			as8_Ret = DIO_E_INVALID_VALUE;
			break;
		}
	}

	return as8_Ret;
}

ERROR_STATUS DIO_WriteValue (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	sint8_t as8_Ret = DIO_E_OK;
	/* A pointer to register in which the required register address will be stored */
	uint8_t* pau8_gpioDataPointer = NULL;

	/* A switch case to determine which Port to change its data */
	switch(GPIO)
	{
	case GPIOA:
		pau8_gpioDataPointer = (uint8_t*)(&PORTA_DATA);
		if(gu8_PortA_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}
		break;
	case GPIOB:
		pau8_gpioDataPointer = (uint8_t*)(&PORTB_DATA);
		if(gu8_PortB_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}
		break;
	case GPIOC:
		pau8_gpioDataPointer = (uint8_t*)(&PORTC_DATA);
		if(gu8_PortC_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}
		break;
	case GPIOD:
		pau8_gpioDataPointer = (uint8_t*)(&PORTD_DATA);
		if(gu8_PortD_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}
		break;
	default:
		as8_Ret = DIO_E_INVALID_PORT;
		break;
	}

	if(as8_Ret == DIO_E_OK)
	{
		*pau8_gpioDataPointer = (*pau8_gpioDataPointer & ~pins) | (value & pins);
	}

	return as8_Ret;
}


ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t* data)
{
	sint8_t as8_Ret = DIO_E_OK;

	if(data != NULL)
	{
		/* A switch case to determine which port will be read from */
		switch(GPIO)
		{
		case GPIOA:
			if(gu8_PortA_InitStatus == PORT_NOT_INITIALIZED)
			{
				as8_Ret = DIO_E_NOT_INIT;
			}else
			{
				*data = PORTA_PIN & pins? 1:0;
			}
			break;
		case GPIOB:
			if(gu8_PortB_InitStatus == PORT_NOT_INITIALIZED)
			{
				as8_Ret = DIO_E_NOT_INIT;
			}else
			{
				*data = PORTB_PIN & pins? 1:0;
			}
			break;
		case GPIOC:
			if(gu8_PortC_InitStatus == PORT_NOT_INITIALIZED)
			{
				as8_Ret = DIO_E_NOT_INIT;
			}else
			{
				*data = PORTC_PIN & pins? 1:0;
			}
			break;
		case GPIOD:
			if(gu8_PortD_InitStatus == PORT_NOT_INITIALIZED)
			{
				as8_Ret = DIO_E_NOT_INIT;
			}else
			{
				*data = PORTD_PIN & pins? 1:0;
			}
			break;
		default:
			as8_Ret = DIO_E_INVALID_PORT;
			break;
		}
	}else
	{
		as8_Ret = DIO_E_NULL_POINTER;
	}

	return as8_Ret;
}

ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	sint8_t as8_Ret = DIO_E_OK;

	/* A switch case to determine which port value to be toggled */
	switch(GPIO)
	{
	case GPIOA:
		if(gu8_PortA_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}else
		{
			PORTA_DATA ^= pins;
		}
		break;
	case GPIOB:
		if(gu8_PortB_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}else
		{
			PORTB_DATA ^= pins;
		}
		break;
	case GPIOC:
		if(gu8_PortC_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}else
		{
			PORTC_DATA ^= pins;
		}
		break;
	case GPIOD:
		if(gu8_PortD_InitStatus == PORT_NOT_INITIALIZED)
		{
			as8_Ret = DIO_E_NOT_INIT;
		}else
		{
			PORTD_DATA ^= pins;
		}
		break;
	default:
		as8_Ret = DIO_E_INVALID_PORT;
	}

	return as8_Ret;
}
