/*
 * motor.c
 *
 * Created: 18/02/2020 05:24:12 م
 *  Author: TOSHIBA
 */ 

/*********************************************
 *				Includes  					 *
 ********************************************/
#include "motor.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/PWM/PWM.h"
                                                                                                                                                               /*********************************************
 /*				Defines  					 */
 /********************************************/                                                                                                                     
                                                                                                                                                                                                                                                                                                           

#define MOTOR_EN_1_PWM_CH   (PWM_CH1B)
#define MOTOR_EN_2_PWM_CH   (PWM_CH1A)


#define MOTOE_UNINTI (0)
#define MOTOE_INTI (1)
#define MOTOR_START (0x02)

#define MIN_SPEED		0
#define MAX_SPEED		100



						
static uint8_t Motor1_InitFlag=MOTOE_UNINTI;				 
static uint8_t Motor2_InitFlag=MOTOE_UNINTI;	
					  
	

u8_ERROR_STATUS_t Motor_Init(uint8_t u8_Motor_Number){
	uint8_t u8_MotorErrorStatus= E_OK;
	
	switch( u8_Motor_Number){
		case MOTOR_1	:
		if(Motor1_InitFlag == MOTOE_UNINTI)
		{
			 gstr_DIO_Cfg_t str_Motor1Info={GPIOD,MOTOR_EN_1_BIT|MOTOR_OUT_1A_BIT|MOTOR_OUT_1B_BIT,
											OUTPUT};
			DIO_init(&str_Motor1Info);
			Motor1_InitFlag=MOTOE_INTI;
			
		}
		else
		{
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT ;
		}
		break;
		case MOTOR_2 :
		if(Motor2_InitFlag == MOTOE_UNINTI)
		{
			static gstr_DIO_Cfg_t str_Motor2Info={GPIOD,MOTOR_EN_2_BIT|MOTOR_OUT_2A_BIT|MOTOR_OUT_2B_BIT,
												  OUTPUT};
			DIO_init(&str_Motor2Info);
			Motor2_InitFlag=MOTOE_INTI;
		}
		else
		{
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT ;
		}
		break;
		default:
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
		break;
	}
	return u8_MotorErrorStatus;
}

u8_ERROR_STATUS_t Motor_Direction(uint8_t u8_Motor_Number, uint8_t u8_Motor_Direction){
	uint8_t u8_MotorErrorStatus = E_OK;
	switch (u8_Motor_Number){
		case MOTOR_1 :
		if(Motor1_InitFlag ==  MOTOE_INTI)
		{
		switch (u8_Motor_Direction){
			
			case MOTOR_STOP :
			DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
			DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
			
			break;
			
			case MOTOR_FORWARD:
			DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
			DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
	
			break;
			
			case  MOTOR_BACKWARD:
			 DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
			 DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
			
			break;
			
			default:
			u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
			break;
		}
	
		}
		else
		{
			u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE;
		}
		break;
		
		case MOTOR_2 :
			if(Motor2_InitFlag ==  MOTOE_INTI)
			{
				switch (u8_Motor_Direction)
				{
					case MOTOR_STOP :
						DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
						DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
					break;
			
					case MOTOR_FORWARD:
						DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
						DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
					break;
			
					case  MOTOR_BACKWARD:
					
						DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
						DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
					break;
			
					default:
						u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR ;
					break;
				}
			}
			else
			{
				u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE;
			}
		break;
		
		default:
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE;
		break;
	}
	return u8_MotorErrorStatus;
}
u8_ERROR_STATUS_t Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed){
	uint8_t u8_MotorErrorStatus = E_OK;
	switch (u8_Motor_Number){
		case MOTOR_1 :
			if(Motor1_InitFlag ==  MOTOE_INTI)
			{
				if((u8_Mot_Speed >= MIN_SPEED) && (u8_Mot_Speed<= MAX_SPEED))
				{
					gstr_Pwm_Cfg_t str_Motor1_EN={MOTOR_EN_1_PWM_CH , PWM_PRESCALER_1024};
					Pwm_Init(&str_Motor1_EN);
					Pwm_Start(MOTOR_EN_1_PWM_CH,u8_Mot_Speed,FREQ_100_ );
					Motor1_InitFlag |= MOTOR_START;
				}
				
				else
				{
					u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER +  ERROR_INVALIDE_PARAMETAR;

				}
				
			}
			
			else
			{
				u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER +  ERROR_INVALIDE_PARAMETAR;

			}
		break;
		 
		case MOTOR_2 :
			if(Motor2_InitFlag ==  MOTOE_INTI)
		
			{
				if((u8_Mot_Speed >= MIN_SPEED) && (u8_Mot_Speed<= MAX_SPEED))	
				{
					static gstr_Pwm_Cfg_t str_Motor2_EN={MOTOR_EN_2_PWM_CH , PWM_PRESCALER_1024};
					Pwm_Init(&str_Motor2_EN);
					Pwm_Start(MOTOR_EN_2_PWM_CH,u8_Mot_Speed,FREQ_100_ );
					Motor2_InitFlag |= MOTOR_START;
				}
				else
				{
					u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER +  ERROR_INVALIDE_PARAMETAR;

				}
			}
			else
			{
				u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER +  ERROR_INVALIDE_PARAMETAR;

			}
		
		break;
		
		default:
			u8_MotorErrorStatus = MOTOR_MODULE_ERROR_NUMBER +  ERROR_INVALIDE_PARAMETAR;
		break;
	}
	return u8_MotorErrorStatus;
	
}
u8_ERROR_STATUS_t Motor_SpeedUpdate(uint8_t u8_Motor_Number, uint8_t u8_Speed){
	uint8_t u8_MotorErrorStatus = E_OK;
	switch (u8_Motor_Number){
		case MOTOR_1:
		if((Motor1_InitFlag & MOTOE_INTI) ==  MOTOE_INTI )
		{
			if((Motor1_InitFlag & MOTOR_START) ==  MOTOR_START)
			{	
				if((u8_Speed >= MIN_SPEED) && (u8_Speed<= MAX_SPEED))
				{
					Pwm_Start(MOTOR_EN_1_PWM_CH,u8_Speed,FREQ_100_ );
				}
				else
				{
					u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
				}
			}
			else
			{
				u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_MODULE_UNSTARTED;
			}
		}
		else
		{
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE ;
		}
		
		break;
		
		case MOTOR_2:
		if((Motor2_InitFlag & MOTOE_INTI) ==  MOTOE_INTI )
		{
			if((Motor2_InitFlag & MOTOR_START) ==  MOTOR_START)
			{
				if((u8_Speed >= MIN_SPEED) && (u8_Speed<= MAX_SPEED))
				{
					Pwm_Start(MOTOR_EN_2_PWM_CH,u8_Speed,FREQ_100_ );
				}
				else
				{
					u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
				}
			}
			else
			{
				u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_MODULE_UNSTARTED;
			}
		}
		else
		{
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE ;
		}
		break;
		
		default:
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
		break;
	}
	return u8_MotorErrorStatus;
}
u8_ERROR_STATUS_t Motor_Stop(uint8_t u8_Motor_Number){
	uint8_t u8_MotorErrorStatus = E_OK;
	switch (u8_Motor_Number){
		case MOTOR_1 :
		
		if((Motor1_InitFlag & MOTOE_INTI) ==  MOTOE_INTI )
		{
			if((Motor1_InitFlag & MOTOR_START) ==  MOTOR_START)
			{
			DIO_Write (MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
			DIO_Write (MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
			Motor1_InitFlag &=(~MOTOR_START);
			}
			else
			{
				u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_MODULE_UNSTARTED ;
			}
		}
		else
		{
			u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE ;
		}
			break;
			case MOTOR_2 :
				if((Motor2_InitFlag & MOTOE_INTI) ==  MOTOE_INTI )
				{
					if((Motor2_InitFlag & MOTOR_START) ==  MOTOR_START)
					{
						DIO_Write (MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
						DIO_Write (MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
						Motor2_InitFlag &=(~MOTOR_START);
					}
					else
					{
						u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_MODULE_UNSTARTED ;
					}
				}
				else
				{
					u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_MODULE ;
				}
			break;
			default:
				u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
			break;
	}
	return 	u8_MotorErrorStatus;
}
		
u8_ERROR_STATUS_t Motor_GetStatus(uint8_t u8_Motor_Number, uint8_t* pu8_Mot_status){
	uint8_t u8_MotorErrorStatus = E_OK;
	if(pu8_Mot_status != NULL)
	{
		switch (u8_Motor_Number){
			case MOTOR_1	 :
			* pu8_Mot_status= (Motor1_InitFlag & MOTOE_INTI);
					
			break;
			case  MOTOR_2 :
			* pu8_Mot_status= (Motor2_InitFlag & MOTOE_INTI);		
			break;
			
			default:
				u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR;
			break;
		}
	}
	else
	{
		u8_MotorErrorStatus= MOTOR_MODULE_ERROR_NUMBER + ERROR_NULL_PTR ;
	}
	return  u8_MotorErrorStatus;
}