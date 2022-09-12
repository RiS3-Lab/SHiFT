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
#include "stdlib.h"
#include "stdbool.h"
#include "test.h"


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


#if DUALCOREFUZZ == 0

#define AFLINPUTREGION_SIZE (1024*64)
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );

#else

//#define AFLINPUTREGION_SIZE (1024*64)
//#define AFLfuzzerRegion  (uint8_t*)0x24040000

#endif


/**
 * Since stack of a task is protected using MPU, it must satisfy MPU
 * requirements as mentioned at the top of this file.
 */

static StackType_t targetTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );
//static StackType_t monitorTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );

extern WWDG_HandleTypeDef hwwdg2;
extern uint32_t __user_heap_start__[];

// Entry function for the fuzzer
void vStartMPUDemo( void );

// Task helper to manage the target
//static void monitorTask( void * pvParameters );

// The target task
static void targetTask( void * pvParameters );

// Helper to launch target tasks
static void spawnNewTarget();


void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
  /* Prevent unused argument(s) compilation warning */
 // UNUSED(hwwdg);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_WWDG_EarlyWakeupCallback could be implemented in the user file
   */

  //HAL_WWDG_Refresh(&hwwdg2);

  //HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);

}

/*
static void monitorTask(void * pvParameters )
{

	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;


   ( void ) pvParameters;
   for(;;)
   {

	   ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	   HAL_WWDG_Refresh(&hwwdg2); //if no data received refresh the watchdog

	   int i = 0;

	   while(i<McuASAN_MAX_NUMBER_ALLOCS)
	   {
	        if(AFLfuzzer.allocs[i])
	   	    {
	   	       free(AFLfuzzer.allocs[i]);
	   		}
	   		i++;
	   }

	   taskYIELD(); //lets the kernel clean the TCB
	   spawnNewTarget();

   }

}*/



static void targetTask( void * pvParameters )
{
	/* Unused parameters. */
   ( void ) pvParameters;
   //uint32_t notificationvalue;

   #if RTOSENABLED
   Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
   #endif
   uint32_t notification;


   ///HAL_NVIC_SetPriority(HSEM2_IRQn, 0x05, 0);
   // Activate the notification from CM7
   ///__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));
   ///HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));
   HSEM_activate_notification(HSEM_ID_1);


   //__HAL_WWDG_ENABLE_IT(&hwwdg2, WWDG_IT_EWI);
   //HAL_NVIC_SetPriority(WWDG_IRQn, 5 ,0U);
   //NVIC_EnableIRQ(WWDG_IRQn);
   ///MX_WWDG2_Init();
   WWDG_activate();
   // check the values configured there currently the time out is 10 [ms], this should be less than Fuzzer CM7 timeout for synchronization

   //Notify the CM7 that CM4 is ready this is done earlier

	/*Take HSEM */
	///HAL_HSEM_FastTake(HSEM_ID_3);
	/*Release HSEM in order to notify the CPU1(CM7)*/
	///HAL_HSEM_Release(HSEM_ID_3,0);
   HSEM_notify(HSEM_ID_3);


    //bool resetEnabled = false;
	for( ; ; )
	{

		notification= ulTaskNotifyTake(pdTRUE, 1); // wait for data coming from CM7
		if (notification == 0 )
		{
			//HAL_WWDG_Refresh(&hwwdg2); //if no data received refresh the watchdog
			WWDG_Refresh();
			continue;
		}
		WWDG_Refresh(); // we need to refresh the watchdog before an after executing the test.
								   // this assures that our test has a valid window to execute and finish
								   // otherwise spurious crashes were observed because the watchdog expired
								   // in the middle of the execution
		AFLfuzzer.notiVCM4TOCM7 = test(&AFLfuzzer.inputAFL.uxBuffer[4], AFLfuzzer.inputAFL.u32availablenopad-4 );
		WWDG_Refresh();

		//TODO: the HSEM is not included in the MPU regions we need a system call for this purpose, currently the task
		//is running in privileged mode for testing purposes

		// Activate the notification from CM7 again since it is disabled in the ISR
		/// __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));
		///HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));
		HSEM_activate_notification(HSEM_ID_1);


		/*Take HSEM */
		//HAL_HSEM_FastTake(HSEM_ID_2);
		/*Release HSEM in order to notify the CPU1(CM7)*/
	    //HAL_HSEM_Release(HSEM_ID_2,0);
		HSEM_notify(HSEM_ID_2);

		//WRITE_REG(hwwdg2.Instance->CR, 64);
		//while(1);

	}
}


/*
static void testTask( void * pvParameters )
{
	( void ) pvParameters;

	for( ; ; )
	{
	 HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	 vTaskDelay(250);

	}
}
*/

static void spawnNewTarget( )
{
   #if RTOSENABLED

   Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
   //uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
   //uint16_t *paflbitmap =  (uint16_t *)pAFLfuzzer->aflbmp;
   #endif


   TaskParameters_t targetTaskParameters =
      {
      	.pvTaskCode		= targetTask,
      	.pcName			= "Target",
      	.usStackDepth	= configMINIMAL_STACK_SIZE,
      	.pvParameters	= NULL,
      	.uxPriority		= 20,
      	.puxStackBuffer	= targetTaskStack ,
      	.xRegions		=	{
      			                { pAFLfuzzer, AFLINPUTREGION_SIZE, portMPU_REGION_READ_WRITE }, // AFL bitmap, diff buffer, TX diff buffer
      							{ ( void * )0x10000000, 64*1024, portMPU_REGION_READ_WRITE },   // Shadow memory is actually 48k, but we need a power of two
								{__user_heap_start__, 8*1024, portMPU_REGION_READ_WRITE}
      						}
      };

   /*
   TaskParameters_t targetTaskParameters =
   {
   	.pvTaskCode		= targetTask,
   	.pcName			= "Target",
   	.usStackDepth	= configMINIMAL_STACK_SIZE,
   	.pvParameters	= pAFLfuzzer,
   	.uxPriority		= 20,
   	.puxStackBuffer	= targetTaskStack,
   	.xRegions		=	{
   			                { AFLfuzzerRegion, AFLINPUTREGION_SIZE, portMPU_REGION_READ_WRITE}, // input from AFL, TX diff buffer
   							{ paflbitmap, AFL_BITMAP_SIZE_BYTES, portMPU_REGION_READ_WRITE},    // bitmap
   							{ ( void * )0x24010000, 64*1024, portMPU_REGION_READ_WRITE },       // guards instrumentation
   						}
   };
*/

   //create a new task
   xTaskCreateRestricted( &( targetTaskParameters ), &AFLfuzzer.xTaskTarget );



   // we need to do this here because the HSEM is not accessible on the MPU regions

}


void HAL_HSEM_FreeCallback(uint32_t SemMask)
{

  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  if (SemMask == __HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1)) // the ID of the notification from CM7
  {
	  //notify that data is ready for the target
	  if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING){
	  xTaskNotifyFromISR(AFLfuzzer.xTaskTarget, 1  ,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
   	  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	  }
  }


}


void vStartMPUDemo( void )
{


//Initialize the region with AFL variables
#if RTOSENABLED
 // Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
  //uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
#endif

/*
TaskParameters_t monitorTaskParameters =
       {
       	.pvTaskCode		= monitorTask,
       	.pcName			= "monitor",
       	.usStackDepth	= configMINIMAL_STACK_SIZE,
       	.pvParameters	= NULL,
       	.uxPriority		= 20 | portPRIVILEGE_BIT ,
       	.puxStackBuffer	= monitorTaskStack,
       	.xRegions		=	{
       			                { 0,0,0},
       							{ 0,0,0},
 								{0,0,0}
       						}
       };

xTaskCreateRestricted( &( monitorTaskParameters ), &AFLfuzzer.xTaskMonitor );
*/

spawnNewTarget();



}
/*-----------------------------------------------------------*/

/*
#if DUALCOREFUZZ

portDONT_DISCARD void vHandleMemoryFault( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
BaseType_t xHigherPriorityTaskWoken = pdFALSE;




  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {

	  AFLfuzzer.notiVCM4TOCM7 = FAULT_CRASH; //we detected a crash
	  //Take HSEM
	  HAL_HSEM_FastTake(HSEM_ID_2);
	  ///Release HSEM in order to notify the CPU1(CM7)
	  HAL_HSEM_Release(HSEM_ID_2,0);
	  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

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



#else

portDONT_DISCARD void vHandleMemoryFault( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
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

#endif
*/
/*-----------------------------------------------------------*/
