/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_main.h"
#include "fuzzing.h"
#include "stdio.h"
#include "TargetDualCoreNoRTOS.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//FDCAN_RxHeaderTypeDef RxHeader;

__IO uint8_t ubKeyNumber = 0x0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif


#define DEVICE_CAN_ID                            0x78E

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

FDCAN_HandleTypeDef hfdcan2;

UART_HandleTypeDef huart3;

WWDG_HandleTypeDef hwwdg2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void MX_FDCAN2_Init(void);
/* USER CODE BEGIN PFP */
/*
void __io_putchar(uint8_t ch) {
HAL_UART_Transmit(&huart3, &ch, 1, 1);
}
*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
  /* USER CODE END 1 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */



	  /*HW semaphore Clock enable*/
	  __HAL_RCC_HSEM_CLK_ENABLE();
	  /* Activate HSEM notification for Cortex-M4*/
	  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	  /*
	  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	  perform system initialization (system clock config, external memory configuration.. )
	  */
	  HAL_PWREx_ClearPendingEvent();
	  //HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);


	  if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDG2RST) ==  RESET)
	  {
	     // we only need to go to sleep if we are powering up for the first time)
	     HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	  }
	  else // here we need to clean up some peripherals that a soft reset will not do so
	  {
		  //the timer 17 needs cleaning since it will trigger an interrupt immediately during configuration finishing in a deadloop
		  __HAL_RCC_TIM17_CLK_ENABLE();
		  __HAL_RCC_TIM17_FORCE_RESET();
		  __HAL_RCC_TIM17_CLK_DISABLE();
		  // more cleaning must be here


	  }


	  /* Clear reset flags in any case */
	  __HAL_RCC_CLEAR_RESET_FLAGS();

	  /* Clear HSEM flag */
	  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));


/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  GPIO_USER_Init();
  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FDCAN2_Init();
  /* USER CODE BEGIN 2 */

  //HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);


  SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
   | SCB_SHCSR_BUSFAULTENA_Msk
   | SCB_SHCSR_MEMFAULTENA_Msk; // enable Usage-/Bus-/MPU Fault

  /*
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk | // enable div by zero trap
 		  SCB_CCR_UNALIGN_TRP_Msk;    // enable unaligned access trap
*/

  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;

  HAL_NVIC_SetPriority(HSEM2_IRQn, 0x05, 0); // activate the HSEM notifications

  //app_main(); // we need to call app_main if we need to use FreeRTOS on CM4
  // otherwise we will configure the MPU here and call the targetNoRTOS

  printf("Initialized CM4!\n");

  targetNoRTOS();



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief FDCAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */
	  FDCAN_FilterTypeDef sFilterConfig;
  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = ENABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = ENABLE;
  hfdcan2.Init.NominalPrescaler = 10;
  hfdcan2.Init.NominalSyncJumpWidth = 8;
  hfdcan2.Init.NominalTimeSeg1 = 11;
  hfdcan2.Init.NominalTimeSeg2 = 4;
  hfdcan2.Init.DataPrescaler = 1;
  hfdcan2.Init.DataSyncJumpWidth = 1;
  hfdcan2.Init.DataTimeSeg1 = 1;
  hfdcan2.Init.DataTimeSeg2 = 1;
  hfdcan2.Init.MessageRAMOffset = 500;
  hfdcan2.Init.StdFiltersNbr = 1;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.RxFifo0ElmtsNbr = 1;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_64;
  hfdcan2.Init.RxFifo1ElmtsNbr = 0;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxBuffersNbr = 0;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.TxEventsNbr = 0;
  hfdcan2.Init.TxBuffersNbr = 0;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 1;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_64;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* Configure Rx filter */
  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = DEVICE_CAN_ID;
  sFilterConfig.FilterID2 = 0x7FF;
  if (HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }

  /* Configure global filter to reject all non-matching frames */
  if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK)
  {
      /* Start Error */
      Error_Handler();
  }

  /* Start the FDCAN module */
  if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }

  /* USER CODE END FDCAN2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 7500000;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief WWDG2 Initialization Function
  * @param None
  * @retval None
  */
void MX_WWDG2_Init(void)
{

  /* USER CODE BEGIN WWDG2_Init 0 */

  /* USER CODE END WWDG2_Init 0 */

  /* USER CODE BEGIN WWDG2_Init 1 */

  /* USER CODE END WWDG2_Init 1 */
  hwwdg2.Instance = WWDG2;
  hwwdg2.Init.Prescaler = WWDG_PRESCALER_2;
  hwwdg2.Init.Window = 80;
  hwwdg2.Init.Counter = 80;
  hwwdg2.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN WWDG2_Init 2 */

  /* USER CODE END WWDG2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LD3_Pin */
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
#if 0
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  FDCAN_RxHeaderTypeDef RxHeader;
  printf("Trg!\n");
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
    /* Reception Error */
    Error_Handler();
    }

    /* Display LEDx */
    if ((RxHeader.Identifier == DEVICE_CAN_ID) && (RxHeader.IdType == FDCAN_STANDARD_ID) && (RxHeader.DataLength == FDCAN_DLC_BYTES_2))
    {

       //ubKeyNumber = RxData[0];
       printf("Keynumber %d\n",RxData[0]);

    }

    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
      /* Notification Error */

      Error_Handler();
    }
  }
}
#endif

void   GPIO_USER_Init(void)
{

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitTypeDef   GPIO_InitStructure;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = LD1_PIN;
	HAL_GPIO_Init(LD1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = LD2_PIN;
	HAL_GPIO_Init(LD2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = LD3_PIN;
	HAL_GPIO_Init(LD3_GPIO_PORT, &GPIO_InitStructure);
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

    __disable_irq();
#if WATCHDOGENABLED
  activateWWDG();
#endif
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
