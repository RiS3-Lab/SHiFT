/*
 * fuzzing.h
 *
 *  Created on: Sep 23, 2021
 *      Author: alejandro
 */

#ifndef INC_FUZZING_H_
#define INC_FUZZING_H_

#include "main.h"






#include "ring.h"
//#include "test.h"
//#include "test2.h"
//#include "testmodbus.h"
#include "afl.h"


#include "FreeRTOS.h"
#include "task.h"
#include "ConfigFuzzing.h"

#define b2(x)   (   (x) | (   (x) >> 1) )
#define b4(x)   ( b2(x) | ( b2(x) >> 2) )
#define b8(x)   ( b4(x) | ( b4(x) >> 4) )
#define b16(x)  ( b8(x) | ( b8(x) >> 8) )
#define b32(x)  (b16(x) | (b16(x) >>16) )
#define next_power_of_2(x)      (b32(x-1) + 1)


typedef enum
{
EX_NO_EX,
EX_ASAN_DOUBLE_FREE,
EX_ASAN_USE_AFTER_FREE,
EX_ASAN_INVALID_FREE,
EX_ASAN_RW_OVERFLOW,
EX_ASAN_DEL_MISMATCH,
EX_ASAN_REALLOC_MISMATCH,
EX_ASAN_FAIL_POISON,
EX_MPU_VIOLATION,
EX_CORTEX_DIV0,
EX_CORTEX_UNA_ACCESS,
EX_CORTEX_BUS_FAULT,
EX_CORTEX_UNDEF_INST,
EX_HARDFAULT, // we need to reboot the MCU this is not recoverable

}type_exception_t;



typedef struct
{
//#if DUALCOREFUZZ == 1
//	uint16_t aflbmp[AFL_BITMAP_SIZE];
//#endif
	uint16_t aflbmp[AFL_BITMAP_SIZE];
	tuple_t  afldiff [AFL_BITMAP_SIZE/4];  // This array must be in a section that USB master can access
	RingBuffer_t inputAFL;
	uint32_t aflheader[4];
	uint32_t inputLength;
    uint32_t inputLengthpadded;
    uint32_t timespan;
    uint32_t *allocs[McuASAN_MAX_NUMBER_ALLOCS];
    uint16_t previousGuard;
    uint32_t N; //a counter for instrumentation
    bool iniGuard;
    uint16_t indexdif;
    volatile bool bRXcomplete;  // variable must be declared as volatile otherwise the compiler may optimize out it
    volatile bool bTXcomplete;
    volatile bool breceiving;
    uint32_t PCcrash;
    TaskHandle_t xTaskFuzzer;
    TaskHandle_t xTaskTarget;
    type_exception_t xTypeEx;


#if USARTHW == 1
    bool receiving;
#endif
#ifdef DUALCOREFUZZ
    TaskHandle_t xTaskMonitor;
    uint32_t notiVCM4TOCM7;
    uint32_t notiVCM7TOCM4;
#endif

}Fuzzer_t;




void FuzzingTestWrapper();
void FuzzingInputHandler(uint8_t* Buf, uint32_t *Len);
bool checkCRC(RingBuffer_t *input);
void activateCortexMtraps();

#endif /* INC_FUZZING_H_ */
