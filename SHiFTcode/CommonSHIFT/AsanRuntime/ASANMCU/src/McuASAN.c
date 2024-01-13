/*
 * Alejandro Mera
 *
 */

#include <McuASANconfig.h>
#if McuASAN_CONFIG_IS_ENABLED
#include <McuASAN.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
//#include <//printf.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "fuzzing.h"

#if McuASAN_CONFIG_FreeRTOs
#include "FreeRTOS.h"
#include "task.h"

#endif

#ifdef __cplusplus
extern "C" {
#endif


#define Max(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define Min(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a > _b ? _b : _a; })

#if McuASAN_CONFIG_KSAN
#define McuASAN_CONFIG_ASAN 0
#else
#define McuASAN_CONFIG_ASAN 1
#endif


#ifndef MPU_ENABLED
#define MPU_ENABLED 1
#endif


#if defined(STM32H743xx) || defined(STM32L552xx)  || defined(STM32L552xx) || defined(STM32H745xx)
extern UART_HandleTypeDef HUSART;
#endif

// helpers system calls prototypes must be implemented in user space

__weak void SytemCall_1_code()
{

}

__weak void SytemCall_2_code()
{

}

__weak  void SytemCall_3_code()
{

}


__weak  void SytemCall_4_code(void *val)
{

}

__weak  void SytemCall_5_code(void *val)
{

}


#if McuASAN_CONFIG_ASAN


static inline uptr RoundUpTo(uptr size, uptr boundary) {
  return (size + boundary - 1) & ~(boundary - 1);
}


static inline uptr RoundDownTo(uptr x, uptr boundary) {
  return x & ~(boundary - 1);
}

static inline bool IsAligned(uptr a, uptr alignment) {
  return (a & (alignment - 1)) == 0;
}

static inline bool IsPowerOfTwo(uptr x) {
  return (x & (x - 1)) == 0;
}

static inline uptr Log2(uptr x) {
  //CHECK(IsPowerOfTwo(x));
  //return LeastSignificantSetBitIndex(x);
  return (uptr) ffs(x);
}



bool asan_inited = false;


// Every chunk of memory allocated by this allocator can be in one of 3 states:
// CHUNK_AVAILABLE: the chunk is in the free list and ready to be allocated.
// CHUNK_ALLOCATED: the chunk is allocated and not yet freed.
// CHUNK_QUARANTINE: the chunk was freed and put into quarantine zone.
enum {
  CHUNK_AVAILABLE  = 0,  // 0 is the default value even if we didn't set it.
  CHUNK_ALLOCATED  = 2,
  CHUNK_QUARANTINE = 3
};

/*** constants****/

#define SHADOW_GRANULARITY (1ULL << 3)  // 3 is the shadow scale
const int kAsanGlobalRedzoneMagic = 0xf9;
const int kAsanHeapLeftRedzoneMagic = 0xfa;
const int kAsanHeapFreeMagic = 0xfd;
uint32_t __asan_option_detect_stack_use_after_return __attribute__ ((section ("._asan_var")));
static const uptr kMaxAllowedMallocSize = McuASAN_CONFIG_KMAX_ALLOWED_MALLOC_SIZE;
static const uptr max_user_defined_malloc_size = McuASAN_CONFIG_MAX_USER_DEFINED_MALLOC_SIZE;
static const uptr kChunkHeaderSize = sizeof(AsanChunk);
static const uptr kChunkHeader2Size = sizeof(ChunkBase) - kChunkHeaderSize;
static const uptr kAllocBegMagic = 0xCC6E96B9;
const uint32_t kInvalidTid = 0xffffff;
uint8_t alloc_dealloc_mismatch = McuASAN_FLAG_ALLOC_DEALLOC_MISMATCH;
uint8_t new_delete_type_mismatch = McuASAN_FLAG_NEW_DELETE_TYPE_MISMATCH;
uint32_t max_free_fill_size = McuASAN_FLAG_MAX_MALLOC_FILL_SIZE;
uint8_t allocator_frees_and_returns_null_on_realloc_zero = McuASAN_FLAG_ALLOCATOR_FREES_AND_RETURNS_NULL_ON_REALLOC_ZERO;

static const uint64_t kAllocaRedzoneSize = 32UL;
static const uint64_t kAllocaRedzoneMask = 31UL;
const int kAsanAllocaLeftMagic = 0xca;

const int kAsanAllocaRightMagic = 0xcb;

#if McuASAN_CONFIG_FreeRTOs
#if DUALCOREFUZZ

#else
extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ] __attribute__( ( aligned( AFLINPUTREGION_SIZE ) ) );

#endif

void FreeRTOSReportFailure(type_exception_t  tEX);
#endif


/* hooks if using -fsanitize=address */
/* -fasan-shadow-offset=number */
/* -fsanitize=kernel-address */
static void __asan_ReportGenericError(void)
{
#if 1
  //printf("ASAN generic failure\n");

#if McuASAN_CONFIG_FreeRTOs
  FreeRTOSReportFailure(EX_ASAN_RW_OVERFLOW);
#endif


#else
  __asm volatile("bkpt #0"); /* stop application */
  for(;;){}
#endif
}

/* below are the required callbacks needed by ASAN */
void __asan_report_store1(void *address)
{

	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");

}
void __asan_report_store2(void *address)
{
	__asm volatile("push {r0-r7}");
    __asan_ReportGenericError();
    __asm volatile("pop  {r0-r7}");
}
void __asan_report_store4(void *address)
{
	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");
}
void __asan_report_store8(void *address)
{
	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");
}
void __asan_report_store_n(void *address)
{
	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");
}
void __asan_report_load1(void *address)
{
        // ASAN instrumentation may break firmware functionality
		// when the original code uses registers r0 to r7 as scratchpad.
	    // ASAN callbacks are inserted without taking care of current registers values,
	    // therefore, after returning from the callback the firmware may crash
	    // since the values on r0 and r7 may be different.
	    // Adding push and pop wrappers mitigate this issue saving the scratchpad values
	    __asm volatile("push {r0-r7}");
		__asan_ReportGenericError();
		__asm volatile("pop  {r0-r7}");
}


void __asan_report_load2(void *address) {

	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");

}
void __asan_report_load4(void *address) {

	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");

}


void __asan_report_load8(void *address) {

	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");

}


void __asan_report_load_n(void *address) {

	__asm volatile("push {r0-r7}");
	__asan_ReportGenericError();
	__asm volatile("pop  {r0-r7}");

}
#endif


static void NYI(void) {
  __asm volatile("bkpt #0"); /* stop application */
  for(;;){}
}

void __asan_init(void) {

	   if(!asan_inited)
	   {
		   __asan_option_detect_stack_use_after_return  = McuASAN_FLAG_DETECT_STACK_USE_AFTER_RETURN;
		   memset((uint8_t *)( (uint32_t)(McuASAN_CONFIG_APP_MEM_START>>3) + McuASAN_CONFIG_APP_MEM_OFFSET),
				   0,
				   McuASAN_CONFIG_APP_MEM_SIZE>>3 );
		   asan_inited = true;

	   }

}

void __asan_stack_malloc_0(size_t size, void *addr) { NYI();}
void __asan_stack_malloc_1(size_t size, void *addr) { NYI();}
void __asan_stack_malloc_2(size_t size, void *addr) { NYI();}
void __asan_stack_malloc_3(size_t size, void *addr) { NYI();}
void __asan_stack_malloc_4(size_t size, void *addr) { NYI();}
void __asan_stack_malloc_5(size_t size, void *addr) { NYI();}
void __asan_handle_no_return(void) { NYI(); }

void __asan_stack_free_0(uptr ptr, uptr size){ NYI();};
void __asan_stack_free_1(uptr ptr, uptr size){ NYI();};
void __asan_stack_free_2(uptr ptr, uptr size){ NYI();};
void __asan_stack_free_3(uptr ptr, uptr size){ NYI();};
void __asan_stack_free_4(uptr ptr, uptr size){ NYI();};
void __asan_stack_free_5(uptr ptr, uptr size){ NYI();};



uptr MEM_TO_SHADOW(uptr address) {
  return   ((((uint32_t)address)>>3 ) + McuASAN_CONFIG_APP_MEM_OFFSET); /* divided by 8: every byte has a shadow bit */
}

void FastPoisonShadow(uptr aligned_beg, uptr aligned_size, uint8_t value)
{

  uptr shadow_beg = MEM_TO_SHADOW(aligned_beg);
  uptr shadow_end = MEM_TO_SHADOW(
      aligned_beg + aligned_size - SHADOW_GRANULARITY) + 1;

    uptr page_size = 1024; // we don't have paging so lets set to 1024
    uptr page_beg = RoundUpTo(shadow_beg, page_size);
    uptr page_end = RoundDownTo(shadow_end, page_size);

    if (page_beg >= page_end) {
      memset((void *)shadow_beg, value, shadow_end - shadow_beg);
    } else {
      if (page_beg != shadow_beg) {
        memset((void *)shadow_beg, value, page_beg - shadow_beg);
      }
      if (page_end != shadow_end) {
        memset((void *)page_end, value, shadow_end - page_end);
      }
      //ReserveShadowMemoryRange(page_beg, page_end - 1, nullptr);
    }

}


void FastPoisonShadowPartialRightRedzone(
    uptr aligned_addr, uptr size, uptr redzone_size, uint8_t value) {
  //DCHECK(CanPoisonMemory());
  bool poison_partial = McuASAN_FLAG_POISON_PARTIAL;
  uint8_t *shadow = (uint8_t*)MEM_TO_SHADOW(aligned_addr);
  for (uptr i = 0; i < redzone_size; i += SHADOW_GRANULARITY, shadow++) {
    if (i + SHADOW_GRANULARITY <= size) {
      *shadow = 0;  // fully addressable
    } else if (i >= size) {
      *shadow = (SHADOW_GRANULARITY == 128) ? 0xff : value;  // unaddressable
    } else {
      // first size-i bytes are addressable
      *shadow = poison_partial ?(uint8_t)(size - i) : 0;
    }
  }
}

void PoisonRedZones(global_t g)
{

uptr aligned_size = RoundUpTo(g.size, SHADOW_GRANULARITY);


  FastPoisonShadow(g.beg + aligned_size, g.size_with_redzone - aligned_size,
                   kAsanGlobalRedzoneMagic);
  if (g.size != aligned_size) {
    FastPoisonShadowPartialRightRedzone(
        g.beg + RoundDownTo(g.size, SHADOW_GRANULARITY),
        g.size % SHADOW_GRANULARITY,
        SHADOW_GRANULARITY,
        kAsanGlobalRedzoneMagic);
  }

/*
   FastPoisonShadow(g.beg, aligned_size,
                    0);
   if (g.size != aligned_size) {
     FastPoisonShadowPartialRightRedzone(
         g.beg + RoundDownTo(g.size, SHADOW_GRANULARITY),
         g.size % SHADOW_GRANULARITY,
         SHADOW_GRANULARITY,
         0);
   }

*/


}

void __asan_version_mismatch_check_v8(void) {  }

void __asan_unregister_globals(void) {  }

void __asan_register_globals( global_t *globals, uptr n)
{
   int i;
  // global_t *aux;

   for(i=0; i<n ; i++)
   {

	   // Check if the global is a valid address in RAM
	   if( (globals[i].beg >= McuASAN_CONFIG_APP_MEM_START) &&
		   (globals[i].beg <  (McuASAN_CONFIG_APP_MEM_START + McuASAN_CONFIG_APP_MEM_SIZE ) ))
	   {

		   //aux=&globals[i];
		   PoisonRedZones(globals[i]);
	   }

   }

}


void __asan_storeN_noabort(uptr addr, uptr size) {
  //if (__asan_region_is_poisoned(addr, size)) {
  //  GET_CALLER_PC_BP_SP;
    //ReportGenericError(pc, bp, sp, addr, true, size, 0, false);
  //}

}





void __asan_alloca_poison(uptr addr, uptr size) {


  uptr LeftRedzoneAddr = addr - kAllocaRedzoneSize;
  uptr PartialRzAddr = addr + size;
  uptr RightRzAddr = (PartialRzAddr + kAllocaRedzoneMask) & ~kAllocaRedzoneMask;
  uptr PartialRzAligned = PartialRzAddr & ~(SHADOW_GRANULARITY - 1);
  FastPoisonShadow(LeftRedzoneAddr, kAllocaRedzoneSize, kAsanAllocaLeftMagic);
  FastPoisonShadowPartialRightRedzone(
      PartialRzAligned, PartialRzAddr % SHADOW_GRANULARITY,
      RightRzAddr - PartialRzAligned, kAsanAllocaRightMagic);
  FastPoisonShadow(RightRzAddr, kAllocaRedzoneSize, kAsanAllocaRightMagic);
}


static inline uptr MemToShadow(uptr p) {
  //PROFILE_ASAN_MAPPING();
  //CHECK(AddrIsInMem(p));
  return MEM_TO_SHADOW(p);
}



void __asan_allocas_unpoison(uptr top, uptr bottom) {
  if ((!top) || (top > bottom)) return;
  memset((void *)MemToShadow(top), 0,
               (bottom - top) / SHADOW_GRANULARITY);
}




static uint32_t RZSize2Log(uint32_t rz_size) {
  uint32_t res = Log2(rz_size) - 4;
  return res;
}

uptr ComputeRZLog(uptr user_requested_size) {
    uint32_t rz_log =
    user_requested_size <= 64        - 16   ? 0 :
    user_requested_size <= 128       - 32   ? 1 :
    user_requested_size <= 512       - 64   ? 2 :
    user_requested_size <= 4096      - 128  ? 3 :
    user_requested_size <= (1 << 14) - 256  ? 4 :
    user_requested_size <= (1 << 15) - 512  ? 5 :
    user_requested_size <= (1 << 16) - 1024 ? 6 : 7;
    uint32_t min_rz =  McuASAN_FLAG_REDZONE;  //atomic_load(&min_redzone, memory_order_acquire);
    uint32_t max_rz =  McuASAN_FLAG_MAX_REDZONE;  //atomic_load(&max_redzone, memory_order_acquire);
  return Min(Max(rz_log, RZSize2Log(min_rz)), RZSize2Log(max_rz));
}






void PoisonShadow(uptr addr, uptr size, uint8_t value) {
  //if (value && !CanPoisonMemory()) return;
  //CHECK(AddrIsAlignedByGranularity(addr));
  //CHECK(AddrIsInMem(addr));
  //CHECK(AddrIsAlignedByGranularity(addr + size));
  //CHECK(AddrIsInMem(addr + size - SHADOW_GRANULARITY));
  //CHECK(REAL(memset));
   if( (addr>= McuASAN_CONFIG_APP_MEM_START) &&
			   (addr <  (McuASAN_CONFIG_APP_MEM_START + McuASAN_CONFIG_APP_MEM_SIZE ) ))
   {
	   FastPoisonShadow(addr, size, value);
   }
   else
   {
	   //printf("\n AddressSanitizer failed to poison memory, it is not allocated in RAM");
#if McuASAN_CONFIG_FreeRTOs
  FreeRTOSReportFailure(EX_ASAN_FAIL_POISON);
#endif

   }

}

static uptr ComputeUserRequestedAlignmentLog(uptr user_requested_alignment) {
    if (user_requested_alignment < 8)
      return 0;
    if (user_requested_alignment > 512)
      user_requested_alignment = 512;
    return Log2(user_requested_alignment) - 2;
  }


static uint32_t RZLog2Size(uint32_t rz_log) {
  //CHECK_LT(rz_log, 8);
  return 16 << rz_log;
}


#if McuASAN_CONFIG_CHECK_MALLOC_FREE
/* undo possible defines for malloc and free */
#ifdef malloc
  #undef malloc
  void *malloc(size_t);
#endif
#ifdef free
  #undef free
  void free(void*);
#endif
#ifdef realloc
  #undef realloc
  void	*realloc(void *, size_t);
#endif



 static void addAlloc(uint32_t *ptr)
 {
	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;

	int i=0;
  	if(ptr)
  	{
	   while(i<McuASAN_MAX_NUMBER_ALLOCS)
  	   {
  		    if(pAFLfuzzer->allocs[i]==0)
  		    {
  		    	pAFLfuzzer->allocs[i] = ptr;
  			    break;
  		    }
  		    i++;
  	    }
  	 }
 }

 static void delAlloc(uint32_t *ptr)
 {
	Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;
	int i=0;
  	if(ptr)
  	{
  	    while(i<McuASAN_MAX_NUMBER_ALLOCS)
  	    {
  		    if(pAFLfuzzer->allocs[i]==ptr)
  		    {
  		    	pAFLfuzzer->allocs[i]= NULL;
  			    break;
  		    }
  		    i++;
  	    }
  	}
 }

 /*
  void FlushAlloc()
  {
  	int i=0;
  	while(i<McuASAN_MAX_NUMBER_ALLOCS)
  	{
  		if(allocs[i])
  		{
  			free(allocs[i]);
  			allocs[i] = NULL;
  		}
  		i++;
  	}
  }
*/

void *Allocate(uptr size, uptr alignment,
                 AllocType alloc_type, bool can_fill) {
    /*
	if (UNLIKELY(!asan_inited))
      AsanInitFromRtl();
    if (RssLimitExceeded()) {
      if (AllocatorMayReturnNull())
        return nullptr;
      ReportRssLimitExceeded(stack);
    }*/

    //CHECK(stack);
    const uptr min_alignment = SHADOW_GRANULARITY;

    const uptr user_requested_alignment_log =
        ComputeUserRequestedAlignmentLog(alignment);


    if (alignment < min_alignment)
      alignment = min_alignment;
    if (size == 0) {
      // We'd be happy to avoid allocating memory for zero-size requests, but
      // some programs/tests depend on this behavior and assume that malloc
      // would not return NULL even for zero-size allocations. Moreover, it
      // looks like operator new should never return NULL, and results of
      // consecutive "new" calls must be different even if the allocated size
      // is zero.
      size = 1;
    }
    //CHECK(IsPowerOfTwo(alignment));
    uptr rz_log = ComputeRZLog(size);
    uptr rz_size = RZLog2Size(rz_log);
    uptr rounded_size = RoundUpTo(Max(size, kChunkHeader2Size), alignment);
    uptr needed_size = rounded_size + rz_size;

    if (alignment > min_alignment)
      needed_size += alignment;
    // the primary allocator is only available with Fuchsia and in Adroid 11
    // since we don't have it, we will use standard libc allocator
    bool using_primary_allocator = false;
    // If we are allocating from the secondary allocator, there will be no
    // automatic right redzone, so add the right redzone manually.

    //if (!PrimaryAllocator::CanAllocate(needed_size, alignment)) {
    needed_size += rz_size; // manually adding the right red zone
      //using_primary_allocator = false;
    // }


    //CHECK(IsAligned(needed_size, min_alignment));

    if (size > kMaxAllowedMallocSize || needed_size > kMaxAllowedMallocSize ||
        size > max_user_defined_malloc_size) {
        //printf("AddressSanitizer failed to allocate %d bytes\n", (size_t)size);

        return NULL;
     }

    //AsanThread *t = GetCurrentThread();
    void *allocated;
    allocated = malloc(needed_size);


    if(!allocated)
    {
    	//printf("AddressSanitizer malloc run out of memory\n");
        return NULL;
    }

    addAlloc(allocated);

    //if (*(uint8_t *)MEM_TO_SHADOW((uptr)allocated) == 0 ) {
      // Heap poisoning is enabled, but the allocator provides an unpoisoned
      // chunk. This is possible if CanPoisonMemory() was false for some
      // time, for example, due to flags()->start_disabled.
      // Anyway, poison the block before using it for anything else.
      //uptr allocated_size = allocator.GetActuallyAllocatedSize(allocated);
      uptr allocated_size = needed_size;
      PoisonShadow((uptr)allocated, allocated_size, kAsanHeapLeftRedzoneMagic);
    //}

    uptr alloc_beg = (uint32_t)(allocated);
    //uptr alloc_end = alloc_beg + needed_size;
    uptr beg_plus_redzone = alloc_beg + rz_size;
    uptr user_beg = beg_plus_redzone;

    if (!IsAligned(user_beg, alignment))
      user_beg = RoundUpTo(user_beg, alignment);
    //uptr user_end = user_beg + size;
    //CHECK_LE(user_end, alloc_end);

    uptr chunk_beg = user_beg - kChunkHeaderSize;
    AsanChunk *m = (AsanChunk *)(chunk_beg);
    m->alloc_type = alloc_type;
    m->rz_log = rz_log;
    uint32_t alloc_tid = 0; // we are not supporting threads
    m->alloc_tid = alloc_tid;
    //CHECK_EQ(alloc_tid, m->alloc_tid);  // Does alloc_tid fit into the bitfield?
    m->free_tid = kInvalidTid;
    m->from_memalign = user_beg != beg_plus_redzone;
    if (alloc_beg != chunk_beg) {
      //CHECK_LE(alloc_beg+ 2 * sizeof(uptr), chunk_beg);
      ((uptr *)alloc_beg)[0] = kAllocBegMagic;
      ((uptr *)alloc_beg)[1] = chunk_beg;
    }
    if (using_primary_allocator) {
      //CHECK(size);
      m->user_requested_size = size;
      //CHECK(allocator.FromPrimary(allocated));
    }
    else {

     // we assume the behavior of the secondary allocator will be the same as pthe primary allocator
     //CHECK(!allocator.FromPrimary(allocated));
      m->user_requested_size = size;   // SizeClassMap::kMaxSize;
      //uptr *meta = reinterpret_cast<uptr *>(allocator.GetMetaData(allocated));
      //meta[0] = size;
      //meta[1] = chunk_beg;
    }
    m->user_requested_alignment_log = user_requested_alignment_log;

    //m->alloc_context_id = StackDepotPut(*stack);

    uptr size_rounded_down_to_granularity =
        RoundDownTo(size, SHADOW_GRANULARITY);
    // Unpoison the bulk of the memory region.
    if (size_rounded_down_to_granularity)
      PoisonShadow(user_beg, size_rounded_down_to_granularity, 0);
    // Deal with the end of the region if size is not aligned to granularity.
    if (size != size_rounded_down_to_granularity ) {
      uint8_t *shadow =
          (uint8_t *)MEM_TO_SHADOW(user_beg + size_rounded_down_to_granularity);
      *shadow = McuASAN_FLAG_POISON_PARTIAL ? (size & (SHADOW_GRANULARITY - 1)) : 0;
    }

    /* no
    AsanStats &thread_stats = GetCurrentThreadStats();
    thread_stats.mallocs++;
    thread_stats.malloced += size;
    thread_stats.malloced_redzones += needed_size - size;

    if (needed_size > SizeClassMap::kMaxSize)
      thread_stats.malloc_large++;
    else
      thread_stats.malloced_by_size[SizeClassMap::ClassID(needed_size)]++;

    */

    void *res = (void *)(user_beg);
    if (can_fill && McuASAN_FLAG_MAX_MALLOC_FILL_SIZE) {
      uptr fill_size = Min(size, McuASAN_FLAG_MAX_MALLOC_FILL_SIZE);
      memset(res, McuASAN_FLAG_MALLOC_FILL_BYTE, fill_size);
    }

    // Must be the last mutation of metadata in this function.
    //atomic_store((uint8_t *)m, CHUNK_ALLOCATED, memory_order_release);
    *(uint8_t *)m = CHUNK_ALLOCATED;
    //ASAN_MALLOC_HOOK(res, size); //no malloc hooks
    return res;
  }



void ReportDoubleFree(uptr addr) {
	__asm volatile("push {r0-r7}");
 //printf("Error buffer double free address: %p \n", (uint32_t * )addr);
#if McuASAN_CONFIG_FreeRTOs
  FreeRTOSReportFailure(EX_ASAN_DOUBLE_FREE);
#endif
 __asm volatile("pop  {r0-r7}");
}

void ReportFreeNotMalloced(uptr addr) {

	__asm volatile("push {r0-r7}");
 //printf("Error invalid free  address: %p \n", (uint32_t * )addr);
#if McuASAN_CONFIG_FreeRTOs
  FreeRTOSReportFailure(EX_ASAN_INVALID_FREE);
#endif
	__asm volatile("pop  {r0-r7}");

}


void ReportInvalidFree(void *ptr, uint8_t chunk_state) {
    if (chunk_state == CHUNK_QUARANTINE)
      ReportDoubleFree((uptr)ptr);
    else
      ReportFreeNotMalloced((uptr)ptr);
  }

bool AtomicallySetQuarantineFlagIfAllocated(AsanChunk *m, void *ptr) {
  //uint8_t old_chunk_state = CHUNK_ALLOCATED;
  // Flip the chunk_state atomically to avoid race on double-free.
  /*if (!atomic_compare_exchange_strong((atomic_uint8_t *)m, &old_chunk_state,
                                      CHUNK_QUARANTINE,
                                      memory_order_acquire)) {
    ReportInvalidFree(ptr, old_chunk_state, stack);
    // It's not safe to push a chunk in quarantine on invalid free.
    return false;
  }*/
  uint8_t *state = (uint8_t *)m;
  if(*state == CHUNK_ALLOCATED)
  {
	  *state = CHUNK_QUARANTINE;
	  return true;
  }
  else
  {
	  ReportInvalidFree(ptr, *state);
	  return false;
  }


  //CHECK_EQ(CHUNK_ALLOCATED, old_chunk_state);
  return true;
}


void ReportAllocTypeMismatch(uptr addr,
                             AllocType alloc_type,
                             AllocType dealloc_type) {
/*
  const char *s[] = {
		  "Malloc",
		  "New",
		  "New BR" };*/
  __asm volatile("push {r0-r7}");
  //printf("Error type mismatch alloc:%s, dealloc:%s \n", s[alloc_type], s[dealloc_type]);
#if McuASAN_CONFIG_FreeRTOs
  FreeRTOSReportFailure(EX_ASAN_REALLOC_MISMATCH);
#endif
  __asm volatile("pop  {r0-r7}");
}


void ReportNewDeleteTypeMismatch(uptr addr, uptr delete_size,
                                 uptr delete_alignment) {
	__asm volatile("push {r0-r7}");
	//printf("Error New Delete alignment mismatch  size:%ld, alig:%ld \n", delete_size, delete_alignment );
#if McuASAN_CONFIG_FreeRTOs
  FreeRTOSReportFailure(EX_ASAN_DOUBLE_FREE);
#endif
	__asm volatile("pop  {r0-r7}");

}

uptr Beg(AsanChunk *m)
{
	return (uptr)(m) + kChunkHeaderSize;
}

uptr AllocBeg(AsanChunk *m)
{

	if (m->from_memalign)
	{
	     //return get_allocator().GetBlockBegin(reinterpret_cast<void *>(this));
		while(1); // this is a special case that we do not support since we do not control the allocator, the code should not reach this point
				  // unless the allocation of malloc is unnaligned TODO check what happens during testing
	}
	return (Beg(m) - RZLog2Size(m->rz_log));
}



void Recycle(AsanChunk *m) {
  //CHECK_EQ(m->chunk_state, CHUNK_QUARANTINE);
  //atomic_store((atomic_uint8_t*)m, CHUNK_AVAILABLE, memory_order_relaxed);

  *(uint8_t*)m = CHUNK_AVAILABLE;

  //CHECK_NE(m->alloc_tid, kInvalidTid);
  //CHECK_NE(m->free_tid, kInvalidTid);

  PoisonShadow(Beg(m),
               RoundUpTo(m->user_requested_size, SHADOW_GRANULARITY),
               kAsanHeapLeftRedzoneMagic);

  void *p = (void *)(AllocBeg(m));

  if (p != m) {
    uptr *alloc_magic = (uptr *)(p);
    //CHECK_EQ(alloc_magic[0], kAllocBegMagic);
    // Clear the magic value, as allocator internals may overwrite the
    // contents of deallocated chunk, confusing GetAsanChunk lookup.
    alloc_magic[0] = 0;
    //CHECK_EQ(alloc_magic[1], reinterpret_cast<uptr>(m));
  }

  // Statistics.
  //AsanStats &thread_stats = GetCurrentThreadStats();
  //thread_stats.real_frees++;
  //thread_stats.really_freed += m->UsedSize();

  delAlloc(p);
  free(p);


}



// Expects the chunk to already be marked as quarantined by using
  // AtomicallySetQuarantineFlagIfAllocated.
void QuarantineChunk(AsanChunk *m, void *ptr) {



    if (McuASAN_FLAG_MAX_FREE_FILL_SIZE > 0) {
      // We have to skip the chunk header, it contains free_context_id.
      //uptr scribble_start = (uptr)m + kChunkHeaderSize + kChunkHeader2Size;
      //if (m->UsedSize() >= kChunkHeader2Size) {  // Skip Header2 in user area.
      //  uptr size_to_fill = m->UsedSize() - kChunkHeader2Size;
      //  size_to_fill = Min(size_to_fill, (uptr)fl.max_free_fill_size);
      //  REAL(memset)((void *)scribble_start, fl.free_fill_byte, size_to_fill);
      // }

      uptr size_to_fill = m->user_requested_size;
      size_to_fill = Min((size_to_fill), max_free_fill_size);
      memset(ptr, McuASAN_FLAG_FREE_FILL_BYTE, size_to_fill);
    }

    // Poison the region.
    PoisonShadow((uptr)ptr ,
                 RoundUpTo(m->user_requested_size, SHADOW_GRANULARITY),
                 kAsanHeapFreeMagic);

    //AsanStats &thread_stats = GetCurrentThreadStats();
    //thread_stats.frees++;
    //thread_stats.freed += m->UsedSize();

    // Push into quarantine.
    /*
    if (t) {
      AsanThreadLocalMallocStorage *ms = &t->malloc_storage();
      AllocatorCache *ac = GetAllocatorCache(ms);
      quarantine.Put(GetQuarantineCache(ms), QuarantineCallback(ac, stack), m,
                     m->UsedSize());
    } else {
      SpinMutexLock l(&fallback_mutex);
      AllocatorCache *ac = &fallback_allocator_cache;
      quarantine.Put(&fallback_quarantine_cache, QuarantineCallback(ac, stack),
                     m, m->UsedSize());
    }
    */

    Recycle(m);
}


void Deallocate(void *ptr, uptr delete_size, uptr delete_alignment, AllocType alloc_type)
{

	uptr p = (uptr)(ptr);
    if (p == 0) return;

    uptr chunk_beg = p - kChunkHeaderSize;
    AsanChunk *m = (AsanChunk *)(chunk_beg);

    // On Windows, uninstrumented DLLs may allocate memory before ASan hooks
    // malloc. Don't report an invalid free in this case.
    /*
    if (SANITIZER_WINDOWS &&
        !get_allocator().PointerIsMine(ptr)) {
      if (!IsSystemHeapAddress(p))
        ReportFreeNotMalloced(p, stack);
      return;
    }*/

    //ASAN_FREE_HOOK(ptr); we do not support hooks

    // Must mark the chunk as quarantined before any changes to its metadata.
    // Do not quarantine given chunk if we failed to set CHUNK_QUARANTINE flag.
    if (!AtomicallySetQuarantineFlagIfAllocated(m, ptr)) return;

    if (m->alloc_type != alloc_type) {
      if (alloc_dealloc_mismatch) {
        ReportAllocTypeMismatch((uptr)ptr, (AllocType)m->alloc_type,
                                (AllocType)alloc_type);
      }
    }
    /*
    else {  // we do not support this type of error
      if (new_delete_type_mismatch &&
          (alloc_type == FROM_NEW || alloc_type == FROM_NEW_BR) &&
          ((delete_size && delete_size != m->UsedSize()) ||
           ComputeUserRequestedAlignmentLog(delete_alignment) !=
               m->user_requested_alignment_log)) {
        ReportNewDeleteTypeMismatch(p, delete_size, delete_alignment);
      }
    }
    */

    QuarantineChunk(m, ptr);
 }



void *Reallocate(void *old_ptr, uptr new_size) {
    //CHECK(old_ptr && new_size);
    uptr p = (uptr)(old_ptr);
    uptr chunk_beg = p - kChunkHeaderSize;
    AsanChunk *m = (AsanChunk *)(chunk_beg);

    //AsanStats &thread_stats = GetCurrentThreadStats();
    //thread_stats.reallocs++;
    //thread_stats.realloced += new_size;

    void *new_ptr = Allocate(new_size, 8, FROM_MALLOC, true);
    if (new_ptr) {
      uint8_t chunk_state = m->chunk_state;
      if (chunk_state != CHUNK_ALLOCATED)
        ReportInvalidFree(old_ptr, chunk_state);
      //CHECK_NE(REAL(memcpy), nullptr);
      uptr user_requested_size =  m->user_requested_size;
      uptr memcpy_size = Min(new_size, user_requested_size);
      // If realloc() races with free(), we may start copying freed memory.
      // However, we will report racy double-free later anyway.
      memcpy(new_ptr, old_ptr, memcpy_size);
      Deallocate(old_ptr, 0, 0, FROM_MALLOC);
    }
    return new_ptr;
  }




/*
 * rrrrrrrr  red zone border (incl. size below)
 * size
 * memory returned
 * rrrrrrrr  red zone boarder
 */

void *asan_malloc(size_t size) {
#if MPU_ENABLED
	//return (void *) ASAN_malloc(size);
	return (void *) MPU_ASAN_malloc(size);

#else

    return Allocate(size, 8, FROM_MALLOC, true);

#endif
}

void asan_free(void *ptr) {
#if MPU_ENABLED
	//ASAN_free(ptr);
	MPU_ASAN_free(ptr);

#else
	 Deallocate(ptr, 0, 0, FROM_MALLOC);
#endif
}


void *asan_realloc( void *ptr, size_t size ) {


if (!ptr)
{
	return Allocate(size, 8, FROM_MALLOC, true);
}

    if (size == 0)
    {
        if (allocator_frees_and_returns_null_on_realloc_zero)
        {
          Deallocate(ptr, 0, 0, FROM_MALLOC);
          return NULL;
        }
        // Allocate a size of 1 if we shouldn't free() on Realloc to 0
        size = 1;
    }
    return Reallocate(ptr, size);

}

#endif


#if McuASAN_CONFIG_FreeRTOs

#if DUALCOREFUZZ
extern WWDG_HandleTypeDef hwwdg2;


void activateWWDG()
{
	MX_WWDG2_Init();
}


void refreshWWDG()
{
	HAL_WWDG_Refresh(&hwwdg2);

}


void NotifyHSEM(uint32_t HS)
{
	/*Fast take */
	HAL_HSEM_FastTake(HS);
	/*Release HSEM in order to notify the CPU1(CM7)*/
	HAL_HSEM_Release(HS,0);
}

void ActivateNotificationHSEM(uint32_t HS)
{

    __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HS));
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HS));
}


#endif





void FreeRTOSReportFailure(type_exception_t  tEX)
{


	  Fuzzer_t *pAFLfuzzer = (Fuzzer_t *)AFLfuzzerRegion;



	  if(xTaskGetCurrentTaskHandle() == AFLfuzzer.xTaskTarget )
	  {

		  //MPU_ASAN_flush_alloc(); //this must be executed as a system call
		  //xTaskNotifyGiveIndexed(AFLfuzzer.xTaskFuzzer,FAULT_ASAN,eSetValueWithOverwrite);
		  AFLfuzzer.xTypeEx = tEX;


#if DUALCOREFUZZ == 0

		  xTaskNotifyIndexed(AFLfuzzer.xTaskFuzzer,0,FAULT_ASAN,eSetValueWithOverwrite);

		  taskYIELD(); //bug reported to FreeRTOS
		  //MPU_SytemCall_1();
		  //vTaskDelay(0);


		  while(1);
#else

		  	AFLfuzzer.notiVCM4TOCM7 = FAULT_CRASH; //we detected a crash
		  	//HAL_HSEM_FastTake(HSEM_ID_2);          //notify CM7 about the crash
		  	//HAL_HSEM_Release(HSEM_ID_2,0);
		  	MPU_HSEM_notify(HSEM_ID_2);

		  	//&hwwdg2->Instance->CR=64; //this should trigger a reboot immediately
		  	//hwwdg2.Instance->CR=64; //this should trigger a reboot immediately

		  	while(1);

#endif

		  //Notify the fuzzer task that the target crashed
		  //xTaskNotify(AFLfuzzer.xTaskFuzzer,FAULT_ASAN,eSetValueWithOverwrite);
		  //the target task will be deleted by the fuzzer task
		  //vTaskDelete(AFLfuzzer.xTaskTarget);
		  //portYIELD();
		  // port yield should be called and nothing else should be executed
	  }
	  else
	  {
		  //printf("Fuzzer crashed");
		  for( ; ; )
		  {
			  // this should never happen if we reach this point the whole firmware state can be corrupted
			  // TODO: can we reboot the MCU here?
		  }

	  }


}
#endif









#if McuASAN_CONFIG_KSAN


#if McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE > 0
static void *freeQuarantineList[McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE];
/*!< list of free'd blocks in quarantine */
static int freeQuarantineListIdx; /* index in list (ring buffer), points to free element in list */
#endif


typedef enum {
  kIsWrite, /* write access */
  kIsRead,  /* read access */
} rw_mode_e;


/* see https://github.com/gcc-mirror/gcc/blob/master/libsanitizer/asan/asan_interface_internal.h */
static uint8_t shadow[McuASAN_CONFIG_APP_MEM_SIZE/8]; /* one shadow byte for 8 application memory bytes. A 1 means that the memory address is poisoned */

static uint8_t *MemToShadow(void *address) {
  address -= McuASAN_CONFIG_APP_MEM_START;
  return shadow+(((uint32_t)address)>>3); /* divided by 8: every byte has a shadow bit */
}



static void PoisonShadowByte1Addr(void *addr) {
  if (addr>=(void*)McuASAN_CONFIG_APP_MEM_START && addr<(void*)(McuASAN_CONFIG_APP_MEM_START+McuASAN_CONFIG_APP_MEM_SIZE)) {
    *MemToShadow(addr) |= 1<<((uint32_t)addr&7); /* mark memory in shadow as poisoned with shadow bit */
  }
}

static void ClearShadowByte1Addr(void *addr) {
  if (addr>=(void*)McuASAN_CONFIG_APP_MEM_START && addr<(void*)(McuASAN_CONFIG_APP_MEM_START+McuASAN_CONFIG_APP_MEM_SIZE)) {
    *MemToShadow(addr) &= ~(1<<((uint32_t)addr&7)); /* clear shadow bit: it is a valid memory */
  }
}




static bool SlowPathCheck(int8_t shadow_value, void *address, size_t kAccessSize) {
  /* return true if access to address is poisoned */
  int8_t last_accessed_byte = (((uint32_t)address) & 7) + kAccessSize - 1;
  return (last_accessed_byte >= shadow_value);
}

static void ReportError(void *address, size_t kAccessSize, rw_mode_e mode) {
  //printf("ASAN ptr failure: addr 0x%x, %s, size: %d \n", (uint) address, mode==kIsRead?"read":"write", kAccessSize);
  __asm volatile("bkpt #0"); /* stop application if debugger is attached */
}

static void CheckShadow(void *address, size_t kAccessSize, rw_mode_e mode) {
  int8_t *shadow_address;
  int8_t shadow_value;

  if (address>=(void*)McuASAN_CONFIG_APP_MEM_START && address<(void*)(McuASAN_CONFIG_APP_MEM_START+McuASAN_CONFIG_APP_MEM_SIZE)) {
    shadow_address = (int8_t*)MemToShadow(address);
    shadow_value = *shadow_address;
    if (shadow_value==-1) {
      ReportError(address, kAccessSize, mode);
    } else if (shadow_value!=0) { /* fast check: poisoned! */
      if (SlowPathCheck(shadow_value, address, kAccessSize)) {
        ReportError(address, kAccessSize, mode);
      }
    }
  }
}

void __asan_load4_noabort(void *address) {
  CheckShadow(address, 4, kIsRead); /* check if we are reading from poisoned memory */
}

void __asan_store4_noabort(void *address) {
  CheckShadow(address, 4, kIsWrite); /* check if we are writing to poisoned memory */
}

void __asan_load2_noabort(void *address) {
  CheckShadow(address, 2, kIsRead); /* check if we are reading from poisoned memory */
}

void __asan_store2_noabort(void *address) {
  CheckShadow(address, 2, kIsWrite); /* check if we are writing to poisoned memory */
}

void __asan_load1_noabort(void *address) {
  CheckShadow(address, 1, kIsRead); /* check if we are reading from poisoned memory */
}

void __asan_store1_noabort(void *address) {
  CheckShadow(address, 1, kIsWrite); /* check if we are writing to poisoned memory */
}




#if McuASAN_CONFIG_CHECK_MALLOC_FREE
/* undo possible defines for malloc and free */
#ifdef malloc
  #undef malloc
  void *malloc(size_t);
#endif
#ifdef free
  #undef free
  void free(void*);
#endif
#ifdef realloc
  #undef realloc
  void	*realloc(void *, size_t);
#endif


/*
 * rrrrrrrr  red zone border (incl. size below)
 * size
 * memory returned
 * rrrrrrrr  red zone boarder
 */

void *__asan_malloc(size_t size) {
  /* malloc allocates the requested amount of memory with redzones around it.
   * The shadow values corresponding to the redzones are poisoned and the shadow values
   * for the memory region are cleared.
   */
  void *p = malloc(size+2*McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER); /* add size_t for the size of the block */
  void *q;

  q = p;
  /* poison red zone at the beginning */
  for(int i=0; i<McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER; i++) {
    PoisonShadowByte1Addr(q);
    q++;
  }
  *((size_t*)(q-sizeof(size_t))) = size; /* store memory size, needed for the free() part */
  /* clear valid memory */
  for(int i=0; i<size; i++) {
    ClearShadowByte1Addr(q);
    q++;
  }
  /* poison red zone at the end */
  for(int i=0; i<McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER; i++) {
    PoisonShadowByte1Addr(q);
    q++;
  }
  return p+McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER; /* return pointer to valid memory */
}
#endif

#if McuASAN_CONFIG_CHECK_MALLOC_FREE
void *__asan_realloc( void *ptr, size_t new_size )
{
    void *newp = __asan_malloc(new_size);
    if(newp)
    {
	    memcpy( newp, ptr, new_size);
	    __asan_free(ptr);
	    return newp;
    }
    else
    {
    	return NULL;
    }

}
#endif


#if McuASAN_CONFIG_CHECK_MALLOC_FREE
void __asan_free(void *p) {
  /* Poisons shadow values for the entire region and put the chunk of memory into a quarantine queue
   * (such that this chunk will not be returned again by malloc during some period of time).
   */
  size_t size = *((size_t*)(p-sizeof(size_t))); /* get size */
  void *q = p;

  for(int i=0; i<size; i++) {
    PoisonShadowByte1Addr(q);
    q++;
  }
  q = p-McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER; /* calculate beginning of malloc()ed block */
#if McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE > 0
  /* put the memory block into quarantine */
  freeQuarantineList[freeQuarantineListIdx] = q;
  freeQuarantineListIdx++;
  if (freeQuarantineListIdx>=McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE) {
    freeQuarantineListIdx = 0;
  }
  if (freeQuarantineList[freeQuarantineListIdx]!=NULL) {
    free(freeQuarantineList[freeQuarantineListIdx]);
    freeQuarantineList[freeQuarantineListIdx] = NULL;
  }
#else
  free(q); /* free block */
#endif
}
#endif /* McuASAN_CONFIG_CHECK_MALLOC_FREE */

void McuASAN_Init(void) {

  for(int i=0; i<sizeof(shadow); i++) { /* initialize full shadow map */
    shadow[i] = -1; /* poison everything  */
  }
  /* because the shadow is part of the memory area: poison the shadow */
  for(int i=0; i<sizeof(shadow); i+=8) {
    PoisonShadowByte1Addr(&shadow[i]);
  }
#if McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE > 0
  for(int i=0; i<McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE; i++) {
    freeQuarantineList[i] = NULL;
  }
  freeQuarantineListIdx = 0;
#endif
}

#endif

#endif /* McuASAN_CONFIG_IS_ENABLED */
