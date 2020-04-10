#include "../includes/Port.h"
#include "../includes/Port_lCfg.h"
#include "../includes/MCU_hw.h"
#include "../../Services/includes/common_macros.h"

#define NUM_OF_CHANNELS_IN_PORT							8
#define GPIO_LOCK_MASK                      0x4cf434b

uint32_t BASEAddresses[]={
	GPIOPort_A_APB_BASE,
	GPIOPort_B_APB_BASE,
	GPIOPort_C_APB_BASE,
	GPIOPort_D_APB_BASE,
	GPIOPort_E_APB_BASE,
	GPIOPort_F_APB_BASE
	
};

void Port_Init(void)
{
	uint8_t i =ZERO,PORT_NUM;
	for(i=ZERO; i< NUM_OF_ACTIVATED_CHANNELS; i++)
	{
		PORT_NUM= PortDriver_CfgArr[i].Channel / NUM_OF_CHANNELS_IN_PORT;
		
		//Set the direction
		if(PortDriver_CfgArr[i].Channel == PortDriver_Channel_Direction_INPUT)
		{
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODIR_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		else if(PortDriver_CfgArr[i].Channel == PortDriver_Channel_Direction_OUTPUT)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODIR_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		//Set the alternative function
		GPIOREG(BASEAddresses[PORT_NUM],GPIOLOCK_OFFSET) = GPIO_LOCK_MASK;//UNLOCK the gpio commit
		CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOCR_OFFSET),PortDriver_CfgArr[i].Channel);// gpio Commit
		
		//Set af select val
		if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DIO)
		{
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOAFSEL_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		else
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOAFSEL_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		
		//Set the channel function
		if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_Analog)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOADCCTL_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		else if(PortDriver_CfgArr[i].PortDriver_Channel_Function == PortDriver_Channel_Function_X_DMA)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODMACTL_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		else
		{
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOADCCTL_OFFSET),PortDriver_CfgArr[i].Channel);
			CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODMACTL_OFFSET),PortDriver_CfgArr[i].Channel);
			GPIOREG(BASEAddresses[PORT_NUM],GPIOPCTL_OFFSET) |= PortDriver_CfgArr[i].PortDriver_Channel_Function <<PortDriver_CfgArr[i].Channel*4;
		}
		// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>In case adc or dma<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
		//current
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Current_mA)
		{
			case PortDriver_Channel_Current_mA_2:
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR2R_OFFSET),PortDriver_CfgArr[i].Channel);
			  CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR4R_OFFSET),PortDriver_CfgArr[i].Channel);
	  		CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR8R_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
			case PortDriver_Channel_Current_mA_4:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR2R_OFFSET),PortDriver_CfgArr[i].Channel);
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR4R_OFFSET),PortDriver_CfgArr[i].Channel);
	  		CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR8R_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
			case PortDriver_Channel_Current_mA_8:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR2R_OFFSET),PortDriver_CfgArr[i].Channel);
			  CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR4R_OFFSET),PortDriver_CfgArr[i].Channel);
	  		SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIODR8R_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
			default:
				//ERR
				break;
		}
		//Set the slew rate
		if(PortDriver_CfgArr[i].PortDriver_Channel_SlewRate == PortDriver_Channel_SlewRate_Disable)
		{
			 CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOSLR_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		else if(PortDriver_CfgArr[i].PortDriver_Channel_SlewRate == PortDriver_Channel_SlewRate_Enable)
		{
			SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOSLR_OFFSET),PortDriver_CfgArr[i].Channel);
		}
		else
		{
			//ERR
		}
		//attachment pull up/down
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Attachment)
		{
			case PortDriver_Channel_Attachment_NotConnected:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),PortDriver_CfgArr[i].Channel);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),PortDriver_CfgArr[i].Channel);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
			
		  case PortDriver_Channel_Attachment_PullDownRes:
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),PortDriver_CfgArr[i].Channel);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),PortDriver_CfgArr[i].Channel);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
			
		  case PortDriver_Channel_Attachment_PullupRes:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),PortDriver_CfgArr[i].Channel);
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),PortDriver_CfgArr[i].Channel);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
		  case PortDriver_Channel_Attachment_openDrain:		
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOODR_OFFSET),PortDriver_CfgArr[i].Channel);
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPUR_OFFSET),PortDriver_CfgArr[i].Channel);
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOPDR_OFFSET),PortDriver_CfgArr[i].Channel);
				break;
			default:
			//ERR
			break;
		}
		//interrupt
		switch(PortDriver_CfgArr[i].PortDriver_Channel_Exti)
		{
			case PortDriver_Channel_Exti_Disable:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//Mask the pin
				break;
			
			case PortDriver_Channel_Exti_LevelSense:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//Mask the pin
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),PortDriver_CfgArr[i].Channel);//Level sense
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIEV_OFFSET),PortDriver_CfgArr[i].Channel);//HIGH LEVEL sense
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//unmask the pin
				break;
			
			case PortDriver_Channel_Exti_FallingEdge:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//Mask the pin
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),PortDriver_CfgArr[i].Channel);//EDGE sense
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//unmask the pin
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIEV_OFFSET),PortDriver_CfgArr[i].Channel);//Falling EDGE sense
				break;
			
			case PortDriver_Channel_Exti_RisingEdge:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//Mask the pin
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),PortDriver_CfgArr[i].Channel);//EDGE sense
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//unmask the pin
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIEV_OFFSET),PortDriver_CfgArr[i].Channel);//Rising EDGE sense
				break;
			
			case PortDriver_Channel_Exti_BothEdge:
				CLR_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//Mask the pin
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIS_OFFSET),PortDriver_CfgArr[i].Channel);//EDGE sense
			  SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIBE_OFFSET),PortDriver_CfgArr[i].Channel);//BOTH Edge
				SET_BIT(GPIOREG(BASEAddresses[PORT_NUM],GPIOIM_OFFSET),PortDriver_CfgArr[i].Channel);//unmask the pin
				break;
			
			default:
				break;
		}
		
	}
}