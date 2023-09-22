/*
 * afl_call.h
 *
 *  Created on: Mar 21, 2023
 *      Author: alejandro
 */

#ifndef INC_AFL_CALL_H_
#define INC_AFL_CALL_H_

#ifdef __cplusplus
extern "C" {
#endif
/* afl_call.c/.cpp */
int startForkserver(int ticks);
int doneWork(int val);
#ifdef __cplusplus
}
#endif

#endif /* INC_AFL_CALL_H_ */
