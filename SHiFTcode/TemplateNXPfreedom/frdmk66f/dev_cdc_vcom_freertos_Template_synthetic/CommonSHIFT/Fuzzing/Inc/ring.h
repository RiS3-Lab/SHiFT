/*
 * ring.h
 *
 *  Created on: Sep 10, 2021
 *      Author: alejandro
 */

#ifndef SRC_RING_H_
#define SRC_RING_H_

#include "afl.h"



#include "stdint.h"
#include "stdbool.h"

typedef struct
{
uint8_t uxBuffer[MAX_BUFFER_INPUT];
uint32_t u32start;
uint32_t u32end;
uint32_t u32available;
uint32_t u32availablenopad;
bool    overflow;
}RingBuffer_t;


//Function prototypes for ModbusRingBuffer
void RingAdd(RingBuffer_t *xRingBuffer, uint8_t u8Val); // adds a byte to the ring buffer
uint32_t RingGetAllBytes(RingBuffer_t *xRingBuffer, uint8_t *buffer); // gets all the available bytes into buffer and return the number of bytes read
uint32_t RingGetNBytes(RingBuffer_t *xRingBuffer, uint8_t *buffer, uint32_t uNumber); // gets uNumber of bytes from ring buffer, returns the actual number of bytes read
uint32_t RingCountBytes(RingBuffer_t *xRingBuffer); // return the number of available bytes
void RingClear(RingBuffer_t *xRingBuffer); // flushes the ring buffer
void RingZeroes(RingBuffer_t *xRingBuffer); // clear the ring buffer and zeroes the content
void RingCopy(RingBuffer_t *xRingBuffer, uint8_t* u8Buff, uint32_t len);


#endif /* SRC_RING_H_ */
