#include "../std_types.h"
#include "../registers.h"
#include "../../MCAL/DIO/DIO.h"
#include<stdio.h>

extern uint8_t u8_DIO_PortInitFLag;



/////////////////					Test cases prototype 					///////////////////////////


// init function //
static void DIO_Init_TestCase_0(void);
static void DIO_Init_TestCase_1(void);
static void DIO_Init_TestCase_2(void);
static void DIO_Init_TestCase_3(void);
static void DIO_Init_TestCase_4(void);
static void DIO_Init_TestCase_5(void);
static void (*DIO_Init_TestCasesFun[6])(void)={DIO_Init_TestCase_0,DIO_Init_TestCase_1,DIO_Init_TestCase_2,DIO_Init_TestCase_3,DIO_Init_TestCase_4,DIO_Init_TestCase_5};
extern void Test_DIO_InilFun(void);


//		write function	//
static void DIO_Write_TestCase_0(void);
static void DIO_Write_TestCase_1(void);
static void DIO_Write_TestCase_2(void);
static void DIO_Write_TestCase_3(void);
static void DIO_Write_TestCase_4(void);
static void (*DIO_write_TestCasesFun[5])(void)={DIO_Write_TestCase_0,DIO_Write_TestCase_1,DIO_Write_TestCase_2,DIO_Write_TestCase_3,DIO_Write_TestCase_4};
extern void Test_DIO_writeFun(void);


// 			read function //
static void DIO_Read_TestCase_0(void);
static void DIO_Read_TestCase_1(void);
static void DIO_Read_TestCase_2(void);
static void DIO_Read_TestCase_3(void);
static void DIO_Read_TestCase_4(void);
static void (*DIO_Read_TestCasesFun[5])(void)={DIO_Read_TestCase_0,DIO_Read_TestCase_1,DIO_Read_TestCase_2,DIO_Read_TestCase_3,DIO_Read_TestCase_4};
extern void Test_DIO_ReadFun(void);


// 				toggle function 		//

static void DIO_Toggle_TestCase_0(void);
static void DIO_Toggle_TestCase_1(void);
static void DIO_Toggle_TestCase_2(void);
static void DIO_Toggle_TestCase_3(void);
static void (*DIO_Toggle_TestCasesFun[4])(void)={DIO_Toggle_TestCase_0,DIO_Toggle_TestCase_1,DIO_Toggle_TestCase_2,DIO_Toggle_TestCase_3};
extern void Test_DIO_ToggleFun(void);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////// 		Test cases implementation ////////////////////////////////////////

//  init fun. //
static void DIO_Init_TestCase_0(void){
	
	char ErrorStatus = 0;
	
	gstr_DIO_Cfg_t  DIO_Cfg={GPIOA,PIN3,OUTPUT};
	
	printf("Test case 0: Passing NULL Pointer :");

	
	ErrorStatus=DIO_init(NULL);
	
	if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_NULL_PTR)
	
	printf(" PASS\n\n\n");
	
	else 
	
		printf(" Faild\n\n\n");
}
static void DIO_Init_TestCase_2(void){
	
	char ErrorStatus=0;
	
	gstr_DIO_Cfg_t  DIO_Cfg={5,PIN3,OUTPUT};
	
	printf("Test case 2:Passing Invalide Port ID :");
	
	ErrorStatus=DIO_init(&DIO_Cfg);
	
	if(ErrorStatus == DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PORT )
		printf(" PASS\n\n\n");
	else 
		printf("Faild\n\n\n");
}
static void DIO_Init_TestCase_1(void){
	
	uint8_t ErrorStatus = 0;
	printf("Test case 1:\n");
	uint8_t * apu8_TestCaseName[]={"Passing  Port A as ","Passing  Port B as ","Passing  Port C as ","Passing  Port D as ","Output :","Input :"};
	uint8_t * apu8_Register[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	uint8_t au8_Direstion[]={0xFF,0x00};
	for (int j=0; j<2;j++)
	{
		for(int i=0;i<4;i++)
		{	
			printf("		""%s""%s",apu8_TestCaseName[i],apu8_TestCaseName[4+j]);
			gstr_DIO_Cfg_t  DIO_Cfg={i,PIN3,au8_Direstion[j]};
			ErrorStatus=DIO_init(&DIO_Cfg);
			
				
			if(*apu8_Register[i] == PIN3 ||*apu8_Register[i] == (~(PIN3)&*apu8_Register[i]) )
			{
				if(ErrorStatus==E_OK)	
				{	printf(" PASS\n\n\n");
					*apu8_Register[i]=0;
				}
			}
					
			else 
				printf(" Faild\n\n\n");
			
			ErrorStatus = 0;
		}
		u8_DIO_PortInitFLag=0;
	
	}
	u8_DIO_PortInitFLag=0;
		
	
	
}

static void DIO_Init_TestCase_3(void){
	
	char ErrorStatus=0;
	
	gstr_DIO_Cfg_t  DIO_Cfg={GPIOA,PIN3,44};
	
	printf("Test case 2:Passing Invalide Value :");
	
	ErrorStatus=DIO_init(&DIO_Cfg);
	
	if(ErrorStatus == DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_VALUE )
		printf(" PASS\n\n\n");
	else 
		printf("Faild\n\n\n");
}

static void DIO_Init_TestCase_4(void){
	
	char ErrorStatus=0;
	
	gstr_DIO_Cfg_t  DIO_Cfg={GPIOA,PIN3,OUTPUT};
	
	printf("Test case 4 :MULTIPLE INIT. For same Port ID :");
	
	ErrorStatus=DIO_init(&DIO_Cfg);
	ErrorStatus=DIO_init(&DIO_Cfg);
	
	if(ErrorStatus == DIO_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT )
		printf(" PASS\n\n\n");
	else 
		printf("Faild\n\n\n");
}

static void DIO_Init_TestCase_5(void){
	
	char ErrorStatus=0;
	
	gstr_DIO_Cfg_t  DIO_Cfg={GPIOA,PIN3,OUTPUT};
	
	printf("Test case 5 :MULTIPLE INIT. For different Port ID :");
	
	ErrorStatus=DIO_init(&DIO_Cfg);
    DIO_Cfg.u8_GPIO = GPIOB;
	ErrorStatus=DIO_init(&DIO_Cfg);
    DIO_Cfg.u8_GPIO = GPIOC;
	ErrorStatus=DIO_init(&DIO_Cfg);
    DIO_Cfg.u8_GPIO = GPIOD;
	ErrorStatus=DIO_init(&DIO_Cfg);
	
	if(ErrorStatus == E_OK )
		printf(" PASS\n\n\n");
	else 
		printf("Faild\n\n\n");
}

extern void Test_DIO_InilFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST DIO INIT FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 6 ; Test_Case_Stage ++ )
	{
		DIO_Init_TestCasesFun[Test_Case_Stage]();
		
	}
}



// write fun. 	//
static void DIO_Write_TestCase_0(void){
	
	char ErrorStatus = 0;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A - PIN/s status  ","FOR Port B - PIN/s status ","FOR Port C - PIN/s status  ","FOR Port D - PIN/s status  ","HIGH:","LOW :"};
	uint8_t * apu8_PortDirRegister[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0xff;
	}
	uint8_t * apu8_Register[]={&PORTA_DATA,&PORTB_DATA,&PORTC_DATA,&PORTD_DATA};
	uint8_t au8_Value[]={0xFF,0x00};

	printf("Test case 0: PAssing valide argmement: \n");
	for (int j=0; j<2;j++)
	{
		for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("		""%s""%s",apu8_TestCaseName[PORT_ID],apu8_TestCaseName[4+j]);
			
			ErrorStatus = DIO_Write(PORT_ID,PIN3,au8_Value[j]);
			
			if(*apu8_Register[PORT_ID] == PIN3 ||(*apu8_Register[PORT_ID] == (~(PIN3)&*apu8_Register[PORT_ID])) )
			{
				if(ErrorStatus==E_OK)	
				{	printf(" PASS\n\n\n");
					
					*apu8_Register[PORT_ID]=0;
				}
			}
						
			else 
			{
				printf(" Faild\n\n\n");
			}		
			ErrorStatus = 0;
		}
	}
	u8_DIO_PortInitFLag=0;
}

static void DIO_Write_TestCase_1(void){
	
	char ErrorStatus = 0;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	printf("Test case 1: Passing invalide value : \n");
	
		for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("		""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Write(PORT_ID,PIN3,7);
			
				if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_VALUE )	
				{	printf(" PASS\n\n\n");
					
				}	
				else 
				{
					printf(" Faild\n\n\n");
				}		
			ErrorStatus = 0;
		}
		u8_DIO_PortInitFLag=0;
	}
	
static void DIO_Write_TestCase_2(void){
	
	char ErrorStatus = 0;
	u8_DIO_PortInitFLag=0x0f;
	printf("Test case 2: Passing invalide Port ID: ");
			
	ErrorStatus = DIO_Write(4,PIN3,0xff);
	
		if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PORT  )	
		{	
			printf(" PASS\n\n\n");	
		}	
		else 
		{
			printf(" Faild\n\n\n");
		}		
	
	u8_DIO_PortInitFLag=0;
	}
		
static void DIO_Write_TestCase_3(void){
	
	uint8_t ErrorStatus = 0;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	printf("\n\n\nTest case 3: Calling write fun. without init :\n\n\n ");
			
	for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("					      ""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Write(PORT_ID,PIN3,0xff);
			
				if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PORT )	
				{	printf(" PASS\n\n\n");
					
				}	
				else 
				{
					printf(" Faild\n\n\n");
				}		
			ErrorStatus = 0;
		}
	
	u8_DIO_PortInitFLag=0;
	}	
	
static void DIO_Write_TestCase_4(void){
	
	char ErrorStatus = 0;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	uint8_t * apu8_PortDirRegister[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0x00;
	}
	

	printf("Test case 4: calling the funcion with wrong cfg: \n");

	
		for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("		""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Write(PORT_ID,PIN3,0xff);
		
		
			if(ErrorStatus== DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_CFG)	
			{	
				printf(" PASS\n\n\n");	
			}
					
			else 
			{
				printf(" Faild\n\n\n");
			}		
			ErrorStatus = 0;
		}
	
	u8_DIO_PortInitFLag=0;
}	

extern void Test_DIO_writeFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST DIO Write FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 5 ; Test_Case_Stage ++ )
	{
		DIO_write_TestCasesFun[Test_Case_Stage]();
		
	}
}	
	

// read fun. //

static void DIO_Read_TestCase_0(void){
	
	uint8_t ErrorStatus = 0, u8_ActualOutput;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	uint8_t * apu8_ExpectedOutput[]={&PORTA_PIN,&PORTB_PIN,&PORTC_PIN,&PORTD_PIN};
	uint8_t * apu8_PortDirRegister[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0x00;
	}
	for(int i=0;i<4;i++)
	{
		*apu8_ExpectedOutput[i]=0xff;
	}
	printf("Test case 0: Passing valide argmement: \n");
	
	for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
	{	
		printf("		""%s",apu8_TestCaseName[PORT_ID]);
		
		ErrorStatus = DIO_Read(PORT_ID,PIN3,&u8_ActualOutput);
		
		if( u8_ActualOutput == (*apu8_ExpectedOutput[PORT_ID]&PIN3) )
		{
			if(ErrorStatus==E_OK)	
			{	
				printf(" PASS\n\n\n");
			}	
		}	
				
		else 
		{
			printf(" Faild\n\n\n");
		}
		u8_ActualOutput=0;		
		ErrorStatus = 0;
	}
	
	u8_DIO_PortInitFLag=0;
}	
	
	
static void DIO_Read_TestCase_1(void){
	
	uint8_t ErrorStatus = 0, u8_ActualOutput;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	
	printf("Test case 1: Passing NULL Pointer :\n");
	for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
	{	
		printf("		""%s",apu8_TestCaseName[PORT_ID]);

		ErrorStatus = DIO_Read(PORT_ID,PIN3,NULL);
		
		if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_NULL_PTR)
		
		printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild\n\n\n");
	}
		
	u8_DIO_PortInitFLag=0x00;
}

static void DIO_Read_TestCase_2(void){
	
	uint8_t ErrorStatus = 0 , u8_ActualOutput;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	printf("\n\n\nTest case 2: Calling Read fun. without init :\n\n\n ");
			
	for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("					      ""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Read(PORT_ID,PIN3,&u8_ActualOutput);
			
				if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PORT )	
				{	printf(" PASS\n\n\n");
					
				}	
				else 
				{
					printf(" Faild\n\n\n");
				}		
			ErrorStatus = 0;
		}
	
	u8_DIO_PortInitFLag=0;
	}	
	
static void DIO_Read_TestCase_3(void){
	
	char ErrorStatus = 0, u8_ActualOutput;
	u8_DIO_PortInitFLag=0x0f;
	printf("Test case 3: Passing invalide Port ID: ");
			
	ErrorStatus = DIO_Read(4,PIN3,&u8_ActualOutput);
	
		if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PORT  )	
		{	
			printf(" PASS\n\n\n");	
		}	
		else 
		{
			printf(" Faild\n\n\n");
		}		
	
	u8_DIO_PortInitFLag=0;
	}

static void DIO_Read_TestCase_4(void){
	
	char ErrorStatus = 0 ,u8_ActualOutput;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	uint8_t * apu8_PortDirRegister[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0xff;
	}
	

	printf("Test case 4: calling the funcion with wrong cfg: \n");

	
		for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("		""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Read(PORT_ID,PIN3,&u8_ActualOutput);
		
		
			if(ErrorStatus== DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_CFG)	
			{	
				printf(" PASS\n\n\n");	
			}
					
			else 
			{
				printf(" Faild  %d \n\n\n",ErrorStatus);
			}		
			ErrorStatus = 0;
		}
	
	u8_DIO_PortInitFLag=0;
}	
	
extern void Test_DIO_ReadFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST DIO Read FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 5 ; Test_Case_Stage ++ )
	{
		DIO_Read_TestCasesFun[Test_Case_Stage]();
		
	}
}	



	
// toggle fun //
static void DIO_Toggle_TestCase_0(void){
	
	uint8_t ErrorStatus = 0, u8_ActualOutput;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	uint8_t * apu8_PortDataRegister[]={&PORTA_DATA,&PORTB_DATA,&PORTC_DATA,&PORTD_DATA};
	uint8_t * apu8_PortDirRegister[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0xff;
	}
	printf("Test case 0: Passing valide argmement: \n");
	
	for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
	{	
		printf("		""%s",apu8_TestCaseName[PORT_ID]);
		
		ErrorStatus = DIO_Toggle(PORT_ID,PIN3);
		u8_ActualOutput= * apu8_PortDataRegister[PORT_ID];
		if( u8_ActualOutput == (0x00^PIN3) )
		{
			if(ErrorStatus==E_OK)	
			{	
				printf(" PASS\n\n\n");
			}
		}
			
		else 
		{
			printf(" Faild\n\n\n");
		}
		u8_ActualOutput=0;		
		ErrorStatus = 0;
	}
	
	u8_DIO_PortInitFLag=0;
	
		for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0x00;
	}
}	

	
static void DIO_Toggle_TestCase_1(void){
	
	char ErrorStatus = 0;
	u8_DIO_PortInitFLag=0x0f;
	printf("Test case 1: Passing invalide Port ID: ");
			
	ErrorStatus = DIO_Toggle(4,PIN3);
	
		if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PORT  )	
		{	
			printf(" PASS\n\n\n");	
		}	
		else 
		{
			printf(" Faild\n\n\n");
		}		
	
	u8_DIO_PortInitFLag=0;
	}
	
static void DIO_Toggle_TestCase_2(void){
	
	uint8_t ErrorStatus = 0 ;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	printf("\n\n\nTest case 2: Calling Read fun. without init :\n\n\n ");
			
	for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("					      ""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Toggle(PORT_ID,PIN3);
			
				if(ErrorStatus==DIO_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PORT )	
				{	printf(" PASS\n\n\n");
					
				}	
				else 
				{
					printf(" Faild\n\n\n");
				}		
			ErrorStatus = 0;
		}
	
	u8_DIO_PortInitFLag=0;
	}	
		
static void DIO_Toggle_TestCase_3(void){
	
	char ErrorStatus = 0 ;
	u8_DIO_PortInitFLag=0x0f;
	uint8_t * apu8_TestCaseName[]={"FOR Port A : ","FOR Port B : ","FOR Port C : ","FOR Port D : "};
	uint8_t * apu8_PortDirRegister[]={&PORTA_DIR,&PORTB_DIR,&PORTC_DIR,&PORTD_DIR};
	for(int i=0;i<4;i++)
	{
		*apu8_PortDirRegister[i]=0x00;
	}
	

	printf("Test case 4: calling the funcion with wrong cfg: \n");

	
		for(int PORT_ID=0;PORT_ID<4;PORT_ID++) 
		{	
			printf("		""%s",apu8_TestCaseName[PORT_ID]);
			
			ErrorStatus = DIO_Toggle(PORT_ID,PIN3);
		
		
			if(ErrorStatus== DIO_MODULE_ERROR_NUMBER + ERROR_INVALIDE_CFG)	
			{	
				printf(" PASS\n\n\n");	
			}
					
			else 
			{
				printf(" Faild\n\n\n");
			}		
			ErrorStatus = 0;
		}
	
	u8_DIO_PortInitFLag=0;
}	

extern void Test_DIO_ToggleFun(void){

	char Test_Case_Stage=0;

	printf("\n                      TEST DIO Toggle FUNCTION\n\n");

	for( ; Test_Case_Stage < 4 ; Test_Case_Stage ++ )
	{
		DIO_Toggle_TestCasesFun[Test_Case_Stage]();
		
	}
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	