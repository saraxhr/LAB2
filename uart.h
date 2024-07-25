/*
 * uart.h
 *
 * Created: 7/21/2024 3:47:53 PM
 *  Author: sarax
 */ 


#ifndef UART_H
#define UART_H

#include <avr/io.h>

void uart_init(unsigned int baud);
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void uart_print(char *str);

#endif
