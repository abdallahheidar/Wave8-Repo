/*
 * Infotainment.c
 *
 * Created: 2020-03-13 9:43:14 PM
 * Author : EbrahimOseif
 */ 

#include "Char_lcd.h"
#include "SOS.h"
#include "pushButton.h"

#define     QUESTION_1_FINISHED		1
#define     QUESTION_2_FINISHED		2
#define     QUESTION_3_FINISHED		3
#define     QUESTION_4_FINISHED		4
#define     QUESTION_5_FINISHED		5

#define     QUESTION_1_STARTED		1
#define     QUESTION_2_STARTED		2
#define     QUESTION_3_STARTED		3
#define     QUESTION_4_STARTED		4
#define     QUESTION_5_STARTED		5

#define		DISPLAY_QUESTION		1
#define		DISPLAY_ANSWER			2
#define		ANSWER_QUESTION			3
#define		QUESTION_FINISHED		4

uint8_t gu8_question_state = DISPLAY_QUESTION;
uint8_t gu8_finished_question = 0 ;
uint8_t gu8_started_question = QUESTION_1_STARTED;

uint8_t gu8_button0_state;
uint8_t gu8_button1_state;

uint8_t gu8_Yes_Answer;
uint8_t gu8_No_Answer;


#define  ANSWERED		 1
#define  NOT_ANSWERED    0

uint8_t gu8_Answered;



uint8_t question[5][48] = {"01:R U ready1?  ",
                           "02:R U ready2?  ",
                           "03:R U ready3?  ",
                           "04:R U ready4?  ",
                           "05:R U ready5?  "};
uint8_t answer[16] =	  {"YES         NO  "};

void Question_1(){

		switch( gu8_started_question)
		{
			case QUESTION_1_STARTED:
			
			switch(gu8_question_state){
			
				case DISPLAY_QUESTION:
						LCD_sendString(question[0]);
						gu8_question_state = DISPLAY_ANSWER;
						break;
				
				case DISPLAY_ANSWER:
						LCD_goto_RowColumn(LINE1, 0);
						LCD_sendString(&answer);
						gu8_question_state = ANSWER_QUESTION;

						break;
						
				case ANSWER_QUESTION:
				
							Answer();
								gu8_question_state = QUESTION_FINISHED;
							
							 
						 break;
	
				case QUESTION_FINISHED:
								
				gu8_finished_question = QUESTION_1_FINISHED;
				gu8_started_question = QUESTION_2_STARTED;

				gu8_question_state = DISPLAY_QUESTION;
				/*PORTD_DIR = 0XFF;
				PORTD_DATA = 0XFF;*/
				break;
			}
			break;
			
			case QUESTION_2_STARTED:
			
			switch(gu8_question_state){
				
				case DISPLAY_QUESTION:
				LCD_goto_RowColumn(LINE0, 0);
				LCD_sendString(question[1]);
				gu8_question_state = DISPLAY_ANSWER;
								//PORTD_DATA = 0X00;

				break;
				case DISPLAY_ANSWER:
				LCD_goto_RowColumn(LINE1, 0);
				LCD_sendString(&answer);
				gu8_question_state = ANSWER_QUESTION;

				break;
				
				case ANSWER_QUESTION:
				
				Answer();
					gu8_question_state = QUESTION_FINISHED;
			
			break;
				
				case QUESTION_FINISHED:
				
				gu8_question_state = DISPLAY_QUESTION;
				gu8_started_question = QUESTION_3_STARTED;

				gu8_finished_question = QUESTION_2_FINISHED;
				break;
			}
			break;
			
			case  QUESTION_3_STARTED:
			
			switch(gu8_question_state){
				
				
				case DISPLAY_QUESTION:
				
				LCD_goto_RowColumn(LINE0, 0);
				LCD_sendString(question[2]);
				gu8_question_state = DISPLAY_ANSWER;
				break;
				
				case DISPLAY_ANSWER:
				
				LCD_goto_RowColumn(LINE1, 0);
				LCD_sendString(&answer);
				gu8_question_state = ANSWER_QUESTION;

				break;
				
				case ANSWER_QUESTION:
				
				Answer();
					gu8_question_state = QUESTION_FINISHED;
				
				break;
				
				case QUESTION_FINISHED:
				
				gu8_question_state = DISPLAY_QUESTION;
				gu8_started_question = QUESTION_4_STARTED;
				gu8_finished_question = QUESTION_3_FINISHED;
				break;
			}
			break;
			
			case QUESTION_4_STARTED:
			
			switch(gu8_question_state){
				
				
				case DISPLAY_QUESTION:
				
				LCD_goto_RowColumn(LINE0, 0);
				LCD_sendString(question[3]);
				gu8_question_state = DISPLAY_ANSWER;
				break;
				
				case DISPLAY_ANSWER:
				
				LCD_goto_RowColumn(LINE1, 0);
				LCD_sendString(&answer);
				gu8_question_state = ANSWER_QUESTION;

				break;
				
				case ANSWER_QUESTION:
				
				Answer();
					gu8_question_state = QUESTION_FINISHED;
				
				break;
				
				case QUESTION_FINISHED:
								
				gu8_question_state = DISPLAY_QUESTION;
				gu8_started_question = QUESTION_5_STARTED;
				gu8_finished_question = QUESTION_4_FINISHED;

				break;
			}
			break;
			
			case QUESTION_5_STARTED:
			
			switch(gu8_question_state){
				
				
				case DISPLAY_QUESTION:
				
				LCD_goto_RowColumn(LINE0, 0);
				LCD_sendString(question[4]);
				gu8_question_state = DISPLAY_ANSWER;
				break;
				
				case DISPLAY_ANSWER:
				
				LCD_goto_RowColumn(LINE1, 0);
				LCD_sendString(&answer);
				gu8_question_state = ANSWER_QUESTION;
				break;
				
				case ANSWER_QUESTION:
						
						Answer();
							gu8_question_state = QUESTION_FINISHED;
					
						
					break;
					
				case QUESTION_FINISHED:
				
				result();
				gu8_question_state = DISPLAY_QUESTION;
				gu8_finished_question = QUESTION_5_FINISHED;
				break;
			}
			break;
		
			
		}
		

		
}
	
void Question_2(){

	if ( gu8_finished_question == QUESTION_2_STARTED){
		
		switch(gu8_question_state){
			
			case DISPLAY_QUESTION:
			LCD_sendString(question[1]);
			gu8_question_state = DISPLAY_ANSWER;
			break;
			case DISPLAY_ANSWER:
			LCD_goto_RowColumn(LINE1, 0);

			LCD_sendString(&answer);
			gu8_question_state = QUESTION_FINISHED;

			break;
			
			case QUESTION_FINISHED:
			gu8_question_state = DISPLAY_QUESTION;
			gu8_started_question = QUESTION_3_STARTED;

			gu8_finished_question = QUESTION_2_FINISHED;
			break;
		}
	}

	
		
	}
	
void Question_3()
{
	
	if (gu8_finished_question == QUESTION_3_STARTED)
	{
	switch(gu8_question_state){
		
		
		case DISPLAY_QUESTION:
		LCD_sendString(question[2]);
		gu8_question_state = DISPLAY_ANSWER;
		break;
		case DISPLAY_ANSWER:
		LCD_goto_RowColumn(LINE1, 0);

		LCD_sendString(&answer);
		gu8_question_state = QUESTION_FINISHED;

		break;
		
		case QUESTION_FINISHED:
		gu8_question_state = DISPLAY_QUESTION;
		gu8_started_question = QUESTION_4_STARTED;

		gu8_finished_question = QUESTION_3_FINISHED;
		break;
	}	
	}
	
		
	}
	
void Question_4()
{
		if (gu8_finished_question == QUESTION_4_STARTED){
			
			 switch(gu8_question_state){
				 
				 
				 case DISPLAY_QUESTION:
				 LCD_sendString(question[3]);
				 gu8_question_state = DISPLAY_ANSWER;
				 break;
				 case DISPLAY_ANSWER:
				 LCD_goto_RowColumn(LINE1, 0);

				 LCD_sendString(&answer);
				 gu8_question_state = QUESTION_FINISHED;

				 break;
				 
				 case QUESTION_FINISHED:
				 gu8_question_state = DISPLAY_QUESTION;
				gu8_started_question = QUESTION_5_STARTED;

				 gu8_finished_question = QUESTION_4_FINISHED;
				 break;
			 }
		}

	
	   
	} 
	
void Question_5()
	{
		
	if (gu8_finished_question == QUESTION_5_STARTED){

	 switch(gu8_question_state){
		 
		 
		 case DISPLAY_QUESTION:
		 LCD_sendString(question[4]);
		 gu8_question_state = DISPLAY_ANSWER;
		 break;
		 case DISPLAY_ANSWER:
		 LCD_goto_RowColumn(LINE1, 0);

		 LCD_sendString(&answer);
		 gu8_question_state = QUESTION_FINISHED;

		 break;
		 
		 case QUESTION_FINISHED:
		 gu8_question_state = DISPLAY_QUESTION;

		 gu8_finished_question = QUESTION_5_FINISHED;
		 break;
	 }
	}  	
	}
	


void Question_Task(){
			
		 Question_1();
		
}

void Answer(){
	

	if ( pushButtonGetStatus(BTN_0) == Prepressed)
	{
		gu8_button0_state++;
		
		if (gu8_button0_state == 1)
		{
			gu8_button0_state = 0 ;
			gu8_Yes_Answer++;
			
			gu8_Answered = ANSWERED;
			PORTD_DATA = 0xff;
		}
	}
	else if ( pushButtonGetStatus(BTN_1) == Prepressed)
	{
		gu8_button1_state++;
		
		if (gu8_button1_state == 1)
		{
			gu8_button1_state = 0 ;
			gu8_No_Answer++;
			gu8_Answered = ANSWERED;

			PORTD_DATA = 0x00;

		}
	}
	else{
		gu8_Answered = NOT_ANSWERED;
		}
	
}

void result(){
	
	if (gu8_Yes_Answer > gu8_No_Answer )
	{
		LCD_sendString("correct");		
	}else if (gu8_Yes_Answer < gu8_No_Answer )
	{
		LCD_sendString("wrong");
	}
	else
	{
			LCD_sendString("ODD");
	}
}



int main(void)
{
	PORTD_DIR = 0xff;

	SOS_Init();
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	LCD_init();
	sei();


strSOS_TCB_t QuestionTask_st = {
		Question_Task,
		3,
		0,
		0,
		45	
	};
	
	strSOS_TCB_t AnswerTask_st = {
		Answer,
		4,
		0,
		0,
		20
	};

strSOS_TCB_t LCD_Dispatcher_task = {
		LCD_Dispatcher,
		2,
		0,
		0,
		1
	};
	
	SOS_CreateTask(&QuestionTask_st);
	SOS_CreateTask(&AnswerTask_st);
	SOS_CreateTask(&LCD_Dispatcher_task);
	
	
    while (1) 
    {
			//softwareDelayMs(10);
			
			//LCD_sendString("aboseif");
			//LCD_Dispatcher();
			SOS_Run();
    }
}

