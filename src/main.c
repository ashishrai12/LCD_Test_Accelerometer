#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "../drivers/lcd.h"
#include "../drivers/accel.h"

int main(void) {
    char buffer[5];
    uint8_t x_val, y_val, z_val;

    // Initialize HW
    lcd_init();
    accel_init();

    // Initial Screen Setup
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("X=");
    lcd_set_cursor(0, 8);
    lcd_print("Y=");
    lcd_set_cursor(1, 0);
    lcd_print("Z=");

    while (1) {
        // Read Axes
        x_val = accel_read_axis(ACCEL_X_CHANNEL);
        y_val = accel_read_axis(ACCEL_Y_CHANNEL);
        z_val = accel_read_axis(ACCEL_Z_CHANNEL);

        // Update X
        itoa(x_val, buffer, 10);
        lcd_set_cursor(0, 2);
        lcd_print("   "); // Clear previous
        lcd_set_cursor(0, 2);
        lcd_print(buffer);

        // Update Y
        itoa(y_val, buffer, 10);
        lcd_set_cursor(0, 10);
        lcd_print("   "); // Clear previous
        lcd_set_cursor(0, 10);
        lcd_print(buffer);

        // Update Z
        itoa(z_val, buffer, 10);
        lcd_set_cursor(1, 2);
        lcd_print("   "); // Clear previous
        lcd_set_cursor(1, 2);
        lcd_print(buffer);

        _delay_ms(200); // Sampling Rate
    }

    return 0;
}
