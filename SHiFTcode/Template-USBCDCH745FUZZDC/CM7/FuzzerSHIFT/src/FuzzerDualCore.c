/*
 * FreeRTOS V202107.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "fuzzing.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "stdbool.h"
//#include "test.h"


extern USBD_HandleTypeDef hUsbDeviceFS;
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;

const char * EX_str[]=
{
"EX_NO_EX",
"EX_ASAN_DOUBLE_FREE",
"EX_ASAN_USE_AFTER_FREE",
"EX_ASAN_INVALID_FREE",
"EX_ASAN_RW_OVERFLOW",
"EX_ASAN_DEL_MISMATCH",
"EX_ASAN_REALLOC_MISMATCH",
"EX_ASAN_FAIL_POISON",
"EX_MPU_VIOLATION",
"EX_CORTEX_DIV0",
"EX_CORTEX_UNA_ACCESS",
"EX_CORTEX_BUS_FAULT",
"EX_CORTEX_UNDEF_INST",
"EX_HARDFAULT"
};


/** ARMv7 MPU Details:
 *
 * - ARMv7 MPU requires that the size of a MPU region is a power of 2.
 * - Smallest supported region size is 32 bytes.
 * - Start address of a region must be aligned to an integer multiple of the
 *   region size. For example, if the region size is 4 KB(0x1000), the starting
 *   address must be N x 0x1000, where N is an integer.
 */

/**
 * @brief Size of the shared memory region.
 */
#define SHARED_MEMORY_SIZE 32

#define MPUTESTENABLED 0





/**
 * Since stack of a task is protected using MPU, it must satisfy MPU
 * requirements as mentioned at the top of this file.
 */

//static StackType_t targetTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );
static StackType_t FuzzerTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );

// Entry function for the fuzzer
void vStartMPUDemo( void );

// The targte task
//static void targetTask( void * pvParameters );
// The furzzer task
static void fuzzerTask( void * pvParameters );




void HAL_HSEM_FreeCallback(uint32_t SemMask)
{


  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  if (SemMask == __HAL_HSEM_SEMID_TO_MASK(HSEM_ID_2)) // the ID of the notification from CM4 fter executing
  {
	  // this notifies on index 0 by default
	  xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,0,AFLfuzzer.notiVCM4TOCM7, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);


  }

  if (SemMask == __HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3)) // the ID of the notification from CM4 after rebooting
  {
	  printf("CM4 rebooted/ready!\n"); // we will not notify the task and let it recognize automatically a timeout
	  xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,2,1, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);



  }
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );


}



static void fuzzerTask( void * pvParameters )
{
	/* Unused parameters. */
	( void ) pvParameters;
	uint32_t notificationvalue;


#if DUALCOREFUZZ
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	 uint16_t *paflbitmap =  pAFLfuzzer->aflbmp;
#else
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	 uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
#endif

	/**NOTIFICATION INDEXES**
	 	 * 0: Notification from target to fuzzer after test execution
	 	 * 1: Notification from USB USART driver to the fuzzer task when data has arrived
	 	 * 2: Notification from target to fuzzer to signal readiness to execute the test
	 	 *********/

	//initialize the USB stack
	MX_USB_DEVICE_Init();


	/****** we don't need this since CM4 should be waiting for us the first time ***/
	// wait for the target core notification when ready
	//HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));
	//ulTaskNotifyTakeIndexed(2, pdTRUE, TARGET_TIMEOUT/2);

	for( ; ; )
	{

		 ulTaskNotifyTakeIndexed(1,pdTRUE, portMAX_DELAY);  //wait for data coming from fuzzer
		 {
	 	     //fuzz the target test
			 //printf("Received %u bytes\n", (unsigned int)AFLfuzzer.inputAFL.u32availablenopad-4);
			/*
			 for(int j=4; j<AFLfuzzer.inputAFL.u32availablenopad; j++)
			 {

			 		printf("\\x%02x",AFLfuzzer.inputAFL.uxBuffer[j]);

			 }
			 printf("\n");
			 */

			 //**** FUZZ the target ****

			 // Activate the notifications from CM4
			 __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_2));
			 HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_2));
			// HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));

			 AFLfuzzer.inputAFL.uxBuffer[104]='X';
			 //Notify CM4 to start fuzzing
			 // Take the semaphore
			 HAL_HSEM_FastTake(HSEM_ID_1);
			 /*Release HSEM in order to notify the CPU2(CM4)*/
			 HAL_HSEM_Release(HSEM_ID_1,0); // we need to use the Process ID 0 when using the Fast take method

			 //take the notification coming from the hardware semaphore trough the interrupt
			 notificationvalue = ulTaskNotifyTakeIndexed(0, pdTRUE, TARGET_TIMEOUT);

			 if (notificationvalue == 0)
			 {
				 AFLfuzzer.aflheader[0] = FAULT_TMOUT;
				 printf("Target timeout, CM4 should reboot soon!, %c \n",AFLfuzzer.inputAFL.uxBuffer[104]);
				 // wait for the target core notification when ready
				 HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));
				 ulTaskNotifyTakeIndexed(2, pdTRUE, 2*TARGET_TIMEOUT);

			 }
			 else if(notificationvalue == FAULT_CRASH)
			 {

				 AFLfuzzer.aflheader[0] = notificationvalue;
				 printf("T. crash at: 0x%x, %s \n", (unsigned int)AFLfuzzer.PCcrash, (char *)EX_str[AFLfuzzer.xTypeEx]);


				 HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));
				 ulTaskNotifyTakeIndexed(2, pdTRUE, 2*TARGET_TIMEOUT);
			 }
			 else if(notificationvalue == FAULT_ASAN)
			 {

				 notificationvalue = FAULT_CRASH;
				 printf("ASAN violation %s \n", (char *)EX_str[AFLfuzzer.xTypeEx]);
				 __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));
				 HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));
				 ulTaskNotifyTakeIndexed(2, pdTRUE, 2*TARGET_TIMEOUT);
			 }
			 else if (notificationvalue == FAULT_NONE_RTOS)
			 {
				 // we need this because 0 means timeout for the RTOS notification system
				//printf("none\n");
				notificationvalue = FAULT_NONE;
				AFLfuzzer.aflheader[0] = notificationvalue;
				//HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_3));
				//ulTaskNotifyTakeIndexed(2, pdTRUE, 2*TARGET_TIMEOUT);
			 }

			 AFLfuzzer.aflheader[1] = (AFLfuzzer.indexdif * sizeof(tuple_t)  + 4 );


			 tuple_t *auxdiff = AFLfuzzer.afldiff + 1; // the first tuple is empty so we can skip it
			 union ubytes_t *crcbytes;
			 crcbytes = (union ubytes_t *)(auxdiff + AFLfuzzer.indexdif); //set CRC bytes * at the end of the tuple array

			 //calculate the CRC of the return value and payload size
			 uint32_t uwCRCValue = HAL_CRC_Calculate(&hcrc, (uint32_t *)AFLfuzzer.aflheader, 2);
			 //calculate the CRC of the tuples (payload)
			 uwCRCValue = HAL_CRC_Accumulate(&hcrc, (uint32_t *)auxdiff, AFLfuzzer.indexdif);

			 // invert the CRC to match the zlib method
			 crcbytes->vuint32 = ~uwCRCValue; //write the CRC at the end of the buffer

			 AFLfuzzer.bTXcomplete = false;
			 CDC_Transmit_FS((uint8_t *)AFLfuzzer.aflheader, 8);
			 //while(AFLfuzzer.bTXcomplete ==false); //wait for end of transmission
			 ulTaskNotifyTakeIndexed(1,pdTRUE, 10);

			 AFLfuzzer.bTXcomplete = false;
			 CDC_Transmit_FS((uint8_t *)auxdiff, AFLfuzzer.aflheader[1]);
			 //while(AFLfuzzer.bTXcomplete ==false); //wait for end of transmission
			 ulTaskNotifyTakeIndexed(1,pdTRUE, 10);

			 AFLfuzzer.bRXcomplete = false;
			 AFLfuzzer.inputLength = 0;
			 AFLfuzzer.previousGuard = 0;
			 RingZeroes(&AFLfuzzer.inputAFL);

			 // clean the bitmap
			 for(uint32_t i=0; i<AFLfuzzer.indexdif; i++)
			 {
				 paflbitmap[auxdiff[i].index]=0;
			 }

			 memset(AFLfuzzer.afldiff,0,(AFLfuzzer.indexdif+2)*sizeof(tuple_t));
			 AFLfuzzer.indexdif = 0;

			 AFLfuzzer.timespan = HAL_GetTick() - AFLfuzzer.timespan;
			 // printf("Total time: %u \n", (uint)AFLfuzzer.timespan);

		}
	}
}


void vStartMPUDemo( void )
{


#if DUALCOREFUZZ
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#else
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif


TaskParameters_t fuzzerTaskParameters =
{
	.pvTaskCode		= fuzzerTask,
	.pcName			= "Fuzzer",
	.usStackDepth	= configMINIMAL_STACK_SIZE,
	.pvParameters	= NULL,
	.uxPriority		= 20 | portPRIVILEGE_BIT,
	.puxStackBuffer	= FuzzerTaskStack,
	.xRegions		=	{
			                { 0, 0, 0 },
							{ 0, 0, 0 },
							{ 0, 0, 0 },
					}
};


	/* Create the fuzzer task */
	xTaskCreateRestricted( &( fuzzerTaskParameters ), &AFLfuzzer.xTaskFuzzer );


}
/*-----------------------------------------------------------*/


/*
portDONT_DISCARD void vHandleMemoryFault( uint32_t * pulFaultStackAddress )
{

#if DUALCOREFUZZ
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#else
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif




BaseType_t xHigherPriorityTaskWoken = pdFALSE;


  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {
	  //Get the PC where the crash happened
	  AFLfuzzer.PCcrash = pulFaultStackAddress[ 6 ] ;
	  //Notify the fuzzer task that the target crashed
	  xTaskNotifyFromISR(AFLfuzzer.xTaskFuzzer,FAULT_CRASH,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
	  //Delete the target task
	  vTaskDelete(AFLfuzzer.xTaskTarget);
	  // port yield should be called and nothing else should be executed
	  portYIELD_FROM_ISR( xHigherPriorityTaskWoken ); // this line is not necessary
	  //since deleting the task will force a context switch.

  }
  else
  {
	  printf("Fuzzer crashed at PC: %x\n", (unsigned int)pulFaultStackAddress[ 6 ]);
	  for( ; ; )
	  {
		  // this should never happen if we reach this point the whole firmware state can be corrupted
		  // TODO: can we reboot the MCU here?
	  }

  }


}
*/
/*-----------------------------------------------------------*/
