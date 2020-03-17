#include "pushButton.h"
#define F_CPU 16000000ul
#include <util/delay.h>
//#include "timers.h"

uint8_t gu8_BTN0_status = Released;
uint8_t gu8_BTN1_status = Released;
uint8_t gu8_push_buttons_init = FALSE;

void pushButtonsInit(){
	if(gu8_push_buttons_init != TRUE){
		DIO_Cfg_t btn0;
		btn0.GPIO = BTN_0_GPIO;
		btn0.pins = BTN_0_BIT;
		btn0.dir = INPUT;
		DIO_init (&btn0);
	
		DIO_Cfg_t btn1;
		btn1.GPIO = BTN_1_GPIO;
		btn1.pins = BTN_1_BIT;
		btn1.dir = INPUT;
		DIO_init (&btn1);
		gu8_push_buttons_init = TRUE;			
	}
}

void BTN0_GetStatus(){
	if(gu8_push_buttons_init){
		/*gu8_BTN0_status = */pushButtonGetStatus(BTN_0);		
	} 
}

void BTN1_GetStatus(){
	if(gu8_push_buttons_init){
		/*gu8_BTN1_status = */pushButtonGetStatus(BTN_1);
	}
}

ERROR_STATUS pushButtonGetStatus(En_buttonId_t en_butotn_id){
	uint8_t status = Released;
	switch(en_butotn_id){
		case BTN_0:
			DIO_Read( BTN_0_GPIO, BTN_0_BIT, &gu8_BTN0_status);
			//_delay_ms(200);
			//softwareDelayMs(100);
			break;
		case BTN_1:
			DIO_Read( BTN_1_GPIO, BTN_1_BIT, &gu8_BTN1_status);
			//_delay_ms(200);
			//softwareDelayMs(100);
			break;
		default:
			status = Released;
			break;
	}
// 	if(status){
// 		status = Pressed;
// 	}else{
// 		status = Released;
// 	}
	return status;
}