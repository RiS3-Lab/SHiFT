/*
 * test.h
 *
 *  Created on: Sep 3, 2021
 *      Author: alejandro
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include "stdint.h"

void usart1_isr(uint8_t d);
void init_shelly();
void tim3_isr(void);

#endif /* INC_TEST_H_ */
