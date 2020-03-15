/*
 * LCD_APP.c
 *
 * Created: 3/15/2020 2:45:33 PM
 *  Author: Khaled
 */ 


#include "LCD_APP.h"
#include "../MCAL/DIO/DIO.h"

 #define CLEAR                           30
 #define PRINT_FIRST_LINE                CLEAR +1
 #define PRINT_SECOND_LINE               PRINT_FIRST_LINE +1 
 #define GET_QUE                         PRINT_SECOND_LINE +1
 #define SCOR                            GET_QUE +1
 #define GET_ANSWER                      SCOR +1
 #define CHECK_ANSWER                    GET_ANSWER +1
 #define RIGHT_ANSWER                    CHECK_ANSWER +1
 #define WRONG_ANSWER                    RIGHT_ANSWER +1



 #define QUE1                            WRONG_ANSWER +1
 #define QUE2                            QUE1 +1
 #define QUE3                            QUE2 +1
 #define QUE4                            QUE3 +1
 #define QUE5                            QUE4 +1
 #define QUE6                            QUE5 +1
 
 #define ANSWER_WAIT        30

 #define INTERNAL_STATUS_1  1
 #define INTERNAL_STATUS_2  2
 #define INTERNAL_STATUS_3  3
 #define INTERNAL_STATUS_4  4
 #define INTERNAL_STATUS_5  5

 uint8_t Q[11]="DO YOU KNOW";
 uint8_t q1[12]="CORONA VIRS?";
 uint8_t S[9] ="IS NORMAL";
 uint8_t q2[14]="MASK EFFICTIVE?";



 void LCD_APP (void)
 {
    static uint8_t au8_AppStatus = NOT_INITIALIZED;
	 static uint8_t au8_AppStatusNext = NOT_INITIALIZED;
	 static uint8_t au8_InetrnalStatus = NOT_INITIALIZED;
	 static uint8_t au8_CheckCounter = GET_QUE;
	 static uint8_t au8_Answer = NOT_INITIALIZED;
	 static uint8_t *PTR1 = NULL;
	 static uint8_t au8_QueSize1 = ZERO;
	 static uint8_t *PTR2 = NULL;
	 static uint8_t au8_QueSize2 = ZERO;
	 static uint8_t au8_QueNumber = 1;
	 uint8_t au8_ButtonStatus = NOT_INITIALIZED;
	 static uint8_t au8_Score = ZERO;
	 static uint8_t au8_WaitCounter = ZERO;
	  DIO_Cfg_s str_DIO_Info;
	  str_DIO_Info.dir = OUTPUT;
	  str_DIO_Info.GPIO = GPIOB;
	  str_DIO_Info.pins = BIT3|BIT4|BIT5|BIT6|BIT7;
	  DIO_init(&str_DIO_Info);

	 switch (au8_AppStatus)
	 {
	    case NOT_INITIALIZED:
		 if (INITIALIZED == gu8_LCD_InitFlag)
		 {
		    au8_AppStatus = PRINT_FIRST_LINE;
		 }
		 break;
		 /*******************************************************************************************************/
		 case CLEAR:
		 LCD_Clear();
		 LCD_Clear();
		 au8_AppStatus = au8_AppStatusNext;
	
		 break;
		 /*******************************************************************************************************/
       case PRINT_FIRST_LINE:
		 if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		 {
		    LCD_DisplayStringRowColumn("HELLO USER",10,0);
		 } 
		 else
		 {
		    au8_AppStatus = PRINT_SECOND_LINE;
			 gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
		 }
		 break;
		 /*******************************************************************************************************/
		 case PRINT_SECOND_LINE:
		 if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		 {
			 LCD_DisplayStringRowColumn("R U READY",9,16);
			 
		 }
		 else
		 {
			 gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
			 au8_AppStatusNext = GET_QUE;
			 au8_AppStatus = CLEAR;
			 
		 }
		 break;

		 
			 /****************************************************************************************************************/
			 case GET_ANSWER:
			 
			 pushButtonGetStatus(BTN_0,&au8_ButtonStatus);
			 if (Pressed == au8_ButtonStatus)
			 {
			    au8_Answer =  TRUE;
				 au8_AppStatus = CLEAR;
				 au8_AppStatusNext = CHECK_ANSWER;
			 }
			
			 pushButtonGetStatus(BTN_1,&au8_ButtonStatus);
			 if (Pressed == au8_ButtonStatus)
			 {
				 
				 au8_Answer =  FALSE;
				 au8_AppStatus = CLEAR;
				 au8_AppStatusNext = CHECK_ANSWER;
			 }

			 
			 break;
			 /****************************************************************************************************************/
			 case CHECK_ANSWER:

			 if (QUE1 == au8_CheckCounter)
			 {
			      
				  if (TRUE == au8_Answer)
			     {
				     
					  au8_AppStatus = RIGHT_ANSWER;
					  au8_AppStatusNext = GET_QUE;
			     }
			     else
			     {
				     au8_AppStatus = WRONG_ANSWER;
					  au8_AppStatusNext = GET_QUE;
			     }

			 }
			 else if (QUE2 == au8_CheckCounter)
			 {
				  if (TRUE == au8_Answer)
				  {
					  au8_AppStatus = WRONG_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }
				  else
				  {
					  au8_AppStatus = RIGHT_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }

			 }
			 else if (QUE3 == au8_CheckCounter)
			 {
				  if (TRUE == au8_Answer)
				  {
					  au8_AppStatus = RIGHT_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }
				  else
				  {
					  au8_AppStatus = WRONG_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }

			 }
			 else if (QUE4 == au8_CheckCounter)
			 {
				  if (TRUE == au8_Answer)
				  {
					  au8_AppStatus = WRONG_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }
				  else
				  {
					  au8_AppStatus = RIGHT_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }

			 }
			 else if (QUE5 == au8_CheckCounter)
			 {
				  if (TRUE == au8_Answer)
				  {
					  au8_AppStatus = RIGHT_ANSWER;
					  au8_AppStatusNext = GET_QUE;
					
				  }
				  else
				  {
					  au8_AppStatus = WRONG_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }

			 }
		/*****************************************************************************************************************/
		case RIGHT_ANSWER:
		if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		{
			LCD_DisplayStringRowColumn("RIGHT ANSWER",12,0);
			
		}
		else
		{
			if (ANSWER_WAIT > au8_WaitCounter)
			{
				au8_WaitCounter++;
				if (ZERO == (au8_WaitCounter%4))
				{
				   DIO_Toggle(GPIOB,UPPER_NIBBLE);
				}
			}
			else
			{
				gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
				au8_AppStatus = CLEAR;
				au8_WaitCounter = ZERO;
				au8_Score ++;
				DIO_Write(GPIOB,UPPER_NIBBLE,LOW);
			}
		}
    	break;
		/*****************************************************************************************************************/
		case WRONG_ANSWER:
		if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		{
			LCD_DisplayStringRowColumn("WRONG ANSWER",12,0);
			
		}
		else
		{
			if (ANSWER_WAIT > au8_WaitCounter)
			{
			   au8_WaitCounter++;
				DIO_Write(GPIOB,BIT3,HIGH);
			} 
			else
			{
			   gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
			   au8_AppStatus = CLEAR;
				au8_WaitCounter = ZERO;
				DIO_Write(GPIOB,BIT3,LOW);
			}
			
		}
		break;
		 /***************************************************************************************************************/

		 case GET_QUE:
		 switch (au8_QueNumber)
		 {
			 case 1:
			 PTR1 = "DO YOU KNOW";
			 au8_QueSize1 = 11;
			 PTR2 = "CORONA VAIRS?";
			 au8_QueSize2 = 13;
			 au8_CheckCounter = QUE1;
			 break;
			
			case 2:
			PTR1 = "IS NORMAL";
			au8_QueSize1 = 9;
			PTR2 = "MASK EFFICTIVE?";
			au8_QueSize2 = 15;
			au8_CheckCounter = QUE2;
			break;

			case 3:
			PTR1 = "Is the death";
			au8_QueSize1 = 12;
			PTR2 = "rate of virus 7%?";
			au8_QueSize2 = 16;
			au8_CheckCounter = QUE3;
			break;

			case 4:
			PTR1 = "Is incubation";
			au8_QueSize1 = 13;
			PTR2 = "Period 15 days?";
			au8_QueSize2 = 15;
			au8_CheckCounter = QUE4;
			break;

			case 5:
			PTR1 = "Does it lasts" ;
			au8_QueSize1 = 13;
			PTR2 = "for 5hr on skin?";
			au8_QueSize2 = 16;
			au8_CheckCounter = QUE5;
			break;

			default:
			au8_InetrnalStatus = INTERNAL_STATUS_3;
			au8_AppStatus = SCOR;
			break;
		  }
		  if (au8_InetrnalStatus == NOT_INITIALIZED)
		  { if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
			  {
				  LCD_DisplayStringRowColumn(PTR1,au8_QueSize1,0);
				  
			  }
			  else
			  {
				  au8_InetrnalStatus = INTERNAL_STATUS_1;
				  gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
			  }
		  }
		  /*********************************************************/
		  else if (au8_InetrnalStatus == INTERNAL_STATUS_1)
		  {if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
			  {
				  LCD_DisplayStringRowColumn(PTR2,au8_QueSize2,16);
			  }
			  else
			  {
				  gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
				  au8_InetrnalStatus = NOT_INITIALIZED;
				  
				  au8_AppStatus = GET_ANSWER;
				  au8_QueNumber ++;
				  
			  }
		  }
		  break;
		 /****************************************************************************************************************/
		 case SCOR:
		 if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		 {
			 LCD_DisplayStringRowColumn("YOUR SCORE IS ",14,0);
			 
		 }
		 else
		 {
			 if (INITIALIZED != gu8_LCD_DisplayStringFlag)
			 {
			    au8_Score += 48;
				 LCD_DisplayString(&au8_Score,1);
			 } 
			 else
			 {
			    gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
				 gu8_LCD_DisplayStringFlag = NOT_INITIALIZED;
				 au8_AppStatus = 100;
			 }
			 
		 }
		 break;
		 /**************************************************************************************************************/
		 default:
		 break;
	 }
 }