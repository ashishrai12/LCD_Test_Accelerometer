const std = @import("std");

/// MPU6050 Register Map
/// Demonstrated using Zig's packed structs for bit-level memory layout control.
pub const Registers = struct {
    pub const DEVICE_ADDR = 0x68;

    pub const CONFIG = 0x1A;
    pub const GYRO_CONFIG = 0x1B;
    pub const ACCEL_CONFIG = 0x1C;
    pub const PWR_MGMT_1 = 0x6B;
    pub const WHO_AM_I = 0x75;

    // Data Registers
    pub const ACCEL_XOUT_H = 0x3B;
    pub const TEMP_OUT_H = 0x41;
    pub const GYRO_XOUT_H = 0x43;
};

/// Power Management 1 Register
/// Using a packed struct ensures the bits match the hardware datasheet exactly.
pub const PowerManagement1 = packed struct(u8) {
    clk_sel: u3 = 0,
    temp_dis: bool = false,
    _reserved: u1 = 0,
    cycle: bool = false,
    sleep: bool = false,
    device_reset: bool = false,
};

/// Accelerometer Configuration Register
pub const AccelConfig = packed struct(u8) {
    _reserved: u3 = 0,
    afs_sel: u2 = 0, // 0: 2g, 1: 4g, 2: 8g, 3: 16g
    za_st: bool = false,
    ya_st: bool = false,
    xa_st: bool = false,
};

/// Raw Sensor Data
/// 16-bit signed integers in Big Endian format from the MPU6050
pub const AccelData = struct {
    x: i16,
    y: i16,
    z: i16,

    pub fn isLevel(self: AccelData) bool {
        // Simple heuristic for "Level"
        const threshold = 1000;
        return @abs(self.x) < threshold and @abs(self.y) < threshold;
    }
};
