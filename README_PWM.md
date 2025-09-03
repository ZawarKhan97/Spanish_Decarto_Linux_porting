# TC358870 PWM Brightness Control

This implementation provides screen brightness control for the TC358870 bridge on Jetson Orin NX Linux, equivalent to the STM32's hardware PWM functionality.

## Features

- **Continuous PWM Thread**: Runs in background continuously adjusting brightness
- **Smooth Transitions**: Gradual brightness changes (1% increments/decrements)
- **Thread-Safe**: Uses mutexes for safe access to shared variables
- **Graceful Shutdown**: Proper cleanup on program termination
- **Linux Sysfs Interface**: Uses `/sys/class/pwm/pwmchipX/` for PWM control

## PWM Configuration

The PWM parameters match the STM32 Timer 1 configuration:
- **Period**: 640 (htim1.Init.Period = 639 + 1)
- **Max Duty Cycle**: 13107 (sConfigOC.Pulse)
- **Update Rate**: 50ms (like STM32 timer)
- **Brightness Range**: 0-100%

## Files

- `tc358870_init.c` - Main program with integrated PWM thread
- `test_pwm.c` - Standalone PWM test program
- `Makefile` - Build configuration

## Building

```bash
# Build all programs
make all

# Build only main program
make tc358870_init

# Build only PWM test
make test_pwm

# Clean build files
make clean
```

## Usage

### Main Program (tc358870_init)

```bash
# Run with sudo for I2C access and kernel logging
sudo ./tc358870_init

# The program will:
# 1. Initialize TC358870 bridge
# 2. Start PWM thread for brightness control
# 3. Test brightness (20% -> 80% -> 50%)
# 4. Keep running with PWM thread active
# 5. Press Ctrl+C to exit gracefully
```

### PWM Test Program (test_pwm)

```bash
# Run standalone PWM test
./test_pwm

# Commands:
# b <0-100>  - Set brightness (0-100%)
# g           - Get current brightness
# q           - Quit
# Ctrl+C      - Exit gracefully
```

## PWM Thread Operation

1. **Initialization**: Finds available PWM chip, exports channel 0, sets period and duty cycle
2. **Continuous Loop**: Runs every 50ms checking for brightness changes
3. **Smooth Transitions**: Gradually adjusts current brightness towards target
4. **Hardware Control**: Writes duty cycle to sysfs PWM interface
5. **Thread Safety**: Uses mutexes to protect shared variables

## Hardware Requirements

- Jetson Orin NX with PWM support
- PWM chip accessible via `/sys/class/pwm/pwmchipX/`
- Appropriate permissions to access PWM sysfs files

## Signal Handling

The program handles:
- `SIGINT` (Ctrl+C) - Graceful shutdown
- `SIGTERM` - Clean termination

Both signals trigger proper cleanup of PWM thread and hardware.

## Troubleshooting

### No PWM Chip Found
- Check if PWM is enabled in device tree
- Verify `/sys/class/pwm/` directory exists
- Ensure proper permissions

### Permission Denied
- Run with sudo for I2C access
- Check PWM sysfs file permissions
- Verify user is in appropriate groups

### PWM Not Working
- Check PWM chip availability: `ls /sys/class/pwm/`
- Verify PWM export: `ls /sys/class/pwm/pwmchip0/`
- Check kernel logs: `dmesg | grep tc358870`

## Integration with STM32 Code

This implementation provides the same functionality as STM32's:
- `MX_TIM1_Init()` - Timer 1 initialization
- `HAL_TIM_PWM_Start()` - PWM start
- `sConfigOC.Pulse` - Duty cycle setting

The Linux version uses a background thread instead of hardware timer interrupts, but provides the same continuous PWM output.

## Example Output

```
[INFO] tc358870: Starting soft reset + interrupt mask clear
[INFO] tc358870: Step 1: Software Reset
[INFO] tc358870: I2C16: Successfully wrote 0x0004 to reg 0x0004
[INFO] tc358870: Waiting for software reset to complete...
[INFO] tc358870: I2C16: Successfully wrote 0x3F00 to reg 0x0002
[INFO] tc358870: I2C16: Successfully wrote 0x0000 to reg 0x0002
[INFO] tc358870: I2C16: Successfully wrote 0x0000 to reg 0x0006 (writable bits verified)
[INFO] tc358870: Step 2: HDMI Interrupt Configuration
[INFO] tc358870: I2C16: Successfully wrote 0x0F3F to reg 0x0016
[INFO] tc358870: I2C8: Successfully wrote 0xFF to reg 0x8502 (interrupt clear - no verify)
[INFO] tc358870: I2C8: Successfully wrote 0xFF to reg 0x850B (interrupt clear - no verify)
[INFO] tc358870: I2C16: Successfully wrote 0x0F3F to reg 0x0014 (interrupt status clear - no verify)
[INFO] tc358870: I2C8: Successfully wrote 0xFE to reg 0x8512 (interrupt mask - no verify)
[INFO] tc358870: I2C8: Successfully wrote 0xFD to reg 0x851B (interrupt mask - no verify)
[INFO] tc358870: Step 3: HDMI PHY Configuration
[INFO] tc358870: I2C8: Successfully wrote 0x03 to reg 0x8410
[INFO] tc358870: I2C8: Successfully wrote 0x3F to reg 0x8413
[INFO] tc358870: I2C8: Successfully wrote 0x07 to reg 0x8420
[INFO] tc358870: I2C8: Successfully wrote 0x31 to reg 0x84F0
[INFO] tc358870: I2C8: Successfully wrote 0x01 to reg 0x84F4
[INFO] tc358870: Step 4: HDMI Clock Configuration
[INFO] tc358870: I2C16: Successfully wrote 0x12C0 to reg 0x8540
[INFO] tc358870: I2C8: Successfully wrote 0x00 to reg 0x8630
[INFO] tc358870: I2C16: Successfully wrote 0x0753 to reg 0x8631
[INFO] tc358870: I2C8: Successfully wrote 0x02 to reg 0x8670
[INFO] tc358870: I2C16: Successfully wrote 0x12C0 to reg 0x8A0C
[INFO] tc358870: Step 5: EDID Configuration
[INFO] tc358870: I2C8: Successfully wrote 0x01 to reg 0x85E0
[INFO] tc358870: I2C16: Successfully wrote 0x0100 to reg 0x85E3
[INFO] tc358870: Waiting for EDID writes to complete...
[INFO] tc358870: Step 6: HDCP and HDMI System Configuration
[INFO] tc358870: I2C8: Successfully wrote 0x02 to reg 0x8543
[INFO] tc358870: I2C8: Successfully wrote 0x10 to reg 0x8544
[INFO] tc358870: Step 7: HDMI Audio Configuration
[INFO] tc358870: I2C8: Successfully wrote 0x00 to reg 0x8600
[INFO] tc358870: I2C8: Successfully wrote 0xF3 to reg 0x8602
[INFO] tc358870: I2C8: Successfully wrote 0x02 to reg 0x8603
[INFO] tc358870: I2C8: Successfully wrote 0x0C to reg 0x8604
[INFO] tc358870: I2C8: Successfully wrote 0x05 to reg 0x8606
[INFO] tc358870: I2C8: Successfully wrote 0x00 to reg 0x8607
[INFO] tc358870: I2C8: Successfully wrote 0x02 to reg 0x8652
[INFO] tc358870: Step 8: HPD/EDID Detection
[INFO] tc358870: HPD Status = 0x00
[INFO] tc358870: No HDMI cable detected. Skipping RS2.
[INFO] tc358870: Step 9: Final Configuration
[INFO] tc358870: I2C16: Successfully wrote 0x0F1F to reg 0x0016
[INFO] tc358870: I2C16: Successfully wrote 0x0001 to reg 0x0002
[INFO] tc358870: Init sequence completed successfully.
[INFO] tc358870: TC358870 RS1 init complete
[INFO] tc358870: Initializing PWM thread for brightness control...
[INFO] tc358870: Found PWM chip 0
[INFO] tc358870: PWM duty cycle set to 6553
[INFO] tc358870: PWM thread initialized successfully
[INFO] tc358870: PWM thread started successfully
[INFO] tc358870: Testing brightness control...
[INFO] tc358870: Brightness target set to 20%
[INFO] tc358870: PWM duty cycle set to 2621
[INFO] tc358870: Brightness target set to 80%
[INFO] tc358870: PWM duty cycle set to 10485
[INFO] tc358870: Brightness target set to 50%
[INFO] tc358870: PWM duty cycle set to 6553
[INFO] tc358870: Brightness control test complete. Current brightness: 50%
[INFO] tc358870: Program running with PWM thread. Press Ctrl+C to exit.
[INFO] tc358870: PWM thread is continuously adjusting brightness in background
```

## License

This code is provided as-is for educational and development purposes.
