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
#include <stdio.h>
#include "stdbool.h"
#include "afl.h"
#include "fuzzing.h"


extern Fuzzer_t AFLfuzzer;

void __sanitizer_cov_trace_pc(void)
{

	uint16_t *paflbitmap = AFLfuzzer.aflbmp;

	register uint32_t R14 asm("r14");
	//nt32_t R14=10;

	uint16_t guard;

	guard =  (uint16_t) (R14 & AFL_BITMAP_MASK);

	uint16_t bitmapindex = (uint16_t)( guard^AFLfuzzer.previousGuard);

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
