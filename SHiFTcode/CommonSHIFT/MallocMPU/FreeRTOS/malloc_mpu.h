/*
 * malloc_mpu.h
 *
 *  Created on: Nov 12, 2021
 *      Author: alejandro
 */

#ifndef FREERTOS_MALLOC_MPU_H_
#define FREERTOS_MALLOC_MPU_H_

#include "config_malloc.h"
typedef void func(void);
typedef struct
{
uint8_t SubRegBlockA[MALLOCMPU_TOTAL_REGION/2]; // 1 bit for each subregion
uint8_t SubRegBlockB[MALLOCMPU_TOTAL_REGION/2]; // 1 bit for each subregion
uint8_t *StartAddressA;  //it must be  BlockSize*MALLOCMPU_TOTAL_REGION/2 aligned
uint8_t *StartAddressB;
uint32_t Blocksize;   // It must be a multiple of 32
uint32_t Regionsize;  // This is the power value provided by HAL, the actual size calculation is: 2^(Regionsize+1)
uint8_t CurrentBlock; // current block could be 'A' or 'B'
uint8_t Firstregion;
uint8_t TotalRegion;
func *callbackInvalidFree;
}mpu_heap_t;


#endif /* FREERTOS_MALLOC_MPU_H_ */
