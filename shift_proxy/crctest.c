#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


uint32_t _poly = 0x04C11DB7;


void crc32(const uint8_t *data, size_t n_bytes, uint32_t* crc) {
  static uint32_t table[0x100];
  static uint32_t c;

    if(!*table)// this table is only initialized once in a fuzzing compaign
    {
        
        for(uint32_t i = 0; i < 256; ++i)
        {
           c = i << 24;
           
           for(uint32_t j=0; j<8; j++)
           {
              c =  ((c & 0x80000000)?  (c<<1) ^ _poly :   (c<<1));     
           }
           table[i] =  c & 0xffffffff;

        }
    }
       
    uint32_t   length = n_bytes;
    *crc = 0xffffffff;
    uint32_t k = 0;
    uint32_t v = 0;

    while( length >= 4)
    {
           
        v = ((data[k] << 24) & 0xFF000000) | ((data[k+1] << 16) & 0xFF0000) | 
            ((data[k+2] << 8) & 0xFF00) | (data[k+3] & 0xFF);

        *crc = ((*crc << 8) & 0xffffffff) ^ table[0xFF & ((*crc >> 24) ^ v)];
        *crc = ((*crc << 8) & 0xffffffff) ^ table[0xFF & ((*crc >> 24) ^ (v >> 8))];
        *crc = ((*crc << 8) & 0xffffffff) ^ table[0xFF & ((*crc >> 24) ^ (v >> 16))];
        *crc = ((*crc << 8) & 0xffffffff) ^ table[0xFF & ((*crc >> 24) ^ (v >> 24))];

        k += 4;
        length -= 4;
        
    }


    if(length > 0)
    {
        v = 0;

        for(size_t i=0; i< length; i++)
            v = v | (data[k+i] << 24-i*8);
        if (length == 1)
            v = v & 0xFF000000;
        else if (length == 2)
            v = v & 0xFFFF0000;
        else if (length == 3)
            v = v & 0xFFFFFF00;
        *crc = (( *crc << 8 ) & 0xffffffff) ^ table[0xFF & ( (*crc >> 24) ^ (v ) )];
        *crc = (( *crc << 8 ) & 0xffffffff) ^ table[0xFF & ( (*crc >> 24) ^ (v >> 8) )];
        *crc = (( *crc << 8 ) & 0xffffffff) ^ table[0xFF & ( (*crc >> 24) ^ (v >> 16) )];
        *crc = (( *crc << 8 ) & 0xffffffff) ^ table[0xFF & ( (*crc >> 24) ^ (v >> 24) )];
    }

   

    *crc = ~*crc;

}


void main()
{

uint8_t aux[]={0x0E, 0x00, 0x00, 0x00, 0x74, 0x65, 0x73, 0x74, 0x69, 0x6E, 0x70, 0x75, 0x74, 0x0A, 0x00, 0x00};
uint32_t result;

crc32(aux, 16, &result);

printf("\n CRC  %x\n", result);


}