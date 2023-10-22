/*
 * ConfigFuzzing.h
 *
 *  Created on: Jan 26, 2022
 *      Author: alejandro
 */

#ifndef FUZZING_CONFIG_CONFIGFUZZING_H_
#define FUZZING_CONFIG_CONFIGFUZZING_H_



/* BITMAP defines */
#define SIZE64  (1024 * 64)
#define SIZE32  (1024 * 32)
#define SIZE16  (1024 * 16)
#define SIZE8  (1024 * 8)
#define SIZE4  (1024 * 4)
#define SIZE2  (1024 * 2)
#define MAX_BUFFER_INPUT  (2048)       // 2 kb
#define AFL_BITMAP_SIZE   SIZE4



#define FUZZING_CYCLES_IN_PROCESS 1000   //number of cycles that we will use the same task before deleting and spawning a new one
#define McuASAN_MAX_NUMBER_ALLOCS 10
#define TARGET_TIMEOUT 20

#define  PERSISTENT_MODE 1
#define DUALCOREFUZZ 0



#endif /* FUZZING_CONFIG_CONFIGFUZZING_H_ */
