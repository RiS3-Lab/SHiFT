/*
 * malloc_mpu.h
 *
 *  Created on: Nov 8, 2021
 *      Author: alejandro
 */

#ifndef INC_MALLOC_MPU_H_
#define INC_MALLOC_MPU_H_


#include "stdint.h"
#include "stddef.h"
#include "main.h"




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



void *malloc_mpu(size_t size);
void free_mpu(void *ptr);
void mpu_configurator();


#endif /* INC_MALLOC_MPU_H_ */
