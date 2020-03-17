/*
 * LCD_APP.c
 *
 * Created: 3/15/2020 2:45:33 PM
 *  Author: Khaled
 */ 


#include "LCD_APP.h"
#include "../MCAL/DIO/DIO.h"


/*app state machine cases*/
 #define CLEAR                           30
 #define PRINT_FIRST_LINE                CLEAR +1
 #define PRINT_SECOND_LINE               PRINT_FIRST_LINE +1 
 #define GET_QUE                         PRINT_SECOND_LINE +1
 #define SCOR                            GET_QUE +1
 #define GET_ANSWER                      SCOR +1
 #define CHECK_ANSWER                    GET_ANSWER +1
 #define RIGHT_ANSWER                    CHECK_ANSWER +1
 #define WRONG_ANSWER                    RIGHT_ANSWER +1


 /*que numbers*/
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

 #define TOGGLE_FACTOR      4

 ERROR_STATUS LCD_APP (void)
 {
    ERROR_STATUS au8_Error = E_OK;
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
	  
	  /*init the buzzer and leds*/
	  DIO_Cfg_s str_DIO_Info;
	  str_DIO_Info.dir = OUTPUT;
	  str_DIO_Info.GPIO = GPIOB;
	  str_DIO_Info.pins = BIT3|BIT4|BIT5|BIT6|BIT7;
	  au8_Error |= DIO_init(&str_DIO_Info);

	 switch (au8_AppStatus)
	 {
	    /*initial status*/
		 case NOT_INITIALIZED:
		 if (INITIALIZED == gu8_LCD_InitFlag)
		 {
		    au8_AppStatus = PRINT_FIRST_LINE;
		 }
		 break;
		 /*******************************************************************************************************/
		 /*Clear LCD status*/
		 case CLEAR:
		 au8_Error |= LCD_Clear();
		 au8_Error |= LCD_Clear();
		 au8_AppStatus = au8_AppStatusNext;
	
		 break;
		 /*******************************************************************************************************/
       /*print  welcome string first line*/
		 case PRINT_FIRST_LINE:
		 if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		 {
		    au8_Error |= LCD_DisplayStringRowColumn("HELLO USER",10,0);
		 } 
		 else
		 {
		    au8_AppStatus = PRINT_SECOND_LINE;
			 gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
		 }
		 break;
		 /*******************************************************************************************************/
		 /*print  welcome string second line*/
		 case PRINT_SECOND_LINE:
		 if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		 {
			 au8_Error |= LCD_DisplayStringRowColumn("R U READY",9,16);
			 
		 }
		 else
		 {
			 gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
			 au8_AppStatusNext = GET_QUE;
			 au8_AppStatus = CLEAR;
			 
		 }
		 break;

		 
			 /****************************************************************************************************************/
			 /*get answer from the user using push buttons*/
			 case GET_ANSWER:
			 au8_Error |= pushButtonGetStatus(BTN_0,&au8_ButtonStatus);
			 if (Pressed == au8_ButtonStatus)
			 {
			    au8_Answer =  TRUE;
				 au8_AppStatus = CLEAR;
				 au8_AppStatusNext = CHECK_ANSWER;
			 }
			
			 au8_Error |= pushButtonGetStatus(BTN_1,&au8_ButtonStatus);
			 if (Pressed == au8_ButtonStatus)
			 {
				 au8_Answer =  FALSE;
				 au8_AppStatus = CLEAR;
				 au8_AppStatusNext = CHECK_ANSWER;
			 }
			 break;
			 /****************************************************************************************************************/
			 /*check user answer if it right or wrong*/
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
					  au8_AppStatus = WRONG_ANSWER;
					  au8_AppStatusNext = GET_QUE;
				  }
				  else
				  {
					  au8_AppStatus = RIGHT_ANSWER;
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
		/*if the user answer is right*/
		case RIGHT_ANSWER:
		if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		{
			/*display right answer*/
			au8_Error |= LCD_DisplayStringRowColumn("RIGHT ANSWER",12,0);
		}
		else
		{
			if (ANSWER_WAIT > au8_WaitCounter)
			{
				au8_WaitCounter++;
				/*toggle led*/
				if (ZERO == (au8_WaitCounter%TOGGLE_FACTOR))
				{
				   au8_Error |= DIO_Toggle(GPIOB,UPPER_NIBBLE);
				}
			}
			else
			{
				gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
				au8_AppStatus = CLEAR;
				au8_WaitCounter = ZERO;
				au8_Score ++;
				au8_Error |= DIO_Write(GPIOB,UPPER_NIBBLE,LOW);
			}
		}
    	break;
		/*****************************************************************************************************************/
		/*if the user answer is wrong*/
		case WRONG_ANSWER:
		if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		{
			/*display wrong answer*/
			au8_Error |= LCD_DisplayStringRowColumn("WRONG ANSWER",12,0);
			
		}
		else
		{
			if (ANSWER_WAIT > au8_WaitCounter)
			{
			   au8_WaitCounter++;
				/*turn buzzer on*/
				au8_Error |= DIO_Write(GPIOB,BIT3,HIGH);
			} 
			else
			{
			   gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
			   au8_AppStatus = CLEAR;
				au8_WaitCounter = ZERO;
				au8_Error |= DIO_Write(GPIOB,BIT3,LOW);
			}
			
		}
		break;
		 /***************************************************************************************************************/
		 /*get the question*/
		 case GET_QUE:
		 switch (au8_QueNumber)
		 {
			 /*question 1*/
			 case 1:
			 PTR1 = "DO YOU KNOW";
			 au8_QueSize1 = 11;
			 PTR2 = "CORONA VAIRS?";
			 au8_QueSize2 = 13;
			 au8_CheckCounter = QUE1;
			 break;
			
			/*question 2*/
			case 2:
			PTR1 = "IS NORMAL";
			au8_QueSize1 = 9;
			PTR2 = "MASK EFFICTIVE?";
			au8_QueSize2 = 15;
			au8_CheckCounter = QUE2;
			break;

			/*question 3*/
			case 3:
			PTR1 = "Is the death";
			au8_QueSize1 = 12;
			PTR2 = "rate of virus 7%?";
			au8_QueSize2 = 16;
			au8_CheckCounter = QUE3;
			break;

			/*question 4*/
			case 4:
			PTR1 = "Is incubation";
			au8_QueSize1 = 13;
			PTR2 = "Period 15 days?";
			au8_QueSize2 = 15;
			au8_CheckCounter = QUE4;
			break;

			/*question 5*/
			case 5:
			PTR1 = "Corona infects" ;
			au8_QueSize1 = 14;
			PTR2 = "more than once?";
			au8_QueSize2 = 15;
			au8_CheckCounter = QUE5;
			break;

			default:
			au8_InetrnalStatus = INTERNAL_STATUS_3;
			au8_AppStatus = SCOR;
			break;
		  }
		  /*Display the question and got to next status*/
		  if (au8_InetrnalStatus == NOT_INITIALIZED)
		  { 
		  if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
			  {
				  au8_Error |= LCD_DisplayStringRowColumn(PTR1,au8_QueSize1,0);
				  
			  }
			  else
			  {
				  au8_InetrnalStatus = INTERNAL_STATUS_1;
				  gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
			  }
		  }
	
		  else if (au8_InetrnalStatus == INTERNAL_STATUS_1)
		  {
		  if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
			  {
				  au8_Error |= LCD_DisplayStringRowColumn(PTR2,au8_QueSize2,16);
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
		 /*display user score*/
		 case SCOR:
		 if (INITIALIZED != gu8_LCD_DisplayStringRowColumnFlag)
		 {
			 au8_Error |= LCD_DisplayStringRowColumn("YOUR SCORE IS ",14,0);
			 
		 }
		 else
		 {
			 if (INITIALIZED != gu8_LCD_DisplayStringFlag)
			 {
			    au8_Score += 48;
				 au8_Error |= LCD_DisplayString(&au8_Score,1);
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

	 return au8_Error;
 }