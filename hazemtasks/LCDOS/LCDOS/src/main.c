
#include "..\servicelayer\SOS.h"
#include "..\ECUAL\LCD.h"

void FUN_CALL(void);
void FUN_CALL2(void);
void FUN_CALL3(void);

int main (void)
{
	LCD_init();
/*
	DIO_Cfg_s str_dioconfig={GPIOA,LOWER_NIBBLE,OUTPUT};
	
	DIO_init(&str_dioconfig);
	SOS_Init(&gstr_OSCONFIG);*/
	

	/*SOS_Start_Timer(1000,FUN_CALL,PERIODIC,8);
	SOS_Start_Timer(1000,FUN_CALL2,PERIODIC,9);
	SOS_Start_Timer(1000,FUN_CALL3,PERIODIC,10);*/
	softwareDelayMs(10);
	 char x[12]="hazemebrahim";
	LCD_displayString(x);
	
	while(1)
	{    

 
		/*SOS_Dispatch();*/
	}


}


void FUN_CALL(void)
{
	DIO_Write(GPIOA,BIT0,HIGH);
	softwareDelayMs(1000);
}

void FUN_CALL2(void)
{
	DIO_Write(GPIOA,BIT1,HIGH);
		softwareDelayMs(1000);

}

void FUN_CALL3(void)
{
	
	DIO_Write(GPIOA,BIT2,HIGH);
	softwareDelayMs(1000);
}