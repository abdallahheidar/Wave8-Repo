/*
 * timer.c
 *
 * Created: 16/02/2020 10:10:56 م
 *  Author: TOSHIBA
 */ 

/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "timer.h"

/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/

//#define DEBBUGE 1
#ifdef  DEBBUGE
#define STATIC
#else
#define STATIC static
#endif

#define GENERAL_INTERRUPT_BIT (0x80)

#define INIT_MODULE			1
#define UNINIT_MODULE		0

#define Timer0_INIT_MASK		0x01
#define Timer1_INIT_MASK		0x02
#define Timer2_INIT_MASK		0x04
 
 #define EMPTY_REGISTER			0




/*#define timer 0*/
#define TIMER0_POLLING              (0)
#define TIMER0_INTERRUPT_NORMAL    (0x01)
#define TIMER0_NORMAL_MODE           (0)
#define COUNTER_FALLING_EDGE		0x06
#define COUNTER_RISSING_EDGE		0x07
#define TIMER0_TOV0_BIT				(0x01)
#define TIMER0_RESLUTION			(255)

/*   TIMER0_PRESCALER  */
#define TIMER0_NO_CLOCK       (0x00)
#define TIMER0_STOP           (0xf8)
#define TIMER0_PRESCALER_NO   (0x01)
#define TIMER0_PRESCALER_8    (0x02)
#define TIMER0_PRESCALER_64   (0x03)
#define TIMER0_PRESCALER_256  (0x04)
#define TIMER0_PRESCALER_1024 (0x05)

//TIMER1
#define TIMER1_TOV1_BIT       (0x04)
#define TIMER1_NORMAL_MODE         (0x00)
#define TIMER1_INTERRUPT_NORMAL (0x04)
#define TIMER1_RESLUTION        (65535)
#define TIMER1_MASK_DIS_EN_I        (0xC3)


/*   TIMER1_PRESCALER  */
#define TIMER1_NO_CLOCK       (0x0000)
#define TIMER1_STOP           (0xfff8)
#define TIMER1_PRESCALER_NO   (0x0001)
#define TIMER1_PRESCALER_8    (0x0002)
#define TIMER1_PRESCALER_64   (0x0003)
#define TIMER1_PRESCALER_256  (0x0004)
#define TIMER1_PRESCALER_1024 (0x0005)

//TIMER2 
#define TIMER2_TOV2_BIT         (0x40)
#define TIMER2_INTERRUPT_NORMAL (0x40)
#define TIMER2_NORMAL_MODE      (0x00)
#define TIMER2_RESLUTION        (255)




/*   TIMER2_PRESCALER  */
#define TIMER2_NO_CLOCK      (0X00)
#define TIMER2_STOP           (0xf8)
#define TIMER2_PRESCALER_NO  (0x01)
#define TIMER2_PRESCALER_8   (0x02)
#define TIMER2_PRESCALER_32  (0x03)
#define TIMER2_PRESCALER_64  (0x04)
#define TIMER2_PRESCALER_128 (0x05)
#define TIMER2_PRESCALER_256 (0x06)
#define TIMER2_PRESCALER_1024 (0x07)


 
STATIC uint8_t gu8_PrescalerTimer0=0;
STATIC uint8_t gu8_PrescalerTimer1=0;
STATIC uint8_t gu8_PrescalerTimer2=0;
STATIC uint8_t u8_TimerInitFLag = UNINIT_MODULE;

static void (* p_TOV_0_INT) (void) =NULL;
static void (* p_TOV_1_INT) (void) =NULL;
static void (* p_TOV_2_INT) (void) =NULL;

/*
 * @param: input:  gstrTimerConfig_t *
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Initializes the Timer   
 */

extern u8_ERROR_STATUS_t Timer_Init( gstrTimerConfig_t* pstrTimerConf)
{
	u8_ERROR_STATUS_t TimerErrorStatus=E_OK ;
	uint8_t u8_InitStause =  INIT_MODULE;
	if(pstrTimerConf!=NULL)
	{
		switch(pstrTimerConf->u8_TimerCh)
		{
			case TIMER_CH_0:
				if((u8_TimerInitFLag & Timer0_INIT_MASK) == UNINIT_MODULE)
				{
					TCCR0 = 0x00;
					TCNT0 = 0x00;
					SET_BIT(TIFR,TIMER0_TOV0_BIT);
					TCCR0|=TIMER0_NORMAL_MODE;
					switch(pstrTimerConf->u8_Timer_INT_Mode)
					{
						case TIMER_MODE_INT :
						
							if(pstrTimerConf-> p_TOV_INT != NULL)
							{
								TIMSK|=TIMER0_INTERRUPT_NORMAL;
								p_TOV_0_INT=pstrTimerConf-> p_TOV_INT;
								SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
							}
							else 
							{
								TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
								u8_InitStause =  UNINIT_MODULE;
							}
						
						break;
						case TIMER_MODE_POOLING :
							TIMSK&=~(TIMER0_INTERRUPT_NORMAL);
						break;
						default:
							TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_INT_MODE;
							u8_InitStause =  UNINIT_MODULE;
						break;
					}
			
					switch (pstrTimerConf->u8_TimerMode)
					{
						case COUNTER_MODE_FALLING_EDGE:
					
							TCCR0|= COUNTER_FALLING_EDGE;
						
						break;
						case COUNTER_MODE_RISSING_EDGE:
					
							TCCR0|= COUNTER_RISSING_EDGE;
						
						break;
						case TIMER_MODE :
							switch (pstrTimerConf->u8_TimerPrescaler){
						
								case TIMER_NO_CLOCK :
									gu8_PrescalerTimer0=TIMER0_NO_CLOCK;
								break;
								case TIMER_PRESCALER_NO	 :
									gu8_PrescalerTimer0=TIMER0_PRESCALER_NO;
								break;
						
								case TIMER_PRESCALER_8:
									gu8_PrescalerTimer0=TIMER0_PRESCALER_8;
								break;
						
								case TIMER_PRESCALER_64 :
									gu8_PrescalerTimer0=TIMER0_PRESCALER_64;
								break ;
						
								case TIMER_PRESCALER_256 :
									gu8_PrescalerTimer0=TIMER0_PRESCALER_256;
								break;
						
								case TIMER_PRESCALER_1024 :
									gu8_PrescalerTimer0=TIMER0_PRESCALER_1024;
								break;
						
								default:
									TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler ;
									u8_InitStause =  UNINIT_MODULE;
								break;
						
							}
						break;	
					
						default:
							TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_Mode;
							u8_InitStause =  UNINIT_MODULE;
						break;
				
					}
					u8_TimerInitFLag |= (Timer0_INIT_MASK * u8_InitStause);
				}
				else 
				{
					TimerErrorStatus=  TIMER_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT ;
				}
			break;
			case TIMER_CH_1 :
			
				if((u8_TimerInitFLag & Timer1_INIT_MASK) == UNINIT_MODULE)
				
				{
					TCCR1=0;
					TCNT1=0;
					SET_BIT(TIFR,TIMER1_TOV1_BIT);
					TCCR1 |=TIMER1_NORMAL_MODE;
					switch(pstrTimerConf->u8_Timer_INT_Mode)
					{
						case TIMER_MODE_INT :
							if(pstrTimerConf-> p_TOV_INT != NULL)
							{
								TIMSK|=TIMER1_INTERRUPT_NORMAL;
								p_TOV_1_INT=pstrTimerConf-> p_TOV_INT;
								SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
							}
							else
							{
								TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
								u8_InitStause =  UNINIT_MODULE;
							}
						break;
						case TIMER_MODE_POOLING :
							TIMSK&=~(TIMER1_INTERRUPT_NORMAL);
						break;
						default:
							TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_INT_MODE;
							u8_InitStause =  UNINIT_MODULE;
						break;
					}
					
					switch (pstrTimerConf->u8_TimerMode)
					{
					
						case COUNTER_MODE_FALLING_EDGE:
				
							TimerErrorStatus=E_NOK ;
							u8_InitStause =  UNINIT_MODULE;
						break;
				
						case COUNTER_MODE_RISSING_EDGE:
							TimerErrorStatus=E_NOK ;
							u8_InitStause =  UNINIT_MODULE;
						break;
						case  TIMER_MODE :

							switch (pstrTimerConf->u8_TimerPrescaler)
							{

								case TIMER_NO_CLOCK :
									gu8_PrescalerTimer1 = TIMER1_NO_CLOCK;
								break;
							
								case TIMER_PRESCALER_NO	 :
									gu8_PrescalerTimer1=TIMER1_PRESCALER_NO;
								break;
							
								case TIMER_PRESCALER_8:
									gu8_PrescalerTimer1=TIMER1_PRESCALER_8;
								break;
							
								case TIMER_PRESCALER_64 :
									gu8_PrescalerTimer1=TIMER1_PRESCALER_64;
								break ;
							
								case TIMER_PRESCALER_256 :
									gu8_PrescalerTimer1=TIMER1_PRESCALER_256;
								break;
							
								case TIMER_PRESCALER_1024:
									gu8_PrescalerTimer1=TIMER1_PRESCALER_1024;
								break;
							
								default:
									TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler ;
									u8_InitStause =  UNINIT_MODULE;
								break;
							
							}
							break;
						default:
							u8_InitStause =  UNINIT_MODULE;
							TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_Mode;
						break;
					}
					u8_TimerInitFLag |= (Timer1_INIT_MASK *u8_InitStause );
				}
				else
				{
					TimerErrorStatus=  TIMER_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT ;
				}
			break;
		
			case TIMER_CH_2 :
				if((u8_TimerInitFLag & Timer2_INIT_MASK) == UNINIT_MODULE)
				{
					TCCR2 = 0x00;
					TCNT2 = 0x00;
					ASSR=0;
					SET_BIT(TIFR,TIMER2_TOV2_BIT);
					TCCR2|=TIMER2_NORMAL_MODE;
						switch(pstrTimerConf->u8_Timer_INT_Mode)
						{
							case TIMER_MODE_INT :
							if(pstrTimerConf-> p_TOV_INT != NULL)
							{
								TIMSK|=TIMER2_INTERRUPT_NORMAL;
								p_TOV_2_INT=pstrTimerConf-> p_TOV_INT;
								SET_BIT(SREG,GENERAL_INTERRUPT_BIT);
							}
							else
							{
								TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
								u8_InitStause =  UNINIT_MODULE;
							}
							break;
							case TIMER_MODE_POOLING :
								TIMSK&=~(TIMER2_INTERRUPT_NORMAL);
							break;
							default:
							TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_INT_MODE;
							u8_InitStause =  UNINIT_MODULE;
							break;
						}
					
						switch (pstrTimerConf->u8_TimerMode)
						{
					
							case COUNTER_MODE_FALLING_EDGE:
					
								TimerErrorStatus=E_NOK ;
								u8_InitStause =  UNINIT_MODULE;
							break;
							case COUNTER_MODE_RISSING_EDGE:
					
								TimerErrorStatus=E_NOK ;
								u8_InitStause =  UNINIT_MODULE;
							break;
				
							case  TIMER_MODE :
								switch (pstrTimerConf->u8_TimerPrescaler)
								{
					
								case TIMER_NO_CLOCK :
									gu8_PrescalerTimer2=TIMER2_NO_CLOCK;
								break;
									
								case TIMER_PRESCALER_NO	 :
									gu8_PrescalerTimer2=TIMER2_PRESCALER_NO;
								break;
					
								case TIMER_PRESCALER_8:
									gu8_PrescalerTimer2=TIMER2_PRESCALER_8;
								break;
					
								case TIMER_PRESCALER_32	:
									gu8_PrescalerTimer2=TIMER2_PRESCALER_32;
								break;
					
								case TIMER_PRESCALER_64 :
									gu8_PrescalerTimer2=TIMER2_PRESCALER_64;
								break ;
					
					
								case TIMER_PRESCALER_128 :
									gu8_PrescalerTimer2=TIMER2_PRESCALER_128;
								break;
					
								case TIMER_PRESCALER_256 :
									gu8_PrescalerTimer2=TIMER2_PRESCALER_256;
								break;
					
								case TIMER_PRESCALER_1024:
									gu8_PrescalerTimer2=TIMER2_PRESCALER_1024;
								break;
					
								default:
									TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler ;
									u8_InitStause =  UNINIT_MODULE;
								break;
					
								}
								break;
							default:
							TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_Mode;
							u8_InitStause =  UNINIT_MODULE;
							break;
						}
				
					u8_TimerInitFLag |= (Timer2_INIT_MASK *u8_InitStause ) ;
				}
				else
				{
					TimerErrorStatus=  TIMER_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT ;
				}
			break;
			
			default:
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL;
			break;
 		}
	}
else 
{
	TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
}
	
return TimerErrorStatus;
}
/*
 * @param: input: u8_TimerCh  :Timer Channel 
 * @param: input: u16_CountNO : Number of ticks 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Sets timer prescaler  and initials value     
 */
extern u8_ERROR_STATUS_t Timer_Start (uint8_t u8_TimerCh,uint16_t u16_CountNO)
{
	u8_ERROR_STATUS_t TimerErrorStatus = E_OK ;
	
	uint8_t u8_register_status = EMPTY_REGISTER ;
	
	switch(u8_TimerCh){
		
		case  TIMER_CH_0 :
		
			if((u8_TimerInitFLag & Timer0_INIT_MASK) == Timer0_INIT_MASK)
			{
				if (u16_CountNO<= TIMER0_RESLUTION)
				{
					
					TCNT0=(TIMER0_RESLUTION-u16_CountNO);
					TCCR0|=	gu8_PrescalerTimer0;
					
				}
				
				else
 					TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;

			}
			
		break;
		
		case TIMER_CH_1:
			if((u8_TimerInitFLag & Timer1_INIT_MASK) == Timer1_INIT_MASK)
			{
				u8_register_status = TIMSK;
				TIMSK&=TIMER1_MASK_DIS_EN_I ;
				TCNT1 =(TIMER1_RESLUTION-u16_CountNO);
				TCCR1|=gu8_PrescalerTimer1;
				TIMSK=u8_register_status;
			}
			
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;

			}
		
		break;
		
		
		case  TIMER_CH_2:
			
			if((u8_TimerInitFLag & Timer2_INIT_MASK) == Timer2_INIT_MASK)
			{
				if (u16_CountNO<=TIMER2_RESLUTION)
				{
					//there is special case if the timer is in counter mode not handle
					
					TCNT2=(TIMER2_RESLUTION-u16_CountNO);
					TCCR2|=	gu8_PrescalerTimer2;
					
				}
				else
				{
					TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
				}
				
			}
			
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;

			}
		break;
		
		default:
			TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL ;
		break;
	}
return TimerErrorStatus;
	
}
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Stops the timer      
 */

extern u8_ERROR_STATUS_t Timer_Stop(uint8_t u8_TimerCh)
{
	u8_ERROR_STATUS_t TimerErrorStatus = E_OK ;
	switch(u8_TimerCh)
	{
		case TIMER_CH_0:
			
			if((u8_TimerInitFLag & Timer0_INIT_MASK) == Timer0_INIT_MASK)
			{
				TCCR0&=TIMER0_STOP;
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
				
			break;
		
		case TIMER_CH_1:
			if((u8_TimerInitFLag & Timer1_INIT_MASK) == Timer1_INIT_MASK)
			{
				//TCCR1 &= TIMER1_STOP;//wrong implementatin
				TCCR1 &= TIMER1_STOP;

			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;

			}
				
			break;
		
		case TIMER_CH_2:
			if((u8_TimerInitFLag & Timer2_INIT_MASK) == Timer2_INIT_MASK)
			{
				TCCR2&=TIMER2_STOP;
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
				
			break;
				
			default:
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL ;
			break;
		}
	return TimerErrorStatus;
}
	
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: output: Timer count value 
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Gets timer value      
 */

extern u8_ERROR_STATUS_t Timer_GetValue(uint8_t u8_TimerCh,uint16_t *pu16_TimerValue)
{
	u8_ERROR_STATUS_t TimerErrorStatus = E_OK ;
	if(pu16_TimerValue != NULL)
	{
		uint8_t u8_TIMSK_StatusRegister = EMPTY_REGISTER;
		switch(u8_TimerCh){
			case TIMER_CH_0 :
				if((u8_TimerInitFLag & Timer0_INIT_MASK) == Timer0_INIT_MASK)
				{
					*pu16_TimerValue = TCNT0;
				}
				else
				{
					TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
				}
			break;
			
			case TIMER_CH_1 :
			
			if((u8_TimerInitFLag & Timer1_INIT_MASK) == Timer1_INIT_MASK)
			{
				u8_TIMSK_StatusRegister=TIMSK;
				TIMSK&=TIMER1_MASK_DIS_EN_I ;
				*pu16_TimerValue=TCNT1;
				TIMSK=u8_TIMSK_StatusRegister;
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
			break;
			
			case TIMER_CH_2 ://there is special case in counter mode ASSR Note handle
			if((u8_TimerInitFLag & Timer2_INIT_MASK) == Timer2_INIT_MASK)
			{
				*pu16_TimerValue=TCNT2;
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
			break;
			
			default:
			TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL ;
			break;
		}
	}
	else
	{
		TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
	}	
	return TimerErrorStatus ;
}

/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: input: u16_TimerValue :Timer value 
 * @param: output: None
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Sets timer value      
 */

extern u8_ERROR_STATUS_t Timer_SetValue(uint8_t TimerCh,uint16_t u16_TimerValue){
	
	u8_ERROR_STATUS_t TimerErrorStatus = E_OK ;
   
   uint8_t u8_TIMSK_StatusRegister = 0;
   switch(TimerCh)
   {
	case TIMER_CH_0  :
		if((u8_TimerInitFLag & Timer0_INIT_MASK) == Timer0_INIT_MASK)
		{
			if (u16_TimerValue<=TIMER0_RESLUTION)
			{
				TCNT0 = u16_TimerValue;
			}
			else
			{
					
				TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
			}
		}
		else
		{
			TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
		}
		break; 
		
		case TIMER_CH_1:
			if((u8_TimerInitFLag & Timer1_INIT_MASK) == Timer1_INIT_MASK)
			{
					u8_TIMSK_StatusRegister=TIMSK;
					TIMSK&=TIMER1_MASK_DIS_EN_I ;
					TCNT1 =u16_TimerValue;
					TIMSK=u8_TIMSK_StatusRegister;
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
		break;
		
		case TIMER_CH_2 :
			if((u8_TimerInitFLag & Timer2_INIT_MASK) == Timer2_INIT_MASK)
			{
			
				if (u16_TimerValue<=TIMER2_RESLUTION)
				{ 
					TCNT2 = u16_TimerValue;	
				}
				
				else
				{
					TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
				}
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
		break;
			
		default:
			TimerErrorStatus = TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL;
		break;
	}
	return TimerErrorStatus;
}

	
/*
 * @param: input: u8_TimerCh  :Timer Channel  
 * @param: output: *pu8_TimerStatus :Timer overflow Interrupt status 
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Timer overflow Interrupt status      
 */

extern u8_ERROR_STATUS_t Timer_GetStatus(uint8_t u8_TimerCh,uint8_t *pu8_TimerStatus)
{
	u8_ERROR_STATUS_t TimerErrorStatus = E_OK ;
	if(pu8_TimerStatus != NULL)
	{
		switch(u8_TimerCh)
		{
			
			case TIMER_CH_0 :
			if((u8_TimerInitFLag & Timer0_INIT_MASK) == Timer0_INIT_MASK)
			{
				*pu8_TimerStatus=READ_BIT(TIFR,TIMER0_TOV0_BIT);
				SET_BIT(TIFR,TIMER0_TOV0_BIT);
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
			break;
			
			case TIMER_CH_1:
			if((u8_TimerInitFLag & Timer1_INIT_MASK) == Timer1_INIT_MASK)
			{
				*pu8_TimerStatus=READ_BIT(TIFR,TIMER1_TOV1_BIT);
				SET_BIT(TIFR,TIMER1_TOV1_BIT);
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
			break;
			
			case TIMER_CH_2:
			if((u8_TimerInitFLag & Timer2_INIT_MASK) == Timer2_INIT_MASK)
			{
				*pu8_TimerStatus=READ_BIT(TIFR,TIMER2_TOV2_BIT);
				SET_BIT(TIFR,TIMER2_TOV2_BIT);
				//SET_BIT(TIFR,TIMER2_TOV2_BIT);//why
			}
			else
			{
				TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER ;
			}
			break;
			
			
			default:
			TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL;
			break;
			
		}
	}
	else
	{
		TimerErrorStatus= TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
	}
	
	return TimerErrorStatus;

}


MY_ISR(TIMER0_OVF_vect){
	if ( p_TOV_0_INT!=NULL)
	{
		 p_TOV_0_INT();
	}
	
}
MY_ISR(TIMER1_OVF_vect){
	
	if ( p_TOV_1_INT!=NULL)
	{
		p_TOV_1_INT();
	}
	
}

MY_ISR(TIMER2_OVF_vect)
{
	if ( p_TOV_2_INT!=NULL)
	{
		p_TOV_2_INT();
	}
}