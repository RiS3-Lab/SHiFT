/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define USARTHW 0




#define  RTOSENABLED 1

#define LD1_GPIO_CLK_EN                     __HAL_RCC_GPIOB_CLK_ENABLE
#define LD1_GPIO_PORT                       GPIOB
#define LD1_GPIO_PIN                        GPIO_PIN_0
#define LD2_GPIO_CLK_EN                     __HAL_RCC_GPIOE_CLK_ENABLE
#define LD2_GPIO_PORT                       GPIOE
#define LD2_GPIO_PIN                        GPIO_PIN_1
#define LD3_GPIO_CLK_EN                     __HAL_RCC_GPIOB_CLK_ENABLE
#define LD3_GPIO_PORT                       GPIOB
#define LD3_GPIO_PIN                        GPIO_PIN_14


#include "FreeRTOS.h"
#include "task.h"



#define DUALCOREFUZZ 0


#if DUALCOREFUZZ == 0

#define DTCMRAMORIGIN  0x20000000
#define AFLINPUTREGION_SIZE (1024*64)
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );

#else

#define AFLINPUTREGION_SIZE (1024*128)
#define AFLfuzzerRegion  (uint8_t*)0x24040000

#endif


#define AFLfuzzer  (*pAFLfuzzer)
//#define aflbitmap (*paflbitmap)


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLINK_RX_Pin GPIO_PIN_8
#define STLINK_RX_GPIO_Port GPIOD
#define STLINK_TX_Pin GPIO_PIN_9
#define STLINK_TX_GPIO_Port GPIOD
#define LD2_Pin GPIO_PIN_1
#define LD2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
