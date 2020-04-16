#include "pushButton.h"
ERROR_STATUS pushButtonInit(uint8_t en_butotn_id)
{
	ERROR_STATUS ERR = E_OK;
	DIO_Cfg_s btn;

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
		break;
	}
	return ERR;
}


ERROR_STATUS pushButtonGetStatus(uint8_t BTN , uint8_t * au8_button_status)
{
	uint8_t status = Released;
	switch(BTN){
		case BTN_0:
		DIO_Read( BTN_0_GPIO, BTN_0_BIT, au8_button_status);
		break;
		case BTN_1:
		DIO_Read( BTN_1_GPIO, BTN_1_BIT, au8_button_status);
		break;
		default:
		status = Released;
		break;
	}
	 	if(au8_button_status){
	 		au8_button_status = Pressed;
	 	}else{
			au8_button_status = Released;
	 	}
	return status;
}