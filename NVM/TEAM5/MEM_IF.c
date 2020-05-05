/*
 * MEMIF.c
 *
 * Created: 29/04/2020 00:17:25
 *  Author: sony
 */ 
/*******************************************************************
 *--------------------------- INCLUDES ----------------------------*
 *******************************************************************/

#include "MEM_IF.h"
#include "MEM_IF_Cfg.h"
#include "std_types.h"
#include "EEPROM_EXT.h"
#include "EEPROM_INT.h"


/*******************************************************************
 *------------------------- LOCLA MACROS --------------------------*
 *******************************************************************/
#define COUNTER_INITIAL_VALUE     0u
#define CLEAR_BLOCK_FLAG     0u
#define SET_BLOCK_FLAG       1u

/* main function status */
#define IDLE_STATUS          5u
#define LOGIC_STATUS         6u
#define WAIT_STATUS          7u

/*******************************************************************
 *----------------------- GLOBAL VARIABLES ------------------------*
 *******************************************************************/
static uint8_t gu8_WriteBlockFlag;
static uint8_t gu8_READ_BLOCK_FLAG;

static const uint8_t* gu8_DataPtr;
static uint8_t gu8_BlockNum;

static uint8_t gu8_MainFuncStatus;

/*******************************************************************
 *---------------------- API IMPLEMENTATIONS ----------------------*
 *******************************************************************/
void MEMIF_Init(void)
{
    /*initiate globla variables*/
    gu8_WriteBlockFlag = CLEAR_BLOCK_FLAG;
    gu8_READ_BLOCK_FLAG = CLEAR_BLOCK_FLAG;
    gu8_MainFuncStatus = IDLE_STATUS;
    gu8_DataPtr = NULL;
}


MEMIF_CheckType MEMIF_ReqWriteBlock(unsigned char BlockId,const unsigned char* DataPtr)
{
    MEMIF_CheckType au8_Return = MEMIF_OK; /*consider the return ok as initial value*/
    uint8_t au8_Counter = COUNTER_INITIAL_VALUE;
    uint8_t au8_LogicalBlockId;
    /*check if the pointer is null*/
    if (NULL == DataPtr)
    {
        au8_Return = MEMIF_NOK;
    }
    
    for(au8_Counter = COUNTER_INITIAL_VALUE; au8_Counter < MEMIF_NUM_OF_BLOCKS; au8_Counter++)
    {
        au8_LogicalBlockId = MEMIF_ConfigParam.BlockConfigPtr[au8_Counter].LogicalBlockId;
        /*ensure that given block id exist*/
        if (BlockId == au8_LogicalBlockId)
        {
            break;
        }
        
        if ( au8_Counter == (MEMIF_NUM_OF_BLOCKS - 1u) )
        {
            au8_Return = MEMIF_NOK;
        }
    }
    /*if the parameter is valid*/
    if (MEMIF_OK == au8_Return)
    {
        /*ensure that the module is available*/
        if (IDLE_STATUS != gu8_MainFuncStatus)
        {
            au8_Return = MEMIF_BUSY;
        } 
        else
        {
            /*stores the parameter in global variable to use it in main function*/
            gu8_DataPtr = DataPtr;
            gu8_BlockNum = au8_Counter;
            gu8_WriteBlockFlag = SET_BLOCK_FLAG; /*set write block flag*/
            gu8_MainFuncStatus = LOGIC_STATUS; /*change the main function status to logic status*/
        }
    }
    return au8_Return;
}

MEMIF_CheckType MEMIF_ReqReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
    MEMIF_CheckType au8_Return = MEMIF_OK;/*consider the return ok as initial value*/
    uint8_t au8_Counter,
            au8_LogicalBlockId;
    /*check if the pointer is null*/
    if (NULL == DataPtr)
    {
        au8_Return = MEMIF_NOK;
    }
    
    for(au8_Counter = COUNTER_INITIAL_VALUE; au8_Counter < MEMIF_NUM_OF_BLOCKS; au8_Counter++)
    {
        au8_LogicalBlockId = MEMIF_ConfigParam.BlockConfigPtr[au8_Counter].LogicalBlockId;
        /*ensure that given block id exist*/
        if (BlockId == au8_LogicalBlockId)
        {
            break;
        }
        
        if ( au8_Counter == (MEMIF_NUM_OF_BLOCKS - 1u) )
        {
            au8_Return = MEMIF_NOK;
        }
    }
    /*if the parameter is valid*/
    if (MEMIF_OK == au8_Return)
    {
        /*ensure that the module is available*/
        if (IDLE_STATUS != gu8_MainFuncStatus)
        {
            au8_Return = MEMIF_BUSY;
        }
        
        else
        {
            /*stores the parameter in global variable to use it in main function*/
            gu8_DataPtr = DataPtr;
            gu8_BlockNum = au8_Counter;
            gu8_READ_BLOCK_FLAG = SET_BLOCK_FLAG; /*set read block flag*/
            gu8_MainFuncStatus = LOGIC_STATUS; /*change the main function status to logic status*/
        }
    }
    return au8_Return;
}


void MEMIF_Main(void)
{
    uint8_t au8_StartAddress,
            au8_Length,
            au8_StorageType,
            au8_FuncReturn = EEINT_NOK; /*consider the return of called function is ok as initial value*/
            
    switch (gu8_MainFuncStatus)
    {
        case IDLE_STATUS:
        ;
        break;
        
        case LOGIC_STATUS:
        /*** get data from config structure ***/
        au8_StartAddress = MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockNum].BlockPhyAddress;
        
        au8_Length = MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockNum].BlockLength;
        
        au8_StorageType = MEMIF_ConfigParam.BlockConfigPtr[gu8_BlockNum].BlockStoragePlace;
        /*check if the desired operation is write operation*/
        if (SET_BLOCK_FLAG == gu8_WriteBlockFlag) 
        {
            /*check if the operation occurs on external or internal EEPROM*/
            if (INTERNAL_MEM == au8_StorageType)
            {
                /*write the desired data on internal EEPROM*/
                au8_FuncReturn = EEINT_ReqWrite(au8_StartAddress, gu8_DataPtr, au8_Length);
            } 
            
            else if (EXTERNAL_MEM == au8_StorageType)
            {
                /*write the desired data on external EEPROM*/
                au8_FuncReturn = EEEXT_ReqWrite(au8_StartAddress, gu8_DataPtr, au8_Length);
            }
            else
            {
                ;
            }
        } 
        /*check if the desired operation is read operation*/
        else if (SET_BLOCK_FLAG == gu8_READ_BLOCK_FLAG)
        {
            /*check if the operation occurs on external or internal EEPROM*/
            if (INTERNAL_MEM == au8_StorageType)
            {
                /*read the desired data from internal EEPROM*/
                au8_FuncReturn = EEINT_ReqRead(au8_StartAddress, gu8_DataPtr, au8_Length);
            }
            else if (EXTERNAL_MEM == au8_StorageType)
            {
                /*read the desired data from external EEPROM*/
                au8_FuncReturn = EEEXT_ReqRead(au8_StartAddress, gu8_DataPtr, au8_Length);
            }
            else
            {
                ;
            }
        }
        else
        {
            ;
        }
        
        if (  (EEINT_OK == au8_FuncReturn) || (EEEXT_OK == au8_FuncReturn) )
        {
            gu8_MainFuncStatus = WAIT_STATUS; /*move the status if the called function retrun ok*/
        }
        else
        {
            gu8_MainFuncStatus = LOGIC_STATUS;
        }
        break;
        
        case WAIT_STATUS:
        ;
        break;

        default:
        break;
    }        
}


void MEMIF_IntEepromWriteCbk(void)
{
    /*reset the flags and notify the MEMIF*/
    gu8_WriteBlockFlag = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    
    MEMIF_ConfigParam.BlockWriteDoneNotif();
}

void MEMIF_IntEepromReadCbk(void)
{
    /*reset the flags and notify the MEMIF*/
    gu8_READ_BLOCK_FLAG = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    
    MEMIF_ConfigParam.BlockReadDoneNotif();
}

void MEMIF_ExtEepromWriteCbk(void)
{
    /*reset the flags and notify the MEMIF*/
    gu8_WriteBlockFlag = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    
    MEMIF_ConfigParam.BlockWriteDoneNotif();
}

void MEMIF_ExtEepromReadCbk(void)
{
    /*reset the flags and notify the MEMIF*/
    gu8_READ_BLOCK_FLAG = CLEAR_BLOCK_FLAG;
    
    gu8_MainFuncStatus = IDLE_STATUS;
    
    MEMIF_ConfigParam.BlockReadDoneNotif();
}
