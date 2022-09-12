#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <libserialport.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

#include "types.h"

typedef struct _ReceivedBuf{
    unsigned char * buf;
    uint32_t len;
} ReceivedBuf;

struct sp_port * initSerialPort(char * port_name, int);
void freeSerialPort(struct sp_port* port);

void sendDataSerialPort(struct sp_port* port, uint8_t * buf, uint32_t size);
void flush_rx_tx_buffers(struct sp_port* port);
ReceivedBuf receiveDataSerial(struct sp_port* port);

/* Get unix time in milliseconds */



static u64 get_cur_time_1(void) {

  struct timeval tv;

  gettimeofday(&tv, NULL);

  return (tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000);

}

static u64 get_cur_time_us_1(void) {

  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

  return (tv.tv_sec * 1000000ULL) + tv.tv_usec;

}


#endif 