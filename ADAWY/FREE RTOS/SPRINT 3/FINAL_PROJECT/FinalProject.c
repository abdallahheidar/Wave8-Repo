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

void UART_RecData (uint8_t Data);
void ReciveTask (void *pvParameters);
void TransmitTask (void *pvParameters);
void SystemInitTask (void *pvParameters);



TaskHandle_t TransmitTaskHAndle;
TaskHandle_t ReciveTaskHAndle;
TaskHandle_t SystemInitTaskHAndle;


void FinalProject (void)
{
    xTaskCreate (SystemInitTask, "R",100, NULL, 4,&SystemInitTaskHAndle);

    xTaskCreate (TransmitTask, "T", 200, NULL, 2,&TransmitTaskHAndle);

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
static int i = 0;
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
                au8_DataCounter++;
                
                while (NOT_INITIALIZED == gu8_LCD_DisplayCharFlag)
                {
                    LCD_DisplayChar(au8_KeyPadData); /*display the number on LCD*/
                    
                }
                gu8_LCD_DisplayCharFlag = NOT_INITIALIZED;
                
                xSemaphoreGive( SendDataSemaphoreHandle );
                
            }
            
        }
        
        
        pushButtonGetStatus(BTN_1,&au8_PBStatus);
        
        if ((Pressed == au8_PBStatus) && (pdTRUE == xSemaphoreTake( SendDataSemaphoreHandle, ( TickType_t ) 1 )))
        {
            Led_On(LED_1);
            xLEdLastWakeTime = xTaskGetTickCount();
            
            while (au8_DataCounter > au8_TransmitCounter)
            {
                UART_TRANSMIT_Char(arru8_TransmitArr[au8_TransmitCounter], NULL);
                au8_TransmitCounter++;
                
            }
            au8_DataCounter = DATA_COUNTER_INITIAL_VALUE;
            au8_TransmitCounter = TRANSMIT_COUNTER_INITIAL_VALUE;
            LCD_Clear();
            
            // Wait for the next cycle.
            vTaskDelayUntil( &xLEdLastWakeTime, 200 );
            
            Led_Off(LED_1);
             
        }
        
        
    }
}


void ReciveTask (void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1000;
    
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    while(1)
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        
        
    }
}


void UART_RecData (uint8_t Data)
{
    ;
}