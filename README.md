# Zig-Systems Accelerometer Monitor

[![Zig](https://img.shields.io/badge/Zig-0.11.0-orange.svg)](https://ziglang.org)
[![Nushell](https://img.shields.io/badge/Nushell-Integrated-blue.svg)](https://www.nushell.sh)
[![Build Status](https://github.com/ashishrai12/LCD_Test_Accelerometer/actions/workflows/ci.yml/badge.svg)](https://github.com/ashishrai12/LCD_Test_Accelerometer/actions)

A next-generation systems programming demonstration using **Zig** for firmware and **Nushell** for data orchestration. This project replaces the overhead of Python and C++ with explicit, memory-efficient systems tools.

---

## Technical Philosophy

### 1. No Hidden Control Flow
Unlike C++ or Python, Zig ensures that every CPU instruction is visible. There are no hidden allocations, no hidden function calls (via operators), and no preprocessor magic. What you see in the code is exactly what the hardware executes.

### 2. Comptime Mastery
The firmware leverages Zig's `comptime` to perform JSON template validation and register configuration at compile time, ensuring zero runtime overhead for static configurations.

### 3. Bit-Perfect Hardware Mapping
Using Zig's **packed structs**, we map the MPU6050 registers with bit-level precision, eliminating the need for manual bit-shifting and masking logic found in traditional C drivers.

---

## System Architecture

```mermaid
graph TD
    subgraph Firmware_Zig
        A[MPU6050 Packed Structs] --> B[I2C Driver]
        B --> C[JSON Serializer]
        C --> D[UART Out]
    end
    
    subgraph Data_Pipe_Nushell
        D -->|JSON Stream| E[Serial Input]
        E --> F[from json]
        F --> G[upsert Status]
        G --> H[Terminal Dashboard]
    end
```

---

## Project Structure
```text
LCD_Test_Accelerometer/
├── src/
│   ├── main.zig        # Firmware entry & JSON logic
│   ├── registers.zig   # MPU6050 Packed Struct registers
│   └── uart.zig        # Low-level UART implementation
├── scripts/
│   └── monitor.nu      # Nushell serial monitor & processor
├── legacy/
│   └── c_version/      # Archived original C firmware
└── README.md
```

---

## Getting Started

### 1. Build Firmware (Zig)
Requires Zig 0.11.0+.
```bash
zig build-exe src/main.zig -target avr-freestanding -mcpu atmega328p
```

### 2. Monitor Data (Nushell)
Ensure `nu` is installed.
```bash
nu scripts/monitor.nu /dev/ttyUSB0
```

---

## Data Protocol
The firmware outputs a minified, line-delimited JSON format to minimize UART bandwidth while maintaining high parseability:
```json
{"x":102,"y":-45,"z":16000}
```

---

## License
MIT



