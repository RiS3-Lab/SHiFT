/*
 * test.c
 *
 *  Created on: Sep 3, 2021
 *      Author: alejandro
 */
#include "FreeRTOS.h"
#include "task.h"
#include "test.h"
#include "main.h"
//#include "stdio.h"
#include "afl.h"
//#include "stdlib.h"
#include "McuASAN.h"
#include "sys_command_line.h"

#if DUALCOREFUZZ

#else
uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ];
#endif


void Delay(__IO uint32_t nCount)	 //delay
{
    //for(; nCount != 0; nCount--);
}





int test(uint8_t *buf, uint32_t size)
{

return 0;
}

