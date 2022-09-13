/*
 * callbacks.c
 *
 *  Created on: Jan 28, 2022
 *      Author: alejandro
 */



#include "modbus_rtu.h"
#include "modbus_rtu_conf.h"
#include "string.h"
#include "afl.h"
#include "fuzzing.h"


extern uint16_t modbusMemory[MODBUS_SLAVE_REGISTERS_NUM];
extern uint8_t modbusRxTxBuffer[MODBUS_MAX_FRAME_SIZE];
extern modbus_t  modbusVars;
extern UART_HandleTypeDef huart4;


#if DUALCOREFUZZ == 0
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif


#define modbusRxCount modbusVars.modbusRxCountV
#define modbusSlaveFrameReadyFlag modbusVars.modbusSlaveFrameReadyFlagV
#define xFrameReadySemaphore modbusVars.xFrameReadySemaphoreV
#define xModbusSlaveTask modbusVars.xModbusSlaveTaskV




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
#if DUALCOREFUZZ == 0

  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if(huart==&huart4)
	{
		modbusRxCount = Size;  //MODBUS_MAX_FRAME_SIZE - DMA1_Channel5->CNDTR;
		//xSemaphoreGiveFromISR(xFrameReadySemaphore, NULL);
		//notify the fuzzer that data has arrived to through USART
		xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,2,1,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
		//portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

		//xTaskNotifyFromISR(AFLfuzzer.xTaskTarget,0,eSetValueWithOverwrite, &xHigherPriorityTaskWoken); //notify that data arrived
	}

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
#if DUALCOREFUZZ == 0

  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


  if(huart==&huart4)
  {

	  while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, modbusRxTxBuffer, MODBUS_MAX_FRAME_SIZE) != HAL_OK)
	 	   {
	 	  					HAL_UART_DMAStop(&huart4);
	 	    }
	    modbusRxCount = 0;
	    xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,0,FAULT_NONE_RTOS,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
	    //notify that the test finished

  }

  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}



void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

	 if(huart==&huart4)
	 {
	   HAL_UART_DMAStop(&huart4);
	   while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, modbusRxTxBuffer, MODBUS_MAX_FRAME_SIZE) != HAL_OK)
	   {
	  	   HAL_UART_Abort(&huart4);
	  	   HAL_UART_DeInit(&huart4);
	  	   HAL_UART_Init(&huart4);


	   }

	 }

/*
  #if DUALCOREFUZZ == 0

  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
  #endif

  BaseType_t xHigherPriorityTaskWoken = pdFALSE;


  if(huart==&huart4)
  {

	    HAL_UARTEx_ReceiveToIdle_DMA(&huart4, modbusRxTxBuffer, MODBUS_MAX_FRAME_SIZE); //wait for more data
	    modbusRxCount = 0;
	    xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,0,FAULT_NONE_RTOS,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
	    //notify that the test finished

  }

  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

*/

}




void cleanInitShadow()
{

#if DUALCOREFUZZ == 0

  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif
	//AFLfuzzer.bRXcomplete = false;
    //AFLfuzzer.inputLength = 0;
    AFLfuzzer.previousGuard = 0;
    //RingZeroes(&AFLfuzzer.inputAFL);
    memset(AFLfuzzer.aflbmp,0,AFL_BITMAP_SIZE*sizeof(uint16_t));
    memset(AFLfuzzer.afldiff,0, AFL_BITMAP_SIZE/4 *sizeof(tuple_t)); //we need on extra tuple to clean which is used for the CRC
    AFLfuzzer.indexdif = 0;

}
