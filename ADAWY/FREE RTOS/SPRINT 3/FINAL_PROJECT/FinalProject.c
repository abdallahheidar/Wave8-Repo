/*
 * FinalProject.c
 *
 * Created: 4/18/2020 12:53:18 PM
 *  Author: K.Aladawy
 */ 
#include "FinalProject.h"

#define TRANSMIT_MAX_SIZE               6       
#define DATA_COUNTER_INITIAL_VALUE      0
#define TRANSMIT_COUNTER_INITIAL_VALUE  0

static void UART_RecData (uint8_t Data);
static void ReciveTask (void *pvParameters);
static void TransmitTask (void *pvParameters);
static void SystemInitTask (void *pvParameters);



static TaskHandle_t TransmitTaskHAndle;
static TaskHandle_t ReciveTaskHAndle;
static TaskHandle_t SystemInitTaskHAndle;
static SemaphoreHandle_t ReciveSemaphoreHandle; 
static uint8_t garru8_ReciveArr[TRANSMIT_MAX_SIZE];
static uint8_t gu8_ReciveDataSize = 0;
static uint8_t gu8_ReciveCounter = 0;

void FinalProject (void)
{
    xTaskCreate (SystemInitTask, "R",100, NULL, 4,&SystemInitTaskHAndle);

    xTaskCreate (TransmitTask, "T", 300, NULL, 2,&TransmitTaskHAndle);

    xTaskCreate (ReciveTask, "R", 200, NULL, 3,&ReciveTaskHAndle);
    

    /*Start Scheduler*/
    vTaskStartScheduler();
}


void SystemInitTask (void *pvParameters)
{
    
    
    while (1)
    {
        Led_Init(LED_0); /*initialize LED0*/
        
        Led_Init(LED_1); /*initialize LED1*/
        
        while(NOT_INITIALIZED == gu8_LCD_InitFlag)
        LCD_init(); /*initialize LCD module*/
        
        UART_INIT(Uart_Parity_no,Uart_Stop_Bit_One,Uart_Data_8_Bit,Uart_Baud_Rate_9600,Uart_Async_Normal_Speed,Uart_Multi_Processor_Communication_Disable,
                  Uart_Interrupt,UART_RecData); /*initialize UART module*/
                  
        pushButtonInit(BTN_1); /*initialize push button1*/
        
        KeyPad_Init();

        vTaskSuspend( SystemInitTaskHAndle );
        
    }
    
}


void TransmitTask (void *pvParameters)
{
    TickType_t xLastWakeTime;
    TickType_t xLEdLastWakeTime;
    const TickType_t xFrequency = 100;
    
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    uint8_t au8_KeyPadData = 255,
            au8_PBStatus    = Released,
            au8_TransmitCounter = TRANSMIT_COUNTER_INITIAL_VALUE,
            au8_SendFlag = 255,
            au8_DataCounter = DATA_COUNTER_INITIAL_VALUE;
    
    uint8_t arru8_TransmitArr[TRANSMIT_MAX_SIZE];
    
    static SemaphoreHandle_t SendDataSemaphoreHandle; 
    SendDataSemaphoreHandle = xSemaphoreCreateBinary();

    while(1)
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        
        keyPad_GetPressedkey(&au8_KeyPadData);
        
        if ( 255 != au8_KeyPadData) /*check if the keypad pressed*/
        {
            if ( au8_DataCounter < TRANSMIT_MAX_SIZE)
            {
                arru8_TransmitArr[au8_DataCounter] = au8_KeyPadData; /*store the number in transmit data array*/
                
                while(NOT_INITIALIZED == gu8_LCD_DisplayStringRowColumnFlag)
                {
                    LCD_DisplayStringRowColumn(&au8_KeyPadData,1,au8_DataCounter);
                }
                gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
                
                au8_DataCounter++;
                
                xSemaphoreGive( SendDataSemaphoreHandle );
            }
            
        }
        
        
        pushButtonGetStatus(BTN_1,&au8_PBStatus);
        
        if ((Pressed == au8_PBStatus) && (pdTRUE == xSemaphoreTake( SendDataSemaphoreHandle, ( TickType_t ) 1 )))
        {
            Led_On(LED_1);
            xLEdLastWakeTime = xTaskGetTickCount();
            
            UART_TRANSMIT_Char(au8_DataCounter +'0', NULL); /*send data size*/
            
            while (au8_DataCounter > au8_TransmitCounter)
            {
                UART_TRANSMIT_Char(arru8_TransmitArr[au8_TransmitCounter], NULL);
                au8_TransmitCounter++;
                
            }
            au8_DataCounter = DATA_COUNTER_INITIAL_VALUE;
            au8_TransmitCounter = TRANSMIT_COUNTER_INITIAL_VALUE;
            
            while(NOT_INITIALIZED == gu8_LCD_DisplayStringRowColumnFlag)
            {
                LCD_DisplayStringRowColumn((uint8_t*)"         ",TRANSMIT_MAX_SIZE,0);
            }
            
            gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
            
            // Wait for the next cycle.
            vTaskDelayUntil( &xLEdLastWakeTime, 200 );
            
            Led_Off(LED_1);
             
        }
        
        
    }
}


void ReciveTask (void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    
    ReciveSemaphoreHandle = xSemaphoreCreateBinary();
    
    while(1)
    {
        
        if (pdTRUE == xSemaphoreTake( ReciveSemaphoreHandle, ( TickType_t ) 50 ))
        {
            // Initialise the xLastWakeTime variable with the current time.
            xLastWakeTime = xTaskGetTickCount();
            
            Led_On(LED_0);
            
            while(NOT_INITIALIZED == gu8_LCD_DisplayStringRowColumnFlag)
            {
                 LCD_DisplayStringRowColumn(garru8_ReciveArr,gu8_ReciveDataSize,16);
            }
            gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
            
            gu8_ReciveDataSize = 0;
            gu8_ReciveCounter = 0;
            
            // Wait for the next cycle.
            vTaskDelayUntil( &xLastWakeTime, 500 );
            
            Led_Off(LED_0);
            
            // Wait for the next cycle.
            vTaskDelayUntil( &xLastWakeTime, 2000 );   
            
            while(NOT_INITIALIZED == gu8_LCD_DisplayStringRowColumnFlag)
            {
                LCD_DisplayStringRowColumn((uint8_t*)"         ",TRANSMIT_MAX_SIZE,16);
            }
            gu8_LCD_DisplayStringRowColumnFlag = NOT_INITIALIZED;
                          
        }        
    }
}


void UART_RecData (uint8_t Data)
{
    if (gu8_ReciveDataSize == 0)
    {
        gu8_ReciveDataSize = Data - '0';
    }
    else if (gu8_ReciveDataSize > gu8_ReciveCounter)
    {
        garru8_ReciveArr[gu8_ReciveCounter] = Data;
        
        gu8_ReciveCounter++;
    }
    
    if (gu8_ReciveDataSize == gu8_ReciveCounter)
    {
        xSemaphoreGive( ReciveSemaphoreHandle );
    }
}