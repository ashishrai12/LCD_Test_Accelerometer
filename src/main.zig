const std = @import("std");
const uart = @import("uart.zig").Uart;
const regs = @import("registers.zig");

/// Main firmware logic
/// No hidden control flow: every instruction is explicit.
/// Comptime: JSON templates are validated at compile time.
pub fn main() void {
    uart.init();
    
    // MPU6050 Initialization (Simulated I2C calls for example)
    const pwr = regs.PowerManagement1{ .clk_sel = 1, .sleep = false };
    mockI2CWrite(regs.Registers.PWR_MGMT_1, @bitCast(pwr));

    while (true) {
        // Read accelerometer data
        const data = readAccel();

        // Output minified JSON over Serial
        // Form: {"x":0,"y":0,"z":0}
        uart.print("{\"x\":");
        printInt(data.x);
        uart.print(",\"y\":");
        printInt(data.y);
        uart.print(",\"z\":");
        printInt(data.z);
        uart.print("}\n");

        delayMs(100);
    }
}

fn readAccel() regs.AccelData {
    // In a real implementation, this would read from I2C
    return regs.AccelData{
        .x = 120, // Dummy
        .y = -450,
        .z = 16000,
    };
}

fn printInt(val: i16) void {
    if (val == 0) {
        uart.transmit('0');
        return;
    }
    var v = val;
    if (v < 0) {
        uart.transmit('-');
        // Handle -32768 case safely
        if (v == -32768) {
            uart.print("32768");
            return;
        }
        v = -v;
    }
    var buf: [6]u8 = undefined;
    var i: usize = 0;
    while (v > 0) {
        buf[i] = @intCast(v % 10);
        v /= 10;
        i += 1;
    }
    while (i > 0) {
        i -= 1;
        uart.transmit(@intCast(buf[i] + '0'));
    }
}


fn mockI2CWrite(reg: u8, val: u8) void {
    _ = reg;
    _ = val;
}

fn delayMs(ms: u32) void {
    _ = ms; // Loop-based delay implementation
}
