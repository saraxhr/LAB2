/*
 * lcd.c
 *
 * Created: 7/21/2024 3:46:19 PM
 *  Author: sarax
 */ 


#include "lcd.h"

void lcd_init(void) {
	// Establecer los pines de control como salida
	DDRD |= (1 << RS) | (1 << E);
	
	// Establecer los pines de datos como salida
	DATA_DDR = 0xFC; // Pines PD2 a PD7 como salida
	
	// Inicialización en modo de 8 bits
	_delay_ms(20); // Esperar más de 15ms después de encender
	lcd_command(0x30); // Función de set en modo 8 bits
	_delay_ms(5); // Esperar más de 4.1ms
	lcd_command(0x30); // Función de set en modo 8 bits
	_delay_us(200); // Esperar más de 100µs
	lcd_command(0x30); // Función de set en modo 8 bits
	_delay_us(200); // Esperar más de 100µs

	// Configuración de la pantalla
	lcd_command(0x38); // Función de set: 8 bits, 2 líneas, 5x8 puntos
	lcd_command(0x0C); // Encender pantalla, sin cursor
	lcd_command(0x01); // Limpiar pantalla
	_delay_ms(2); // Esperar más de 1.53ms
	lcd_command(0x06); // Modo de entrada: incrementar automáticamente, sin desplazamiento
}

void lcd_command(uint8_t cmd) {
	CONTROL_PORT &= ~(1 << RS); // RS = 0 para comando

	DATA_PORT = (DATA_PORT & 0x03) | (cmd & 0xFC); // Poner el comando en el puerto de datos
	CONTROL_PORT |= (1 << E); // E = 1 para habilitar
	_delay_us(1); // Esperar un poco
	CONTROL_PORT &= ~(1 << E); // E = 0 para deshabilitar
	_delay_ms(2); // Esperar para que el comando se procese
}

void lcd_data(uint8_t data) {
	CONTROL_PORT |= (1 << RS); // RS = 1 para datos

	DATA_PORT = (DATA
