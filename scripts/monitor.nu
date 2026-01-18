#!/usr/bin/env nu

# MPU6050 Terminal Monitor
# Parses JSON stream from Serial and displays a dashboard

def main [port: string = "/dev/ttyUSB0"] {
    print $"Opening Serial port ($port)..."
    
    # Open serial port and read line by line
    # Note: On Windows this might be COMx
    open $port 
    | lines 
    | each { |line|
        try {
            # Parse minified JSON from firmware
            let data = ($line | from json)
            
            # Use 'upsert' to add a dynamic Status column based on tilt
            let processed = ($data | upsert status { |row|
                if ($row.x | into int | abs) > 2000 or ($row.y | into int | abs) > 2000 {
                    "Tilted"
                } else {
                    "Level"
                }
            })
            
            # Print to a terminal-based dashboard (table format)
            clear
            print "=== MPU6050 Zig-Systems Monitor ==="
            print $processed
        } catch {
            # Ignore malformed packets during startup
        }
    }
}
