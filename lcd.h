/*
 * lcd.h
 *
 * Created: 7/21/2024 3:45:55 PM
 *  Author: sarax
 */ 


#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>

// Define los pines de control del LCD
#define RS PD2
#define E PD3
// No definir RW porque está conectado a GND en el hardware

// Define los puertos de datos y control del LCD
#define CONTROL_PORT PORTD
#define DATA_PORT PORTD
#define DATA_DDR DDRD

// Funciones de la LCD
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);

#endif
