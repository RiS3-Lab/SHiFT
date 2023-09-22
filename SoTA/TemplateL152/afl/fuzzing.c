#include "fuzzing.h"
#include "main.h"
//#include "driver/uart.h"
//#include "driver/gpio.h"

///#include "test.h"

/*
#ifdef  RTOSENABLED


#else
	Fuzzer_t AFLfuzzer;
#endif

*/

extern Fuzzer_t AFLfuzzer;
extern CRC_HandleTypeDef hcrc;

#define TRUE 1
#define FALSE 0


uint8_t checkCRC(RingBuffer_t *input)
{
	uint32_t numberwords;
	uint32_t *crcreceived;

	numberwords = (input->u32available-4)/4;

	uint32_t uwCRCValue = 0;

	return TRUE; //

	//CRC_Calculate((uint32_t *)input->uxBuffer, numberwords *4 , &uwCRCValue);
	uwCRCValue=HAL_CRC_Calculate(&hcrc, (uint32_t *)input->uxBuffer, numberwords );

	uwCRCValue = ~uwCRCValue;
	crcreceived = (uint32_t *)(input->uxBuffer);

	if (crcreceived[numberwords] == uwCRCValue)
	{
		return TRUE;
	}
	return FALSE;

}



void SendBackFault(uint32_t faultcode)
{




	RingClear(&AFLfuzzer.inputAFL);
	AFLfuzzer.inputLength = 0;
	AFLfuzzer.inputLengthpadded = 0;


	AFLfuzzer.aflheader[0] = faultcode;
	AFLfuzzer.aflheader[1] = 4; // 4 bytes for CRC and no payload
	uint32_t uwCRCValue = 0;
	CRC_Calculate((uint32_t *)AFLfuzzer.aflheader, 2*4, &uwCRCValue);
	//AFLfuzzer.aflheader[2] = ~uwCRCValue;
	AFLfuzzer.aflheader[2] = uwCRCValue;

	AFLfuzzer.bTXcomplete = 0;

  	//uart_write_bytes(2, (uint8_t *)AFLfuzzer.aflheader, 12);

	//cdc_acm_data_send_wp(&USB_OTG_dev, 12, (uint8_t *)AFLfuzzer.aflheader);


	//CDC_Transmit_FS((uint8_t *)AFLfuzzer.aflheader, 12);

}



void FuzzingInputHandler(uint8_t* Buf, uint32_t *Len)
{



	  union ubytes_t auxbytes;
	  uint32_t u32Tocopy;



	  if( *Len>0  )
	  {
	      if(AFLfuzzer.inputLength == 0)
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
	          }

	      }

	      //u32copied = 0;

	      if(AFLfuzzer.inputLengthpadded)
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
	  	    		AFLfuzzer.bTXcomplete = 0;
	  	    		//packet_sent = 0;
	  	    		//AFLfuzzer.timespan = HAL_GetTick();
	  	    	}
	  	    	else
	  	    	{
	  	    		// wrong CRC
	  	    		//u32copied = 0;
	  	    		SendBackFault(FAULT_COMM);

	  	    	}

	  	     }


	      }
      }
}




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


