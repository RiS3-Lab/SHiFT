
#ifndef INC_TESTMODBUS_H_
#define INC_TESTMODBUS_H_

#include "stdint.h"

#define T35  5
#define  MAX_BUFFER  64	//!< maximum size for the communication buffer in bytes

typedef struct
{
uint8_t u8id; //!< 0=master, 1..247=slave number
uint8_t u8serno; //!< serial port: 0-Serial, 1..3-Serial1..Serial3; 4: use software serial
uint8_t u8txenpin; //!< flow control pin: 0=USB or RS-232 mode, >0=RS-485 mode
uint8_t u8state;
uint8_t u8lastError;
uint8_t au8Buffer[MAX_BUFFER];
uint16_t u16regs[MAX_BUFFER];
volatile uint8_t u8BufferSize;
uint8_t u8lastRec;
uint16_t *au16regs;
uint16_t u16InCnt, u16OutCnt, u16errCnt;
uint16_t u16timeOut;
uint32_t u32time, u32timeOut;
uint8_t u8regsize;
unsigned char fctsupported[8];
} modbusHandler_t;

#define modbusHandle_size sizeof(modbusHandler_t)

#define b2(x)   (   (x) | (   (x) >> 1) )
#define b4(x)   ( b2(x) | ( b2(x) >> 2) )
#define b8(x)   ( b4(x) | ( b4(x) >> 4) )
#define b16(x)  ( b8(x) | ( b8(x) >> 8) )
#define b32(x)  (b16(x) | (b16(x) >>16) )
#define next_power_of_2(x)      (b32(x-1) + 1)


uint32_t modbusparsing(uint8_t *au8Buffer, uint8_t bufferlen );



#endif
