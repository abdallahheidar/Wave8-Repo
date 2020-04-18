


#include "ECU/LCD/LCD.h"


#define LCD_DISPLAY_ON_CURSOR_OFF 0x0C

uint8_t gu8_DIO_Init_Return = E_OK;
uint8_t gu8_DIO_Write_Return = E_OK;
uint8_t gu8_DIO_Read_Return = E_OK;
uint8_t gu8_DIO_WritePort_Return = E_OK;



ERROR_STATUS LCD_init_Test (void);


ERROR_STATUS LCD_SendCommand_Test (void);

ERROR_STATUS LCD_DisplayChar_Test (void);


ERROR_STATUS LCD_DisplayString_Test (void);


ERROR_STATUS LCD_DisplayStringRowColumn_Test (void);


ERROR_STATUS LCD_Clear_Test (void);

ERROR_STATUS LCD_GoToRowColumn_Test (void);





int main (void)
{
	uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);

	printf("choose 1 for LCD_init_Test \n");
	printf("choose 2 for LCD_SendCommand_Test \n");
	printf("choose 3 for LCD_DisplayChar_Test \n");
	printf("choose 4 for LCD_DisplayString_Test \n");
	printf("choose 5 for LCD_DisplayStringRowColumn_Test \n");
	printf("choose 6 for LCD_Clear_Test \n");
	printf("choose 7 for LCD_GoToRowColumn_Test \n");


	printf("The number of the desired function to test is ");
	scanf("%d",&au8_Test_Func_Number);

	switch (au8_Test_Func_Number)
	{
	case 1:
		LCD_init_Test();
		break;

	case 2:
		LCD_SendCommand_Test();
		break;

	case 3:
		LCD_DisplayChar_Test();
		break;

	case 4:
		LCD_DisplayString_Test();
			break;

	case 5:
		LCD_DisplayStringRowColumn_Test();
			break;

	case 6:
		LCD_Clear_Test();
			break;

	case 7:
		LCD_GoToRowColumn_Test();
			break;
	default:
		printf("Invalid function number");
		break;
	}



	return 0;

}



ERROR_STATUS LCD_init_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_repeat = ZERO;
	uint8_t au8_Result = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCD_Init test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}



ERROR_STATUS LCD_SendCommand_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = ZERO;
	uint8_t au8_repeat = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			au8_Result = LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_SendCommand(0x100);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		case 5:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCD_SendCommand test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}



ERROR_STATUS LCD_DisplayChar_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = ZERO;
	uint8_t au8_repeat = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			au8_Result = LCD_DisplayChar('A');
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayChar('A');
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayChar('A');
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_DisplayChar('A');
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		case 5:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_DisplayChar('A');
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCD_DisplayChar test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}



ERROR_STATUS LCD_DisplayString_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = ZERO;
	uint8_t au8_repeat = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			au8_Result = LCD_DisplayString("AK",2);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayString(NULL,2);
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayString("AKS",42);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayString("AKS",42);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		case 5:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_DisplayString("AKS",42);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 6:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_DisplayString("AKS",42);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCd_displayString test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}



ERROR_STATUS LCD_DisplayStringRowColumn_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = ZERO;
	uint8_t au8_repeat = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn("AKS",3,0);
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn(NULL,3,0);
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn("ASD",3,55);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn("ASCB",3,0);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		case 5:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn(NULL,3,0);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 6:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn(NULL,3,0);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 7:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_DisplayStringRowColumn(NULL,3,0);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCD_DisplayStringRowColumn test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}



ERROR_STATUS LCD_Clear_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = ZERO;
	uint8_t au8_repeat = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			au8_Result = LCD_Clear();
			printf("The expected output is 1 and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_Clear();
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			au8_Result = LCD_Clear();
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			au8_Result = LCD_Clear();
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		case 5:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			au8_Result = LCD_Clear();
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCD_Clear test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}



ERROR_STATUS LCD_GoToRowColumn_Test (void)
{
	uint8_t au8_TestNumber = ZERO;
	uint8_t au8_Result = ZERO;
	uint8_t au8_repeat = ZERO;

	while (TRUE)
	{

		printf("Please enter test number: ");

		scanf("%d",&au8_TestNumber);

		switch (au8_TestNumber)
		{
		case 1:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			au8_Result = LCD_GoToRowColumn(2);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 2:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_GoToRowColumn(2);
			printf("The expected output is 0  and the actual output is %d", au8_Result);
			break;

		case 3:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_GoToRowColumn(99);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 4:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_OK;
			LCD_init();
			au8_Result = LCD_GoToRowColumn(2);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;


		case 5:
			gu8_DIO_Read_Return = E_OK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_GoToRowColumn(2);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		case 6:
			gu8_DIO_Read_Return = E_NOK;
			gu8_DIO_WritePort_Return = E_NOK;
			LCD_init();
			au8_Result = LCD_GoToRowColumn(2);
			printf("The expected output is 1  and the actual output is %d", au8_Result);
			break;

		default:
			printf("invalid test number");
			break;
		}

		printf("\nTo exit LCD_GoToRowColumn test press E or any char to continue ");
		scanf("%c", &au8_repeat);

		printf(" ");
		scanf("%c", &au8_repeat);

		if ('E'  == au8_repeat)
		{

			break;
		}

		printf(" ");
		scanf("%c", &au8_repeat);
	}

}
