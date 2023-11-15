#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdbool.h>
#include <stdint.h>
#include "serialport.h"

void getFeedback(uint32_t* exit_status, uint8_t* bitmap);
void sendInputs( uint8_t* buf, uint32_t len);

typedef struct _diff_tuple{
  u16 index;
  u8 value;
} DiffTuple;



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
  Status_First_Val = FAULT_NONE,
  Status_Last_Val = FAULT_NONE_RTOS,
};

void protocol_cleaning_and_setting_up();


#define CRCL152 0  // enables CRC for STM32L152
#define DBGPRINT 1 // 1 enables debugging of AFL data send through protocol

#endif
