/*
 * DIO.c
 *
 * Created: 2/15/2020 5:58:35 PM
 *  Author: Khaled Aladawy
 */ 

 #include "DIO.h"
 
 ERROR_STATUS DIO_init (DIO_Cfg_s * DIO_info)
 {
    /*variable to store errors*/
	 uint8_t Error = E_OK;

	 /*check if the given pointer is NULL return error*/
	 if (NULL == DIO_info)
	 {
	    Error |=  E_NOK;
	 }
	 
	 else
	 {
	    switch (DIO_info->GPIO)
	    {
		   case GPIOA:
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
   		break;
         /*************************************************************************************************************************/		
   		case GPIOB:
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
   		break;
		   /********************************************************************************************************************************/
	   	case GPIOC:
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
   		break;
		   /*******************************************************************************************************************************/
   		case GPIOD:
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
   		break;
			/******************************************************************************************************************************/
			default:
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
		break;
		/*****************************************************************************************************************************/
		case GPIOB:
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
		break;
		/*****************************************************************************************************************************/
		case GPIOC:
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
		break;
		/********************************************************************************************************************************/
		case GPIOD:
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
		break;
		/*************************************************************************************************************************************/
		default:
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
	 }
	 else
	 {
	    switch (GPIO)
	    {
		    case GPIOA:
			 /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
		    if (ZERO < (PORTA_PIN & pins))
		    *data = HIGH;
		    else
		    *data = LOW;
		    break;
		    
		    case GPIOB:
			 /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
		    if (ZERO < (PORTB_PIN & pins))
		    *data = HIGH;
		    else
		    *data = LOW;
		    break;
		    
		    case GPIOC:
		    if (ZERO < (PORTC_PIN & pins))
		    *data = HIGH;
		    else
		    *data = LOW;
		    break;
		    
		    case GPIOD:
			 /*Check if the desired pin LOW return 0 and if it HIGH return 255*/
		    if (ZERO < (PORTD_PIN & pins))
		    *data = HIGH;
		    else
		    *data = LOW;
		    break;

			 default:
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
		 /* xor the pin to change it's state*/
	    PORTA_DATA = PORTA_DATA ^ (pins);
	    break;
	    
	    case GPIOB:
		 /* xor the pin to change it's state*/
	    PORTB_DATA = PORTB_DATA ^ (pins);
	    break;
	    
	    case GPIOC:
		 /* xor the pin to change it's state*/
	    PORTC_DATA = PORTC_DATA ^ (pins);
	    break;
	    
	    case GPIOD:
		 /* xor the pin to change it's state*/
	    PORTD_DATA = PORTD_DATA ^ (pins);
	    break;

		 default:
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