/*
 * main.h
 *
 *  Created on: Sep 16, 2023
 *      Author: alejandro
 */

#ifndef MAIN_H_
#define MAIN_H_

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif
  #ifndef __packed
    #define __packed  __attribute__((packed))
  #endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */


#include "stdbool.h"
#include "ConfigFuzzing.h"
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"


#if DUALCOREFUZZ == 0

#define DTCMRAMORIGIN  0x20000000
#define AFLINPUTREGION_SIZE (1024*16)

extern uint8_t AFLfuzzerRegion[AFLINPUTREGION_SIZE ];

#else

#define AFLINPUTREGION_SIZE (1024*128)
#define AFLfuzzerRegion  (uint8_t*)0x24040000

#endif


#define AFLfuzzer  (*pAFLfuzzer)
#define aflbitmap (*paflbitmap)







#endif /* MAIN_H_ */
