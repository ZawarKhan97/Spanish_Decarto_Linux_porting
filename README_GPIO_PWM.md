# GPIO-Based PWM Control for TC358870

This implementation provides GPIO-based PWM control for screen brightness on Jetson Orin NX, using the PH.07 pin (GPIO41) as a fallback when hardware PWM is not available.

## Overview

The GPIO PWM system uses direct memory mapping to control the PH.07 pin, generating PWM signals by software-controlled timing. This provides the same functionality as the STM32's hardware PWM but implemented in software on Linux.

## Hardware Configuration

### Pin Configuration
- **Pin**: PH.07 (GPIO41)
- **Base Address**: 0x02434000 (GPIO4)
- **Function**: GPIO Output for PWM generation
- **PADCTL Value**: 0x00000004 (GPIO mode)

### Memory Mapping
- **GPIO4 Base**: 0x02434000
- **GPIO Size**: 0x1000 (4KB)
- **Output Register**: 0x000
- **Output Enable**: 0x004
- **PADCTL Offset**: 0x8C (for PH.07)

## Features

- **Software PWM Generation**: Creates PWM signals by toggling GPIO pin
- **Configurable Duty Cycle**: 0-100% brightness control
- **Thread-Safe Operation**: Uses mutexes for safe variable access
- **Real-time Control**: Immediate brightness changes
- **Fallback Support**: Automatically used when hardware PWM unavailable

## Implementation Details

### PWM Signal Generation
```c
void generate_pwm_signal(int duty_cycle) {
    // Calculate timing based on duty cycle
    int high_time_us = (duty_cycle * 1000) / PWM_MAX_DUTY;
    int low_time_us = 1000 - high_time_us;
    
    // Generate PWM cycle
    if (high_time_us > 0) {
        gpio_set_high();  // Set PH.07 HIGH
        usleep(high_time_us);
    }
    
    if (low_time_us > 0) {
        gpio_set_low();   // Set PH.07 LOW
        usleep(low_time_us);
    }
}
```

### GPIO Configuration
```c
// Configure PH.07 as GPIO output
volatile uint32_t *padctl = gpio_regs + (0x8C / 4);
padctl[0] = 0x00000004;  // GPIO mode

// Set as output (clear bit 7 in OE register)
volatile uint32_t *oe_reg = gpio_regs + (0x004 / 4);
oe_reg[0] &= ~(1U << 7);
```

## Files

- `tc358870_init.c` - Main program with integrated GPIO PWM fallback
- `test_gpio_pwm.c` - Standalone GPIO PWM test program
- `Makefile` - Build configuration

## Building

```bash
# Build all programs
make all

# Build only GPIO PWM test
make test_gpio_pwm

# Clean build files
make clean
```

## Usage

### Main Program (tc358870_init)
```bash
# Run with sudo for I2C and GPIO access
sudo ./tc358870_init

# The program will:
# 1. Try hardware PWM first
# 2. Fall back to GPIO PWM if hardware PWM unavailable
# 3. Initialize TC358870 bridge
# 4. Start PWM thread (hardware or GPIO)
# 5. Test brightness control
```

### GPIO PWM Test Program
```bash
# Run standalone GPIO PWM test
sudo ./test_gpio_pwm

# Commands:
# b <0-100>  - Set brightness (0-100%)
# g           - Get current brightness
# q           - Quit
# Ctrl+C      - Exit gracefully
```

## PWM Parameters

- **Period**: 1000μs (1ms)
- **Frequency**: 1kHz
- **Duty Cycle Range**: 0-100%
- **Resolution**: 1% increments
- **Update Rate**: 50ms (like STM32)

## Integration with STM32 Code

This GPIO PWM implementation provides equivalent functionality to STM32's:
- **Hardware Timer**: Replaced with software timing loops
- **PWM Output**: Replaced with GPIO pin toggling
- **Duty Cycle Control**: Same 0-100% range
- **Continuous Operation**: Same background thread approach

## Advantages of GPIO PWM

1. **Hardware Independence**: Works on any system with GPIO access
2. **No Hardware Dependencies**: Doesn't require specific PWM hardware
3. **Flexible Timing**: Can adjust PWM frequency and resolution
4. **Debug Visibility**: Easy to monitor with oscilloscope or logic analyzer
5. **Fallback Support**: Automatic fallback when hardware PWM unavailable

## Limitations

1. **CPU Usage**: Software timing consumes CPU cycles
2. **Timing Accuracy**: Less precise than hardware PWM
3. **Frequency Limits**: Limited by software timing resolution
4. **Jitter**: May have slight timing variations

## Troubleshooting

### Permission Denied
```bash
# Run with sudo for GPIO access
sudo ./test_gpio_pwm
```

### GPIO Not Working
- Check if PH.07 is available: `ls /sys/class/gpio/`
- Verify memory mapping permissions
- Check kernel logs: `dmesg | grep gpio`

### PWM Signal Issues
- Use oscilloscope to verify PWM output
- Check duty cycle calculations
- Verify timing delays

### Memory Mapping Errors
- Ensure /dev/mem is accessible
- Check if running with sufficient privileges
- Verify GPIO base address is correct

## Testing

### Hardware Test
1. Connect oscilloscope to PH.07 pin
2. Run test program with different brightness values
3. Verify PWM signal characteristics:
   - Frequency: ~1kHz
   - Duty cycle: 0-100% range
   - Signal integrity: clean transitions

### Software Test
1. Run brightness test sequence
2. Verify immediate response to commands
3. Check thread safety with rapid changes
4. Test graceful shutdown

## Example Output

```
GPIO PWM Test Program for PH.07 (GPIO41)
========================================
Initializing GPIO PWM on PH.07 (GPIO41)...
Original PADCTL[PH.07]: 0x00000000
Configured PADCTL[PH.07]: 0x00000004
PH.07 configured as output
GPIO PWM initialized successfully

GPIO PWM is running on PH.07 (GPIO41).
Commands:
  b <0-100>  - Set brightness (0-100%)
  g           - Get current brightness
  q           - Quit
  Ctrl+C      - Exit gracefully

Running test sequence...
Brightness set to 20%
Brightness set to 80%
Brightness set to 50%
Test sequence complete

GPIO_PWM> b 75
Brightness set to 75%
GPIO_PWM> g
Current brightness: 75%
GPIO_PWM> q
User requested exit
Cleaning up GPIO...
GPIO cleanup complete
Program terminated.
```

## Safety Considerations

1. **Voltage Levels**: Ensure PH.07 output voltage is compatible with connected devices
2. **Current Limits**: Check GPIO pin current rating
3. **Cleanup**: Always run cleanup to set GPIO low before exit
4. **Interrupts**: GPIO PWM may interfere with other GPIO operations

## Future Enhancements

1. **Multiple GPIO Pins**: Support for additional PWM outputs
2. **Configurable Frequency**: Adjustable PWM frequency
3. **Hardware Acceleration**: Use hardware timers when available
4. **Real-time Priority**: Higher priority thread for better timing

## License

This code is provided as-is for educational and development purposes.
