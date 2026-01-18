#ifndef LCD_H
#define LCD_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

// LCD Port Definitions
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR  DDRC
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_DDR  DDRB

#define RS_PIN 0
#define RW_PIN 1
#define EN_PIN 2

// Function Prototypes
void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);

#endif // LCD_H
