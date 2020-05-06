/*
 * NVM.c
 *
 * Created: 29/04/2020 20:01:42
 *  Author: sony
 */ 
#include "NVM.h"
#include "NVM_Cfg.h"
#define UDR                  *((reg_type8_t)(0X2C))
#define IDLE_STATE                  0
#define READ_ALL_STATE          	1
#define WRITE_ALL_STATE         	2
#define READ_ALL_DONE_STATE     	3
#define WRITE_ALL_DONE_STATE    	4
#define READ_BLOCK_STATE        	5
#define WRITE_BLOCK_STATE           6
#define READ_BLOCK_DONE_STATE       7
#define WRITE_BLOCK_DONE_STATE      8
#define WRITING_ALL_STATE           9
#define READING_ALL_STATE           10
#define INITIALIZED                 1
#define UN_INITIALIZED              0
#define BUSY                        1
#define FREE                        0
#define DONE                        1
#define NOT_YET                     0
static uint8_t gu8_SMstate;
static uint8_t gu8_initflag;
static uint8_t gu8_allbusy;
static uint8_t gu8_blockbusy;
static uint8_t gu8_ReadBlock_id;
static uint8_t* gu8_Read_data_ptr;
static uint8_t gu8_WriteBlock_id;
static uint8_t* gu8_Write_data_ptr;
static volatile uint8_t gu8_Writecbknotify;
static  volatile uint8_t gu8_Readcbknotify;
void NVM_Init(void)
{
	if(gu8_initflag==INITIALIZED)
	{
		
	}
	else
	{
		gu8_initflag=INITIALIZED;
		gu8_SMstate=IDLE_STATE;
		gu8_allbusy=FREE;
		gu8_blockbusy=FREE;
	}
}


NVM_CheckType NVM_ReadAll(void)
{
	NVM_CheckType au8_ret_error=NVM_OK;
	if(gu8_initflag==UN_INITIALIZED)
	{
		au8_ret_error=NVM_NOK;
	}
	else
	{
		if(gu8_allbusy==BUSY)
		{
			au8_ret_error=NVM_BUSY;
		}
		else
		{
			gu8_SMstate=READ_ALL_STATE;	
			gu8_allbusy=BUSY;
		}
		
	}
	
	return au8_ret_error;
}


NVM_CheckType NVM_WriteAll(void)
{
	NVM_CheckType au8_ret_error=NVM_OK;
	if(gu8_initflag==UN_INITIALIZED)
	{
		au8_ret_error=NVM_NOK;
	}
	else
	{
		if(gu8_allbusy==BUSY)
		{
			au8_ret_error=NVM_BUSY;
		}
		else
		{
			gu8_SMstate=WRITE_ALL_STATE;
			gu8_allbusy=BUSY;
		}
		
	}
	
	return au8_ret_error;
}


NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr)
{
NVM_CheckType au8_ret_error=NVM_OK;
	if(NULL==DataPtr)
	{
		au8_ret_error=NVM_NOK;
	}
	else
	{
		if(gu8_blockbusy==BUSY)
		{
			au8_ret_error=NVM_BUSY;
		}
		else
		{
			gu8_ReadBlock_id=BlockId;
			gu8_Read_data_ptr=DataPtr;
			gu8_blockbusy=BUSY;
			gu8_SMstate=READ_BLOCK_STATE;
			
		}
		
	}
	
return au8_ret_error;
}
NVM_CheckType NVM_WriteBlock(uint8_t BlockId, uint8_t* DataPtr)
{
	NVM_CheckType au8_ret_error=NVM_OK;
	if(NULL==DataPtr)
	{
		au8_ret_error=NVM_NOK;
	}
	else
	{
		if(gu8_blockbusy==BUSY)
		{
			au8_ret_error=NVM_BUSY;
		}
		else
		{
			gu8_WriteBlock_id=BlockId;
			gu8_Write_data_ptr=DataPtr;
			gu8_blockbusy=BUSY;	
			gu8_SMstate=WRITE_BLOCK_STATE;
		}
		
	}
	return au8_ret_error;
}


void NVM_Main(void)
{
	static uint8_t au8_counter=0;
	static uint8_t au8_counter2=0;
  switch(gu8_SMstate)
  {	  
	  case IDLE_STATE:
	        gu8_allbusy=FREE;
			gu8_blockbusy=FREE;
			au8_counter2=0;
			au8_counter=0;
			break;
      case WRITE_ALL_STATE:
	        if(au8_counter==NVM_NUM_OF_BLOCKS)
			{
				gu8_SMstate=WRITE_ALL_DONE_STATE;
			}
			else
			{
				MEMIF_ReqWriteBlock(NVM_BlocConfig[au8_counter].BlockId,NVM_BlocConfig[au8_counter].BlockRamAddress);
      			au8_counter++;
				gu8_SMstate=WRITING_ALL_STATE;
			}
			break;
	  case  WRITING_ALL_STATE:
	        if(gu8_Writecbknotify==DONE)
			{
				gu8_Writecbknotify=NOT_YET;
				gu8_SMstate=WRITE_ALL_STATE;
			}
	        break;
      case READ_ALL_STATE:
	          
	          if(au8_counter==NVM_NUM_OF_BLOCKS)
	          {
		          gu8_SMstate=READ_ALL_DONE_STATE;
	          }
	          else
	          {
				  
		          MEMIF_ReqReadBlock(NVM_BlocConfig[au8_counter].BlockId,NVM_BlocConfig[au8_counter].BlockRamAddress);
		          au8_counter++;
				  
		          gu8_SMstate=READING_ALL_STATE;
			  }
		   	 break;
	  case  WRITE_BLOCK_STATE:
			for(au8_counter=0;au8_counter<NVM_NUM_OF_BLOCKS;au8_counter++)
				   {
					  if(NVM_BlocConfig[au8_counter].BlockId==gu8_WriteBlock_id)
					  {
						 for(au8_counter2=0;au8_counter2<NVM_BlocConfig[au8_counter].BlockLength;au8_counter2++) 
						 NVM_BlocConfig[au8_counter].BlockRamAddress[au8_counter2]=gu8_Write_data_ptr[au8_counter2];
							break;
					  }
				   }
			 gu8_SMstate=WRITE_BLOCK_DONE_STATE;    
			 break;
	case  WRITE_BLOCK_DONE_STATE:
			gu8_blockbusy=FREE;
			NVM_BlocConfig[au8_counter].BlockWriteNotifPtr();
			au8_counter=0;
			au8_counter2=0;
			gu8_SMstate=IDLE_STATE;
			break;
	case  READ_BLOCK_STATE:
	        for(au8_counter=0;au8_counter<NVM_NUM_OF_BLOCKS;au8_counter++)
	        {
		        if(NVM_BlocConfig[au8_counter].BlockId==gu8_WriteBlock_id)
		        {
			        for(au8_counter2=0;au8_counter2<NVM_BlocConfig[au8_counter].BlockLength;au8_counter2++)
			        NVM_BlocConfig[au8_counter].BlockRamAddress[au8_counter2]=gu8_Write_data_ptr[au8_counter2];
			        break;
		        }
	        }
	        gu8_SMstate=READ_BLOCK_DONE_STATE;
	        break;
	case  READ_BLOCK_DONE_STATE:
	        gu8_blockbusy=FREE;
	      	NVM_BlocConfig[au8_counter].BlockReadNotifPtr();
			au8_counter=0;
			au8_counter2=0;
	      	gu8_SMstate=IDLE_STATE;
	      	break;
    case  READING_ALL_STATE:
	       if(gu8_Readcbknotify==DONE)
		   {
			 
			   gu8_Readcbknotify=NOT_YET;
			   gu8_SMstate=READ_ALL_STATE;
		   }
		   break;
	case  READ_ALL_DONE_STATE:
	        gu8_allbusy=FREE;
			au8_counter=0;
			NVM_GlobalCallbacks.ReadAllCallback();
			gu8_SMstate=IDLE_STATE;
	        break;
	case  WRITE_ALL_DONE_STATE:
	        gu8_allbusy=FREE;
			au8_counter=0;
			NVM_GlobalCallbacks.WriteAllCallBack();
			gu8_SMstate=IDLE_STATE;
	        break;
	default: 
	        break;	
  }
  
}




void NVM_WriteBlockDoneNotif(void)
{
	gu8_Writecbknotify=DONE;
}

void NVM_ReadBlockDoneNotif(void)
{
	gu8_Readcbknotify=DONE;
	
}