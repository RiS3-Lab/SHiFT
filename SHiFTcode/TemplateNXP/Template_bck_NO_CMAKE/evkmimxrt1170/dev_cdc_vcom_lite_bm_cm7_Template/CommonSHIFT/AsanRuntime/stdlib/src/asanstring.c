/*
 * asanstring.c
 *
 *  Created on: Dec 16, 2021
 *      Author: alejandro
 */


#include "stddef.h"

void asan_memcpy(const void *dest, const void *src, size_t n)
{

	// Typecast src and dest addresses to (char *)
	   char *csrc = (char *)src;
	   char *cdest = (char *)dest;

	   // Copy contents of src[] to dest[]
	   for (int i=0; i<n; i++)
	       cdest[i] = csrc[i];
}



void asan_memset(const void *m, int c , size_t  n)
{
  char *s = (char *) m;
  while (n--)
    *s++ = (char) c;

  //return m;
}


/* Nonzero if either X or Y is not aligned on a "long" boundary.  */
#define UNALIGNED(X, Y) \
  (((long)X & (sizeof (long) - 1)) | ((long)Y & (sizeof (long) - 1)))

/* How many bytes are copied each iteration of the 4X unrolled loop.  */
#define BIGBLOCKSIZE    (sizeof (long) << 2)

/* How many bytes are copied each iteration of the word copy loop.  */
#define LITTLEBLOCKSIZE (sizeof (long))

/* Threshhold for punting to the byte copier.  */
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

void asan_memmove(void *dst_void, const void *src_void, size_t length)
{

char *dst = dst_void;
const char *src = src_void;
long *aligned_dst;
const long *aligned_src;

 if (src < dst && dst < src + length)
   {
     /* Destructive overlap...have to copy backwards */
     src += length;
     dst += length;
     while (length--)
	{
	  *--dst = *--src;
	}
   }
 else
   {
     /* Use optimizing algorithm for a non-destructive copy to closely
        match memcpy. If the size is small or either SRC or DST is unaligned,
        then punt into the byte copy loop.  This should be rare.  */
     if (!TOO_SMALL(length) && !UNALIGNED (src, dst))
       {
         aligned_dst = (long*)dst;
         aligned_src = (long*)src;

         /* Copy 4X long words at a time if possible.  */
         while (length >= BIGBLOCKSIZE)
           {
             *aligned_dst++ = *aligned_src++;
             *aligned_dst++ = *aligned_src++;
             *aligned_dst++ = *aligned_src++;
             *aligned_dst++ = *aligned_src++;
             length -= BIGBLOCKSIZE;
           }

         /* Copy one long word at a time if possible.  */
         while (length >= LITTLEBLOCKSIZE)
           {
             *aligned_dst++ = *aligned_src++;
             length -= LITTLEBLOCKSIZE;
           }

         /* Pick up any residual with a byte copier.  */
         dst = (char*)aligned_dst;
         src = (char*)aligned_src;
       }

     while (length--)
       {
         *dst++ = *src++;
       }
   }


}


#define LBLOCKSIZE (sizeof (long))

int asan_memcmp(const void *m1, const void *m2, size_t n)
{
 unsigned char *s1 = (unsigned char *) m1;
 unsigned char *s2 = (unsigned char *) m2;
 unsigned long *a1;
 unsigned long *a2;

 /* If the size is too small, or either pointer is unaligned,
    then we punt to the byte compare loop.  Hopefully this will
    not turn up in inner loops.  */
 if (!TOO_SMALL(n) && !UNALIGNED(s1,s2))
   {
     /* Otherwise, load and compare the blocks of memory one
        word at a time.  */
     a1 = (unsigned long*) s1;
     a2 = (unsigned long*) s2;
     while (n >= LBLOCKSIZE)
       {
         if (*a1 != *a2)
  	    break;
         a1++;
         a2++;
         n -= LBLOCKSIZE;
       }

     /* check m mod LBLOCKSIZE remaining characters */

     s1 = (unsigned char*)a1;
     s2 = (unsigned char*)a2;
   }

 while (n--)
   {
     if (*s1 != *s2)
	return *s1 - *s2;
     s1++;
     s2++;
   }

 return 0;
 }


