// trace-pc-guard-cb.cc
#include <stdint.h>
#include <stdio.h>
#include <sanitizer/coverage_interface.h>
#include "main.h"
#include "random_guard.h"
#include "stdbool.h"
#include "afl.h"
#include "fuzzing.h"



#ifdef  DUALCOREFUZZ



#else
	Fuzzer_t AFLfuzzer;
#endif


//extern uint16_t aflbitmap[AFL_BITMAP_SIZE];
//uint64_t N;
//bool iniGuard = false;
//extern uint16_t previousGuard;
//extern tuple_t  afldiff [AFL_BITMAP_SIZE];
//extern uint16_t indexdif;




// This callback is inserted by the compiler as a module constructor
// into every DSO. 'start' and 'stop' correspond to the
// beginning and end of the section with the guards for the entire
// binary (executable or DSO). The callback will be called at least
// once per DSO and may be called multiple times with the same parameters.
void __sanitizer_cov_trace_pc_guard_init(uint32_t *start, uint32_t *stop) {
   // Counter for the guards.


Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;




  if(AFLfuzzer.iniGuard == false)
  {
	  AFLfuzzer.N=0;
	  AFLfuzzer.iniGuard = true;
	  AFLfuzzer.previousGuard = 0;
	  AFLfuzzer.indexdif = 0;
  }

  if (start == stop ) return;  // Initialize only once.
  //printf("INIT: %p %p\n", start, stop);
  //sprintf(auxbuff, "INIT: %p %p\n", start, stop);
  for (uint32_t *x = start; x < stop; x++)
    *x = randomGuard[AFLfuzzer.N++] & AFL_BITMAP_MASK;  // Guards are pre-calculated pseudo random values but not at compilation time as the original AFL.
}

// This callback is inserted by the compiler on every edge in the
// control flow (some optimizations apply).
// Typically, the compiler will emit the code like this:
//    if(*guard)
//      __sanitizer_cov_trace_pc_guard(guard);
// But for large functions it will emit a simple call:
//    __sanitizer_cov_trace_pc_guard(guard);
void __sanitizer_cov_trace_pc_guard(uint32_t *guard) {
  //if (!*guard) return;  // Duplicate the guard check.
  // If you set *guard to 0 this code will not be called again for this edge.
  // Now you can get the PC and do whatever you want:
  //   store it somewhere or symbolize it and print right away.
  // The values of `*guard` are as you set them in
  // __sanitizer_cov_trace_pc_guard_init and so you can make them consecutive
  // and use them to dereference an array or a bit vector.
  //void *PC = __builtin_return_address(0);
  //char PcDescr[1024];
  // This function is a part of the sanitizer run-time.
  // To use it, link with AddressSanitizer or other sanitizer.
  //__sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr));
  //printf("guard: %p %x address: %p\n", guard, *guard, PC);

  #if DUALCOREFUZZ
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	 uint16_t *paflbitmap =  pAFLfuzzer->aflbmp;
  #else
	 Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	 uint16_t *paflbitmap =  (uint16_t *)DTCMRAMORIGIN;
  #endif

 // printf("pguard: %x, guard: %x, index: %x \n", previousGuard, *guard, (uint16_t)((*guard) ^ previousGuard));

  uint16_t bitmapindex = (uint16_t)((*guard) ^ AFLfuzzer.previousGuard);

  if(!paflbitmap[bitmapindex])
  {
	  AFLfuzzer.indexdif++; // since we need to start the index in 1 the first tuple is empty,
	              // we will correct the pointer
	  	  	  	  // when sending the data to the PC
	  paflbitmap[bitmapindex] =  AFLfuzzer.indexdif;
	  AFLfuzzer.afldiff[AFLfuzzer.indexdif].index = bitmapindex;

  }
  AFLfuzzer.afldiff[paflbitmap[bitmapindex]].val= (AFLfuzzer.afldiff[paflbitmap[bitmapindex]].val + 1) & 0xff;

  AFLfuzzer.previousGuard = (*guard)>>1;

}
