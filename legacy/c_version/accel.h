#ifndef ACCEL_H
#define ACCEL_H

#include <avr/io.h>

// ADC Channel Definitions for ADXL335 or similar
#define ACCEL_X_CHANNEL 0
#define ACCEL_Y_CHANNEL 1
#define ACCEL_Z_CHANNEL 2

// Function Prototypes
void accel_init(void);
uint8_t accel_read_axis(uint8_t channel);

#endif // ACCEL_H
