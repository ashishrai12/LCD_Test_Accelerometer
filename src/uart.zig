const std = @import("std");

/// UART Driver for AVR (ATmega32/328P style)
/// Demonstrates direct register access with no hidden control flow.
pub const Uart = struct {
    const BAUD = 9600;
    const MYUBRR = (16000000 / 16 / BAUD) - 1;

    // Fixed addresses for ATmega328P as an example
    const UCSR0A = @as(*volatile u8, @ptrFromInt(0xC0));
    const UCSR0B = @as(*volatile u8, @ptrFromInt(0xC1));
    const UCSR0C = @as(*volatile u8, @ptrFromInt(0xC2));
    const UBRR0L = @as(*volatile u8, @ptrFromInt(0xC4));
    const UBRR0H = @as(*volatile u8, @ptrFromInt(0xC5));
    const UDR0 = @as(*volatile u8, @ptrFromInt(0xC6));

    pub fn init() void {
        UBRR0H.* = @intCast(MYUBRR >> 8);
        UBRR0L.* = @intCast(MYUBRR & 0xFF);
        UCSR0B.* = (1 << 3) | (1 << 4); // Enable TX/RX
        UCSR0C.* = (3 << 1); // 8n1
    }

    pub fn transmit(data: u8) void {
        while ((UCSR0A.* & (1 << 5)) == 0) {} // Wait for empty transmit buffer
        UDR0.* = data;
    }

    pub fn print(str: []const u8) void {
        for (str) |c| {
            transmit(c);
        }
    }
};
