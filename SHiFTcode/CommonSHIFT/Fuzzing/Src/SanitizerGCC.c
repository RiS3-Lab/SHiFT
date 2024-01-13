/*
 * SanitizerGCC.c
 *
 *  Created on: Oct 27, 2021
 *      Author: alejandro
 */

/*
 * GCC instrumentation uses BL instruction
 * 10.21 BL Branch with Link.
 * Syntax
 * BL{cond}{.W} label
 * where:
 *
 * cond
 *     is an optional condition code. cond is not available on all forms of this instruction.
 * .W
 *     is an optional instruction width specifier to force the use of a 32-bit BL instruction in Thumb.
 * label
 *     is a PC-relative expression.
 *
 * Operation
 * The BL instruction causes a branch to label, and copies the address of the next
 * instruction into LR (R14, the link register).
 *
 * */

#include <stdint.h>
//#include <stdio.h>
#include "main.h"
#include "random_guard.h"
#include "stdbool.h"
#include "afl.h"
#include "fuzzing.h"
#include "stdint.h"



#ifdef ADAFRUIT
#include "driver_examples.h"
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES 0
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_SOFT 1
#include "printf/printf/printf.h"
#endif

#if PRINTBB == 1

uint32_t bbcache[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // small circular cache of basic blocks to speed up loops
uint8_t indexbb=0;


#if DUALCOREFUZZ
void printBB(void *val)
#else

void SytemCall_5_code(void *val)
#endif

{

	
    int i;
	uint32_t addr = *(uint32_t *)val;

	for(i=0; i<16; i++)
	{
		if(addr == bbcache[i]) return;

	}
	bbcache[indexbb] = addr;
	indexbb++;
    if(indexbb>=16)indexbb=0;
   	printf("#%08X\n",addr);
    
}

#endif

void __sanitizer_cov_trace_pc(void)
{

#if DUALCOREFUZZ
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	 uint16_t *paflbitmap =  pAFLfuzzer->aflbmp;
#else
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	 //uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
	 uint16_t *paflbitmap =  pAFLfuzzer->aflbmp;
#endif

	register uint32_t R14 asm("r14");

#if PRINTBB == 1
	uint32_t bb;
	bb = R14;
#if DUALCOREFUZZ
	printBB(&bb);

#else
	MPU_SytemCall_5(&bb);
#endif

#endif

	uint16_t guard;

	guard =  (uint16_t) (R14 & AFL_BITMAP_MASK);

	uint16_t bitmapindex = (uint16_t)( guard^AFLfuzzer.previousGuard);
	bitmapindex &=AFL_BITMAP_MASK;

	if(!paflbitmap[bitmapindex])
	{
		  AFLfuzzer.indexdif++; // since we need to start the index in 1 the first tuple is empty,
		              // we will correct the pointer
		  	  	  	  // when sending the data to the PC
		  paflbitmap[bitmapindex] =  AFLfuzzer.indexdif;
		  AFLfuzzer.afldiff[AFLfuzzer.indexdif].index = bitmapindex;

	 }
	 AFLfuzzer.afldiff[paflbitmap[bitmapindex]].val = (AFLfuzzer.afldiff[paflbitmap[bitmapindex]].val + 1) & 0xff;

	 AFLfuzzer.previousGuard = guard>>1;



}
