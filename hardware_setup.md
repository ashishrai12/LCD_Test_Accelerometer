# Hardware Setup & Calibration Guide

This document provides detailed instructions on how to wire the hardware and calibrate the accelerometer for accurate readings.

## Hardware Wiring

### Power Requirements
- **MCU & LCD:** 5.0V VCC.
- **Sensor (ADXL335):** Most modules require **3.3V**. Connecting 5V directly to the sensor may damage it. Check your module's datasheet or regulator.

### 1. LCD Connection (8-bit Mode)
| LCD Pin | Symbol | MCU Pin | Notes |
| :--- | :--- | :--- | :--- |
| 1 | VSS | GND | |
| 2 | VDD | 5V | |
| 3 | VO | Potentiometer | Contrast Adjustment |
| 4 | RS | PORTB.0 | |
| 5 | RW | PORTB.1 | Set to 0 (GND) for write-only |
| 6 | E | PORTB.2 | |
| 7-14 | D0-D7 | PORTC.0-7 | 8-bit Data Bus |

### 2. Accelerometer Connection
| Sensor Pin | MCU Pin | Function |
| :--- | :--- | :--- |
| VCC | 3.3V / 5V | Power |
| GND | GND | Ground |
| X-Out | PORTA.0 (ADC0) | Analog X axis |
| Y-Out | PORTA.1 (ADC1) | Analog Y axis |
| Z-Out | PORTA.2 (ADC2) | Analog Z axis |

---

## Accelerometer Calibration

Analog accelerometers output a voltage relative to gravity ($1g$). To get meaningful results, you must determine the **Zero-G Offset** and **Sensitivity**.

### 1. Determining Offset (Zero-G)
The center value (when the axis is horizontal) is typically half of the supply voltage.
- For an 8-bit ADC ($0-255$ range), a perfect $0g$ output should be around **127**.
- In reality, the sensor might output **132** at rest. This value is your **Offset**.

### 2. Sensitivity Calculation
- **1g Value:** Rotate the sensor so the axis is vertical (pointing down). Note the value (e.g., **165**).
- **-1g Value:** Flip it $180^\circ$. Note the value (e.g., **99**).
- **Scale Factor:** $(\text{Value at } 1g - \text{Value at } -1g) / 2$.
  - In this case: $(165 - 99) / 2 = 33$ units per $g$.

### 3. Applying in Code
To convert the raw ADC value to G-force:
$$G = \frac{\text{ADC\_Value} - \text{Offset}}{\text{Sensitivity}}$$

Example implementation (not included in the basic driver):
```c
float g_x = (float)(raw_x - 132) / 33.0;
```

---

## Common Issues
- **Flickering LCD:** Usually caused by a poor contrast pot or loose breadboard wires.
- **Static Values:** Ensure `ADMUX` is correctly switching channels. A small delay is required between switching the channel and starting the conversion.
- **Incorrect Precision:** This project uses `ADLAR=1` to read only the 8 most significant bits from `ADCH`. If you need 10-bit precision, you must clear `ADLAR` and read the `ADC` register (or `ADCL` then `ADCH`).

