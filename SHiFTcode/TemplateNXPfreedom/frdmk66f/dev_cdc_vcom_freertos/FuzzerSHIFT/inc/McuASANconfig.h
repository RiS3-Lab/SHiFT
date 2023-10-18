/*
 * Alejandro Mera
 *
 */

#ifndef MCUASANCONFIG_H_
#define MCUASANCONFIG_H_
#include "stdint.h"

#define HUSART huart3



/** Configurations **/

#ifndef McuASAN_CONFIG_FreeRTOs
#define McuASAN_CONFIG_FreeRTOs 0
#endif



#ifndef McuASAN_CONFIG_IS_ENABLED
  #define McuASAN_CONFIG_IS_ENABLED     (1)
  /*!< 1: ASAN is enabled; 0: ASAN is disabled */
#endif

#ifndef McuASAN_CONFIG_KSAN
 #define McuASAN_CONFIG_KSAN     (0)
/*!<1 enables KSAN runtime, 0 enables ASAN runtime*/
#endif

#ifndef McuASAN_CONFIG_CHECK_MALLOC_FREE
  #define McuASAN_CONFIG_CHECK_MALLOC_FREE  (1)
  /*!< 1: check malloc() and free() */
#endif

#ifndef McuASAN_CONFIG_APP_MEM_START
  #define McuASAN_CONFIG_APP_MEM_START 0x20000000
  /*!< base RAM address */
#endif

#ifndef McuASAN_CONFIG_APP_MEM_SIZE
  #define McuASAN_CONFIG_APP_MEM_SIZE  (128*1024)
  /*!< RAM size */
#endif

#ifndef McuASAN_CONFIG_APP_MEM_OFFSET
  //#define McuASAN_CONFIG_APP_MEM_OFFSET 0x20000000  //this is the standard value
  //#define McuASAN_CONFIG_APP_MEM_OFFSET 0x1C010000  //this is for lower 64k for RAM and upper 64k for SHADOW, technically is wasting too much memory
  //#define McuASAN_CONFIG_APP_MEM_OFFSET 0x1C01C000     //this is using lower 112k for ram and upper 16k for shadow
  //#define McuASAN_CONFIG_APP_MEM_OFFSET 0x1B800000
  //#define McuASAN_CONFIG_APP_MEM_OFFSET 0x1c240000
  #define McuASAN_CONFIG_APP_MEM_OFFSET 0x1C020000
  /*!< offset RAM address */
#endif


#ifndef McuASAN_CONFIG_KMAX_ALLOWED_MALLOC_SIZE
   #define McuASAN_CONFIG_KMAX_ALLOWED_MALLOC_SIZE (1024*4)
#endif


#ifndef McuASAN_CONFIG_MAX_USER_DEFINED_MALLOC_SIZE
   #define McuASAN_CONFIG_MAX_USER_DEFINED_MALLOC_SIZE (2048*2)
#endif




#if McuASAN_CONFIG_CHECK_MALLOC_FREE
#ifndef McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER
  #define McuASAN_CONFIG_MALLOC_RED_ZONE_BORDER  (8)
  /*!< red zone border in bytes around memory blocks. Must be larger than sizeof(size_t)! */
#endif

#ifndef McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE
  #define McuASAN_CONFIG_FREE_QUARANTINE_LIST_SIZE  (8)
  /*!< list of free blocks in quarantine until they are released. Use 0 for no list. */
#endif

#endif /* McuASAN_CONFIG_CHECK_MALLOC_FREE */



/** Flags **/

#ifndef McuASAN_FLAG_POISON_PARTIAL
#define  McuASAN_FLAG_POISON_PARTIAL true
#endif

#ifndef McuASAN_FLAG_DETECT_STACK_USE_AFTER_RETURN
#define McuASAN_FLAG_DETECT_STACK_USE_AFTER_RETURN false
#endif

#ifndef McuASAN_FLAG_MAX_REDZONE
#define McuASAN_FLAG_MAX_REDZONE 64 //Maximal size (in bytes) of redzones around heap objects.
#endif

#ifndef McuASAN_FLAG_REDZONE
#define McuASAN_FLAG_REDZONE 16 	//Minimal size (in bytes) of redzones around heap objects.
									// Requirement: redzone >= 16, is a power of two.
#endif

#ifndef McuASAN_FLAG_ALLOCATOR_FREES_AND_RETURNS_NULL_ON_REALLOC_ZERO
#define McuASAN_FLAG_ALLOCATOR_FREES_AND_RETURNS_NULL_ON_REALLOC_ZERO true
#endif


#ifndef McuASAN_FLAG_MAX_MALLOC_FILL_SIZE
#define McuASAN_FLAG_MAX_MALLOC_FILL_SIZE 512
#endif

#ifndef McuASAN_FLAG_MALLOC_FILL_BYTE
#define McuASAN_FLAG_MALLOC_FILL_BYTE 0xbe
#endif

#ifndef McuASAN_FLAG_MAX_FREE_FILL_SIZE
#define McuASAN_FLAG_MAX_FREE_FILL_SIZE   512 // Maximum number of bytes that will be filled during free
#endif

#ifndef McuASAN_FLAG_FREE_FILL_BYTE
#define McuASAN_FLAG_FREE_FILL_BYTE 0x55
#endif


#ifndef McuASAN_FLAG_ALLOC_DEALLOC_MISMATCH
#define McuASAN_FLAG_ALLOC_DEALLOC_MISMATCH true
#endif



#ifndef McuASAN_FLAG_NEW_DELETE_TYPE_MISMATCH
#define McuASAN_FLAG_NEW_DELETE_TYPE_MISMATCH true
#endif




#endif /* MCUASANCONFIG_H_ */
