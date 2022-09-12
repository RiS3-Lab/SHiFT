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
#include "test.h"
#include "McuASANconfig.h"
#include "ConfigFuzzing.h"





//#include "freertos_tasks_c_additions.h"
//extern USBD_HandleTypeDef hUsbDeviceFS;FAULT_NONE_RTOS
extern CRC_HandleTypeDef hcrc;
extern RNG_HandleTypeDef hrng;
extern UART_HandleTypeDef huart3;
extern uint32_t __user_heap_start__[];


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


// beginning of cAT needded configurations and callbacks
int32_t speed;
uint16_t adr;
uint8_t x;
uint8_t y;
uint8_t bytes_buf[4];
char msg[16];
bool quit_flag;

int x_write(const struct cat_variable *var, size_t write_size)
{
        printf("x variable updated internally to: %u\n", x);
        return 0;
}

int y_write(const struct cat_variable *var, size_t write_size)
{
        printf("y variable updated internally to: %u\n", y);
        return 0;
}

int msg_write(const struct cat_variable *var, size_t write_size)
{
        printf("msg variable updated %lu bytes internally to: <%s>\n", write_size, msg);
        return 0;
}

int speed_write(const struct cat_variable *var, size_t write_size)
{
        printf("speed variable updated internally to: %d\n", speed);
        return 0;
}

int adr_write(const struct cat_variable *var, size_t write_size)
{
        printf("adr variable updated internally to: 0x%04X\n", adr);
        return 0;
}

int bytesbuf_write(const struct cat_variable *var, size_t write_size)
{
        int i = 0;

        printf("bytes_buf variable updated %lu bytes internally to: ", write_size);
        for (i = 0; i < sizeof(bytes_buf); i++)
                printf("%02X", bytes_buf[i]);
        printf("\n");

        return 0;
}

int go_write(const struct cat_command *cmd, const uint8_t *data, const size_t data_size, const size_t args_num)
{
        int i = 0;

        printf("<%s>: x=%d y=%d msg=%s @ speed=%d\n",
                cmd->name,
                *(uint8_t*)(cmd->var[0].data),
                *(uint8_t*)(cmd->var[1].data),
                msg,
                speed
        );

        printf("<bytes>: ");
        for (i = 0; i < sizeof(bytes_buf); i++)
                printf("%02X", bytes_buf[i]);
        printf("\n");
        return 0;
}

int set_write(const struct cat_command *cmd, const uint8_t *data, const size_t data_size, const size_t args_num)
{
        printf("<%s>: SET SPEED TO = %d\n",
                cmd->name,
                speed
        );
        return 0;
}

int set_read(const struct cat_command *cmd, uint8_t *data, size_t *data_size, const size_t max_data_size)
{
        return 0;
}

int test_run(const struct cat_command *cmd)
{
        printf("TEST: <%s>", cmd->name);
        return 0;
}

int quit_run(const struct cat_command *cmd)
{
        printf("QUIT: <%s>", cmd->name);
        quit_flag = true;
        return 0;
}

int print_cmd_list1(const struct cat_command *cmd)
{
        return CAT_RETURN_STATE_PRINT_CMD_LIST_OK;
}

struct cat_variable go_vars[] = {
        {
                .type = CAT_VAR_UINT_DEC,
                .data = &x,
                .data_size = sizeof(x),
                .write = x_write,
                .name = "x"
        },
        {
                .type = CAT_VAR_UINT_DEC,
                .data = &y,
                .data_size = sizeof(y),
                .write = y_write,
                .name = "y"
        },
        {
                .type = CAT_VAR_BUF_STRING,
                .data = msg,
                .data_size = sizeof(msg),
                .write = msg_write,
                .name = "msg"
        }
};

struct cat_variable set_vars[] = {
        {
                .type = CAT_VAR_INT_DEC,
                .data = &speed,
                .data_size = sizeof(speed),
                .write = speed_write,
                .name = "speed"
        },
        {
                .type = CAT_VAR_NUM_HEX,
                .data = &adr,
                .data_size = sizeof(adr),
                .write = adr_write,
                .name = "address"
        },
        {
                .type = CAT_VAR_BUF_HEX,
                .data = &bytes_buf,
                .data_size = sizeof(bytes_buf),
                .write = bytesbuf_write,
                .name = "buffer"
        }
};

struct cat_command cmds[] = {
        {
                .name = "+GO",
                .write = go_write,
                .var = go_vars,
                .var_num = sizeof(go_vars) / sizeof(go_vars[0]),
                .need_all_vars = true
        },
        {
                .name = "+SET",
                .write = set_write,
                .read = set_read,
                .var = set_vars,
                .var_num = sizeof(set_vars) / sizeof(set_vars[0]),
        },
        {
                .name = "#TEST",
                .run = test_run
        },
        {
                .name = "#HELP",
                .run = print_cmd_list1,
        },
        {
                .name = "#QUIT",
                .run = quit_run
        },

};

char buf[128];

struct cat_command_group cmd_group = {
        .cmd = cmds,
        .cmd_num = sizeof(cmds) / sizeof(cmds[0]),
};

struct cat_command_group *cmd_desc[] = {
        &cmd_group
};

struct cat_descriptor desc = {
        .cmd_group = cmd_desc,
        .cmd_group_num = sizeof(cmd_desc) / sizeof(cmd_desc[0]),

        .buf = buf,
        .buf_size = sizeof(buf)
};

struct cat_object cat_obj;

// end of cAT needed call backs
/**
 * @brief Size of the shared memory region.
 */
#define SHARED_MEMORY_SIZE 32

#define MPUTESTENABLED 0



#if DUALCOREFUZZ == 0
//uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif

uint32_t error_cnt;

/**
 * Since stack of a task is protected using MPU, it must satisfy MPU
 * requirements as mentioned at the top of this file.
 */

static StackType_t targetTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );
static StackType_t FuzzerTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ) ) );

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

int write_char(char ch)
{
        putc(ch, stdout);
        return 1;
}

unsigned int input_cursor = 0;

int read_char(char *ch)
{
	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	if(input_cursor >= (pAFLfuzzer->inputAFL.u32availablenopad-4)){
		*ch = '\0';
	}else{
		*ch = pAFLfuzzer->inputAFL.uxBuffer[input_cursor + 4];
		input_cursor ++;
	}
	return 1;
}

struct cat_io_interface iface = {
        .read = read_char,
        .write = write_char
};

static void targetTask( void * pvParameters )
{
	/* Unused parameters. */
	//( void ) pvParameters;

   #if DUALCOREFUZZ == 0
   //uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
   Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
   #endif

	//uint32_t testnumber = 0;
    //vTaskAllocateMPURegions(NULL,targetTaskParameters.xRegions );

   /*
   InitmallocMPU(MALLOCMPU_ADRESS_A,
   MALLOCMPU_ADRESS_B,
   MALLOCMPU_BLOCK_SIZE,
   MALLOCMPU_REGION_SIZE,
   MALLOCMPU_FIRST_REGION,
   MALLOCMPU_TOTAL_REGION,
   callbackInvalidFree);
   uint8_t *pointer;// = mallocMPU(32);
   uint8_t readaux;
   readaux = 10;

   if(pointer)
   	 {
	     readaux = pointer[32];    // This should trigger exception out of bounds read
	     pointer[-1]=readaux; 		   // This should trigger an exception out of bounds write
   		 pointer[0]=1;             // This is a valid access
   		 pointer[32-1]=1;            // This is a valid access

   		 //free_mpu(pointer + 2);    // This should trigger invalid free
   		 //free_mpu(pointer);        // This is a valid free
   		 //pointer[0]=1;      	   // This should trigger exception use after free
   	 }
   pointer[3] = readaux;

   freeMPU(pointer);


    pointer = mallocMPU(32);

    */

    AFLfuzzer.xTypeEx = EX_NO_EX;
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
    uint8_t firstRun=1;

   	xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,2,1,eSetValueWithOverwrite); //notify the fuzzer task the target is ready
   	cat_init(&cat_obj, &desc, &iface, NULL);
   	for( ; ; )
	{

    	ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for the data coming from the fuzzer task

    	if(firstRun)
    	{
    		//AFLfuzzer.bRXcomplete = false;
    		//AFLfuzzer.inputLength = 0;
    		AFLfuzzer.previousGuard = 0;
    		//RingZeroes(&AFLfuzzer.inputAFL);
    		memset(AFLfuzzer.aflbmp,0,AFL_BITMAP_SIZE*sizeof(uint16_t));
    		memset(AFLfuzzer.afldiff,0, AFL_BITMAP_SIZE/4 *sizeof(tuple_t)); //we need on extra tuple to clean which is used for the CRC
    		AFLfuzzer.indexdif = 0;
    		firstRun=0;
    	}

		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		/*
		printf("Input: ");
		for(i=0; i< (AFLfuzzer.inputAFL.u32availablenopad-4); i++ )
		{
			printf("\\x\%02x",AFLfuzzer.inputAFL.uxBuffer[i+4]);
		}
		printf("\n");
		*/
		input_cursor = 0;
		// since if input_cursor goes beyond the input buffer, read will just return \n so the buffer won't overflow
		while(input_cursor < (pAFLfuzzer->inputAFL.u32availablenopad-4))
		{
			cat_service(&cat_obj);
		}
		xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,0,FAULT_NONE_RTOS,eSetValueWithOverwrite);//notify that the test finished
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
	}
}



static void spawnNewTarget( )
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
        	.uxPriority		= 20 | portPRIVILEGE_BIT, //20,     //20 | portPRIVILEGE_BIT,
        	.puxStackBuffer	= targetTaskStack,
        	.xRegions		=	{
        			                { AFLfuzzerRegion, AFLINPUTREGION_SIZE, portMPU_REGION_READ_WRITE }, // AFL bitmap, diff buffer, TX diff buffer, this region is shareable
									{ __user_heap_start__, 8*1024, portMPU_REGION_READ_WRITE  },
   							 	    //{ paflbitmap, AFL_BITMAP_SIZE_BYTES, portMPU_REGION_READ_WRITE},    // This is necessary because AFL_BITMAP is in the TCM region
   								    { ( void * )0x20000000, 64*1024, portMPU_REGION_READ_WRITE },     // shadow memory

									//{0,0,0}
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


	numberofcycles = 0;
	spawnNewTarget();
	// wait for the target task notification when ready
	ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);

	for( ; ; )
	{

		// we will wait for a notification on index 1 when fuzzing data has arrived
		ulTaskNotifyTakeIndexed(1,pdTRUE, portMAX_DELAY);
		{

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
 				  spawnNewTarget();
 				  ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);
			 }
			 else if(notificationvalue == FAULT_CRASH)
			 {
				 AFLfuzzer.aflheader[0] = notificationvalue;
				 printf("T. crash at: 0x%x, %s \n", (unsigned int)AFLfuzzer.PCcrash, (char *)EX_str[AFLfuzzer.xTypeEx]);
				 //The target process was already killed in the Fault Handler ISR,
				 //We need to spawn a new target task
				 numberofcycles = 0;
				 spawnNewTarget();
				 taskYIELD(); // let's the kernel clean the TCB
				 // wait for the target task notification when ready
				 ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);

			 }
			 else if (notificationvalue == FAULT_NONE_RTOS)
			 {
				 // we need this because 0 means timeout for the RTOS notification system
				notificationvalue = FAULT_NONE;
				AFLfuzzer.aflheader[0] = notificationvalue;

#if PERSISTENT_MODE
				numberofcycles++;
				if(numberofcycles>=FUZZING_CYCLES_IN_PROCESS)
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
					spawnNewTarget();
					ulTaskNotifyTakeIndexed(2,pdTRUE, TARGET_TIMEOUT/2);

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

			 #if USARTHW == 0
			 CDC_Transmit_FS((uint8_t *)AFLfuzzer.aflheader, 8);
             #else
			 HAL_UART_Transmit_IT(&huart3, (uint8_t *)AFLfuzzer.aflheader, 8);
			 //HAL_UART_Transmit_DMA(&huart3,(uint8_t *)AFLfuzzer.aflheader, 8);
             #endif

			 //while(AFLfuzzer.bTXcomplete ==false); //wait for end of transmission
			 ulTaskNotifyTakeIndexed(1,pdTRUE, 10);

			 AFLfuzzer.bTXcomplete = false;
             #if USARTHW == 0
			 CDC_Transmit_FS((uint8_t *)auxdiff, AFLfuzzer.aflheader[1]);
             #else
			 HAL_UART_Transmit_IT(&huart3, (uint8_t *)auxdiff, AFLfuzzer.aflheader[1]);
			 //HAL_UART_Transmit_DMA(&huart3, (uint8_t *)auxdiff, AFLfuzzer.aflheader[1]);
             #endif

			 //while(AFLfuzzer.bTXcomplete ==false); //wait for end of transmission
			 ulTaskNotifyTakeIndexed(1,pdTRUE, 10);
			 AFLfuzzer.bRXcomplete = false;
			 AFLfuzzer.inputLength = 0;
			 AFLfuzzer.previousGuard = 0;
			 RingZeroes(&AFLfuzzer.inputAFL);

			 for(uint32_t i=0; i<AFLfuzzer.indexdif; i++)
			 {
				 paflbitmap[auxdiff[i].index]=0;
			 }
			 memset(AFLfuzzer.afldiff,0,(AFLfuzzer.indexdif+2)*sizeof(tuple_t)); //we need on extra tuple to clean which is used for the CRC
			 AFLfuzzer.indexdif = 0;
			 AFLfuzzer.timespan = HAL_GetTick() - AFLfuzzer.timespan;

			 //printf("Total time: %u \n", (uint)AFLfuzzer.timespan);
#if USARTHW == 1
			 HAL_UART_Receive_IT(&huart3, AFLfuzzer.inputAFL.uxBuffer, 4);
			// HAL_UARTEx_ReceiveToIdle_DMA(&huart3, bufferDMA, MAX_BUFFER_INPUT);
#endif
		}

	}
}



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
