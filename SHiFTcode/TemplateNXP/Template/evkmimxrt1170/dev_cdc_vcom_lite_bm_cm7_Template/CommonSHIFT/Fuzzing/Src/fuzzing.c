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

#if defined(STM32H743xx) || defined(STM32L552xx)  || defined(STM32L552xx) || defined(STM32H745xx) || defined(STM32L152xE)

#if USARTHW == 0
#include "usbd_cdc_if.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
#else

extern UART_HandleTypeDef huart2;
#endif

extern CRC_HandleTypeDef hcrc;
//extern RNG_HandleTypeDef hrng;
//extern UART_HandleTypeDef huart3;

#else



uint32_t crc32_for_byte(uint32_t r) {
  for(int j = 0; j < 8; ++j)
    r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
  return r ^ (uint32_t)0xFF000000L;
}

void CRC_Calculate(uint32_t *data, uint32_t n_bytes, uint32_t *crc)
{
  static uint32_t table[0x100];
  if(!*table)// this table is only initialized once in a fuzzing compaign
    for(uint32_t i = 0; i < 0x100; ++i)
      table[i] = crc32_for_byte(i);
  for(uint32_t i = 0; i < n_bytes; ++i)
    *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
}

uint32_t  CRC_Calculate_v(uint32_t *data, uint32_t n_bytes)
{
	uint32_t crc;
	CRC_Calculate(data, n_bytes, &crc);
	return crc;

}



#endif





bool checkCRC(RingBuffer_t *input)
{
	uint32_t numberwords;
	uint32_t *crcreceived;

	numberwords = (input->u32available-4)/4;

#if defined(STM32H743xx) || defined(STM32L552xx)  || defined(STM32L552xx) || defined(STM32H745xx) || defined(STM32L152xE)
	uint32_t uwCRCValue = HAL_CRC_Calculate(&hcrc, (uint32_t *)input->uxBuffer, numberwords );
	uwCRCValue = ~uwCRCValue;

#else
	uint32_t uwCRCValue = 0;
	CRC_Calculate((uint32_t *)input->uxBuffer, numberwords *4 , &uwCRCValue);
#endif



	crcreceived = (uint32_t *)(input->uxBuffer);

	if (crcreceived[numberwords] == uwCRCValue)
	{
		return true;
	}
	return false;

}

extern uint8_t  bufferDMA[512];
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
#if defined(STM32H743xx) || defined(STM32L552xx)  || defined(STM32L552xx) || defined(STM32H745xx) || defined(STM32L152xE)
	uint32_t uwCRCValue = HAL_CRC_Calculate(&hcrc, (uint32_t *)AFLfuzzer.aflheader, 2);
	AFLfuzzer.aflheader[2] = ~uwCRCValue;
#else
	uint32_t uwCRCValue = 0;
	CRC_Calculate((uint32_t *)AFLfuzzer.aflheader, 2*4, &uwCRCValue);
	//AFLfuzzer.aflheader[2] = ~uwCRCValue;
	AFLfuzzer.aflheader[2] = uwCRCValue;

#endif



	AFLfuzzer.bRXcomplete = false;
	AFLfuzzer.inputLength = 0;
	AFLfuzzer.previousGuard = 0;
	AFLfuzzer.faultcom = true;
	RingZeroes(&AFLfuzzer.inputAFL);

#if defined(STM32H743xx) || defined(STM32L552xx)  || defined(STM32L552xx) || defined(STM32H745xx)

#if USARTHW == 0
    #ifdef STM32H723xx
	    CDC_Transmit_HS((uint8_t *)AFLfuzzer.aflheader, 12);
    #else
        CDC_Transmit_FS((uint8_t *)AFLfuzzer.aflheader, 12);
    #endif
#else
    HAL_UART_Transmit(&HUART, (uint8_t *)AFLfuzzer.aflheader, 12,100);

    HAL_UART_Receive_IT(&HUART, AFLfuzzer.inputAFL.uxBuffer, 4);

#endif

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
	  	    		//AFLfuzzer.timespan = HAL_GetTick();
	  	    		//if(AFLfuzzer.inputAFL.u32availablenopad ==0)printf("Zero USB \n");
	  	    		AFLfuzzer.faultcom = false;

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
	  	    		AFLfuzzer.faultcom = true;
	  	    		SendBackFault(FAULT_COMM);

	  	    	}

	  	     }


      }
      portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}



// Activate the Cortex-M traps without unaligned access
void activateCortexMtraps()
{
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
		  | SCB_SHCSR_BUSFAULTENA_Msk
		  | SCB_SHCSR_MEMFAULTENA_Msk; // enable Usage-/Bus-/MPU Fault

	  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;// | // enable div by zero trap

}


// Activate the Cortex-M traps including unaligned access
void activateCortexMtrapsUNA()
{
	 SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
	  | SCB_SHCSR_BUSFAULTENA_Msk
	  | SCB_SHCSR_MEMFAULTENA_Msk; // enable Usage-/Bus-/MPU Fault

	  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk |  // enable div by zero trap
			   SCB_CCR_UNALIGN_TRP_Msk;    // enable unaligned access trap

}

