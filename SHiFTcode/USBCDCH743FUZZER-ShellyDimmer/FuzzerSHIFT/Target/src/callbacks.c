/*
 * callbacks.c
 *
 *  Created on: Mar 3, 2022
 *      Author: alejandro
 */

#include "main.h"



extern ADC_HandleTypeDef hadc1;
uint8_t dma_get_interrupt_flag=0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	dma_get_interrupt_flag = 1;
}

#define ADC_NUM_CHANNELS                    2

extern uint16_t adc_count                  ;
extern uint16_t current_max                ;
extern uint16_t current_max_period         ;
extern uint32_t current_total              ;
extern float    current_total_mag_period   ;
extern uint32_t current_total_mag          ;
extern uint16_t voltage_max                ;
extern uint16_t voltage_max_period         ;
extern uint32_t voltage_total              ;
extern uint16_t max_brightness             ;
extern uint16_t adc_data[ADC_NUM_CHANNELS] ;




void tim3_isr(void)
{

        // Check if ADC has finished converting
        if (dma_get_interrupt_flag)
        {
        	dma_get_interrupt_flag = 0;

            voltage_total += adc_data[0];
            current_total += adc_data[1];
            if (adc_data[1] > current_max_period)
                current_total_mag += adc_data[1] - current_max_period;
            else
                current_total_mag += current_max_period - adc_data[1];
            adc_count++;
            HAL_ADC_Start_DMA(&hadc1, adc_data, ADC_NUM_CHANNELS);
        }
}


uint32_t timer_get_counter(TIM_TypeDef *TIM)
{
	 return TIM->CNT;
}

void timer_set_counter(TIM_TypeDef *TIM, uint32_t val)
{

	TIM->CNT = val;
}

