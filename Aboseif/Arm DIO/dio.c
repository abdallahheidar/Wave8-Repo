/*
 * dio.c
 *
 * Created: 2020-04-10 12:20:42 AM
 *  Author: EbrahimOseif
 */
 
 
 
/************************************************************************/
/*				               INCLUDES			                        */
/************************************************************************/

#include "dio.h"


/************************************************************************/
/*				   functions' implementation                            */
/************************************************************************/

/*
*Input: ChannelId -> to get pin on a port
*					
*Output: 
*In/Out:
*Return STD_level -> the acquired data from a pin
*Description: This function gets the value of a full port
* 			  
*/

STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    STD_levelType return_Value;
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;
	
    switch(PortId)
    {
    case Dio_Port_A:
        return_Value = GET_BIT(PORTA_REG.GPIODATA, ChannelPos);
        break;

    case Dio_Port_B:
        return_Value = GET_BIT(PORTB_REG.GPIODATA, ChannelPos);
        break;

    case Dio_Port_C:
        return_Value = GET_BIT(PORTC_REG.GPIODATA, ChannelPos);
        break;
    case Dio_Port_D:
        return_Value = GET_BIT(PORTD_REG.GPIODATA, ChannelPos);
        break;
    case Dio_Port_E:
        return_Value = GET_BIT(PORTE_REG.GPIODATA, ChannelPos);
        break;
    case Dio_Port_F:
        return_Value = GET_BIT(PORTF_REG.GPIODATA, ChannelPos);
        break;
    default:
        break;
    }
    return return_Value;

}

/*
*Input: ChannelId -> to get pin on a port
*		Level -> level to write 		
*In/Out:
*Description: This function gets the value of a pin 
* 			  
*/
void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;
	
    switch(PortId)
    {
    case Dio_Port_A:
        if(Level == STD_low)
        {
            ClearBit(PORTA_REG.GPIODATA, ChannelPos);
        }
        else
        {
            SetBit(PORTA_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_B:
        if(Level == STD_low)
        {
            ClearBit(PORTB_REG.GPIODATA, ChannelPos);
        }
        else
        {
            SetBit(PORTB_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_C:
        if(Level == STD_low)
        {
            ClearBit(PORTC_REG.GPIODATA, ChannelPos);
        }
        else
        {
            SetBit(PORTC_REG.GPIODATA, ChannelPos);
        }
        break;
		
    case Dio_Port_D:
        if(Level == STD_low)
        {
            ClearBit(PORTD_REG.GPIODATA, ChannelPos);
        }
        else
        {
            SetBit(PORTD_REG.GPIODATA, ChannelPos);
        }
        break;
		
    case Dio_Port_E:
        if(Level == STD_low)
        {
            ClearBit(PORTE_REG.GPIODATA, ChannelPos);
        }
        else
        {
            SetBit(PORTE_REG.GPIODATA, ChannelPos);
        }
        break;
		
    case Dio_Port_F:
        if(Level == STD_low)
        {
            ClearBit(PORTF_REG.GPIODATA, ChannelPos);
        }
        else
        {
            SetBit(PORTF_REG.GPIODATA, ChannelPos);
        }
        break;
		
    default:
        break;
    }
}
/*
*Input: GPIO -> to get PORT name
*					
*Output: 
*In/Out:
*Return:  -> the acquired data wether it was PORT data
*Description: This function gets the value of a full port
* 			  
*/
uint8_t Dio_ReadPort(Dio_PortType PortId )
{
    uint8_t return_Value;
    switch(PortId)
    {
    case Dio_Port_A:
        return_Value = PORTA_REG.GPIODATA;
        break;

    case Dio_Port_B:
        return_Value = PORTB_REG.GPIODATA;
        break;

    case Dio_Port_C:
        return_Value = PORTC_REG.GPIODATA;
        break;
		
    case Dio_Port_D:
        return_Value = PORTD_REG.GPIODATA;
        break;
		
    case Dio_Port_E:
        return_Value = PORTE_REG.GPIODATA;
        break;
		
    case Dio_Port_F:
        return_Value = PORTF_REG.GPIODATA;
        break;
		
    default:
        break;
    }

    return return_Value;
}

/*
*Input: PortId -> to get PORT name
*		Level -> level to write 		
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
void Dio_WritePort( Dio_PortType PortId, uint8_t value)
{
    switch(PortId)
    {
    case Dio_Port_A:
        PORTA_REG.GPIODATA = value;
        break;
		
    case Dio_Port_B:
        PORTB_REG.GPIODATA = value;
        break;

    case Dio_Port_C:
        PORTC_REG.GPIODATA = value;
        break;
		
    case Dio_Port_D:
        PORTD_REG.GPIODATA = value;
        break;
		
    case Dio_Port_E:
        PORTE_REG.GPIODATA = value;
        break;
		
    case Dio_Port_F:
        PORTF_REG.GPIODATA = value;
        break;
		
    default:
        break;
    }
}

/*
*Input: ChannelId -> to get ChannelId
*		
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a pin
* 			  
*/
void Dio_FlipChannel( Dio_ChannelType ChannelId)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    switch(PortId)
    {
    case Dio_Port_A:
        ToggelBit(PORTA_REG.GPIODATA, ChannelPos);
        break;

    case Dio_Port_B:
        ToggelBit(PORTB_REG.GPIODATA, ChannelPos);
        break;

    case Dio_Port_C:
        ToggelBit(PORTC_REG.GPIODATA, ChannelPos);
        break;
		
    case Dio_Port_D:
        ToggelBit(PORTD_REG.GPIODATA, ChannelPos);
        break;
		
    case Dio_Port_E:
        ToggelBit(PORTE_REG.GPIODATA, ChannelPos);
        break;
		
    case Dio_Port_F:
        ToggelBit(PORTF_REG.GPIODATA, ChannelPos);
        break;
		
    default:
        break;
    }

}

/*
*Input: PortId -> to get port num
*		
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a port
* 			  
*/
void Dio_FlipPort(Dio_PortType PortId)
{
    switch(PortId)
    {
    case Dio_Port_A:
        PORTA_REG.GPIODATA = ~ PORTA_REG.GPIODATA;
        break;
		
    case Dio_Port_B:
        PORTB_REG.GPIODATA = ~PORTB_REG.GPIODATA;
        break;
		
    case Dio_Port_C:
        PORTC_REG.GPIODATA = ~PORTC_REG.GPIODATA;
        break;
		
    case Dio_Port_D:
        PORTD_REG.GPIODATA = ~PORTD_REG.GPIODATA;
        break;
		
    case Dio_Port_E:
        PORTE_REG.GPIODATA = ~PORTE_REG.GPIODATA;
        break;
		
    case Dio_Port_F:
        PORTF_REG.GPIODATA = ~PORTF_REG.GPIODATA;
        break;
		
    default:
        break;
    }
}



