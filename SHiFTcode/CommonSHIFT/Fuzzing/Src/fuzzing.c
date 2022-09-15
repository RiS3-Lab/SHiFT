#include "fuzzing.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

/*
#ifdef  RTOSENABLED


#else
	Fuzzer_t AFLfuzzer;
#endif

*/

#if USARTHW == 0
#include "usbd_cdc_if.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
#endif
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
//extern UART_HandleTypeDef huart3;



bool checkCRC(RingBuffer_t *input)
{
	uint32_t numberwords;
	uint32_t *crcreceived;

	numberwords = (input->u32available-4)/4;

	uint32_t uwCRCValue = HAL_CRC_Calculate(&hcrc, (uint32_t *)input->uxBuffer, numberwords );

	uwCRCValue = ~uwCRCValue;
	crcreceived = (uint32_t *)(input->uxBuffer);

	if (crcreceived[numberwords] == uwCRCValue)
	{
		return true;
	}
	return false;

}

extern uint8_t  bufferDMA[550];
void SendBackFault(uint32_t faultcode)
{

//#if DUALCOREFUZZ == 0
	//uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
//#endif


	RingClear(&AFLfuzzer.inputAFL);
	AFLfuzzer.inputLength = 0;
	AFLfuzzer.inputLengthpadded = 0;


	AFLfuzzer.aflheader[0] = faultcode;
	AFLfuzzer.aflheader[1] = 4; // 4 bytes for CRC and no payload
	uint32_t uwCRCValue = HAL_CRC_Calculate(&hcrc, (uint32_t *)AFLfuzzer.aflheader, 2);
	AFLfuzzer.aflheader[2] = ~uwCRCValue;


	AFLfuzzer.bRXcomplete = false;
	AFLfuzzer.inputLength = 0;
	AFLfuzzer.previousGuard = 0;
	RingZeroes(&AFLfuzzer.inputAFL);

#if USARTHW == 0
    CDC_Transmit_FS((uint8_t *)AFLfuzzer.aflheader, 12);
#else
    HAL_UART_Transmit_IT(&huart3, (uint8_t *)AFLfuzzer.aflheader, 12);
    while(!AFLfuzzer.bTXcomplete);
    HAL_UART_Receive_IT(&huart3, AFLfuzzer.inputAFL.uxBuffer, 4);

#endif



}



void FuzzingInputHandler(uint8_t* Buf, uint32_t *Len)
{

	  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	  BaseType_t xHigherPriorityTaskWoken;

	  xHigherPriorityTaskWoken = pdFALSE;


	  union ubytes_t auxbytes;
	  uint32_t u32Tocopy;
	  uint8_t error;


	  error = 0;

	  if( (AFLfuzzer.inputLength != 0 && AFLfuzzer.inputLengthpadded == 0) ||
	   	   AFLfuzzer.inputLength > MAX_BUFFER_INPUT || 	AFLfuzzer.inputLengthpadded> MAX_BUFFER_INPUT )
	  {
	    	  //this is a wrong condition that should never happens,
	    	  //however fuzzing is stressing the whole system so we should clean the whole thing here
	    	  SendBackFault(FAULT_INLEGTH);
	    	  error = 1;
	  }

	  if( AFLfuzzer.inputLength == 0 && error == 0 )
	  {
	      auxbytes.vbytes[0]=Buf[0];
	      auxbytes.vbytes[1]=Buf[1];
	      auxbytes.vbytes[2]=Buf[2];
	      auxbytes.vbytes[3]=Buf[3];
	      AFLfuzzer.inputLength = auxbytes.vint32;
	      //offset = 4;
	      if(AFLfuzzer.inputLength % 4)
	      {
	      	  AFLfuzzer.inputLengthpadded = AFLfuzzer.inputLength + 4 - AFLfuzzer.inputLength % 4;
	      }
	      else
	      {
	      	  AFLfuzzer.inputLengthpadded = AFLfuzzer.inputLength;
	      }

	      if((AFLfuzzer.inputLengthpadded + 4 )> MAX_BUFFER_INPUT)
	      {
        	  //u32copied = 0;
        	  SendBackFault(FAULT_INLEGTH);
        	  error = 1;

          }

      }

      if(AFLfuzzer.inputLengthpadded && (error == 0) )
      {


	    	 u32Tocopy = (AFLfuzzer.inputLengthpadded + 4) - AFLfuzzer.inputAFL.u32available;
	    	 if (u32Tocopy > *Len)
	    	 {
	    		 u32Tocopy = *Len;

	    	 }
	    	 RingCopy(&AFLfuzzer.inputAFL, Buf, u32Tocopy);


	  	     if( (AFLfuzzer.inputLengthpadded + 4) == AFLfuzzer.inputAFL.u32available)
	  	     {

	  	    	if( checkCRC(&AFLfuzzer.inputAFL) )
	  	    	{

	  	    		AFLfuzzer.inputAFL.u32availablenopad = AFLfuzzer.inputLength;
	  	    		AFLfuzzer.bRXcomplete = 1;
	  	    		AFLfuzzer.timespan = HAL_GetTick();
	  	    		if(AFLfuzzer.inputAFL.u32availablenopad ==0)printf("Zero USB \n");

	  	    		xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,
	  	    				1, //index
							1, //value = 1 data received
							eSetBits,
							&xHigherPriorityTaskWoken);
	  	    	}
	  	    	else
	  	    	{
	  	    		// wrong CRC
	  	    		//u32copied = 0;
	  	    		SendBackFault(FAULT_COMM);

	  	    	}

	  	     }


      }
      portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


void activateCortexMtraps()
{
	 SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
	  | SCB_SHCSR_BUSFAULTENA_Msk
	  | SCB_SHCSR_MEMFAULTENA_Msk; // enable Usage-/Bus-/MPU Fault

	  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;// | // enable div by zero trap
			   //SCB_CCR_UNALIGN_TRP_Msk;    // enable unaligned access trap

}

void activateCortexMtrapsUNA()
{
	 SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
	  | SCB_SHCSR_BUSFAULTENA_Msk
	  | SCB_SHCSR_MEMFAULTENA_Msk; // enable Usage-/Bus-/MPU Fault

	  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk | // enable div by zero trap
			   SCB_CCR_UNALIGN_TRP_Msk;    // enable unaligned access trap

}

