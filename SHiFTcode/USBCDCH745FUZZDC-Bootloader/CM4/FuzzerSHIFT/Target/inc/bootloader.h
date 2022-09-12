/*
 * bootloader.h
 *
 *  Created on: Mar 18, 2022
 *      Author: alejandro
 */

#ifndef TARGET_INC_BOOTLOADER_H_
#define TARGET_INC_BOOTLOADER_H_

#include "main.h"


#define  WAIT_HOST    0
#define IDLE        1
#define PAGE_PROG    2

typedef void (*pFunction)(void);

// Flash configuration
#define MAIN_PROGRAM_START_ADDRESS              (uint32_t)0x08002000
#define MAIN_PROGRAM_PAGE_NUMBER                8
#define NUM_OF_PAGES                            (64 - MAIN_PROGRAM_PAGE_NUMBER)

// CAN identifiers
#define DEVICE_CAN_ID                            0x78E
#define CMD_HOST_INIT                            0x01
#define CMD_PAGE_PROG                            0x02
#define CMD_BOOT                                 0x03

#define CAN_RESP_OK                              0x01
#define CAN_RESP_ERROR                           0x02
#define FLASH_PAGE_SIZE                          ((uint32_t)128) //((uint32_t)0x400)



void HAL_FDCAN_RxFifo0CallbackDummie(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);

#endif /* TARGET_INC_BOOTLOADER_H_ */
