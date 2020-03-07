/*
 * BCM_Unit_Testing.c
 *
 * Created: 3/5/2020 1:53:36 PM
 * Author : Aya and Fathy
 */

#include <stdio.h>
#include <stdlib.h>
#include "Testing/BCM_unit_Testing.h"
int main()
{
    uint8_t au8_Test_Func_Number = ZERO;
	//line to correct error in IDE related to printf and scanf functions
	setvbuf(stdout,NULL,_IONBF,0);

	printf("choose 1 for BCM_Init \n");
	printf("choose 2 for BCM_Send \n");
	printf("choose 3 for BCM_Receive \n");
	printf("choose 4 for BCM_TxDispatch\n");
    printf("choose 5 for BCM_RxDispatch\n");
	printf("The number of the desired function to test is ");
	scanf("%d",&au8_Test_Func_Number);
    printf("\n\n");
	switch (au8_Test_Func_Number)
	{
	case 1: BCM_Init_Test_Cases(); break;

	case 2: BCM_Send_Test_Cases(); break;

	case 3: BCM_Receive_Test_Cases(); break;

    case 4: BCM_TxDispatch_Test_1(); break;
    case 5: BCM_RxDispatch_Test_1(); break;
	default:
    printf("Invalid function number");
    break;
	}
	return 0;
}

