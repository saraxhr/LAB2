/*
 * uart.c
 *
 * Created: 7/21/2024 3:48:06 PM
 *  Author: sarax
 */ 


#define F_CPU 16000000UL // Definir la frecuencia del reloj

#include "uart.h"
#include <util/delay.h> // Para usar _delay_ms

void uart_init(unsigned int baud) {
	unsigned int ubrr = F_CPU/16/baud-1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void uart_transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char uart_receive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void uart_print(char *str) {
	while (*str) {
		uart_transmit(*str++);
	}
}
