# LCD Test Accelerometer (AVR-Based)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: AVR](https://img.shields.io/badge/Platform-AVR-blue.svg)](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus)

A professional, modular embedded system project for real-time accelerometer data visualization on a 16x2 LCD using ATmega16/32 microcontrollers.

---

## System Overview

This project interfaces an analog accelerometer (like the ADXL335) with an AVR microcontroller. The system samples three analog channels (X, Y, Z), processes the data through the internal 10-bit ADC (configured for 8-bit precision), and displays the raw values on a character LCD.

### Data Flow
```mermaid
graph LR
    A[ADXL335 Sensor] -->|Analog Voltage| B(AVR ADC Channels)
    B -->|Sampling| C{Digital Processing}
    C -->|8-bit Value| D[LCD Driver]
    D -->|8-bit Interface| E[16x2 LCD Display]
```

---

## Hardware Setup

### Component List
- **Microcontroller:** ATmega16 or ATmega32
- **Display:** 16x2 Character LCD (HD44780 compatible)
- **Sensor:** Analog Accelerometer (e.g., ADXL335)
- **Clock:** 16MHz Crystal/Oscillator

### Pin Mapping Table

| Component | MCU Pin | Function | Description |
| :--- | :--- | :--- | :--- |
| **LCD RS** | PORTB.0 | Control | Register Select |
| **LCD RW** | PORTB.1 | Control | Read/Write (tied to GND optionally) |
| **LCD EN** | PORTB.2 | Control | Enable/Strobe |
| **LCD D0-D7** | PORTC.0-7 | Data | 8-bit Data Bus |
| **Accel X** | PORTA.0 | Input | ADC Channel 0 |
| **Accel Y** | PORTA.1 | Input | ADC Channel 1 |
| **Accel Z** | PORTA.2 | Input | ADC Channel 2 |

---

## Software Setup

### Prerequisites
1. **Toolchain:** `avr-gcc`, `avr-libc`, and `avrdude`.
2. **IDE:** Microchip Studio (formerly Atmel Studio), VS Code with PlatformIO, or a custom Makefile.
3. **F_CPU:** Ensure your clock frequency is defined as `16000000UL`.

### Build Instructions
If using **avr-gcc** via command line:
```bash
# Compile drivers
avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -Os -c drivers/lcd.c -o drivers/lcd.o
avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -Os -c drivers/accel.c -o drivers/accel.o

# Compile main and link
avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -Os src/main.c drivers/lcd.o drivers/accel.o -o main.elf

# Create Hex file
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
```

---

## System Documentation
For detailed information on calibration, sensor offsets, and hardware wiring, please refer to:
**[Hardware Setup & Calibration Guide](hardware_setup.md)**

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

