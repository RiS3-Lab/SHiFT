/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUASAN_H_
#define MCUASAN_H_

#include <stddef.h>
#include "stdint.h"
#include "stdbool.h"


#include "McuASANconfig.h"



#if defined(__clang__) || defined (__GNUC__)
# define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_address))
#else
# define ATTRIBUTE_NO_SANITIZE_ADDRESS
#endif


#if McuASAN_CONFIG_IS_ENABLED && McuASAN_CONFIG_CHECK_MALLOC_FREE
  /* replace malloc and free calls */
  #define malloc   asan_malloc
  #define free     asan_free
  #define realloc  asan_realloc

#endif


typedef  uint32_t uptr;

typedef struct __asan_global_source_location {
  const char *filename;
  int line_no;
  int column_no;
}__asan_global_source_location_t;


typedef struct __asan_global {
   uptr beg;                // The address of the global.
   uptr size;               // The original size of the global.
   uptr size_with_redzone;  // The size with the redzone.
   const char *name;        // Name as a C string.
   const char *module_name; // Module name as a C string. This pointer is a
                            // unique identifier of a module.
   uptr has_dynamic_init;   // Non-zero if the global has dynamic initializer.
   __asan_global_source_location_t *location;  // Source location of a global,
                                             // or NULL if it is unknown.
   uptr odr_indicator;      // The address of the ODR indicator symbol.
 } global_t;




 typedef struct  {
   // 1-st 8 bytes.
   uint32_t chunk_state       : 8;  // Must be first.
   uint32_t alloc_tid         : 24;

   uint32_t free_tid          : 24;
   uint32_t from_memalign     : 1;
   uint32_t alloc_type        : 2;
   uint32_t rz_log            : 3;
   uint32_t lsan_tag          : 2;
   // 2-nd 8 bytes
   // This field is used for small sizes. For large sizes it is equal to
   // SizeClassMap::kMaxSize and the actual size is stored in the
   // SecondaryAllocator's metadata.
   uint32_t user_requested_size : 29;
   // align < 8 -> 0
   // else      -> log2(min(align, 512)) - 2
   uint32_t user_requested_alignment_log : 3;
   uint32_t alloc_context_id;
 }AsanChunk;



typedef struct    {
   // Header2, intersects with user memory.
	 AsanChunk ChunkHeader;
	 uint32_t free_context_id;
 } ChunkBase;


 typedef enum  {
   FROM_MALLOC = 1,  // Memory block came from malloc, calloc, realloc, etc.
   FROM_NEW = 2,     // Memory block came from operator new.
   FROM_NEW_BR = 3   // Memory block came from operator new [ ]
 }AllocType;


/*! \brief
 * Allocate a memory block
 */

void *asan_malloc(size_t size);

/*! \brief
 * Resize and allocate a memory block
 */

void *asan_realloc( void *ptr, size_t new_size );

/*!
 * \brief
 * Free a memory block
 */
void asan_free(void *p);




/*! \brief
 * Call the init function first to initialize the module.
 */
void McuASAN_Init(void);

void *Allocate(uptr size, uptr alignment,AllocType alloc_type, bool can_fill);
void Deallocate(void *ptr, uptr delete_size, uptr delete_alignment, AllocType alloc_type);
void *Reallocate(void *old_ptr, uptr new_size);
void FlushAlloc();

void refreshWWDG();
void activateWWDG();
void NotifyHSEM(uint32_t HS);
void ActivateNotificationHSEM(uint32_t HS);


void SytemCall_1_code();
void SytemCall_2_code();
void SytemCall_3_code();

void SytemCall_4_code(void *val);
void SytemCall_5_code(void *val);


#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* MCUASAN_H_ */

