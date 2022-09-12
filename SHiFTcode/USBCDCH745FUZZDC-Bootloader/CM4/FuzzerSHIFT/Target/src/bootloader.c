/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* USER CODE BEGIN Includes */
#include <string.h>
#include "McuASAN.h"
#include "bootloader.h"





/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
uint8_t redzone1[64]  __attribute__( ( aligned(64)));
uint8_t RxData[64] __attribute__( ( aligned(64)));
uint8_t redzone2[64] __attribute__( ( aligned(64)));
extern FDCAN_HandleTypeDef hfdcan2;


pFunction                     JumpAddress;

uint8_t                       redzone3[FLASH_PAGE_SIZE]  __attribute__( ( aligned(FLASH_PAGE_SIZE)));
uint8_t                       PageBuffer[FLASH_PAGE_SIZE] __attribute__( ( aligned(FLASH_PAGE_SIZE)));
uint8_t                       redzone4[FLASH_PAGE_SIZE] __attribute__( ( aligned(FLASH_PAGE_SIZE)));

volatile int                  PageBufferPtr;
uint8_t                       PageIndex;
int                           PageCRC;

volatile uint8_t              blState;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);


/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void JumpToApplication()
{
  // here finish the fuzzing test for the current input


  /*
  JumpAddress = *(__IO pFunction*)(MAIN_PROGRAM_START_ADDRESS + 4);
  __set_MSP(*(__IO uint32_t*) MAIN_PROGRAM_START_ADDRESS);
  HAL_DeInit();
  JumpAddress();
  */

  //NotifyHSEM(HSEM_ID_2); //notify CM7 end of test
  //while(1); //force reboot CM4 since the bootloader is already finished at this point


}

void TransmitResponsePacket(uint8_t response)
{
  /*
  hcan.pTxMsg->StdId = DEVICE_CAN_ID;
  hcan.pTxMsg->DLC = 1;
  hcan.pTxMsg->Data[0] = response;
  HAL_CAN_Transmit_IT(&hcan);
  */
}

uint8_t CANlen[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

void HAL_FDCAN_RxFifo0CallbackDummie(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{

  FDCAN_RxHeaderTypeDef RxHeader;
  uint32_t DataLength;

  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
	  /* Retreive Rx messages from RX FIFO0 */
	  if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	  {
	     /* Reception Error */
	     Error_Handler();
	  }

	  // Skip messages not intended for our device
	  if (RxHeader.Identifier != DEVICE_CAN_ID )
	  {
		  HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
		  return;
	  }

	  DataLength =  CANlen[(RxHeader.DataLength>>16) & 0x0000FFFF];

      if (blState == PAGE_PROG)
      {
        memcpy(&PageBuffer[PageBufferPtr],
          RxData,
		  DataLength);
        PageBufferPtr += DataLength;

        if (PageBufferPtr == FLASH_PAGE_SIZE) {
          //HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);

          //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
          //uint32_t crc = HAL_CRC_Calculate(&hcrc, (uint32_t*)PageBuffer, FLASH_PAGE_SIZE / 4);

          //if (crc == PageCRC && PageIndex <= NUM_OF_PAGES)
          if ( PageIndex <= NUM_OF_PAGES)
          {
            //HAL_FLASH_Unlock();

            //uint32_t PageError = 0;

            /*
            eraseInitStruct.TypeErase = TYPEERASE_PAGES;
            eraseInitStruct.PageAddress = MAIN_PROGRAM_START_ADDRESS + PageIndex * FLASH_PAGE_SIZE;
            eraseInitStruct.NbPages = 1;
            HAL_FLASHEx_Erase(&eraseInitStruct, &PageError);
            */

            for (int i = 0; i < FLASH_PAGE_SIZE; i += 4)
            {
              //HAL_FLASH_Program(TYPEPROGRAM_WORD, MAIN_PROGRAM_START_ADDRESS + PageIndex * FLASH_PAGE_SIZE + i, *(uint32_t*)&PageBuffer[i]);
            }

            //HAL_FLASH_Lock();

            TransmitResponsePacket(CAN_RESP_OK);
          }
          else
          {
            TransmitResponsePacket(CAN_RESP_ERROR);
          }

          blState = IDLE;

          //HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
        }
        /*
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
        HAL_CAN_Receive_IT(&hcan, CAN_FIFO0);
        */
        return;
      }

      switch(RxData[0])
      {
        case CMD_HOST_INIT:
          blState = IDLE;
          TransmitResponsePacket(CAN_RESP_OK);
          break;
        case CMD_PAGE_PROG:
          if (blState == IDLE) {
        	memset(PageBuffer, 0, FLASH_PAGE_SIZE);
            memcpy(&PageCRC, &RxData[2], sizeof(int));
            PageIndex = RxData[1];
            blState = PAGE_PROG;
            PageBufferPtr = 0;
          } else {
            // Should never get here
          }
          break;
        case CMD_BOOT:
          TransmitResponsePacket(CAN_RESP_OK);
          JumpToApplication();
          break;
        default:
          break;
      }
   }
/*
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
  HAL_CAN_Receive_IT(&hcan, CAN_FIFO0);
  */
}









/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
