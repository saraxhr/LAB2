/*
 * lab2prueba.c
 *
 * Created: 7/21/2024 3:42:11 PM
 * Author : sarax
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "uart.h"

#define F_CPU 16000000UL

void adc_init() {
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t ch) {
	ch &= 0b00000111; // Asegurarse de que el canal sea de 0 a 7
	ADMUX = (ADMUX & 0xF8) | ch; // Seleccionar el canal
	ADCSRA |= (1 << ADSC); // Iniciar la conversión
	while(ADCSRA & (1 << ADSC)); // Esperar a que termine la conversión
	return ADC;
}

int main(void) {
	uart_init();
	adc_init();
	lcd_init();
	lcd_print("Iniciando...");

	uint16_t pot1_val, pot2_val;
	char buffer[16];
	uint8_t counter = 0;

	while(1) {
		pot1_val = adc_read(0); // Leer valor del potenciómetro 1
		pot2_val = adc_read(1); // Leer valor del potenciómetro 2

		// Mostrar valores de los potenciómetros en la LCD
		lcd_set_cursor(0, 0);
		sprintf(buffer, "P1: %d", pot1_val);
		lcd_print(buffer);

		lcd_set_cursor(1, 0);
		sprintf(buffer, "P2: %d", pot2_val);
		lcd_print(buffer);

		// Enviar valores a la UART
		sprintf(buffer, "P1: %d, P2: %d\r\n", pot1_val, pot2_val);
		uart_transmit_string(buffer);

		// Leer comandos de la UART para el contador
		if (uart_data_available()) {
			char cmd = uart_receive();
			if (cmd == '+') {
				counter++;
				} else if (cmd == '-') {
				counter--;
			}
		}

		// Mostrar contador en la LCD
		lcd_set_cursor(0, 8);
		sprintf(buffer, "C: %d", counter);
		lcd_print(buffer);

		_delay_ms(500); // Pequeño retraso
	}
}


