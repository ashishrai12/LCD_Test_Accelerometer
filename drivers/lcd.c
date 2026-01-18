#include "lcd.h"

void lcd_command(unsigned char cmd) {
    LCD_DATA_PORT = cmd;
    LCD_CTRL_PORT &= ~(1 << RS_PIN); // RS = 0 for Command
    LCD_CTRL_PORT &= ~(1 << RW_PIN); // RW = 0 for Write
    LCD_CTRL_PORT |= (1 << EN_PIN);  // EN = 1
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1 << EN_PIN); // EN = 0
    _delay_ms(2);
}

void lcd_data(unsigned char data) {
    LCD_DATA_PORT = data;
    LCD_CTRL_PORT |= (1 << RS_PIN);  // RS = 1 for Data
    LCD_CTRL_PORT &= ~(1 << RW_PIN); // RW = 0 for Write
    LCD_CTRL_PORT |= (1 << EN_PIN);  // EN = 1
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1 << EN_PIN); // EN = 0
    _delay_ms(2);
}

void lcd_init(void) {
    LCD_DATA_DDR = 0xFF; // Set Data Port as output
    LCD_CTRL_DDR |= (1 << RS_PIN) | (1 << RW_PIN) | (1 << EN_PIN); // Set Control Pins as output

    _delay_ms(20);         // Wait for LCD to power up
    lcd_command(0x38);     // 8-bit mode, 2 lines, 5x7 dots
    lcd_command(0x0E);     // Display ON, Cursor ON
    lcd_command(0x01);     // Clear Display
    _delay_ms(2);
    lcd_command(0x06);     // Entry Mode: Inc cursor
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t pos[] = {0x80, 0xC0};
    lcd_command(pos[row] + col);
}

void lcd_clear(void) {
    lcd_command(0x01);
    _delay_ms(2);
}
