/*
 * LCD.c
 *
 * Created: 3/12/2020 11:48:41 AM
 *  Author: Khaled
 */ 



 #include "LCD.h"
 #include "LCD_Cfg.h"



 /*************************************************************/
 /*********************** LOCAL MACROS ***********************/
 /***********************************************************/
 #define WAIT_FOR_40_MS 1;
 #define SET_BITS_DIRECTION 2;

 #define LCD_DATA_PINS LCD_D4|LCD_D5|LCD_D6|LCD_D7

 #define LCD_SEND_ENABLE DIO_Write(LCD_PORT,LCD_EN,HIGH);\
                         DIO_Write(LCD_PORT,LCD_EN,LOW)
         
#define DELAY Delay_ms(Timer_0,1)

 /*************************************************************/
 /********************* GLOBAL VARIABLES *********************/
 /***********************************************************/

 uint8_t gu8_LCD_InitFlag;




 /*************************************************************/
 /***************** LOCAL FUNCTION PROTOTYPE *****************/
 /***********************************************************/
 static void LCD_Send (uint8_t Data);




 /*************************************************************/
 /*************** LOCAL FUNCTION IMPLEMENTAION ***************/
 /***********************************************************/

void LCD_Send (uint8_t Data)
{
   uint8_t au8_Data = ZERO;

	/*read port B value to get pin0 value*/
	DIO_Read(GPIOB,PIN0,&au8_Data);

	/*mask pin0 value*/
	au8_Data &= 0x01;

	au8_Data = au8_Data | Data;

	DIO_Write_Port(LCD_PORT, au8_Data);

	
}






 /*************************************************************/
 /*************** APIS FUNCTION IMPLEMENTAION ****************/
 /***********************************************************/

 ERROR_STATUS LCD_init (void)
 {
    uint8_t au8_Data = ZERO;
    
    Delay_ms(Timer_0,40);

	 /*set LCD pins output*/
    DIO_Cfg_s str_DIO_Info;
    str_DIO_Info.GPIO = LCD_PORT;
    str_DIO_Info.pins = LCD_RS|LCD_RW|LCD_EN|LCD_D4|LCD_D5|LCD_D6|LCD_D7;
    str_DIO_Info.dir = OUTPUT;
	 DIO_init(&str_DIO_Info);

	 /*set 4 bit mode*/
	 au8_Data = 0x20;

	 LCD_Send(au8_Data);

	 LCD_SEND_ENABLE ;

	 DELAY ;

	 /*4 bit mode, 2-line display mode, 5x8 font*/
	 LCD_SendCommand(0x28);

	 /*display off*/
	 LCD_SendCommand(0x08);

	 /*display on, blink cursor on*/
	 LCD_SendCommand(0x0F);

	 /*entry mode cursor move to right and DDRAM address is increased by 1*/
	 LCD_SendCommand(0x06);
 }

 ERROR_STATUS LCD_SendCommand (uint8_t Command)
 {
	 uint8_t au8_SendCommand = ZERO;

	 au8_SendCommand = Command & 0xF0;

	 LCD_Send(au8_SendCommand);

	 LCD_SEND_ENABLE ;

	 au8_SendCommand = Command<<4;
	 
	 LCD_Send(au8_SendCommand);

	 LCD_SEND_ENABLE ;

	 Delay_ms(Timer_0,1);
 }


 ERROR_STATUS LCD_DisplayChar (uint8_t LCD_Char)
 {
    uint8_t au8_SendChar = ZERO;

	 au8_SendChar = LCD_Char & 0xF0;

	 au8_SendChar = au8_SendChar | 0x02;

	 LCD_Send(au8_SendChar);

	 LCD_SEND_ENABLE ;

	 au8_SendChar = LCD_Char<<4;

	 au8_SendChar |= 0x02;
	 
	 LCD_Send(au8_SendChar);
	 
	 LCD_SEND_ENABLE ; 

	 DELAY ;
 }

 ERROR_STATUS LCD_DisplayString (uint8_t * LCD_String, uint8_t String_Size)
 {
    uint8_t au8_StringCounter = ZERO;
	 while (String_Size > au8_StringCounter)
	 {
	    LCD_DisplayChar(LCD_String[au8_StringCounter]);

		 au8_StringCounter++;
	 }
 }
 ERROR_STATUS LCD_DisplayStringRowColumn (uint8_t * LCD_String, uint8_t String_Size, uint8_t Pos)
 {
    LCD_GoToRowColumn(Pos);

	 LCD_DisplayString(LCD_String,String_Size);
 }
 ERROR_STATUS LCD_Clear (void)
 {
    LCD_SendCommand(0x01);
 }
 ERROR_STATUS LCD_GoToRowColumn (uint8_t Pos)
 {
    if (Pos<16)
    {
	    LCD_SendCommand(0x80 + Pos);
    }
	 else
	 {
	    LCD_SendCommand(0xB0 + Pos);
	 }
 }