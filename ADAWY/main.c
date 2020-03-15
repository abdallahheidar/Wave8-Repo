/*
 * Mini_OS.c
 *
 * Created: 3/10/2020 5:27:37 AM
 * Author : Khaled
 */ 

#include "SERVICE/OS/OS.h"
#include "SERVICE/OS/OS_PbCfg.h"
#include "APP/LCD_APP.h"
#include "ECU/PUSH_BUTTON/pushButton.h"

#define SLEEP_IDEAL_MOOD  0x8F

void Task1 (void);
void Task2 (void);
//void Task3 (void);

int main (void)
{	
	SET_BIT(PORTB_DIR,BIT0);
	SET_BIT(PORTB_DIR,BIT1);

	pushButtonInit(BTN_0_BIT);
	OS_Init(&str_OS_InitConf);
	
	Task_Creat(1,0,PERIODIC,Task1);
	Task_Creat(40,1,PERIODIC,LCD_APP);
//	Task_Creat(1,2,PERIODIC,Task3);

	OS_RUN();

	return 0;
}


void Task1 (void)
{

  if (INITIALIZED != gu8_LCD_InitFlag)
  {
     LCD_init();
  } 
  else
  {
     //Task_Delet(0,Task1);
  }
  
}

