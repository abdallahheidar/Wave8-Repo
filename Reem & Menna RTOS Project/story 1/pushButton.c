#include "pushButton.h"
#define F_CPU 16000000ul
#include <util/delay.h>
//#include "timers.h"


ERROR_STATUS pushButtonInit(En_buttonId_t en_butotn_id)
{
	ERROR_STATUS ERR = E_OK;
	DIO_Cfg_t btn;

	switch(en_butotn_id){
		case BTN_0:
			btn.GPIO = BTN_0_GPIO;
			btn.pins = BTN_0_BIT;
			btn.dir = INPUT;
			DIO_init (&btn);
			break;
		case BTN_1:
			btn.GPIO = BTN_1_GPIO;
			btn.pins = BTN_1_BIT;
			btn.dir = INPUT;
			DIO_init (&btn);
			break;
		default:
			ERR = ERROR_BTN_MODULE + ERROR_INVALID_PARAMETER;
			break;
	}
	return ERR;
}


ERROR_STATUS pushButtonGetStatus(En_buttonId_t BTN , uint8_t * au8_button_status)
{
	uint8_t status = Released;
	switch(BTN){
		case BTN_0:
			DIO_Read( BTN_0_GPIO, BTN_0_BIT, au8_button_status);
			//_delay_ms(200);
			//softwareDelayMs(100);
			break;
		case BTN_1:
			DIO_Read( BTN_1_GPIO, BTN_1_BIT, au8_button_status);
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