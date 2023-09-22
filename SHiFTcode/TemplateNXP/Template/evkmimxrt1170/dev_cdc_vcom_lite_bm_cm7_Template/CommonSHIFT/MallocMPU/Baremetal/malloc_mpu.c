/*
 * malloc_mpu.c
 *
 *  Created on: Nov 8, 2021
 *      Author: alejandro
 */


#include "malloc_mpu.h"

#if MALLOCBAREMETAL == 1
extern mpu_heap_t mh; // in baremetal this is a global variable
#endif

void *malloc_mpu(size_t size)
{
	int i, RegionIndex, SubRegion;

	int j, RI;

#if MALLOCBAREMETAL == 1
	mpu_heap_t *mpuheap;
	mpuheap = &mh;
#else
	//here execute the RTOS extension to get the heap allocator metadata
	// mpuheap = metdata();
	//
#endif


	uint8_t *regions, *pointer;


	int NumBlocks;

	if(size==0) return NULL;  //mpuheap->TotalRegion
	if (size % mpuheap->Blocksize) return NULL; // it only support multiples of block size
	if (size > mpuheap->Blocksize * (mpuheap->TotalRegion/2*8-2)) return NULL; // the block size is bigger than the heap

	NumBlocks = size / mpuheap->Blocksize + 2; // we add 2 sub-regions for redzones

	if(mpuheap->CurrentBlock == 'A')
	{
		mpuheap->CurrentBlock = 'B';
		regions = mpuheap->SubRegBlockB;
	}
	else
	{
		mpuheap->CurrentBlock = 'A';
		regions = mpuheap->SubRegBlockA;
	}


	uint8_t consecutive, firstfree;
	consecutive=0;

	for(i = 0; i < mpuheap->TotalRegion/2 * 8; i ++ )
	{
		RegionIndex = i / 8;
		SubRegion  = i % 8;

		//look for a space in memory that can hold the chunk required
		if( !(regions[RegionIndex] & (1 << SubRegion)) )
		{
			if(consecutive == 0)
			{
				consecutive=1;
				firstfree = i;
			}
			else
			{
				consecutive++;
				if(consecutive == NumBlocks)
				{
					//generate MPU configuration
					for(j= firstfree+1; j < i; j++) // firstfree is the first redzone, j == i is the second redzone
					{
						RI = j/8;
						regions[RI] = regions[RI]  | 1<<(j%8);
					}

					//calculate the pointer to return
					if(mpuheap->CurrentBlock == 'A') pointer = mpuheap->StartAddressA + mpuheap->Blocksize * (firstfree + 1);
					else pointer = mpuheap->StartAddressB + mpuheap->Blocksize * (firstfree +1);
					//Configure the MPU
					mpu_configurator();

					return pointer;
				}

			}
		}
		else
		{
			consecutive = 0;
		}

	}

	return NULL;
}

void free_mpu(void *ptr)
{
	uint8_t block = 0;
	mpu_heap_t *mpuheap;
	mpuheap = &mh;
	uint8_t *StartAddress;
	uint8_t *regions;


	int i, RegionIndex, SubRegion;
	int preRegionIndex, preSubRegion;

	if(ptr == NULL ||  (uint32_t)ptr % mpuheap->Blocksize)
	{
		mpuheap->callbackInvalidFree();
		return;
	}

	if((uint8_t *)ptr > mpuheap->StartAddressA &&
			(uint8_t *)ptr <  ( mpuheap->StartAddressA + mpuheap->Blocksize * 8 * mpuheap->TotalRegion /2 ) )
	{
		block = 'A';
		regions = mpuheap->SubRegBlockA;
		StartAddress = mpuheap->StartAddressA;
	}
	if((uint8_t *)ptr > mpuheap->StartAddressB &&
			(uint8_t *)ptr <  ( mpuheap->StartAddressB + mpuheap->Blocksize * 8 * mpuheap->TotalRegion /2 ) )
	{
		block = 'B';
		regions = mpuheap->SubRegBlockB;
		StartAddress = mpuheap->StartAddressB;
	}

	if(block)
	{
		i = ((uint8_t *)ptr - StartAddress) / mpuheap->Blocksize;
		RegionIndex = i/8;
		SubRegion = i%8;

		preRegionIndex = (i-1)/8;
		preSubRegion = (i-1)%8;

		// This is a valid address to free when the subregion is 1, and the previous is 0 (i.e., it is a redzone)
		if(regions[RegionIndex]&1<< SubRegion && !(regions[preRegionIndex]&1<< preSubRegion ))
		{
			//Free all the consecutive blocks till finding a redzone or reaching the end of the array
		   	while( regions[RegionIndex]&1<< SubRegion  && RegionIndex <  mpuheap->TotalRegion/2 )
			{
				regions[RegionIndex] = regions[RegionIndex] & ~(1<<SubRegion);
				i++;
				RegionIndex = i/8;
				SubRegion = i%8;
			}
		   	//Configure the MPU
		   	mpu_configurator();
		}
		else
		{
			mpuheap->callbackInvalidFree();
			return;
		}
	}
	else
	{
		mpuheap->callbackInvalidFree();
		return;
	}


}

void mpu_configurator()
{

	mpu_heap_t *mpuheap;
	mpuheap = &mh;
	uint8_t i;
	uint32_t *BaseAddress;


	MPU_Region_InitTypeDef MPU_InitStruct;

	HAL_MPU_Disable();

	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Size = MALLOCMPU_REGION_SIZE;
	MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	for(i = 0; i< mpuheap->TotalRegion/2 ; i++)
	{
		//Block A
		BaseAddress = (uint32_t *)(mpuheap->StartAddressA + mpuheap->Blocksize*8*i);
		MPU_InitStruct.BaseAddress = (uint32_t)BaseAddress;
		MPU_InitStruct.Number = mpuheap->Firstregion + i;
		MPU_InitStruct.SubRegionDisable = mpuheap->SubRegBlockA[i];
		HAL_MPU_ConfigRegion(&MPU_InitStruct);
		//Block B
		BaseAddress = (uint32_t *)(mpuheap->StartAddressB + mpuheap->Blocksize*8*i);
		MPU_InitStruct.BaseAddress = (uint32_t)BaseAddress;
		MPU_InitStruct.Number = mpuheap->Firstregion + i + mpuheap->TotalRegion/2;
		MPU_InitStruct.SubRegionDisable = mpuheap->SubRegBlockB[i];
		HAL_MPU_ConfigRegion(&MPU_InitStruct);
	}

	// Configure RAM region as Region N°0, 8kB of size and R/W region
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT); 
}

