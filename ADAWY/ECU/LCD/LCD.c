/*
 * LCD.c
 *
 * Created: 3/12/2020 11:48:41 AM
 *  Author: Khaled
 */ 



 #include "LCD.h"




 /*************************************************************/
 /*********************** LOCAL MACROS ***********************/
 /***********************************************************/
 
 #define LCD_DATA_PINS LCD_D4|LCD_D5|LCD_D6|LCD_D7

 /*Init Function State machine Cases*/
 #define WAIT 1
 #define SET_PINS 2
 #define SET_4_BIT_MODE 3
 #define SET_INIT_MODE 4

 /*Set init mode cases in init function*/
 #define INIT_COMMAND_INITAIL_VALUE 0
 #define INIT_COMMAND_FIRST 1
 #define INIT_COMMAND_SECOND 2
 #define INIT_COMMAND_THIRD 3

 /*Display String function state machine cases*/
 #define SENDING_CHAR 1
 #define CHAR_SEND 2

 /*Display String Row Column function state machine cases*/
 #define GO_TO 1
 #define DISPLAY_STRING 2

 /*enable LCD to perform the command*/
 #define LCD_SEND_ENABLE DIO_Write(LCD_PORT,LCD_EN,HIGH);\
                         DIO_Write(LCD_PORT,LCD_EN,LOW)
         
/*Initial function macros*/
#define INITIAL_WAIT 40
#define LCD_4_BIT_MODE_VALUE 0x20
#define WAIT_COUNTER_INITAIL_VALUE 0
#define LCD_4BIT_MODE_2LINE_DISPLAY_5_8_FONT 0x28
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON_CURSOR_OFF 0x0C
#define LCD_ENTERY_MODE_RIGHT_INCREASED 0x06


#define SEND_CHAR_CFG_VALUE 0x02
#define LCD_CLEAR_COMMAND 0x01
#define FIRST_ROW_FIRST_COLUME 0x80
#define SECOND_ROW_FIRST_COLUME 0xB0

#define WAIT_FOR_1_MS  au8_Wait = 1


 /*************************************************************/
 /********************* GLOBAL VARIABLES *********************/
 /***********************************************************/
 uint8_t gu8_LCD_InitFlag;
 uint8_t gu8_LCD_SencCommandFlag;
 uint8_t gu8_LCD_DisplayCharFlag;
 uint8_t gu8_LCD_DisplayStringFlag;
 uint8_t gu8_LCD_DisplayStringRowColumnFlag;
 uint8_t gu8_LCD_GoToRowColumFlag;


 /*************************************************************/
 /***************** LOCAL FUNCTION PROTOTYPE *****************/
 /***********************************************************/
 static ERROR_STATUS LCD_Send (uint8_t Data);


 /*************************************************************/
 /*************** LOCAL FUNCTION IMPLEMENTAION ***************/
 /***********************************************************/

 /**
 * Input: Data or command need to send to LCD.
 * Output:
 * In/Out: 
 * Return:
 * Description: This function read the LCD port bit0 and keep it's value
 *              and write the desired value thought 4 bit mode
 */
ERROR_STATUS LCD_Send (uint8_t Data)
{
   uint8_t au8_Data = ZERO;
	uint8_t au8_Error = E_OK;

	/*read port B value to get pin0 value*/
	au8_Error |= DIO_Read(GPIOB,PIN0,&au8_Data);

	/*mask pin0 value*/
	au8_Data &= 0x01;

	au8_Data = au8_Data | Data;

	au8_Error |= DIO_Write_Port(LCD_PORT, au8_Data);

	Error_Push(DIO_MODULE, UNKNOWN_ERROR);

	return au8_Error;
}

 /*************************************************************/
 /*************** APIS FUNCTION IMPLEMENTAION ****************/
 /***********************************************************/

 /**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the LCD.
 *
 */
 ERROR_STATUS LCD_init (void)
 {
    uint8_t au8_Error = E_OK;
	 uint8_t au8_Data = ZERO;

	 DIO_Cfg_s str_DIO_Info;

	 static uint8_t au8_LCD_InitState = SET_PINS;
	 static uint8_t au8_WaitCounter = WAIT_COUNTER_INITAIL_VALUE;
	 static uint8_t au8_Wait = ZERO;
	 static uint8_t au8_NextState = NOT_INITIALIZED;
	 static uint8_t au8_InitCommandCounter = INIT_COMMAND_INITAIL_VALUE;
    
	 if (INITIALIZED != gu8_LCD_InitFlag)
	 {
	    switch (au8_LCD_InitState)
	    {
		    case SET_PINS:
		    /*set LCD pins output*/
		    str_DIO_Info.GPIO = LCD_PORT;
		    str_DIO_Info.pins = LCD_RS|LCD_RW|LCD_EN|LCD_D4|LCD_D5|LCD_D6|LCD_D7;
		    str_DIO_Info.dir = OUTPUT;
		    au8_Error = DIO_init(&str_DIO_Info);

		    au8_Wait = INITIAL_WAIT ;

		    au8_LCD_InitState = WAIT;

			 /*the state after wait*/
		    au8_NextState = SET_4_BIT_MODE;
		    break;

		    case WAIT:
		    if (au8_Wait > au8_WaitCounter)
		    {
			    au8_WaitCounter++ ;
		    }
		    else if (au8_Wait == au8_WaitCounter)
		    {
			    /*return the counter to its iniail value*/
				 au8_WaitCounter = WAIT_COUNTER_INITAIL_VALUE;

			    au8_LCD_InitState = au8_NextState;
		    }
		    break;
			 /*********************************************************************************************************/
		    case SET_4_BIT_MODE:
		    /*set 4 bit mode*/
		    au8_Data = LCD_4_BIT_MODE_VALUE ;

		    au8_Error = LCD_Send(au8_Data);

		    LCD_SEND_ENABLE ;

		    WAIT_FOR_1_MS ;

		    au8_LCD_InitState = WAIT;

		    au8_NextState = SET_INIT_MODE;
		    break;
          /***************************************************************************************************************/
		    case SET_INIT_MODE:
		    if (INIT_COMMAND_INITAIL_VALUE == au8_InitCommandCounter)
		    {
			    /*4 bit mode, 2-line display mode, 5x8 font*/
			    au8_Error = LCD_SendCommand(LCD_4BIT_MODE_2LINE_DISPLAY_5_8_FONT);
			    au8_InitCommandCounter++ ;
		    }

		    else if (INIT_COMMAND_FIRST == au8_InitCommandCounter)
		    {
			    /*display off*/
			    au8_Error = LCD_SendCommand(LCD_DISPLAY_OFF);
			    au8_InitCommandCounter++ ;
		    }

		    else if (INIT_COMMAND_SECOND == au8_InitCommandCounter)
		    {
			    /*display on, blink cursor on*/
			    au8_Error = LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
			    au8_InitCommandCounter++ ;
		    }

		    else if (INIT_COMMAND_THIRD == au8_InitCommandCounter)
		    {
			    /*entry mode cursor move to right and DDRAM address is increased by 1*/
			    au8_Error = LCD_SendCommand(LCD_ENTERY_MODE_RIGHT_INCREASED);
			    gu8_LCD_InitFlag = INITIALIZED;
				 gu8_LCD_SencCommandFlag = NOT_INITIALIZED;
		    }
		    break;
	    }
	 } 
	 else 
	 {
	    Error_Push(LCD_MODULE, ERROR_ALREADY_INITIALIZED);
	 }
	 return au8_Error;
 }

 /**
 * Input: Command need to execute.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: execute LCD command.
 *
 */
 ERROR_STATUS LCD_SendCommand (uint8_t Command)
 {
	 uint8_t au8_Error = E_OK;
	 
	 uint8_t au8_SendCommand = ZERO;

	 static uint8_t au8_LCD_SendCommandState = NOT_INITIALIZED;

	 if (NOT_INITIALIZED == au8_LCD_SendCommandState)
	 {
	    /*SEND THE UPPER NIBBLE OF THE COMMAND*/
		 au8_SendCommand = Command & UPPER_NIBBLE;

	    au8_Error = LCD_Send(au8_SendCommand);

	    LCD_SEND_ENABLE ;

		 /*SEND THE LOWER NIBBLE OF THE COMMAND*/
	    au8_SendCommand = Command SHIFT_4_BIT_LEFT;
	    
	    au8_Error = LCD_Send(au8_SendCommand);

	    LCD_SEND_ENABLE ;

		 au8_LCD_SendCommandState = INITIALIZED ;
	 } 
	 else
	 {
	    gu8_LCD_SencCommandFlag = INITIALIZED;
		 au8_LCD_SendCommandState = NOT_INITIALIZED;
		 //delet task or return error
		 
	 }
	 
	 return au8_Error;
 }

 /**
 * Input: address of needed char in the LCD CGROM (ASCI).
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Display a character on LCD.
 *
 */
 ERROR_STATUS LCD_DisplayChar (uint8_t LCD_Char)
 {
    uint8_t au8_Error = E_OK;
	 
	 uint8_t au8_SendChar = ZERO;

	 static uint8_t au8_LCD_DisplayCharState = NOT_INITIALIZED;

	 if (NOT_INITIALIZED == au8_LCD_DisplayCharState)
	 {
	    /*get the upper nibble of the char*/
		 au8_SendChar = LCD_Char & UPPER_NIBBLE;

		 /*add send char confg*/
	    au8_SendChar = au8_SendChar | SEND_CHAR_CFG_VALUE;

	    au8_Error = LCD_Send(au8_SendChar);

	    LCD_SEND_ENABLE ;

		 /*get the lower nibble of the char*/
	    au8_SendChar = LCD_Char SHIFT_4_BIT_LEFT;

		 /*add send char confg*/
	    au8_SendChar |= SEND_CHAR_CFG_VALUE;
	    
	    au8_Error = LCD_Send(au8_SendChar);
	    
	    LCD_SEND_ENABLE ;

		 au8_LCD_DisplayCharState = INITIALIZED ;
		 
		 
	 } 
	 else if (INITIALIZED == au8_LCD_DisplayCharState)
	 { 
		 gu8_LCD_DisplayCharFlag = INITIALIZED;
		 au8_LCD_DisplayCharState = ZERO;
	 }


	 return au8_Error;
 }

 /**
 * Input: Pointer to a string and string size.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Display a string on LCD.
 *
 */
 ERROR_STATUS LCD_DisplayString (uint8_t * LCD_String, uint8_t String_Size)
 {
    uint8_t au8_Error = E_OK;
	 
	 static uint8_t au8_StringCounter = ZERO;

	 static uint8_t LCD_DisplayStringState = SENDING_CHAR;

	 if (NULL == LCD_String)
	 {
	    Error_Push(LCD_MODULE, ERROR_NULL_POINTER);
	 }
	 else
	 {
	    if (au8_StringCounter < String_Size)
	    {
		    switch(LCD_DisplayStringState)
		    {
			    /*send char*/
				 case SENDING_CHAR:
			    au8_Error = LCD_DisplayChar(LCD_String[au8_StringCounter]);
			    LCD_DisplayStringState = CHAR_SEND;
			    break;
				 /*display the char*/
			    case CHAR_SEND:
			    au8_Error = LCD_DisplayChar(LCD_String[au8_StringCounter]);
			    au8_StringCounter++ ;
			    LCD_DisplayStringState = SENDING_CHAR;
			    break;

			    default:
			    au8_Error = E_NOK;
			    break;
		    }
		    
	    }
	    else
	    {
		    gu8_LCD_DisplayStringFlag = INITIALIZED;
		    au8_StringCounter = ZERO;
	    }
	 }

	 return au8_Error;
 }
 
/**
* Input: Pointer to a string and string size and position (0:31).
* Output:
* In/Out:
* Return: The error status of the function.
* Description: Display a string on LCD on specific position.
*
*/
 ERROR_STATUS LCD_DisplayStringRowColumn (const uint8_t * LCD_String, uint8_t String_Size, uint8_t Pos)
 {
    uint8_t au8_Error = E_OK;
	 static uint8_t LCD_DisplayStringRowColumState = GO_TO;

	 /*check if the given pointer is null*/
	 if (NULL == LCD_String)
	 {
	    Error_Push(LCD_MODULE, ERROR_NULL_POINTER);
	 }
	 else
	 {
	    switch (LCD_DisplayStringRowColumState)
	    {
		    /*go to disered position*/
			 case GO_TO:
		    if (gu8_LCD_GoToRowColumFlag != INITIALIZED)
		    {
			    au8_Error = LCD_GoToRowColumn(Pos);
		    }
		    else
		    {
			    LCD_DisplayStringRowColumState = DISPLAY_STRING;
			    gu8_LCD_GoToRowColumFlag = NOT_INITIALIZED;
		    }
		    break;
		    /*********************************************************************************************************/
		    /*display the given string*/
			 case DISPLAY_STRING:
		    if (INITIALIZED != gu8_LCD_DisplayStringFlag)
		    au8_Error = LCD_DisplayString(LCD_String,String_Size);
		    else
		    {
			    gu8_LCD_DisplayStringFlag = NOT_INITIALIZED;
			    gu8_LCD_DisplayStringRowColumnFlag = INITIALIZED;
			    LCD_DisplayStringRowColumState = GO_TO;
		    }
		    break;
		    /***********************************************************************************************************/
		    default:
		    au8_Error = E_NOK;
		    break;
	    }
	 }

	 return au8_Error;
 }
 
 /**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Clear the LCD.
 *
 */
 ERROR_STATUS LCD_Clear (void)
 {
    uint8_t au8_Error = E_OK;
	 
	 au8_Error = LCD_SendCommand(LCD_CLEAR_COMMAND);

	 return au8_Error;
 }
 
 /**
 * Input:  position on the LCD (0:31)
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: go to specific position on the LCD.
 *
 */
 ERROR_STATUS LCD_GoToRowColumn (uint8_t Pos)
 {
    uint8_t au8_Error = E_OK;

	 /*check the pos in first or second line*/
	 if (Pos < LCD_COLOUM_SIZE )
    {
	    if (INITIALIZED != gu8_LCD_SencCommandFlag)
		 /*second the commend of go to first line with desired position*/
		    au8_Error = LCD_SendCommand(FIRST_ROW_FIRST_COLUME + Pos);
		 else
		 {
		    gu8_LCD_SencCommandFlag = NOT_INITIALIZED;
			 gu8_LCD_GoToRowColumFlag = INITIALIZED;
		 }
    }
	 else if ((Pos >= LCD_COLOUM_SIZE) && (Pos < 2 * LCD_COLOUM_SIZE))
	 {
	    if (INITIALIZED != gu8_LCD_SencCommandFlag)
	    {
		   /*second the commend of go to second line with desired position*/
			au8_Error = LCD_SendCommand(SECOND_ROW_FIRST_COLUME + Pos);
	    }
		 else
	    {
		    gu8_LCD_SencCommandFlag = NOT_INITIALIZED;
		    gu8_LCD_GoToRowColumFlag = INITIALIZED;
	    }
		 
	 }
	 else
	 {
	    Error_Push(LCD_MODULE, ERROR_INVALID_PARAMETER);
	 }

	 return au8_Error;
 }