/*
 * LCD.c
 *
 * Created: 3/15/2020 11:49:48 AM
 *  Author: MENA
 */ 
#include "DIO.h"
#include  "softwareDelay.h"
#include  "LCD.h"



ERROR_STATUS LCD_init(void){
	
	ERROR_STATUS error_state = E_OK ;


/*static uint8_t init_task_state = init_state_1 ;
	
	
	counter++ ;

	switch(init_task_state){
		
		case init_state_1 :
		
		portA_cfg.GPIO = LCD_PORT ;
		portA_cfg.pins = LCD_RS| LCD_R_W | LCD_DATA | LCD_EN ;
		portA_cfg.dir = OUTPUT ;
		
		DIO_init(&portA_cfg);
		//softwareDelayMs(15);

		
		init_task_state = init_state_2;

		break;
		
		case init_state_2 :
		TCNT1L= counter;
		if (counter>10)
		{
		LCD_sendCommand(DATA_MODE_4_BIT);
		
		/ * send 4 bit mode commands * /
		LCD_sendCommand(DATA_MODE_2_LINE_4_BIT);
		
		/ * cursor state* /
		LCD_sendCommand(CURSOR_ON) ;
		LCD_sendCommand(CLEAR_SCREEN);
		//softwareDelayMs(25);
		
		init_task_state = init_state_done;
		}
		break;
		case init_state_done :
		if(counter > 10+20)
		init_done = TRUE ;
	
		break;
		default:
		break;
		
	}
	*/


	DIO_Cfg_s portA_cfg ;
	
	portA_cfg.GPIO = LCD_PORT ;
	portA_cfg.pins = LCD_RS| LCD_R_W | LCD_DATA | LCD_EN ;
	portA_cfg.dir = OUTPUT ;
	
	DIO_init(&portA_cfg);
	softwareDelayMs(15);
	
	/* return home mode commands */
	LCD_sendCommand(DATA_MODE_4_BIT);
	
	/* send 4 bit mode commands */
	LCD_sendCommand(DATA_MODE_2_LINE_4_BIT);
	
	/* cursor state*/
	LCD_sendCommand(CURSOR_ON) ;
	LCD_sendCommand(CLEAR_SCREEN);
	
	softwareDelayMs(25);
	return error_state ;

}

ERROR_STATUS LCD_sendCommand(uint8_t command) {
	
	/*send most first then least */
	uint8_t MSB_command , LSB_command ;
	ERROR_STATUS error_state = E_OK ;
	
		
	MSB_command = GET_NIBBLE_HIGH(command) ;
	LSB_command = GET_NIBBLE_LOW(command) ;
	
	
	/* select whether it is WRITE or READ */
	DIO_Write(LCD_PORT,LCD_R_W,LOW);
	
	/* select whether it is DATA or COMMAND */
	DIO_Write(LCD_PORT ,LCD_RS , LOW);
		
	softwareDelayMs(1);
	
	/* send MSB_command */
	
	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , MSB_command<<4) ;
	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
	
	softwareDelayMs(5);
	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
	
	
	/* select whether it is WRITE or READ */
//	DIO_Write(LCD_PORT,LCD_R_W,LOW);
		
	/* select whether it is DATA or COMMAND */
//	DIO_Write(LCD_PORT ,LCD_RS , LOW);
	
	/* send LSB_command */
	
	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , LSB_command<<4) ;
	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
	softwareDelayMs(5);
	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
	
	
	softwareDelayMs(10);

	
	//error_state |= DIO_Write(LCD_PORT ,LCD_DATA , ZERO_VALUE) ;


	return error_state ;
	
	
}



ERROR_STATUS LCD_displayChar(uint8_t data) {
	
	/*send most first then least */
	uint8_t MSB_data , LSB_data ;
	
	ERROR_STATUS error_state = E_OK ;
		
	MSB_data = GET_NIBBLE_HIGH(data) ;
	LSB_data = GET_NIBBLE_LOW(data) ;
	
	
	/* select whether it is DATA or COMMAND */
	DIO_Write(LCD_PORT ,LCD_RS , HIGH);
	/* select whether it is WRITE or READ */
	DIO_Write(LCD_PORT,LCD_R_W,LOW);

	
	
	/* send MSB_data */
		
	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , MSB_data<<4) ;
	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
	softwareDelayMs(5);
	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
		

	
	
	/* send LSB_data */
		
	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , LSB_data<<4) ;
	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
	softwareDelayMs(5);
	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
		
	
 //	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , ZERO_VALUE) ;
	 
	//softwareDelayMs(20);
	softwareDelayMs(5);

	return error_state ;
	
	
}


ERROR_STATUS LCD_displayString(uint8_t * str_data ) {
	ERROR_STATUS error_state = E_OK ;

	uint8_t au8_counter = ZERO_VALUE ;
	if (str_data==NULL )
	{
		return NULL_PTR_ERROR +	LCD_MODEULE_ERROR ;
	}
	
	while(str_data[au8_counter]!='\0'){
		
		LCD_displayChar(str_data[au8_counter]);
		au8_counter++ ;
	}
	return error_state ;
}


ERROR_STATUS LCD_clear() {
	
	ERROR_STATUS error_state = E_OK ;

	LCD_sendCommand(CLEAR_SCREEN);
	return error_state ;
}


ERROR_STATUS LCD_gotoRowColumn( uint8_t row , uint8_t col) {
	ERROR_STATUS error_state = E_OK ;

	uint8_t address = 0 ;
	
	switch(row)
	{
		case 0:
		address = col;
		break;
		case 1:
		address = 0x40 + col;
		break;
		default:
		error_state = INVALID__PARAMETER + LCD_MODEULE_ERROR ;
		break;
		
	}
	LCD_sendCommand ( address | SET_CURSOR_LOCATION);
	return error_state ;
}
