/*
 * fuzzing.h
 *
 *  Created on: Sep 23, 2021
 *      Author: alejandro
 */

#ifndef INC_FUZZING_H_
#define INC_FUZZING_H_


#include "ring.h"
#include "afl.h"



typedef struct
{

	uint16_t aflbmp[AFL_BITMAP_SIZE];
	tuple_t  afldiff [AFL_BITMAP_SIZE/16];  // This array must be in a section that USB master can access
	uint32_t aflheader[4];
	RingBuffer_t inputAFL;
	uint32_t inputLength;
    uint32_t inputLengthpadded;
    uint32_t timespan;
    uint16_t previousGuard;
    uint32_t N; //a counter for instrumentation
    uint8_t iniGuard;
    uint16_t indexdif;
    volatile uint8_t bRXcomplete;  // variable must be declared as volatile otherwise the compiler may optimize out it
    volatile uint8_t bTXcomplete;
    uint32_t PCcrash;


}Fuzzer_t;




void FuzzingTestWrapper();
void FuzzingInputHandler(uint8_t* Buf, uint32_t *Len);
void CRC_Calculate(uint32_t *Buf, uint32_t len, uint32_t *crc);
//uint32_t CRC_Accumulate(uint32_t *Buf, uint32_t len, uint32_t accu);



#endif /* INC_FUZZING_H_ */
