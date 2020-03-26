/*
 * TIMERS_Test.c
 *
 *  Created on: Mar 25, 2020
 *      Author: Khaled
 */

#include "TIMERS_Test.h"

#define RESULT_INITIAL_VALUE  6



static void Timer_Init_Test (void);
static void Timer_Start_Test (void);
static void Timer_Stop_Test (void);
static void Timer_Get_Value_Test (void);
static void Timer_Set_Value_Test (void);
static void Timer_Get_Status_Test (void);


void TIMERS_Test (void)
{
	uint8_t au8_func=0;
	uint8_t au8_Exit ='c';


	printf("1-TIMERS INIT \n");
	printf("2-TIMERS START \n");
	printf("3-TIMERS STOP  \n");
	printf("4-TIMERS GET VALUE \n");
	printf("5-TIMERS SET VALUE \n");
	printf("6-TIMERS GET STATUS \n");
	printf("choose number of function: ");
	scanf("%d",&au8_func);


	switch (au8_func)
	{
	case 1:
		Timer_Init_Test();
		break;

	case 2:
		Timer_Start_Test();
		break;

	case 3:
		Timer_Stop_Test();
		break;

	case 4:
		Timer_Get_Value_Test();
		break;

	case 5:
		Timer_Set_Value_Test();
		break;
	case 6:
		Timer_Get_Status_Test();
		break;

	default:
		break;
	}

}


void Timer_Init_Test (void)
{
	Timer_Cfg_ST Timer_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;


	/*case 1*/
	au8_Result = Timer_Init(NULL);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 1  passed \n");

	else
		printf("        test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	au8_Result = Timer_Init(&Timer_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("     test case 2  passed \n");

	else
		printf("     test case 2  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 3*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = 5;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	au8_Result = Timer_Init(&Timer_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("   test case 3  passed \n");

	else
		printf("   test case 3  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 4*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_0;
	Timer_Info.Timer_Interrupt_Mode = 5;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	au8_Result = Timer_Init(&Timer_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("   test case 4  passed \n");

	else
		printf("   test case 4  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 5*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_0;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = 5;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	au8_Result = Timer_Init(&Timer_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("   test case 5  passed \n");

	else
		printf("   test case 5  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 6*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_0;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_32;
	au8_Result = Timer_Init(&Timer_Info);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("   test case 6  passed \n");

	else
		printf("   test case 6  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 7*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_0;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	au8_Result = Timer_Init(&Timer_Info);


	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                         test case 7  passed \n");

	else
		printf("                                                         test case 7  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 8*/
	au8_Result = Timer_Init(&Timer_Info);


	Error_Print();

	if(E_NOK == au8_Result)
		printf(" test case 8  passed \n");

	else
		printf("  test case 8  failed \n");

	Error_Dinit();





}


void Timer_Start_Test (void)
{
	Timer_Cfg_ST Timer_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;


	/*case 1*/
	au8_Result = Timer_Start(Timer_2,150);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 1  passed \n");

	else
		printf("        test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_2;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	Timer_Init(&Timer_Info);

	au8_Result = Timer_Start(Timer_1,150);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("        test case 2  passed \n");

	else
		printf("        test case 2  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 3*/
	au8_Result = Timer_Start(Timer_2,1500);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("      test case 3  passed \n");

	else
		printf("      test case 3  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 4*/
	au8_Result = Timer_Start(Timer_2,150);

	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                            test case 4  passed \n");

	else
		printf("                                                            test case 4  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
}


void Timer_Stop_Test (void)
{
	Timer_Cfg_ST Timer_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;

	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_2;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	Timer_Init(&Timer_Info);


	/*case 1*/
	au8_Result = Timer_Stop(Timer_2);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 1  passed \n");

	else
		printf("               test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	Timer_Start(Timer_2,100);

	au8_Result = Timer_Stop(Timer_1);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 2  passed \n");

	else
		printf("               test case 2  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 3*/
	au8_Result = Timer_Stop(50);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("      test case 3  passed \n");

	else
		printf("      test case 3  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 4*/
	au8_Result = Timer_Stop(Timer_2);

	Error_Print();

	if(E_OK == au8_Result)
		printf("                                                            test case 4  passed \n");

	else
		printf("                                                            test case 4  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
}


void Timer_Get_Value_Test (void)
{
	Timer_Cfg_ST Timer_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint16_t au16_Data = ZERO;


	/*case 1*/
	au8_Result = Timer_Get_Value(Timer_2,&au16_Data);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 1  passed \n");

	else
		printf("               test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_2;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	Timer_Init(&Timer_Info);


	au8_Result = Timer_Get_Value(Timer_1,&au16_Data);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 2  passed \n");

	else
		printf("               test case 2  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 3*/
	au8_Result = Timer_Get_Value(Timer_2,NULL);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("                  test case 3  passed \n");

	else
		printf("                  test case 3  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 4*/
	TCNT2 = 100;
	au8_Result = Timer_Get_Value(Timer_2,&au16_Data);

	Error_Print();

	if((E_OK == au8_Result) && (TCNT2 == au16_Data))
		printf("                        and get correct value                      test case 4  passed \n");

	else
		printf("                                                                   test case 4  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
}


void Timer_Set_Value_Test (void)
{
	Timer_Cfg_ST Timer_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;



	/*case 1*/
	au8_Result = Timer_Set_Value(Timer_2,100);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 1  passed \n");

	else
		printf("               test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_2;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	Timer_Init(&Timer_Info);


	au8_Result = Timer_Set_Value(Timer_1,100);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 2  passed \n");

	else
		printf("               test case 2  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 3*/
	au8_Result = Timer_Set_Value(Timer_2,1000);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("             test case 3  passed \n");

	else
		printf("             test case 3  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 4*/
	TCNT2 = 100;
	au8_Result = Timer_Set_Value(Timer_2,100);

	Error_Print();

	if((E_OK == au8_Result) && (TCNT2 == 100))
		printf("                        and set correct value                      test case 4  passed \n");

	else
		printf("                                                                   test case 4  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
}


void Timer_Get_Status_Test (void)
{
	Timer_Cfg_ST Timer_Info;
	uint8_t au8_Result = RESULT_INITIAL_VALUE;
	uint8_t au8_Data = ZERO;


	/*case 1*/
	au8_Result = Timer_Get_Status(Timer_2,&au8_Data);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 1  passed \n");

	else
		printf("               test case 1  failed \n");

	Error_Dinit();
	/*********************************************************************************************/
	/*case 2*/
	Timer_Info.Ptr_TCB_Function = NULL;
	Timer_Info.Timer_Ch = Timer_2;
	Timer_Info.Timer_Interrupt_Mode = TIMER_MODE_POLLING;
	Timer_Info.Timer_Mode = TIMER_MODE;
	Timer_Info.Timer_PreScaler = PRESCALER_1;
	Timer_Init(&Timer_Info);


	au8_Result = Timer_Get_Status(Timer_1,&au8_Data);;

	Error_Print();

	if(E_NOK == au8_Result)
		printf("               test case 2  passed \n");

	else
		printf("               test case 2  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 3*/
	au8_Result = Timer_Get_Status(Timer_2,NULL);

	Error_Print();

	if(E_NOK == au8_Result)
		printf("                  test case 3  passed \n");

	else
		printf("                  test case 3  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
	/*case 4*/
	CLEAR_BIT(TIFR,BIT6);
	au8_Result = Timer_Get_Status(Timer_2,&au8_Data);;

	Error_Print();
     /*not equal because get status reset the status after read it*/
	if((E_OK == au8_Result) && (ZERO == au8_Data))
		printf("                        and get correct status                     test case 4  passed \n");

	else
		printf("                                                                   test case 4  failed \n");

	Error_Dinit();
	/***********************************************************************************************/
}
