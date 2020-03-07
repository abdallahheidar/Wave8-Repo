#include "BCM_unit_Testing.h"
#include "../SL/Utilis/std_types.h"
#include "../SL/Utilis/module_retval.h"
#include "../SL/BCM/BCM.h"
uint8_t gu8_UART_Init_Return;
uint8_t gu8_SPI_Init_Return;


void BCM_Init_Test_Cases()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n\n");
   printf("choose 1 for Test NULL Pointer with taking into consideration UART and SPI are working well \n");
   printf("choose 2 for Test Not NULL Pointer with taking into consideration UART and SPI are working well \n");
   printf("choose 3 for Test Invalid Pre Configuration value \n");
   printf("choose 4 for Test Invalid Channel Parameter \n");
   printf("choose 5 for Test Multiple Init  \n");
   printf("\n\n");
   printf("Enter The number of the desired Test Case ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
      case 1: BCM_Init_Test_1(); break;
      case 2: BCM_Init_Test_2(); break;
      case 3: BCM_Init_Test_3(); break;
      case 4: BCM_Init_Test_4(); break;
      case 5: BCM_Init_Test_5(); break;
      default: printf("Invalid Test Case number"); break;
    }

}

void BCM_Init_Test_1()
{
   ERROR_STATUS u8_Ret_Rerror = E_OK;
   printf(" Test Case is To Check Null Parameter\n\n ");
   u8_Ret_Rerror = BCM_Init (NULL );
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
   }
   else
   {
       printf("FAILED",u8_Ret_Rerror);
       Error_Print();
   }
}

void BCM_Init_Test_2()
{
   ERROR_STATUS u8_Ret_Rerror = E_OK;
   gstr_BCM_Config_t  ConfigPtr = {1,0,0} ;
   //set UART return function as E_NOk
   gu8_UART_Init_Return = E_NOK;
   printf(" Test Case is To Check Channel initialization \n\n ");
   u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }

}
void BCM_Init_Test_3()
{
   ERROR_STATUS u8_Ret_Rerror = E_OK;
   gstr_BCM_Config_t  ConfigPtr = {0,SPI_Channel_1,0} ;

   printf(" Test Case is To Check Invalid Pre Configuration value\n\n ");
   u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
}

void BCM_Init_Test_4()
{
   ERROR_STATUS u8_Ret_Rerror = E_OK;
   gstr_BCM_Config_t  ConfigPtr = {4,0,0} ;
   printf(" Test Case is To Check Invalid Channel Parameter\n\n ");
   u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }

}

void BCM_Init_Test_5()
{
   ERROR_STATUS u8_Ret_Rerror = E_OK;
   gstr_BCM_Config_t  ConfigPtr = {1,0,0} ;

   printf(" Test Case is To Check Multiple Init \n\n ");
   u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
}

/*************************************************************************************/

void BCM_Send_Test_Cases()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n\n");
   printf("choose 1 for Test BCM is Already Initialized Before Sending \n");
   printf("choose 2 for Test NULL Pointer Parameter \n");
   printf("choose 3 for Test Invalid Channel Parameter \n");
   printf("choose 4 for Test Invalid Size Parameter \n");
   printf("choose 5 for Test Multiple Init  \n");
   printf("\n\n");
   printf("Enter The number of the desired Test Case ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
      case 1: BCM_Send_Test_1(); break;
      case 2: BCM_Send_Test_2(); break;
      case 3: BCM_Send_Test_3(); break;
      case 4: BCM_Send_Test_4(); break;
      default: printf("Invalid Test Case number"); break;
    }

}

void BCM_Send_Test_1()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;

   printf(" Test Case is To Check BCM Not Initialized \n\n ");
   u8_Ret_Rerror = BCM_Send (NULL, 100, UART_Channel_1);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}

void BCM_Send_Test_2()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   printf(" Test Case is To Check Null Parameter\n\n ");
   u8_Ret_Rerror = BCM_Send (NULL, 100, SPI_Channel_1);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}

void BCM_Send_Test_3()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    uint8_t u8_test=0 ;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   printf(" Test Case is To Check Invalid Parameter\n\n ");
   u8_Ret_Rerror = BCM_Send (&u8_test, 100, 4);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}

void BCM_Send_Test_4()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    uint8_t u8_test=0 ;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   printf(" Test Case is To Check Invalid Parameter\n\n ");
   u8_Ret_Rerror = BCM_Send (&u8_test, 0, SPI_Channel_1);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}


/*****************************************************************************/

void BCM_Receive_Test_Cases()
{
   uint8_t au8_Test_Case_Number = ZERO;
   printf("Please Enter the number of the required Test case \n\n");
   printf("choose 1 for Test If BCM is Already Initialized Before Receiving\n");
   printf("choose 2 for Test NULL Pointer Parameter \n");
   printf("choose 3 for Test NULL Pointer Parameter for consumer function \n");
   printf("choose 4 for Test Invalid Channel Parameter \n");
   printf("choose 5 for Test Invalid Size Parameter \n");
   printf("\n\n");
   printf("Enter The number of the desired Test Case ");
   scanf("%d",&au8_Test_Case_Number);
   printf("\n");
   switch (au8_Test_Case_Number)
   {
      case 1: BCM_Receive_Test_1(); break;
      case 2: BCM_Receive_Test_2(); break;
      case 3: BCM_Send_Test_3(); break;
      case 4: BCM_Send_Test_4(); break;
      default: printf("Invalid Test Case number"); break;
    }

}


void BCM_Receive_Test_1()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    BCM_Rx_Call_Back_ptr Func_ptr;
    uint8_t u8_test=0 ;
   printf(" Test Case is To Check BCM Not Initialized \n\n ");
   u8_Ret_Rerror = BCM_Receive(&u8_test, 100, SPI_Channel_1,Func_ptr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}

void BCM_Receive_Test_2()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    BCM_Rx_Call_Back_ptr Func_ptr;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);

   printf(" Test Case is To Check Null Parameter \n\n ");
   u8_Ret_Rerror = BCM_Receive(NULL, 100, SPI_Channel_1,Func_ptr);

   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}

void BCM_Receive_Test_3()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    uint8_t u8_test;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);

   printf(" Test Case is To Check Null Parameter \n\n ");
   u8_Ret_Rerror = BCM_Receive(&u8_test, 100, SPI_Channel_1,NULL);

   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}

ERROR_STATUS BCM_Receive_Test_4()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    BCM_Rx_Call_Back_ptr Func_ptr;
    uint8_t u8_test;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   printf(" Test Case is To Check Invalid Channel Parameter \n\n ");
   u8_Ret_Rerror = BCM_Receive(&u8_test, 100, 4,Func_ptr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}


ERROR_STATUS BCM_Receive_Test_5()
{
    ERROR_STATUS u8_Ret_Rerror = E_OK;
    BCM_Rx_Call_Back_ptr Func_ptr;
    uint8_t u8_test;
    gstr_BCM_Config_t  ConfigPtr = {0,0,0} ;
    u8_Ret_Rerror = BCM_Init (&ConfigPtr);
   printf(" Test Case is To Check Invalid Size Parameter \n\n ");
   u8_Ret_Rerror = BCM_Receive(&u8_test, 0, SPI_Channel_1,Func_ptr);
   if (u8_Ret_Rerror == E_NOK)
   {
       printf("SUCCEED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }
   else
   {
       printf("FAILED\n",u8_Ret_Rerror);
       Error_Print();
       printf("\n");
   }


}


/************************************************************************************/

void BCM_TxDispatch_Test_1()
{
   printf(" Test Case is To Check BCM Not Initialized \n\n ");
   printf("SUCCEED\n");
   BCM_TxDispatch();
   Error_Print();

}


/****************************************************************************************/

void BCM_RxDispatch_Test_1()
{
   printf(" Test Case is To Check BCM Not Initialized \n\n ");
   printf("SUCCEED\n");
   BCM_RxDispatch();
   Error_Print();

}


