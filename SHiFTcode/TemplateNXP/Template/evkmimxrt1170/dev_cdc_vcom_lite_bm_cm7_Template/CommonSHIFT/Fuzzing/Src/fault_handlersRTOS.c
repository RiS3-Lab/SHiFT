/*
 * Alejandro
 * 1 tab == 4 spaces!
 */



#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "fuzzing.h"
#include <stdio.h>


#if DUALCOREFUZZ == 0
//uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );
#endif


void deleteTask()
{

	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(AFLfuzzer.xTaskFuzzer,FAULT_CRASH,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
	//HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	vTaskDelete(AFLfuzzer.xTaskTarget);

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

 	  //printf("Fuzzer crashed at PC: %x\n", (unsigned int)pulFaultStackAddress[ 6 ]);
	  for( ; ; )
	  {
		  // this should never happen if we reach this point the whole firmware state can be corrupted
		  // TODO: can we reboot the MCU here?
	  }

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
		  printf("Fuzzer crash bus fault!\n");
		  NVIC_SystemReset();

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
		  printf("Fuzzer crash usage fault!: ");
		  if(SCB->CFSR & SCB_CFSR_DIVBYZERO_Msk) printf("EX_CORTEX_DIV0 \n");
		  if(SCB->CFSR & SCB_CFSR_UNALIGNED_Msk) printf("EX_CORTEX_UNA_ACCESS \n");
		  if(SCB->CFSR & SCB_CFSR_UNDEFINSTR_Msk) printf("EX_CORTEX_UNDEF_INST \n");
		  NVIC_SystemReset();
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
		" ldr   r1, handler_address_const				    \n"
		" bx r1												\n"
		" .align 4		           			                \n"
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
			" ldr r1, handler_address_const1					\n"
			" bx r1												\n"
			" .align 4		           			                \n"
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
			" .align 4		           			                \n"
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
			" .align 4		           			                \n"
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
			" ldr r1, handler_address_const5					\n"
			" bx r1												\n"
			" .align 4		           			                \n"
			" handler_address_const5: .word vUsageFault_Handler	\n"
		);

}



