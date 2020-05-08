 /*
 ============================================================================
 Name        : I2C.c
 Author      : Muhammed Gamal
 Description : Source file for the I2C(TWI) AVR driver
 ============================================================================
 */


/*********************************includes**********************************/
#include "i2c.h"
#include "I2C_Cfg.h"
/***************************************************************************/


/*********************************definitions*******************************/
#define TWI_NO_PRESCALLER           0
#define TWI_PRESCALLER_4            1
#define TWI_PRESCALLER_16           2
#define TWI_PRESCALLER_64           3
#define DEVICE_ID                   0x10
#define TWO                         2
#define FOUR                        4
#define SIXTEEN                     16
#define CLEAR                       0
#define FIRST_ENTRY                 0
#define SECOND_ENTRY                1
#define READ_MASK                   0x01
#define WRITE_MASK                  0xFE
#define CLEAR                       0
#define END                         0
#define NULL	                    ((void *)0)
#define FLAG_HIGH                   1
#define FLAG_LOW                    0
#define MEM_RANGE                   256
/***************************************************************************/


/******************************global variables*****************************/
I2C_CbkPftype Consumer_Clb_Ptr = NULL;
I2C_CbkPftype Operation_Clb_Ptr = NULL;
uint8_t I2C_FLAG;
/***************************************************************************/


/************************************************************************************
* Function Name: I2C_Init
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function initializes the module
************************************************************************************/
void I2C_Init(void)
{
	uint8_t au8_TWBR_Value;

    /* select the prescaller */
	switch(I2C_ConfigParam.PreScaler)
	{
	case TWI_NO_PRESCALLER:
		au8_TWBR_Value = 0;
		break;
	case TWI_PRESCALLER_4:
		au8_TWBR_Value = 1;
		break;
	case TWI_PRESCALLER_16:
		au8_TWBR_Value = 2;
		break;
	case TWI_PRESCALLER_64:
		au8_TWBR_Value = 3;
		break;
	}

	/* set the bit rate */
	TWBR = ((I2C_ConfigParam.CPUFreq) / (I2C_ConfigParam.TargerRate * (FOUR^au8_TWBR_Value) * TWO))-(SIXTEEN/((FOUR^au8_TWBR_Value)*TWO));

	TWSR = CLEAR;    /* clear the status register */

    /* Two Wire Bus address my address if any master device want to call me: 0x10 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = DEVICE_ID; /* set the device address */

    TWCR = (1<<TWEN) | (1<<TWIE); /* enable TWI and TWI interrupt*/

    Consumer_Clb_Ptr = I2C_ConfigParam.ActionDoneCbkPtr;  /* set the call back function */

    I2C_FLAG = FLAG_LOW;           /* reset the flag */
}


/************************************************************************************
* Function Name: I2C_start
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this local function sends the start bit
************************************************************************************/
static void I2C_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1<<TWIE);
}


/************************************************************************************
* Function Name: I2C_Stop
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: this function sends the stop bit
************************************************************************************/
void I2C_Stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) | (1<<TWIE);
}


/************************************************************************************
* Function Name: I2C_ReqWrite
* Parameters (in): -SlaveAddress
*                  -*DataPtr
*                  -DataLen
* Parameters (inout): None
* Parameters (out): None
* Return value: I2C_CheckType
* Description: this function writes data on I2C bus
************************************************************************************/
I2C_CheckType I2C_ReqWrite(unsigned char SlaveAddress, const unsigned char* DataPtr, unsigned char DataLen)
{
	uint8_t au8_stats = I2C_OK;
	static uint8_t au8_counter = CLEAR;
	/* errors checking */
	if(SlaveAddress > MEM_RANGE || DataPtr == NULL || DataLen > MEM_RANGE)
	{
		au8_stats = I2C_NOK;
	}

	else
	{
		if(I2C_FLAG == FLAG_LOW)
		{
			I2C_FLAG = FLAG_HIGH;       /*  raise the flag */
			if(DataLen != END)
			{
				if(au8_counter == FIRST_ENTRY)
				{
					Operation_Clb_Ptr = I2C_ReqWrite;    /* set the call back operation */
					I2C_start();                        /* send the start bit */
				}

				else if(au8_counter == SECOND_ENTRY)
				{
					TWDR = SlaveAddress & WRITE_MASK;   /* slave address and write operation */
				}

				else
				{
					/* Put data On TWI data Register */
					TWDR = *DataPtr;
					DataLen--;
					DataPtr++;
				}

				/*
				 * Clear the TWINT flag before sending the data TWINT=1
				 * Enable TWI Module TWEN=1
				 */
				TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWIE);

				au8_counter++;
			}
		}
	}

	if(DataLen == END)
	{
		au8_counter = CLEAR;  /* reset the counter */
		I2C_FLAG = FLAG_LOW;  /* reset the flag */

		if(Consumer_Clb_Ptr != NULL)
		{
			Consumer_Clb_Ptr();    /* notify the consumer */
		}
	}

	return au8_stats;
}


/************************************************************************************
* Function Name: I2C_ReqRead
* Parameters (in): -SlaveAddress
*                  -DataLen
* Parameters (inout): None
* Parameters (out): - *DataPtr
* Return value: I2C_CheckType
* Description: this function writes data on I2C bus
************************************************************************************/
I2C_CheckType I2C_ReqRead(unsigned char SlaveAddress, unsigned char* DataPtr, unsigned char DataLen)
{
	uint8_t au8_stats = I2C_OK;
	static uint8_t au8_counter = CLEAR;

	/* errors checking */
	if(SlaveAddress > MEM_RANGE || DataPtr == NULL || DataLen > MEM_RANGE)
	{
		au8_stats = I2C_NOK;
	}

	else
	{
		if(I2C_FLAG == FLAG_LOW)
		{
			I2C_FLAG = FLAG_HIGH;       /*  raise the flag */

			if(DataLen > END)
			{
				if(au8_counter == FIRST_ENTRY)
				{
					Operation_Clb_Ptr = I2C_ReqRead;    /* set the call back operation */
					I2C_start();                       /* send the start bit */
				}

				else if(au8_counter == SECOND_ENTRY)
				{
					TWDR = SlaveAddress | READ_MASK;   /* slave address and read operation */

					/*
					 * Clear the TWINT flag before sending the data TWINT=1
					 * Enable TWI Module TWEN=1
					 */
					TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWIE);

				}

				else
				{
					/*
					 * Clear the TWINT flag before reading the data TWINT=1
					 * Enable sending ACK after reading or receiving data TWEA=1
					 * Enable TWI Module TWEN=1
					 */
					TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1<<TWIE);

					/* Read Data */
					*DataPtr = TWDR;
					DataLen--;
					DataPtr++;
				}
				au8_counter++;
			}
		}
	}

	if(DataLen == END)
	{
		au8_counter = CLEAR;  /* reset the counter */
		I2C_FLAG = FLAG_LOW;  /* reset the flag */

		if(Consumer_Clb_Ptr != NULL)
		{
			Consumer_Clb_Ptr();    /* notify the consumer */
		}
	}

	return au8_stats;
}



/************************************************************************************
					     				ISR
************************************************************************************/
ISR(TWI_vect)
{
	I2C_FLAG = FLAG_LOW;
	if(Operation_Clb_Ptr != NULL)
	{
		Operation_Clb_Ptr();    /* call the function to complete the operation */
	}
}
