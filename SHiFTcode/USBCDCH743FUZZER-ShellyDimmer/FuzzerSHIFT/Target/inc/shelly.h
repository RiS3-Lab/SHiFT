/*
 * test.h
 *
 *  Created on: Sep 3, 2021
 *      Author: alejandro
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include "stdint.h"
#include "main.h"

void usart1_isr(uint8_t d);
void init_shelly();
void tim3_isr(void);
uint32_t timer_get_counter(TIM_TypeDef *TIM);
void timer_set_counter(TIM_TypeDef *TIM, uint32_t val);

#endif /* INC_TEST_H_ */
