#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#include "debug.h"
#include "protocol.h"
#include "serialport.h"

//extern u8 trace_diff[];
//extern u32 num_diff_trace;
extern u32 num_diff_max;

extern char * port_name;
extern u32 sp_baud_rate;
extern struct sp_port * dev_h;

extern u64 total_execs;

extern u32 exec_tmout;




#if CRCL152 ==1

uint32_t _poly = 0x04C11DB7;


void crc32(const uint8_t *data, size_t n_bytes, uint32_t* crc) {
  static uint32_t table[0x100];
  static uint32_t c;

  if(!*table)// this table is only initialized once in a fuzzing compaign
    for(size_t i = 0; i < 256; ++i)
    {
       c = i << 24;
       for(size_t j=0; j<8; j++)
       {
          c =  ((c & 0x80000000)?  (c<<1) ^ _poly :   (c<<1));     
       }
       table[i] =  c & 0xffffffff;
      
    }
       
    size_t   length = n_bytes;
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

        k = k + 4;
        length = length - 4;
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




#else

uint32_t crc32_for_byte(uint32_t r) {
  for(int j = 0; j < 8; ++j)
    r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
  return r ^ (uint32_t)0xFF000000L;
}

void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
  static uint32_t table[0x100];
  if(!*table)// this table is only initialized once in a fuzzing compaign
    for(size_t i = 0; i < 0x100; ++i)
      table[i] = crc32_for_byte(i);
  for(size_t i = 0; i < n_bytes; ++i)
    *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
}

#endif




#define MAX_LEN_SEND_BUF 4 + MAX_LEN_INPUT_PAYLOAD + 4

u32 last_sent_len;
u8 last_sent_buf[MAX_LEN_SEND_BUF];
u32 retry_max = 5;



#ifdef MEASSURE_TIME
u64 FM_time = 0;
u64 total_time = 0;

FILE *pFile = NULL;
char * pfile_name = "profile.txt"; 
#endif
/*
FILE *warning_File = NULL;
char * warning_file_name = "warning.txt"; 
*/

void reportInput(FILE* out){
    fprintf(out, "seq number:%llu\n", total_execs);
    u32 i = 0;
    fprintf(out, "feeding input:");
    for(i = 0 ; i < last_sent_len ; i ++){
        fprintf(out, "%02x",last_sent_buf[i]);
    }
    fprintf(out, "\n");
}

void reportReceived(FILE* out, ReceivedBuf received){
    fprintf(out, "received buf:");
    for(u32 i = 0 ; i < received.len ; i ++){
        fprintf(out, "%02x",received.buf[i]);
    }
    fprintf(out, "\n");
}
/*
void report_warning(int retry_counter){
    fprintf(warning_File, "attempt: %d ", retry_counter);
    fprintf(warning_File, "triggering input is:\n");
    int i = 0 ;
    for(i = 0 ; i < last_sent_len; i ++){
        fprintf(warning_File, "%02x",last_sent_buf[i]);
    }
    fprintf(warning_File, "\n\n");
}
*/

ReceivedBuf normalRetry(){
    usleep(exec_tmout * 1000);
    fprintf(stderr,"normal retry\n\n");
    sendDataSerialPort(dev_h, last_sent_buf, last_sent_len);
    return receiveDataSerial(dev_h);
}

ReceivedBuf bigRetry(){
    freeSerialPort(dev_h);
    usleep(5 * exec_tmout * 1000);
    fprintf(stderr,"big retry\n\n");
    dev_h = initSerialPort(port_name,sp_baud_rate);
    sendDataSerialPort(dev_h, last_sent_buf, last_sent_len);
    return receiveDataSerial(dev_h);
}

ReceivedBuf retry(u32 retry_counter ){
    ReceivedBuf received_buf;
    flush_rx_tx_buffers(dev_h);
    if(retry_counter == (retry_max - 1)){
        // now or never
        received_buf = bigRetry();
    }else{
        received_buf = normalRetry();
    }
    return received_buf;
}


void getFeedback(uint32_t* exit_status, uint8_t* bitmap){

#ifdef MEASSURE_TIME
    u64 readStartTime = get_cur_time_us_1();
#endif
    ReceivedBuf received = receiveDataSerial(dev_h);

#ifdef MEASSURE_TIME
    u64 readEndTime = get_cur_time_us_1();
    fprintf(pFile, "read time: %lld\n", readEndTime - readStartTime);
    fprintf(pFile, "read %d bytes\n", received.len);

    //meassure time
    u64 last_FM_time = FM_time;
    FM_time = get_cur_time_us_1();
    if(FM_time <= last_FM_time){
        FATAL("time progress in reverse");
    }

    u64 last_total_time = total_time;
    total_time = FM_time;
    /// printf("time lapse:%lld", time_lapse);
    
    fprintf(pFile, "FM time: %lld\n", FM_time - last_FM_time);
    fprintf(pFile, "total time: %lld\n", total_time - last_total_time);
    FM_time = 0;
#endif

    // validate and maybe retry
    u32 retry_counter = 0;
    for(retry_counter = 0; retry_counter < retry_max ; retry_counter ++){
        if(received.buf == NULL){
            reportInput(stderr);
            reportReceived(stderr, received);
            received = retry(retry_counter);
            continue;
        }
        // parse the exit_status, len, crc fields
        *exit_status = *((uint32_t*)received.buf); 
        uint32_t payload_crc_len  = *((uint32_t*)received.buf + 1);
        uint32_t received_crc32 = *(uint32_t*)(received.buf + received.len - 4);

        // check exit status
        if (*exit_status == FAULT_COMM){
            fprintf(stderr, "FAULT_COMM received\n");
            reportInput(stderr);
            reportReceived(stderr, received);
            free(received.buf);
            received = retry(retry_counter);
            continue;
        }

        if(*exit_status == FAULT_INLEGTH){
            fprintf(stderr, "Firmware complained about incorrect length, maybe length field is corrupted\n");
            reportInput(stderr);
            reportReceived(stderr, received);
            free(received.buf);
            received = retry(retry_counter);
            continue;
        }

        // check crc
        uint32_t calc_crc = 0;
        crc32(received.buf, received.len - 4, &calc_crc);
        calc_crc &= 0xffffffff;
        if( calc_crc != received_crc32){
            fprintf(stderr, "cannot validate received crc %u, calculated:%u\n", received_crc32, calc_crc);
            reportInput(stderr);
            reportReceived(stderr, received);
            free(received.buf);
            received = retry(retry_counter);
            continue;
        }

        int num_entries = (received.len - 8 - 4) / 4;
        
        if(num_entries > num_diff_max){
            fprintf(stderr, "Num of pairs is too many, maximum:%d, accepted:%d\n", num_diff_max, num_entries);
            reportInput(stderr);
            reportReceived(stderr, received);
            free(received.buf);
            received = retry(retry_counter);
            continue;
        }
        if(num_entries == 0){
            fprintf(stderr,"no entry is sent\n");
            reportInput(stderr);
            reportReceived(stderr, received);
            free(received.buf);
            received = retry(retry_counter);
            continue;
        }
        if((received.len - 8 - 4) % 4 != 0){
            fprintf(stderr, "receive len: %d cannot be divided by 4\n", received.len);
            reportInput(stderr);
            reportReceived(stderr, received);
            free(received.buf);
            received = retry(retry_counter);
            continue;
        }
        memset(bitmap, 0, MAP_SIZE);
        //memset(trace_diff, 0, MAP_SIZE);
        //num_diff_trace = 0;
        //DiffTuple* cur_entry = (DiffTuple*)trace_diff;
        //for(int cur = 0 ; cur < num_entries; cur++,cur_entry++){
        for(int cur = 0 ; cur < num_entries; cur++){
            uint16_t index = *(uint16_t*)(received.buf + 8 + cur * 4);
            uint16_t value = *(uint16_t*)(received.buf + 8 + cur * 4 + 2);
            if(index >= MAP_SIZE){
                fprintf(stderr, "index in the pair, %d ,exceeds MAP_SIZE, %d\n", index, MAP_SIZE);
                reportInput(stderr);
                reportReceived(stderr, received);
                free(received.buf);
                received = retry(retry_counter);
                continue;
            }
            if(value > 255){
                fprintf(stderr, "value for index %u exceeds 255: %u\n", index, value);
                reportInput(stderr);
                reportReceived(stderr, received);
                free(received.buf);
                received = retry(retry_counter);
                continue;
            }
            /*else if(value == 0){
                fprintf(stderr, "value for index %x is zero, so it should not be sent\n", index);
                reportInput(stderr);
                reportReceived(stderr, received);
                free(received.buf);
                received = retry(retry_counter);
                continue;
            }*/
            
            bitmap[index] = (uint8_t)value;
            //cur_entry->index = index;
            //cur_entry->value = (uint8_t)value;
        }
        //num_diff_trace = num_entries; 
        // everything going well, just stop retrying
        break;
    }
    if(retry_counter == retry_max){
        reportReceived(stderr, received);
        reportInput(stderr);
        FATAL("retried %d times, big retry 1 time, still cannot work", retry_max);
    }
    //memcpy(bitmap, received_buf + 8, MAP_SIZE);
    free(received.buf);
}


void sendInputs(uint8_t* buf, uint32_t size){
    u32 padded_bytes = (4 - (size % 4) ) % 4;
    if( (size + padded_bytes) > MAX_LEN_INPUT_PAYLOAD){
        // size by itself must be strictly greater than MAX_LEN_INPUT_PAYLOAD, 
        //since MAX_LEN_INPUT_PAYLOAD is divisible by 4, adding pad will not make a size originally smaller or equal to MAX_LEN_INPUT_PAYLOAD to be greater than MAX_LEN_INPUT_PAYLOAD
        size = MAX_LEN_INPUT_PAYLOAD;
        padded_bytes = 0;
    }
    uint32_t total_size = 4 + size + padded_bytes + 4;
    uint8_t* buf_to_send = (uint8_t*) malloc(total_size);
    *(uint32_t*) buf_to_send = size + 4;// this indicates the real length(excluding the padded bytes)
    memcpy(buf_to_send + 4, buf, size);
    memset(buf_to_send + 4 + size, 0 , padded_bytes);
    u32 crc_result = 0;
    crc32(buf_to_send, 4 + size + padded_bytes, &crc_result);
    *(uint32_t*) (buf_to_send + 4 + size + padded_bytes) = crc_result;

#if DBGPRINT==1

    FILE *logfile;
    char buffaux[1024];
    char *ptr = &buffaux[0];
    int i;


    time_t timer;
    char buffer[27];
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    buffer[26]=0;


  
    logfile = fopen("/home/alejandro/Documents/semi-fuzz-project/SHiFT/vanillaAFLplusplus/log/lofgile.txt", "a"); 

    if(logfile)
    {      
        //for(i=0; i<total_size; i++)
        for(i=0; i<size; i++)
        {
            //sprintf returns the number of written characters without the null, 
            //so ptr will point exactly where we need to write the next one
            //ptr += sprintf(ptr, "\\x%02X", buf_to_send[i]); 
            ptr += sprintf(ptr, "\\x%02X", buf[i]); 
        }
        fprintf(logfile,"%s Size: %d, Total Size: %d, CRC 0x%x, Data: %s\n", buffer, size, total_size, crc_result, buffaux);
        fclose(logfile);
    }
    

#endif



#ifdef MEASSURE_TIME
    // start recording time
    if(FM_time != 0){
        FATAL("time counter is polluted");
    }
    FM_time = get_cur_time_us_1();
    //end of recording time
    u64 writeStartTime = get_cur_time_us_1();
#endif
    sendDataSerialPort(dev_h, buf_to_send, total_size);

#ifdef MEASSURE_TIME
    u64 writeEndTime = get_cur_time_us_1();
    fprintf(pFile, "wrote %d bytes\n",total_size);
    fprintf(pFile, "write time: %lld\n", writeEndTime - writeStartTime);
#endif

    // keep the last seen buf

    memcpy(last_sent_buf , buf_to_send, total_size);
    last_sent_len = total_size;

    free(buf_to_send);
}

void protocol_cleaning_and_setting_up(){
#ifdef MEASSURE_TIME
    if( access( pfile_name, F_OK ) == 0 ) {
        remove(pfile_name);
    }
    pFile = fopen(pfile_name, "a");

#endif
    /*
    if( access( warning_file_name, F_OK ) == 0 ) {
        remove(warning_file_name);
    } 
    warning_File = fopen(warning_file_name,"a");
    */
}