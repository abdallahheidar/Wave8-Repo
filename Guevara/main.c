/*
 * Static_design_Rebuild.c
 *
 * Created: 20/03/2020 03:33:18 ص
 *  Author: mo
 */ 

#include "MCAL/Timer/Timer.h"
#include "SL/SOS/SOS.h"
#include "ECUAL/LCD/LCD.h"
#include "MCAL/PushButtons/pushButton.h"
int main(void)
{
	
	DIO_init(&Dio_configurationB);
	DIO_init(&Dio_configurationC);
	LCD_config_pins();
	DIO_init(&Dio_configurationD);
	SOS_Init(&TMU_Configuration);

	SOS_Create_Task(LCD_init,1,0,50);
	SOS_Create_Task(Task1,1,1,20);
	SOS_Create_Task(Task2,1,2,10);
	//	SOS_Create_Task(Tmu_excute,1,2,50);
	
	while(1)
	{
		SOS_Run();
	}

}