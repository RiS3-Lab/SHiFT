/*
 * ubsan_handlers.c
 *
 *  Created on: Mar 4, 2022
 *      Author: alejandro
 */


#include "stdint.h"

typedef  uint32_t uptr;

typedef uptr ValueHandle;

typedef uptr SourceLocation;

typedef uptr TypeDescriptor;


typedef struct OverflowData_t {
  SourceLocation Loc;
  TypeDescriptor Type;
}OverflowData;

int i;
//https://community.st.com/s/question/0D53W000007XQl9SAG/division-by-zero-exception-flag-not-set-in-stm32h7-fpu
void __ubsan_handle_divrem_overflow(OverflowData *Data,
                                             ValueHandle LHS, ValueHandle RHS) {


	// this is a hacky way to trigger a division by zero exception
	// we do this by performing an integer division by zero upon detecting a float division by zero
	// the int div0 will be  caught by cortex-M hardware and handled by SHiFT usage fault handlers
	// notice that this is caught in the first place by UBSAN.
	// The FPU will not trigger an exception because of the silicon bug
	// that we identified for the STM32hx family, so without UBSAN this fault will not be
	// identified
	__asm volatile
		(

			" mov   r2, #0         \n" // elevate privileges so we can use system calls
			" udiv  r3, r4, r2     \n"	// we can do this because we are in handler mode
		);

}
