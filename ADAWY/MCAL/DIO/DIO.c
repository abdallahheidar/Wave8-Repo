/*
 * DIO.c
 *
 * Created: 2/15/2020 5:58:35 PM
 *  Author: Khaled Aladawy
 */ 

 #include "DIO.h"
 static uint8_t gu8_PortA_State,gu8_PortB_State,gu8_PortC_State,gu8_PortD_State;
 
 ERROR_STATUS DIO_init (DIO_Cfg_s * DIO_info)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;

	 /*check if the given pointer is NULL return error*/
	 if (NULL == DIO_info)
	 {
	    Error |=  E_NOK;
		 Error_Push(DIO_MODULE,ERROR_NULL_POINTER);
	 }
	 
	 else
	 {
	    switch (DIO_info->GPIO)
	    {
		   case GPIOA:
			SET_BIT(gu8_PortA_State,DIO_info->pins);
	   	if (OUTPUT == DIO_info->dir)
		   /** 
	   	OR the Port direction value with pins to SET this pins without affect on other pins
	    	*/
	   	PORTA_DIR = PORTA_DIR | (DIO_info->pins);
		
	   	else if (INPUT== DIO_info->dir)
	   	/** 
   		AND the Port direction value with NOT pins to CLEAR this pins without affect on other pins
   		*/
	   	PORTA_DIR = PORTA_DIR & (~(DIO_info->pins));

			else
			{
			   Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
				Error |= E_NOK;
			}
   		break;
         /*************************************************************************************************************************/		
   		case GPIOB:
			SET_BIT(gu8_PortB_State,DIO_info->pins);
	   	if (OUTPUT == DIO_info->dir)
		   /** 
   		OR the Port direction value with pins to SET this pins without affect on other pins 
	   	*/ 
   		PORTB_DIR = PORTB_DIR | (DIO_info->pins);
		
   		else if (INPUT== DIO_info->dir)
   		/** 
   		AND the Port direction value with NOT pins to CLEAR this pins without affect on other pins
   		*/
   		PORTB_DIR = PORTB_DIR & (~(DIO_info->pins));
			else
			{
				Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
				Error |= E_NOK;
			}
   		break;
		   /********************************************************************************************************************************/
	   	case GPIOC:
			SET_BIT(gu8_PortC_State,DIO_info->pins);
   		if (OUTPUT == DIO_info->dir)
   		/** 
   		OR the Port direction value with pins to SET this pins without affect on other pins
   		*/
   		PORTC_DIR = PORTC_DIR | (DIO_info->pins);
		
   		else if (INPUT== DIO_info->dir)
	   	/** 
   		AND the Port direction value with NOT pins to CLEAR this pins without affect on other pins
   		*/
   		PORTC_DIR = PORTC_DIR & (~(DIO_info->pins));
			else
			{
				Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
				Error |= E_NOK;
			}
   		break;
		   /*******************************************************************************************************************************/
   		case GPIOD:
			SET_BIT(gu8_PortD_State,DIO_info->pins);
   		if (OUTPUT == DIO_info->dir)
   		/** 
   		OR the Port direction value with pins to SET this pins without affect on other pins
   		*/
   		PORTD_DIR = PORTD_DIR | (DIO_info->pins);
		
   		else if (INPUT== DIO_info->dir)
   		/** 
   		AND the Port direction value with NOT pins to CLEAR this pins without affect on other pins
   		*/
    		PORTD_DIR = PORTD_DIR & (~(DIO_info->pins));
			else
			{
				Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
				Error |= E_NOK;
			}
   		break;
			/******************************************************************************************************************************/
			default:
			Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
			Error |=  E_NOK;
			
			break;
  	   }
	 }
	 
	return Error;
 }


 ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
 {
	 /*variable to store errors*/
	 uint8_t Error = E_OK;
	 switch (GPIO)
	{
		case GPIOA:
		if ((GET_BIT(gu8_PortA_State,pins)) == pins)
		{
		   if (value == HIGH)
		   /** 
		   OR the Port DATA value with pins to SET this pins without affect on other pins
		   */
		   PORTA_DATA = PORTA_DATA | (pins);
		
		   else if (value == LOW)
		   /** 
		   AND the Port DATA value with NOT pins to CLEAR this pins without affect on other pins
		   */
		   PORTA_DATA = PORTA_DATA & (~(pins));
		   else
		   {
		      Error |= E_NOK;
		      Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
		   }
		}
		else
		{
		   Error |= E_NOK;
		   Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		}
		
		break;
		/*****************************************************************************************************************************/
		case GPIOB:
		if ((GET_BIT(gu8_PortB_State,pins)) == pins)
		{
		   if (value == HIGH)
		   /** 
		   OR the Port DATA value with pins to SET this pins without affect on other pins
		   */
		   PORTB_DATA = PORTB_DATA | (pins);
		
	   	else if (value == LOW)
		   /** 
		   AND the Port DATA value with NOT pins to CLEAR this pins without affect on other pins
		   */
		   PORTB_DATA = PORTB_DATA & (~(pins));

		   else
		   {
			   Error |= E_NOK;
			   Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
		   }
		}
		else
		{
			Error |= E_NOK;
			Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		}
		break;
		/*****************************************************************************************************************************/
		case GPIOC:
		if ((GET_BIT(gu8_PortC_State,pins)) == pins)
		{
		   if (value == HIGH)
		   /** 
	   	OR the Port DATA value with pins to SET this pins without affect on other pins
	   	*/
	   	PORTC_DATA = PORTC_DATA | (pins);
		
	   	else if (value == LOW)
		   /** 
		   AND the Port DATA value with NOT pins to CLEAR this pins without affect on other pins
		   */
		   PORTC_DATA = PORTC_DATA & (~(pins));

		   else
		   {
		   	Error |= E_NOK;
		   	Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
		   }
		}
		else
		{
			Error |= E_NOK;
			Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		}
		
		break;
		/********************************************************************************************************************************/
		case GPIOD:
		if ((GET_BIT(gu8_PortD_State,pins)) == pins)
		{
		    if (value == HIGH)
		    /** 
	    	OR the Port DATA value with pins to SET this pins without affect on other pins
		   */
		   PORTD_DATA = PORTD_DATA | (pins);
		
		   else if (value == LOW)
		   /** 
		   AND the Port DATA value with NOT pins to CLEAR this pins without affect on other pins
		   */
		   PORTD_DATA = PORTD_DATA & (~(pins));

		   else
		   {
		   	Error |= E_NOK;
		   	Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
		   }
		}
		else
		{
			Error |= E_NOK;
			Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		}
		
		break;
		/*************************************************************************************************************************************/
		default:
		Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
		Error |=  E_NOK;
		break;
	}
		return Error ;
 }


 ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t * data)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 
	 /*check if the pointer is NULL return error*/
	 if (NULL == data)
	 {
	    Error |=  E_NOK;
		 Error_Push(DIO_MODULE,ERROR_NULL_POINTER);
	 }
	 else
	 {
	    switch (GPIO)
	    {
		    case GPIOA:
			 if ((GET_BIT(gu8_PortA_State,pins)) == pins)
			 {
			    /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
			    if (ZERO < (PORTA_PIN & pins))
			    *data = HIGH;
			    else
			    *data = LOW;
			 }
			 else
			 {
			    Error |= E_NOK;
				 Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
			 }
		    break;
		    
		    case GPIOB:
			 if ((GET_BIT(gu8_PortB_State,pins)) == pins)
			 {
				 /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
				 if (ZERO < (PORTB_PIN & pins))
				 *data = HIGH;
				 else
				 *data = LOW;
			 }
			 else
			 {
				 Error |= E_NOK;
				 Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
			 }
		    break;
		    
		    case GPIOC:
			 if ((GET_BIT(gu8_PortC_State,pins)) == pins)
			 {
				 /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
				 if (ZERO < (PORTC_PIN & pins))
				 *data = HIGH;
				 else
				 *data = LOW;
			 }
			 else
			 {
				 Error |= E_NOK;
				 Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
			 }
		    break;
		    
		    case GPIOD:
			 if ((GET_BIT(gu8_PortD_State,pins)) == pins)
			 {
				 /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
				 if (ZERO < (PORTD_PIN & pins))
				 *data = HIGH;
				 else
				 *data = LOW;
			 }
			 else
			 {
				 Error |= E_NOK;
				 Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
			 }
		    break;

			 default:
			 Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
			 Error |=  E_NOK;
			 break;
	    }
	 }
	 
    
    return Error ;
 }


 ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 
	 switch (GPIO)
    {
	    case GPIOA:
		 if ((GET_BIT(gu8_PortA_State,pins)) == pins)
		 {
		    /* xor the pin to change it's state*/
		    PORTA_DATA = PORTA_DATA ^ (pins);
		 }
		 else
		 {
		    Error |= E_NOK;
		    Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		 }
	    break;
	    
	    case GPIOB:
		 if ((GET_BIT(gu8_PortB_State,pins)) == pins)
		 {
			 /* xor the pin to change it's state*/
			 PORTB_DATA = PORTB_DATA ^ (pins);
		 }
		 else
		 {
			 Error |= E_NOK;
			 Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		 }
		 break;
	    
	    case GPIOC:
		  if ((GET_BIT(gu8_PortC_State,pins)) == pins)
		  {
			  /* xor the pin to change it's state*/
			  PORTC_DATA = PORTC_DATA ^ (pins);
		  }
		  else
		  {
			  Error |= E_NOK;
			  Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		  }
	    break;
	    
	    case GPIOD:
		 if ((GET_BIT(gu8_PortD_State,pins)) == pins)
		 {
			 /* xor the pin to change it's state*/
			 PORTD_DATA = PORTD_DATA ^ (pins);
		 }
		 else
		 {
			 Error |= E_NOK;
			 Error_Push(DIO_MODULE,ERROR_NOT_INITIALIZED);
		 }
	    break;

		 default:
		 Error_Push(DIO_MODULE,ERROR_INVALID_PARAMETER);
		 Error |=  E_NOK;
		 break;
    }

	 return Error;
 }



 ERROR_STATUS DIO_Write_Port (uint8_t GPIO, uint8_t value)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;
	 switch (GPIO)
	{
		case GPIOA:
		PORTA_DATA = value;
		break;
		/*****************************************************************************************************************************/
		case GPIOB:
		PORTB_DATA = value;
		break;
		/*****************************************************************************************************************************/
		case GPIOC:
		PORTC_DATA = value;
		break;
		/********************************************************************************************************************************/
		case GPIOD:
		PORTD_DATA = value;
		break;
		/*************************************************************************************************************************************/
		default:
		Error |=  E_NOK;
		break;
	}
		return Error ;
 }