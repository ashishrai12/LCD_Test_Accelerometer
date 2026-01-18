#include "accel.h"
#include <util/delay.h>

void accel_init(void) {
    // DDRA is input by default, but let's be explicit
    DDRA &= ~((1 << ACCEL_X_CHANNEL) | (1 << ACCEL_Y_CHANNEL) | (1 << ACCEL_Z_CHANNEL));
    
    // REFS0=1: AVCC with external capacitor at AREF pin
    // ADLAR=1: Left adjust result (8-bit precision in ADCH)
    ADMUX = (1 << REFS0) | (1 << ADLAR); 
    
    // ADEN=1: Enable ADC
    // ADPS2:0=111: Prescaler 128 (16MHz/128 = 125kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint8_t accel_read_axis(uint8_t channel) {
    // Select ADC channel (clear lower 5 bits of ADMUX and set channel)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    
    // Small delay for channel switching stability
    _delay_ms(1);
    
    // Start conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion completion
    while (ADCSRA & (1 << ADSC));
    
    // Return the 8-bit value from ADCH
    return ADCH;
}
