/*
 * asanstring.h
 *
 *  Created on: Dec 16, 2021
 *      Author: Alejandro Mera
 */

#ifndef INC_ASANSTRING_H_
#define INC_ASANSTRING_H_
#include <stddef.h>


#define memcpy   asan_memcpy
#define memset   asan_memset
#define memmove  asan_memmove
#define memcmp   asan_memcmp



void asan_memcpy(const void *dest, const void *src, size_t n);
void asan_memset(const void *m, int c , size_t  n);
void asan_memmove(void *dst_void, const void *src_void, size_t length);
int asan_memcmp(const void *m1, const void *m2, size_t n);













#endif /* INC_ASANSTRING_H_ */
