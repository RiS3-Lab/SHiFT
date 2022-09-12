#include "midi_lowlevel.h"
#include "leds.h" 
#include "main.h"
#include "fuzzing.h"
#include "afl.h"


//char canary1[128];
extern char midiBuffer[MIDI_BUF_SIZE] __attribute__( ( aligned( next_power_of_2(MIDI_BUF_SIZE)  ) ) );    /* for debugging */ //buffer
extern UART_HandleTypeDef huart4;
//char canary2[128];




/*

char redzone1[ext_power_of_2(MIDI_BUF_SIZE)] __attribute__( ( aligned( next_power_of_2(MIDI_BUF_SIZE)  ) ) );

char redzone2[ext_power_of_2(MIDI_BUF_SIZE)] __attribute__( ( aligned( next_power_of_2(MIDI_BUF_SIZE)  ) ) );

MIDIMsgBuilder midiMsgBuilder __attribute__( ( aligned( next_power_of_2(sizeof(MIDIMsgBuilder) )  ) ) );                   //buffers

char redzone3[next_power_of_2(sizeof(MIDIMsgBuilder))] __attribute__( ( aligned( next_power_of_2(sizeof(MIDIMsgBuilder) )  ) ) );

MIDI_Router_Standard midiRouter __attribute__( ( aligned( next_power_of_2(sizeof(MIDI_Router_Standard) )  ) ) );                //buffers

char redzone4[next_power_of_2(sizeof(MIDI_Router_Standard))] __attribute__( ( aligned( next_power_of_2(sizeof(MIDI_Router_Standard) )  ) ) );
*/


void SytemCall_1_code()
{
	MIDI_low_level_setup();
}

void MIDI_low_level_setup(void)
{

	//uint8_t status = 0;




	while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, (uint8_t*) midiBuffer, MIDI_BUF_SIZE) != HAL_OK)
	{
		HAL_UART_Abort(&huart4);
		HAL_UART_DeInit(&huart4);
		HAL_UART_Init(&huart4);
	}

    //status = 1;
    //return status;
}


void SytemCall_2_code()
{
	while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, (uint8_t*) midiBuffer, MIDI_BUF_SIZE) != HAL_OK)
	{
		HAL_UART_Abort(&huart4);
		HAL_UART_DeInit(&huart4);
		HAL_UART_Init(&huart4);
	}
}

void MIDI_process_buffer(void)
{



    int MIDIlastIndex = 0;
    int numItems = ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //wait for data coming from USART



    while (numItems--) {
        MIDI_process_byte(midiBuffer[MIDIlastIndex]);
        /* increase last index so the function starts at the correct point next interrupt */
        MIDIlastIndex = (MIDIlastIndex + 1) % MIDI_BUF_SIZE; 
    }

    SytemCall_2();  // configure port to receive more data



}




void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

	 if(huart==&huart4)
	 {
	   HAL_UART_DMAStop(&huart4);


	   while(HAL_UARTEx_ReceiveToIdle_DMA(&huart4, (uint8_t*) midiBuffer, MIDI_BUF_SIZE) != HAL_OK)
	   {
	  	   HAL_UART_Abort(&huart4);
	  	   HAL_UART_DeInit(&huart4);
	  	   HAL_UART_Init(&huart4);


	   }

	 }
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
#if DUALCOREFUZZ == 0

  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
#endif

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if(huart==&huart4)
	{
		// notify with the buffer size
		xTaskNotifyIndexedFromISR(AFLfuzzer.xTaskFuzzer,2,Size,eSetValueWithOverwrite, &xHigherPriorityTaskWoken);

	}

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}



/* Not even called */
/*
void DMA1_Stream5_IRQHandler (void)
{
    if (DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5) 
            && DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5)) {
        LEDs_greenToggle();
        DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
        DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);
    }
    NVIC_ClearPendingIRQ(DMA1_Stream5_IRQn);
}


void TIM2_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(TIM2_IRQn);
    //if (TIM_GetITStatus(TIM2, TIM_IT_Update)) { P2IM is not solving this SRR site
        MIDI_TIMER_INTERRUPT();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
   // }
}
*/

/*
static void USART2_Enable_Rx_nolib(void)
{

}*/

/*
void MIDI_low_level_setup_nolib(void)
{
    //USART2_Enable_Rx_nolib();
	//USART2_Enable_Rx();
    //Timer_setup();

}
*/
