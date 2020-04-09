/*
 * PortDriver.c
 *
 * Created: 4/8/2020 6:28:44 PM
 *  Author: Khaled
 */ 

/**********************************************************/
/************************ INCLUDES ************************/
/**********************************************************/
#include "PortDriver.h" 
 
/**********************************************************/
/****************** GPIO REGISTER MAPING ******************/
/**********************************************************/ 
typedef struct
{
    uint32_t GPIODATA         ;
    uint8_t  REserved[0x3FC]  ; /*offset: 0x04 -> 0x3FC*/
    uint32_t GPIODIR          ;
    uint32_t GPIOIS           ;
    uint32_t GPIOIBE          ;
    uint32_t GPIOIEV          ;
    uint32_t GPIOIM           ;
    uint32_t GPIORIS          ;
    uint32_t GPIOMIS          ;
    uint32_t GPIOICR          ;
    uint32_t GPIOAFSEL        ; 
    uint8_t  Reserved_2[0xDC] ; /*offset : 0x424 -> 0x500*/
    uint32_t GPIODR2R         ; 
    uint32_t GPIODR4R         ;
    uint32_t GPIODR8R         ;
    uint32_t GPIOODR          ;
    uint32_t GPIOPUR          ;
    uint32_t GPIOPDR          ;
    uint32_t GPIOSLR          ;
    uint32_t GPIODEN          ;
    uint32_t GPIOLOCK         ;
    uint32_t GPIOCR           ;
    uint32_t GPIOAMSEL        ;
    uint32_t GPIOPCTL         ;
    uint32_t GPIOADCCTL       ;
    uint32_t GPIODMACTL       ;
}PORT_RegType;

#define PORT_A      ( PORT_RegType*)BASE_ADDRESS_A
#define PORT_B      ( PORT_RegType*)BASE_ADDRESS_B
#define PORT_C      ( PORT_RegType*)BASE_ADDRESS_C
#define PORT_D      ( PORT_RegType*)BASE_ADDRESS_D
#define PORT_E      ( PORT_RegType*)BASE_ADDRESS_E
#define PORT_F      ( PORT_RegType*)BASE_ADDRESS_F

/**********************************************************/
/************************* MACROS *************************/
/**********************************************************/
#define NUM_OF_CHANNELS                                     8
#define NUM_OF_PORTS 6
																			   
#define CFG_ST_COUNTER_INITIAL_VALUE                        0
#define TEMP_VALUE_INITIAL_VALUE                            0 

#define BASE_ADDRESS_A                                      0x40004000
#define BASE_ADDRESS_B                                      0x40005000
#define BASE_ADDRESS_C                                      0x40006000
#define BASE_ADDRESS_D                                      0x40007000
#define BASE_ADDRESS_E                                      0x40024000
#define BASE_ADDRESS_F                                      0x4005D000

#define EXT_INTERRUPT_DETECT_FACTOR                         10
#define EXT_INTERRUPT_LEVEL_DETECT                          2
#define EXT_INTERRUPT_EDGE_DETECT                           1

#define GPIO_UNLOCK_VALUE                                   0x4C4F434B
#define GPIO_LOCK_VALUE                                     0X0125346D
/**********************************************************/
/******************** EXTERN VARIABLES ********************/
/**********************************************************/
extern PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS];

/**********************************************************/
/******************** GLOBAL VARIABLES ********************/
/**********************************************************/ 
 static volatile  PORT_RegType* U32ARR_BaseAddrArr[NUM_OF_PORTS] = { PORT_A,
                                                                     PORT_B,
                                                                     PORT_C,
                                                                     PORT_D,
                                                                     PORT_E,
                                                                     PORT_F };                                      
/**********************************************************/
/******************* APIS IMPLEMENTATION ******************/
/**********************************************************/                                    
void PortDriver_init (void)
{
    uint8_t                   au8_CfgStCounter  = CFG_ST_COUNTER_INITIAL_VALUE;
    uint32_t                  au32_TempValue    = TEMP_VALUE_INITIAL_VALUE;
    PortDriver_PortNumType    au8_PortNum       = NUM_OF_PORTS;
    PortDriver_ChannelNumType au8_ChannelOffset = NUM_OF_CHANNELS;        
    


        

    
    for(au8_CfgStCounter = CFG_ST_COUNTER_INITIAL_VALUE; au8_CfgStCounter < NUM_OF_ACTIVATED_CHANNELS; au8_CfgStCounter++)
    {
        au8_PortNum = PortDriver_CfgArr[au8_CfgStCounter].Channel / NUM_OF_CHANNELS;  /*determine the channel PORT*/

        au8_ChannelOffset = PortDriver_CfgArr[au8_CfgStCounter].Channel % NUM_OF_CHANNELS; /*determine the channel pin*/

        /*TODO: UNLOCK GPIO AND COMMITTED*/
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOLOCK = GPIO_UNLOCK_VALUE ;

        au32_TempValue = ( 1 << au8_ChannelOffset );
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOCR |= au32_TempValue;
        
        /*** CONFIGURE PIN DIRECTION ***/
        /*
         * GPIODIR reg bits 0:7, each bit represent pin direction in the port (0:INPUT,  1:OUTPUT)
         */
        au32_TempValue = ( (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Direction) << (au8_ChannelOffset));  /*calculate pin direction mask*/
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODIR |= au32_TempValue;  /*store pin direction in the proper bit in proper register*/
        
        /*** SELECT PIN FUNCTION(DIO / ALTERTNATIVE FUNCTION) ***/
        /*
         * GPIOAFSEL reg bits 0:7, each bit represent pin ALTERNATIVE function enable in the port (0:DIO,  1:ALTERNATIVE)
         * GPIOPCTL reg bits 0:31, each half-byte (4-bits) represent Pin ALTERNATIVE function, each pin has different value for different function
         */
        if (PORTDRIVER_CHANNEL_FUNCTION_X_DIO == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Function)
        {
            /* clear proper bit in GPIOAFSEL register to select DIO function*/
            au32_TempValue = ~( 1 << au8_ChannelOffset );  /*calculate pin DIO function mask*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOAFSEL &= au32_TempValue; /*store pin DIO function value in the proper bit in proper GPIOAFSEL register*/
        } 
        else
        {
            /* set proper bit in GPIOAFSEL register to select ALTERNATIVE function*/
            au32_TempValue = ( 1 << au8_ChannelOffset );  /*calculate pin function mask*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOAFSEL |= au32_TempValue; /*store pin ALTERNATIVE function value in the proper bit in proper GPIOAFSEL register*/
            
            /* store proper value in proper field in GPIOPCTL register to select desired function*/
            au32_TempValue = ( 0xF << au8_ChannelOffset); /*calculate bits mask*/
            au32_TempValue |= (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPCTL; /*mask proper half-byte(4-bits)*/
            au32_TempValue &= (((PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Function) << au8_ChannelOffset) | 0xFFFFFFFF); /*store function value in proper bits*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPCTL = au32_TempValue; /*store function value in proper field in proper GPIOPCTL register*/
        }
        
        //GPIOADCCTL : ADC   for future implementation
        //GPIOMACTL : uDMA   for future implementation
        
        /*** CONFIGERATE PIN PROPERTIES ***/
        /*
         *
         *
         *
         *
         */
        /*select drive strength*/
        au32_TempValue = ( 1 << au8_ChannelOffset );  /*calculate pin mask*/

        switch (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Current_mA)
        {
            case PORTDRIVER_CHANNEL_CURRENT_mA_2:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODR2R |= au32_TempValue; /*configure the pin to 2 mA*/
            break;

            case PORTDRIVER_CHANNEL_CURRENT_mA_4:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODR4R |= au32_TempValue; /*configure the pin to 4 mA*/
            break;

            case PORTDRIVER_CHANNEL_CURRENT_mA_8:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODR8R |= au32_TempValue; /*configure the pin to 8 mA*/
            break;

            default:
            break;

        }
        
        /*selsect pin pad*/
        switch (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Attachment)
        {
            case PORTDRIVER_CHANNEL_ATTACHMENT_NOTCONNECTED:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOODR &= ~(au32_TempValue) ;
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPDR &= ~(au32_TempValue) ;
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPUR &= ~(au32_TempValue) ;
            break;

            case PORTDRIVER_CHANNEL_ATTACHMENT_PULLUPRES:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPUR |= au32_TempValue ;
            break;
            
            case PORTDRIVER_CHANNEL_ATTACHMENT_PULLDOWNRES:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPDR |= au32_TempValue ;
            break;
            
            case PORTDRIVER_CHANNEL_ATTACHMENT_OPENDRAIN:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOODR |= au32_TempValue;

            /*enable/disable slew rate*/
            if (PORTDRIVER_CHANNEL_SLEWRATE_ENABLE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_SlewRate)
            {
                (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOSLR |= au32_TempValue;
            }
            break;
            
            default:
            break;
        }

        
        /*TODO: SELECT PIN OPERATION MODE*/
        //MOVE THIS POINT TO PIN FUNCTION
        //GPIODEN
        //GPIOAMSEL
        
        /*** CONFIGURE INTERRUPT CONTROL ***/
        if (PORTDRIVER_CHANNEL_EXTI_DISABLE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
        {
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIM &= ~(au32_TempValue) ;
        }
        else
        {
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIM |= au32_TempValue ;

            if (EXT_INTERRUPT_EDGE_DETECT == (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti / EXT_INTERRUPT_DETECT_FACTOR))
            {
                (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIS &= ~(au32_TempValue);

                if(PORTDRIVER_CHANNEL_EXTI_BOTH_EDGE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                {
                    (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIBE |= au32_TempValue;
                }

                else
                {
                    (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIBE &= ~(au32_TempValue);

                    if(PORTDRIVER_CHANNEL_EXTI_RISIN_GEDGE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                    {
                        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIEV |= au32_TempValue;
                    }

                    else if (PORTDRIVER_CHANNEL_EXTI_FALLIN_GEDGE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                    {
                        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIEV &= ~(au32_TempValue);
                    }
                }

            } 
            else if (EXT_INTERRUPT_LEVEL_DETECT == (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti / EXT_INTERRUPT_DETECT_FACTOR))
            {
                (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIS |= au32_TempValue;
            }
        }
        
        
        /*TODO: LOCK GPIO AND UNCOMMITTED*/
        au32_TempValue = ~( 1 << au8_ChannelOffset );
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOCR |= au32_TempValue;
        
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOLOCK = GPIO_LOCK_VALUE ;
        
        
   
    }
    

}
