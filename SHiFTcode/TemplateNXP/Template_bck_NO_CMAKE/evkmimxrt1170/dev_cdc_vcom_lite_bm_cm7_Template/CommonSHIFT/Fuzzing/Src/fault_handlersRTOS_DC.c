/*
 * Alejandro
 * 1 tab == 4 spaces!
 */



#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "fuzzing.h"

extern WWDG_HandleTypeDef hwwdg2;

#if DUALCOREFUZZ == 0
//uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif


void deleteTask()
{

	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	//BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	AFLfuzzer.notiVCM4TOCM7 = FAULT_CRASH; //we detected a crash
	HAL_HSEM_FastTake(HSEM_ID_2);
	HAL_HSEM_Release(HSEM_ID_2,0);

	//hwwdg2.Instance->CR=64; //this should trigger a reboot immediately
    while(1);
	//NVIC_SystemReset();


	//xTaskNotifyFromISR(AFLfuzzer.xTaskMonitor,FAULT_CRASH,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
	//HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	//vTaskDelete(AFLfuzzer.xTaskTarget);

	/*

	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    //Notify the fuzzer task that the target crashed
    AFLfuzzer.notiVCM4TOCM7 = FAULT_CRASH; //we detected a crash
    HAL_HSEM_FastTake(HSEM_ID_2);
    HAL_HSEM_Release(HSEM_ID_2,0);
    xTaskNotifyFromISR(AFLfuzzer.xTaskMonitor,FAULT_CRASH,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    vTaskDelete(AFLfuzzer.xTaskTarget);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken);

    while(1);
*/
    /*
    xTaskNotifyFromISR(AFLfuzzer.xTaskFuzzer,FAULT_CRASH,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    //Delete the target task
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
    vTaskDelete(AFLfuzzer.xTaskTarget);
    // port yield should be called and nothing else should be executed
    //portYIELD_FROM_ISR( xHigherPriorityTaskWoken ); // this line is not necessary
    //since deleting the task will force a context switch.

	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(AFLfuzzer.xTaskFuzzer,FAULT_CRASH,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	vTaskDelete(AFLfuzzer.xTaskTarget);
	*/

}


portDONT_DISCARD void vHandleMemoryFault( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;


  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {
	  //Get the PC where the crash happened
	  AFLfuzzer.PCcrash = pulFaultStackAddress[ 6 ] ;
	  AFLfuzzer.xTypeEx = EX_MPU_VIOLATION;
	  deleteTask();

  }
  else
  {
	  //printf("Fuzzer crashed at PC: %x\n", (unsigned int)pulFaultStackAddress[ 6 ]);
	  for( ; ; )
	  {
		  // this should never happen if we reach this point the whole firmware state can be corrupted
		  // TODO: can we reboot the MCU here?
	  }

  }


}



portDONT_DISCARD void vNMI_Handler( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;


  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {
	  //Get the PC where the crash happened
		  AFLfuzzer.PCcrash = pulFaultStackAddress[ 6 ] ;
		  AFLfuzzer.xTypeEx = EX_MPU_VIOLATION;
		  deleteTask();
  }
  else
  {
	  //printf("Fuzzer crashed at PC: %x\n", (unsigned int)pulFaultStackAddress[ 6 ]);
	  for( ; ; )
	  {
		  // this should never happen if we reach this point the whole firmware state can be corrupted
		  // TODO: can we reboot the MCU here?
	  }

  }


}


portDONT_DISCARD void vHardFault_Handler( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;

  //this exception is not recoverable
  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {
	  AFLfuzzer.PCcrash = pulFaultStackAddress[ 6 ] ;
	  AFLfuzzer.xTypeEx = EX_HARDFAULT;
	  AFLfuzzer.notiVCM4TOCM7 = FAULT_CRASH; //we detected a crash
	  HAL_HSEM_FastTake(HSEM_ID_2);
	  HAL_HSEM_Release(HSEM_ID_2,0);
	  //this is not recoverable we need to reset the core, we will let the watch dog to reboot the core
	  while(1);

  }


}


portDONT_DISCARD void vBusFault_Handler( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;



  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {
	  //Get the PC where the crash happened
	  AFLfuzzer.PCcrash = pulFaultStackAddress[ 6 ] ;
	  AFLfuzzer.xTypeEx = EX_CORTEX_BUS_FAULT;
	  deleteTask();
  }
  else
  {
	  //printf("Fuzzer crashed at PC: %x\n", (unsigned int)pulFaultStackAddress[ 6 ]);
	  for( ; ; )
	  {
		  // this should never happen if we reach this point the whole firmware state can be corrupted
		  // TODO: can we reboot the MCU here?
	  }

  }


}

portDONT_DISCARD void vUsageFault_Handler( uint32_t * pulFaultStackAddress )
{

Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;


  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
  {
	  //Get the PC where the crash happened
	  AFLfuzzer.PCcrash = pulFaultStackAddress[ 6 ] ;
	  if(SCB->CFSR & SCB_CFSR_DIVBYZERO_Msk)
	  {
	      AFLfuzzer.xTypeEx = EX_CORTEX_DIV0;
		  SCB->CFSR |= SCB_CFSR_DIVBYZERO_Msk; //to clean the bit we need to write 1
	  }
	  if(SCB->CFSR & SCB_CFSR_UNALIGNED_Msk)
	  {
          AFLfuzzer.xTypeEx = EX_CORTEX_UNA_ACCESS;
          SCB->CFSR |= SCB_CFSR_UNALIGNED_Msk;
	  }
	  if(SCB->CFSR & SCB_CFSR_UNDEFINSTR_Msk)
	  {
		  AFLfuzzer.xTypeEx = EX_CORTEX_UNDEF_INST;
		  SCB->CFSR |= SCB_CFSR_UNDEFINSTR_Msk;

	  }
	  deleteTask();

  }
  else
  {
	  //printf("Fuzzer crashed at PC: %x\n", (unsigned int)pulFaultStackAddress[ 6 ]);
	  for( ; ; )
	  {
		  // this should never happen if we reach this point the whole firmware state can be corrupted
		  // TODO: can we reboot the MCU here?
	  }

  }


}




/**
 * @brief Mem fault handler.
 */
void MemManage_Handler( void ) __attribute__ (( naked ));
/*-----------------------------------------------------------*/

void MemManage_Handler( void )
{
	__asm volatile
	(
		" tst lr, #4										\n"
		" ite eq											\n"
		" mrseq r0, msp										\n"
		" mrsne r0, psp										\n"
		" mov   r2, #0                                      \n" // elevate privileges so we can use system calls
		" msr   control, r2                                 \n"	// we can do this because we are in handler mode
		" ldr r1, handler_address_const						\n"
		" bx r1												\n"
		"													\n"
		" handler_address_const: .word vHandleMemoryFault	\n"
	);
}
/*-----------------------------------------------------------*/



/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler( void ) __attribute__ (( naked ));
void NMI_Handler(void)
{

		__asm volatile
		(
			" tst lr, #4										\n"
			" ite eq											\n"
			" mrseq r0, msp										\n"
			" mrsne r0, psp										\n"
			" mov   r2, #0                                      \n" // elevate privileges so we can use system calls
			" msr   control, r2                                 \n"	// we can do this because we are in handler mode
			" ldr r1, handler_address_const1						\n"
			" bx r1												\n"
			"													\n"
			" handler_address_const1: .word vNMI_Handler	\n"
		);

}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler( void ) __attribute__ (( naked ));
void HardFault_Handler(void)
{

		__asm volatile
		(
			" tst lr, #4										\n"
			" ite eq											\n"
			" mrseq r0, msp										\n"
			" mrsne r0, psp										\n"
			" mov   r2, #0                                      \n" // elevate privileges so we can use system calls
			" msr   control, r2                                 \n"	// we can do this because we are in handler mode
			" ldr r1, handler_address_const2						\n"
			" bx r1												\n"
			"													\n"
			" handler_address_const2: .word vHardFault_Handler	\n"
		);

}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler( void ) __attribute__ (( naked ));
void BusFault_Handler(void)
{

		__asm volatile
		(
			" tst lr, #4										\n"
			" ite eq											\n"
			" mrseq r0, msp										\n"
			" mrsne r0, psp										\n"
			" mov   r2, #0                                      \n" // elevate privileges so we can use system calls
			" msr   control, r2                                 \n"	// we can do this because we are in handler mode
			" ldr r1, handler_address_const3						\n"
			" bx r1												\n"
			"													\n"
			" handler_address_const3: .word vBusFault_Handler	\n"
		);

}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler( void ) __attribute__ (( naked ));
void UsageFault_Handler(void)
{
		__asm volatile
		(
			" tst lr, #4										\n"
			" ite eq											\n"
			" mrseq r0, msp										\n"
			" mrsne r0, psp										\n"
			" mov   r2, #0                                      \n" // elevate privileges so we can use system calls
			" msr   control, r2                                 \n"	// we can do this because we are in handler mode
			" ldr r1, handler_address_const5						\n"
			" bx r1												\n"
			"													\n"
			" handler_address_const5: .word vUsageFault_Handler	\n"
		);

}



