/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "asan_test.h"
#include "McuASAN.h"
#include <stdint.h>
#include <stdio.h>
#include "main.h"



uint8_t arr[4];
//uint8_t arr3[4];

const uint8_t arr2[]="1234567";

static  uint8_t Test1(uint8_t size)
{
	uint8_t *buff;
	int i;

	buff = malloc(size);

	for(i=0; i<size; i++)
	{
		buff[i]=i;
	}
	buff[i] = i; /* BOOM: out of bound access */

	free(buff);

	i = buff[0];    /* BOOM: use after free */
	return buff[0]; /* BOOM: out of bound access */
}


static  uint8_t Test2(uint8_t size)
{
	int i,j;

	for(i=0; i<size; i++)
	{
		j += arr2[i];
	}

	j += arr2[i]; /* BOOM: out of bound access */
	return j;
}


static uint8_t Test3(void)
{
	uint8_t buff[8];
	int i;

	for(i=0; i<8; i++)
	{
		buff[i]=i;

	}
    return(buff[i]); /* BOOM: out of bound access */
}

static uint8_t Test4(uint8_t c)
{
	int i;

	for(i=0; i<c ; i++)
	{
		arr[i]=c; /* BOOM: at the fifth iteration it should fail because out of bound write */
	}


	return(arr[i]); /* BOOM: at the fifth iteration it should fail because out of bound read */
}

void ASAN_Test(void)  {
   Test1(8);
   //Test2(sizeof(arr2));
   //Test3();
   //Test4(5);
}


void ASAN_performance(void)
{
	  uint32_t iniMalloc, finMalloc, iniFree, finFree;
	  uint32_t *pointer;

	  printf("Size,Malloc ASAN,Free ASAN\n");
	  int j=0;
	  int i=1;
	  while (i<=10)
	  {

		 iniMalloc = DWT->CYCCNT;
		 pointer = malloc(32*i);
		 finMalloc = DWT->CYCCNT;

		 iniFree = DWT->CYCCNT;
		 free(pointer);
		 finFree = DWT->CYCCNT;

		 printf("%d,%ld,%ld\n", 32*i, finMalloc - iniMalloc, finFree - iniFree);

		 if(j++ == 9)
		 {
			 j=0;
			 i++;
		 }

	  }

}

