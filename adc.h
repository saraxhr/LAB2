/*
 * adc.h
 *
 * Created: 7/21/2024 3:46:56 PM
 *  Author: sarax
 */ 


#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t ch);

#endif
