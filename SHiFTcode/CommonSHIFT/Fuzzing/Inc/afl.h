#ifndef __AFL_H
#define __AFL_H

#include <stdbool.h>
#include <stdint.h>
#include "ConfigFuzzing.h"

union ubytes_t{
	 uint8_t vbytes [4];
	 uint16_t vuwords[2];
	 int16_t  vwords[2];
	 int32_t  vint32;
	 uint32_t vuint32;

};

typedef struct
{
uint16_t index;
uint16_t val;
}tuple_t;


#define AFL_BITMAP_SIZE_BYTES AFL_BITMAP_SIZE * sizeof(uint16_t)
#if AFL_BITMAP_SIZE == SIZE64
#define AFL_BITMAP_MASK  0xffff
#elif AFL_BITMAP_SIZE == SIZE32
#define AFL_BITMAP_MASK  0x7fff
#elif AFL_BITMAP_SIZE == SIZE16
#define AFL_BITMAP_MASK  0x3fff
#elif AFL_BITMAP_SIZE == SIZE8
#define AFL_BITMAP_MASK  0x1fff
#elif AFL_BITMAP_SIZE == SIZE4
#define AFL_BITMAP_MASK  0x0fff
#endif


// AFL expected return codes
enum {
  /* 00 */ FAULT_NONE,
  /* 01 */ FAULT_TMOUT,
  /* 02 */ FAULT_CRASH,
  /* 03 */ FAULT_ERROR,
  /* 04 */ FAULT_NOINST,
  /* 05 */ FAULT_NOBITS,
  /* 06 */ FAULT_COMM,
  /* 07 */ FAULT_INLEGTH,
  /* 08 */ FAULT_NONE_RTOS,
  /* 09 */ FAULT_ASAN,
};

#endif
