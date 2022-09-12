/*
 * SHiFT
 * Alejandro Mera 2022
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
//#include "application_defined_privileged_functions.h"
#include "queue.h"
#include "main.h"
#include "fuzzing.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "stdbool.h"
#include "McuASANconfig.h"
#include "ConfigFuzzing.h"

#include "modbus_rtu.h"
#include "modbus_rtu_conf.h"


//#include "freertos_tasks_c_additions.h"
//extern USBD_HandleTypeDef hUsbDeviceFS;FAULT_NONE_RTOS
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern UART_HandleTypeDef huart3;
extern uint32_t __user_heap_start__[];
extern UART_HandleTypeDef huart2;






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

#define modbusRxCount modbusVars.modbusRxCountV




#if DUALCOREFUZZ == 0
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif

extern UART_HandleTypeDef huart4 __attribute__( ( aligned( next_power_of_2(sizeof(UART_HandleTypeDef)) ) ) );
extern DMA_HandleTypeDef hdma_uart4_rx   __attribute__( ( aligned( next_power_of_2(sizeof(DMA_HandleTypeDef)) ) ) );;

uint32_t error_cnt;

/**
 * Since stack of a task is protected using MPU, it must satisfy MPU
 * requirements as mentioned at the top of this file.
 */

static StackType_t targetTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );
static StackType_t FuzzerTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );

uint16_t redzone1[MODBUS_SLAVE_REGISTERS_NUM] __attribute__( ( aligned( MODBUS_SLAVE_REGISTERS_NUM * sizeof(uint16_t) ) ) );
uint16_t modbusMemory[MODBUS_SLAVE_REGISTERS_NUM] __attribute__( ( aligned( MODBUS_SLAVE_REGISTERS_NUM * sizeof(uint16_t) ) ) );
uint16_t redzone2[MODBUS_SLAVE_REGISTERS_NUM] __attribute__( ( aligned( MODBUS_SLAVE_REGISTERS_NUM * sizeof(uint16_t) ) ) );
uint8_t modbusRxTxBuffer[MODBUS_MAX_FRAME_SIZE] __attribute__( ( aligned( MODBUS_MAX_FRAME_SIZE  ) ) );
uint16_t redzone3[MODBUS_SLAVE_REGISTERS_NUM] __attribute__( ( aligned( MODBUS_SLAVE_REGISTERS_NUM * sizeof(uint16_t) ) ) );
modbus_t  modbusVars __attribute__( ( aligned( next_power_of_2(sizeof(modbus_t)) ) ) );



// Entry function for the fuzzer
void vStartMPUDemo( void );

// The targte task
static void targetTask( void * pvParameters );
// The furzzer task
static void fuzzerTask( void * pvParameters );

// Helper to launch targte tasks
static void spawnNewTarget();


#if INCLUDE_HeapMPU == 1
void callbackInvalidFree()
{
	INVALID_FREE;
}
#endif

//this is the Modbus task
static void targetTask( void * pvParameters )
{
	/* Unused parameters. */
	//( void ) pvParameters;

   #if DUALCOREFUZZ == 0
   //uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
   Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
   #endif


    AFLfuzzer.xTypeEx = EX_NO_EX;

    /**
     * To test this firmware fuzzing template
     * you need a physical connection between UART2 TX (PD5) -> UART4 RX (PD0)
     * reference to physical connectors of Nucleo-H743 https://os.mbed.com/platforms/ST-Nucleo-H743ZI/
     * ****/


    SytemCall_1(); //modbusSlaveHardwareInit();  // this only starts receiving data, the HW is initialized in

    xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,2,1,eSetValueWithOverwrite); //notify the fuzzer task the target is ready


    while(1)
    {


    	ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //wait for data coming from USART
        modbusSlaveHandler(); //entry point of DMA Modbus library
        xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,0,FAULT_NONE_RTOS,eSetValueWithOverwrite);//notify that the test finished
    }


}



static void spawnNewTarget()
{
   #if DUALCOREFUZZ == 0
   //uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
   Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
   #endif

   TaskParameters_t targetTaskParameters =
   {
        	.pvTaskCode		= targetTask,
        	.pcName			= "Target",
        	.usStackDepth	= configMINIMAL_STACK_SIZE,
        	.pvParameters	= NULL,
        	.uxPriority		= 20, //| portPRIVILEGE_BIT, //20,     //20 | portPRIVILEGE_BIT,
        	.puxStackBuffer	= targetTaskStack,
        	.xRegions		=	{
        			                { AFLfuzzerRegion, AFLINPUTREGION_SIZE, portMPU_REGION_READ_WRITE }, // AFL bitmap, diff buffer, TX diff buffer, this region is shareable
									{ __user_heap_start__, 8*1024, portMPU_REGION_READ_WRITE  },
   								    { ( void * )0x20000000, 64*1024, portMPU_REGION_READ_WRITE },     // shadow memory
									{  modbusMemory, MODBUS_SLAVE_REGISTERS_NUM * sizeof(uint16_t),  portMPU_REGION_READ_WRITE},
									{  modbusRxTxBuffer, MODBUS_MAX_FRAME_SIZE ,  portMPU_REGION_READ_WRITE},
									{  &modbusVars, MODBUS_SLAVE_REGISTERS_NUM * sizeof(uint16_t),  portMPU_REGION_READ_WRITE},
									//{  &huart4, next_power_of_2(sizeof(UART_HandleTypeDef)),  portMPU_REGION_READ_WRITE},
									//{  &hdma_uart4_rx, next_power_of_2(sizeof(DMA_HandleTypeDef)),  portMPU_REGION_READ_WRITE}

        	                     }



   };




   //create a new task
   xTaskCreateRestricted( &( targetTaskParameters ), &AFLfuzzer.xTaskTarget );



}

uint16_t *indexdifP;
uint8_t  bufferDMA[550];
static void fuzzerTask( void * pvParameters )
{
	/* Unused parameters. */
	( void ) pvParameters;
	uint32_t notificationvalue;
	uint32_t numberofcycles;
	int i;
	int refreshtarget = 0;

    #if DUALCOREFUZZ == 0
	//uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
    uint16_t *paflbitmap =  pAFLfuzzer->aflbmp;
    #endif

    indexdifP = &AFLfuzzer.indexdif;


	//initialize the USB stack

    #if USARTHW == 1

    		   AFLfuzzer.receiving = false;
	           HAL_UART_Receive_IT(&huart3, AFLfuzzer.inputAFL.uxBuffer, 4);
	           //HAL_UARTEx_ReceiveToIdle_DMA(&huart3, bufferDMA, MAX_BUFFER_INPUT);
    #endif
	MX_USB_DEVICE_Init();
	error_cnt = 0;

	/**NOTIFICATION INDEXES**
	 * 0: Notification from target to fuzzer after test execution
	 * 1: Notification from USB USART driver to the fuzzer task when data has arrived
	 * 2: Notification from target to fuzzer to signal readiness to execute the test
	 * ********/

	/**Lets poison the AFLfuzzer structure**/
	uint32_t *HelperShadow =  (uint32_t *)( ((uint32_t)pAFLfuzzer>>3) + McuASAN_CONFIG_APP_MEM_OFFSET);
	uint32_t HelperShadowSize = AFLINPUTREGION_SIZE>>3;
	memset((void *)HelperShadow, 0xff,HelperShadowSize);
	// the only section that should be accessible by the target is the input buffer, so lets un-poison it
	HelperShadow =  (uint32_t *)( ((uint32_t)(&AFLfuzzer.inputAFL.uxBuffer)>>3) + McuASAN_CONFIG_APP_MEM_OFFSET);
	HelperShadowSize = MAX_BUFFER_INPUT>>3;
	memset((void *)HelperShadow, 0x00,HelperShadowSize);

	//the address of the fuzzer  needs access as well
	HelperShadow =  (uint32_t *)( ((uint32_t)(&AFLfuzzer.xTaskFuzzer)>>3) + McuASAN_CONFIG_APP_MEM_OFFSET);
	HelperShadowSize = MAX_BUFFER_INPUT>>3;
	memset((void *)HelperShadow, 0x00,4);

	//these redzones are MPU protected
	memset(redzone1,0xaa,sizeof(redzone1));
	memset(redzone2,0xbb,sizeof(redzone2));
	memset(redzone3,0xbb,sizeof(redzone3));

	numberofcycles = 0;
	spawnNewTarget(); // we pass 0 since we don't need to delete the semaphore the first time
	// wait for the target task notification when ready
	ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);

	for( ; ; )
	{

		// we will wait for a notification on index 1 when fuzzing data has arrived through USB-CDC
		ulTaskNotifyTakeIndexed(1,pdTRUE, portMAX_DELAY);
		{

			//send the payload through USART2 TX  pin PD5
			HAL_UART_Transmit(&huart2,&AFLfuzzer.inputAFL.uxBuffer[4] , AFLfuzzer.inputAFL.u32availablenopad-4, 100);
			while(ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT) != 1) //check if data was received by the target through USART on index 2
			{
				//if we do not receive  a confirmation we delete and recreate the target
				// the target will reconfigure USART4 in RX DMA mode
				 vTaskDelete(AFLfuzzer.xTaskTarget);
				 taskYIELD(); //lets the kernel clean the TCB
				 numberofcycles = 0;
				 spawnNewTarget();
				 // wait for the target task notification when ready
				 ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);
				 //send the payload through USART TX  pin PD5
				 HAL_UART_Transmit(&huart2,&AFLfuzzer.inputAFL.uxBuffer[4] , AFLfuzzer.inputAFL.u32availablenopad-4, 100);

				 refreshtarget = 0;

			}


			AFLfuzzer.previousGuard = 0;
			memset(paflbitmap, 0, AFL_BITMAP_SIZE_BYTES);
			memset(AFLfuzzer.afldiff,0,AFL_BITMAP_SIZE_BYTES/4);
			AFLfuzzer.indexdif = 0;


			// notify the MODBUS task (target) that data has arrived through USART
			// we need this synchronization back and forward for robustness when working with real peripherals
			// and channels that can trigger hardware errors and hang during fuzzing
			 xTaskNotify(AFLfuzzer.xTaskTarget,0,eSetValueWithOverwrite);

			 //we will wait on Index 0 for notification from target task when testing finished
			 notificationvalue = ulTaskNotifyTakeIndexed(0,pdTRUE, TARGET_TIMEOUT);

			 if (notificationvalue == 0) // TIMEOUT
			 {
				 AFLfuzzer.aflheader[0] = FAULT_TMOUT;
				 printf("Target timeout, starting a new target process...\n");
			     //We need to kill the target task and spawn a new target
				 vTaskDelete(AFLfuzzer.xTaskTarget);
				 taskYIELD(); //lets the kernel clean the TCB
				 numberofcycles = 0;
				 spawnNewTarget();
				 // wait for the target task notification when ready
				 ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);


			 }
			 else if(notificationvalue == FAULT_ASAN)
			 {

				 i= 0;
				 while(i<McuASAN_MAX_NUMBER_ALLOCS) //clean malloc allocations if any
				 {
					 if(AFLfuzzer.allocs[i])
				     {
						 free(AFLfuzzer.allocs[i]);
					 }
					 i++;
				  }
				  notificationvalue = FAULT_CRASH;
				  AFLfuzzer.aflheader[0] = notificationvalue;
				  printf("ASAN violation %s \n", (char *)EX_str[AFLfuzzer.xTypeEx]);
				  vTaskDelete(AFLfuzzer.xTaskTarget);
				  taskYIELD();
				  refreshtarget = 1;
			 }
			 else if(notificationvalue == FAULT_CRASH)
			 {
				 AFLfuzzer.aflheader[0] = notificationvalue;
				 printf("T. crash at: 0x%x, %s \n", (unsigned int)AFLfuzzer.PCcrash, (char *)EX_str[AFLfuzzer.xTypeEx]);
				 //The target process was already killed in the Fault Handler ISR,
				 //We need to spawn a new target task
				 numberofcycles = 0;
				 refreshtarget = 1;


			 }
			 else if (notificationvalue == FAULT_NONE_RTOS)
			 {
				 // we need this because 0 means timeout for the RTOS notification system
				notificationvalue = FAULT_NONE;
				AFLfuzzer.aflheader[0] = notificationvalue;

#if PERSISTENT_MODE
				numberofcycles++;
				if(numberofcycles>=FUZZING_CYCLES_IN_PROCESS && refreshtarget==0)
				{
					numberofcycles=0;
#endif
					i = 0;

					while(i<McuASAN_MAX_NUMBER_ALLOCS)
					{
						 if(AFLfuzzer.allocs[i])
						 {
							 free(AFLfuzzer.allocs[i]);
						 }
							 i++;
					}
					vTaskDelete(AFLfuzzer.xTaskTarget);
				    taskYIELD();
				    refreshtarget = 1;

#if PERSISTENT_MODE
				}
#endif

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


#if PERSISTENT_MODE
				numberofcycles++;
				if(numberofcycles>=FUZZING_CYCLES_IN_PROCESS && refreshtarget==0)
				{
					numberofcycles=0;
#endif
					i = 0;

					while(i<McuASAN_MAX_NUMBER_ALLOCS)
					{
						 if(AFLfuzzer.allocs[i])
						 {
							 free(AFLfuzzer.allocs[i]);
						 }
							 i++;
					}
					vTaskDelete(AFLfuzzer.xTaskTarget);
				    taskYIELD();
				    refreshtarget =1;

#if PERSISTENT_MODE
				}
#endif


			 if(refreshtarget)
			 {

				refreshtarget= 0;
				spawnNewTarget();
				ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);
			 }


			 AFLfuzzer.bRXcomplete = false;
			 AFLfuzzer.inputLength = 0;
			 AFLfuzzer.previousGuard = 0;
			 RingZeroes(&AFLfuzzer.inputAFL);
		     AFLfuzzer.timespan = HAL_GetTick() - AFLfuzzer.timespan;


		}

	}
}


#if USARTHW == 1

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
#if DUALCOREFUZZ == 0
	//uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif

	if(huart == &huart3)
    {
    	AFLfuzzer.bTXcomplete = true;
    }

}

uint32_t errors;


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

#if DUALCOREFUZZ == 0
	//uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif
/*
     uint8_t *data;

     data = AFLfuzzer.inputAFL.uxBuffer;

	 HAL_UART_Abort_IT(&huart3);
	 HAL_UART_Receive_IT(&huart3, data, 4);
*/

     HAL_UART_Abort(&huart3);
 	 __HAL_UART_FLUSH_DRREGISTER(&huart3);
     HAL_UART_DeInit(&huart3);
	 __HAL_UART_DISABLE(&huart3);
	 __HAL_UART_ENABLE(&huart3);

	 HAL_UART_Init(&huart3);


    errors++;



	 AFLfuzzer.bRXcomplete = false;
	 AFLfuzzer.inputLength = 0;
	 AFLfuzzer.previousGuard = 0;
	 RingZeroes(&AFLfuzzer.inputAFL);
	 HAL_UART_Receive_IT(&huart3, AFLfuzzer.inputAFL.uxBuffer, 4);
	 //HAL_UARTEx_ReceiveToIdle_DMA(&huart3, bufferDMA, MAX_BUFFER_INPUT);

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

#if DUALCOREFUZZ == 0
	//uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif

	union ubytes_t auxbytes;
	uint8_t *data;
	uint8_t padding;
	data = AFLfuzzer.inputAFL.uxBuffer;

    if(AFLfuzzer.breceiving == false)
    {
    	AFLfuzzer.breceiving = true;

    	auxbytes.vbytes[0] = data[0];
    	auxbytes.vbytes[1] = data[1];
    	auxbytes.vbytes[2] = data[2];
    	auxbytes.vbytes[3] = data[3];
    	AFLfuzzer.inputLength = auxbytes.vint32;
        if(auxbytes.vint32 < 530)
        {
        	if (auxbytes.vint32 % 4)
        	{
        	     padding = 4 - auxbytes.vint32 % 4;
        	}
        	if (auxbytes.vint32 % 4)
        	{
        	   padding = 4 - auxbytes.vint32 % 4;
        	}
        	else
        	{
        	    padding = 0;
        	}
        	AFLfuzzer.inputLengthpadded = auxbytes.vint32 + padding;
        	HAL_UART_Receive_IT(&huart3, data+4, AFLfuzzer.inputLengthpadded);
          }
    }
    else
    {
    	AFLfuzzer.breceiving = false;
    	AFLfuzzer.inputAFL.u32available =  AFLfuzzer.inputLengthpadded  + 4;
    	if(checkCRC(&AFLfuzzer.inputAFL))
    	{
    		AFLfuzzer.bRXcomplete = true;
    	}
    	else
    	{
			 AFLfuzzer.inputLength = 0;
			 AFLfuzzer.bRXcomplete = false;
			 AFLfuzzer.inputLength = 0;
			 RingZeroes(&AFLfuzzer.inputAFL);
			 HAL_UART_Receive_IT(&huart3, data, 4);

    	}

    }

}



void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
#if DUALCOREFUZZ == 0
	//uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
    Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif
	uint16_t len;

	len = Size;
	FuzzingInputHandler(bufferDMA, (uint32_t *)(&len));
	if(AFLfuzzer.bRXcomplete == false)
	{
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, bufferDMA, MAX_BUFFER_INPUT);
	}

}

#endif

void vStartMPUDemo( void )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;

TaskParameters_t fuzzerTaskParameters =
{
	.pvTaskCode		= fuzzerTask,
	.pcName			= "Fuzzer",
	.usStackDepth	= configMINIMAL_STACK_SIZE,
	.pvParameters	= NULL,
	.uxPriority		= 20| portPRIVILEGE_BIT, //20 | portPRIVILEGE_BIT,
	.puxStackBuffer	= FuzzerTaskStack,
	.xRegions		=	{
			                { 0, 0, 0 },
							{ 0, 0, 0 },
							{ 0, 0, 0 },
					}
};

	/* Create the fuzzer task */
	xTaskCreateRestricted( &( fuzzerTaskParameters ), &AFLfuzzer.xTaskFuzzer );
	//spawnNewTarget();

}
/*-----------------------------------------------------------*/




/*

void vHandleMemoryFault( uint32_t * pulFaultStackAddress )
{
uint32_t ulPC;
uint16_t usOffendingInstruction;

	// Is this an expected fault?
	//if( ucROTaskFaultTracker[ 0 ] == 1 )
	//{
		// Read program counter.
		ulPC = pulFaultStackAddress[ 6 ];

		// Read the offending instruction.
		usOffendingInstruction = *( uint16_t * )ulPC;

		 // From ARM docs:
		 // If the value of bits[15:11] of the halfword being decoded is one of
		 // the following, the halfword is the first halfword of a 32-bit
		 // instruction:
		 // - 0b11101.
		 // - 0b11110.
		 // - 0b11111.
		 // Otherwise, the halfword is a 16-bit instruction.
		 //

		// Extract bits[15:11] of the offending instruction.
		usOffendingInstruction = usOffendingInstruction & 0xF800;
		usOffendingInstruction = ( usOffendingInstruction >> 11 );

		// Determine if the offending instruction is a 32-bit instruction or
		 // a 16-bit instruction.
		if( usOffendingInstruction == 0x001F ||
			usOffendingInstruction == 0x001E ||
			usOffendingInstruction == 0x001D )
		{
			 //Since the offending instruction is a 32-bit instruction,
			 // increment the program counter by 4 to move to the next
			 // instruction.
			ulPC += 4;
		}
		else
		{
			//Since the offending instruction is a 16-bit instruction,
			// increment the program counter by 2 to move to the next
			// instruction. //
			ulPC += 2;
		}

		// Save the new program counter on the stack.
		pulFaultStackAddress[ 6 ] = ulPC;
}

*/
/*-----------------------------------------------------------*/
