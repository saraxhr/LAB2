/*
 * CFile1.c
 *
 * Created: 7/21/2024 3:47:19 PM
 *  Author: sarax
 */ 


#include "adc.h"

void adc_init(void) {
	ADMUX = (1 << REFS0); // Referencia AVcc
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Habilitar ADC, prescaler de 128
}

uint16_t adc_read(uint8_t ch) {
	ch &= 0b00000111; // Canal debe estar entre 0 y 7
	ADMUX = (ADMUX & 0xF8) | ch; // Seleccionar canal
	ADCSRA |= (1 << ADSC); // Iniciar conversión
	while (ADCSRA & (1 << ADSC)); // Esperar a que termine la conversión
	return ADC;
}
