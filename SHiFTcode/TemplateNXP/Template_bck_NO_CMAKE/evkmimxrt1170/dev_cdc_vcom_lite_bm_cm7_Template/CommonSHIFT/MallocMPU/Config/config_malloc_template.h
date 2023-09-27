/*
 * config_malloc.h
 *
 *  Created on: Nov 8, 2021
 *      Author: alejandro
 */

#ifndef INC_CONFIG_MALLOC_H_
#define INC_CONFIG_MALLOC_H_

#include "stdio.h"
#include "main.h"

#define MALLOCMPU_ADRESS_A       (uint8_t *)0x38000000
#define MALLOCMPU_ADRESS_B       (uint8_t *)0x38001000
#define MALLOCMPU_BLOCK_SIZE	 32  // It must be a multiple of 32 bytes
#define MALLOCMPU_FIRST_REGION   8   // 0 index based
#define MALLOCMPU_LAST_REGION	 15	 //
#define MALLOCMPU_TOTAL_REGION	 8	 // LAST - FIRST + 1
#define MALLOCMPU_HEAP_SIZE	     MALLOCMPU_TOTAL_REGION * MALLOCMPU_BLOCK_SIZE  //
#define MALLOCMPU_REGION_SIZE    MPU_REGION_SIZE_256B  // MALLOCMPU_BLOCK_SIZE * 8
#define MALLOCBAREMETAL	1

#define INVALID_FREE     printf("Invalid free!\n");



#endif /* INC_CONFIG_MALLOC_H_ */
