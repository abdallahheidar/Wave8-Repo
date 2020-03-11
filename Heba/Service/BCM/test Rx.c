ERROR_STATUS BCM_RX_dispatcher()
{
	ERROR_STATUS u8_fun_error_status = OK;
	
	uint8_t u8_BCM_chanalIndx =ZERO;
	
	/*dispatcher can serve only one request for each chanal at one super loop, recored task num to serve*/
	/*loop for each chanal on RX TASKS and serve only one task*/
	for (;u8_BCM_chanalIndx < BCM_MAX_CHANALS ; u8_BCM_chanalIndx++)
	if((gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_RECIVER]) != BCM_CHANAL_UNINTALIZED
	&& (gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_RECIVER]) != BCM_CHANAL_NO_TASKS) /*chanal init and task exist*/
	{
		/*loop thought tasks in chanal*/
		//uint8_t u8_taskINdxr = ZERO;
		//for (;u8_taskINdxr < (gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_RECIVER]);u8_taskINdxr++)
		//{
			/*get state and current task buffer counter and data to send*/
			bcm_taskControlBlock_t* pstr_currentTask =  &g3astr_BCM_Tasks[u8_BCM_chanalIndx][BCM_RECIVER];
			switch(u8_BCM_chanalIndx)
			{
				
				case BCM_SPI_CHANAL:
				switch(pstr_currentTask->u8_taskStatus)
				{

					case STATE_IDLE:
					
					break;
					
					case STATE_RECIVING_HEAEDER:
						
						/*check if we received the frame id and  size*/

						if(u8_bufferCounter>=BCM_FRAM_SIZE_INDX)
						{
							pstr_currentTask->u8_taskStatus = STATE_CHEAKING_HEADER;
						}
					break;
		
						
					case STATE_CHEAKING_HEADER:
			
						pstr_currentTask->u8_BCM_framSize = ZERO;
						pstr_currentTask->u8_BCM_framSize = ((gau8_BCM_RecivingBuffer[BCM_FRAM_SIZE_HIGH_NIBBLE]<<SHIFT_8));
						pstr_currentTask->u8_BCM_framSize |= gau8_BCM_RecivingBuffer[BCM_FRAM_SIZE_LOWER_NIBBLE];
					
					      /*check received frame id = to BCM ID*/
						if (gau8_BCM_RecivingBuffer[ZERO]!=BCM_SPI_ID)
						{
							pstr_currentTask->u8_taskStatus=STATE_ERROR;
						}
						else 
						
						{      /*check  received frame size <= to BCM buffer size*/
							
							if(pstr_currentTask->u8_BCM_framSize > BCM_MAX_RECIVING_BUFFER_SIZE )
							{
								pstr_currentTask->u8_taskStatus = STATE_ERROR;
							}
							else {
								pstr_currentTask->u8_taskStatus = STAE_RECIVING_FRAME;
							}
					    }
							
					break;
					case STAE_RECIVING_FRAME:
					
						if(u8_bufferCounter >= pstr_currentTask->u8_BCM_framSize )
						{
							
							spi_disable();

							if(u8_bufferCounter <= BCM_MAX_RECIVING_BUFFER_SIZE )
							{
								
								pstr_currentTask->u8_taskStatus = STATE_FRAM_RECIVE_COMPLETE;
								
							}
								
							
							else 
								pstr_currentTask->u8_taskStatus = STATE_ERROR;
						}
						
					break;
					
					case STATE_FRAM_RECIVE_COMPLETE:
						
							pstr_currentTask->u8_taskStatus = STATE_FINISED;
							u8_bufferCounter = ZERO;
						
					break;
					
					case STATE_ERROR :
					
					break;
					case STATE_FINISED:;
						uint8_t u8_buffer_size =  (pstr_currentTask->u8_BCM_framSize - BCM_FRAM_HEADER_OVERHEAD);
						*pstr_currentTask->bcmTask->size=u8_buffer_size;
						uint8_t u8_counter = ZERO;
						/*COPY DATA TO USER BUFFER*/
						for (;u8_counter < u8_buffer_size;u8_counter++)
						{
							pstr_currentTask->bcmTask->buffer[u8_counter] = gau8_BCM_RecivingBuffer[u8_counter+BCM_DATA_START_POS];
						}
						pstr_currentTask->bcmTask->bcm_cbf(u8_counter);
						
					break;
					
				}
				break;
				case BCM_UART_CHANAL:
				break;
				case BCM_I2C_CHANAL:
				break;
			}
			
		//}
		
		/*update to next task to serve*/
	}
	else {
		u8_fun_error_status = BCM_MODULE_ERR + MODULE_NOT_INITALIZED;
	}
		return u8_fun_error_status;
}