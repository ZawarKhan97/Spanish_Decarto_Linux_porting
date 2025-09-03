# Power Sequence Test Program for TC358870

This program tests the power sequence functionality that mimics the STM32's power management for the TC358870 bridge, using GPIO pins PQ.05 and PZ.06 on Jetson Orin NX.

## Overview

The power sequence test program replicates the STM32's power management sequence:
1. **LCD_RESET_Pin** (PQ.05) - Controls LCD reset functionality
2. **LCD_EN_Pin** (PZ.06) - Controls LCD enable
3. **DSI_RESET_N_Pin** (PZ.06) - Controls DSI reset (same pin as LCD_EN)

## Hardware Configuration

### Pin Mapping
- **PQ.05** → **GPIO45** → **LCD_RESET_Pin**
- **PZ.06** → **GPIO46** → **LCD_EN_Pin** / **DSI_RESET_N_Pin**

### Memory Mapping
- **Base Address**: 0x02434000 (GPIO4)
- **PADCTL PQ.05**: 0x94 offset
- **PADCTL PZ.06**: 0x98 offset
- **GPIO Size**: 0x1000 (4KB)

## STM32 Power Sequence

Based on the STM32 code analysis, the power sequence follows this pattern:

```c
// STM32 equivalent sequence:
HAL_GPIO_WritePin(GPIOB, LCD_RESET_Pin, GPIO_PIN_SET);    // Step 1
HAL_Delay(100);                                            // 100ms delay
HAL_GPIO_WritePin(GPIOB, LCD_EN_Pin, GPIO_PIN_SET);       // Step 2
HAL_TIM_Base_Start(&htim1);                                // Start PWM
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);                  // Start PWM
HAL_GPIO_WritePin(GPIOB, DSI_RESET_N_Pin, GPIO_PIN_SET);  // Step 3
HAL_GPIO_WritePin(GPIOB, LCD_RESET_Pin, GPIO_PIN_RESET);  // Step 4
HAL_Delay(200);                                            // 200ms delay
HAL_GPIO_WritePin(GPIOB, LCD_RESET_Pin, GPIO_PIN_SET);    // Step 5
HAL_Delay(1000);                                           // 1 second delay
```

## Linux Implementation

The Linux version replicates this sequence using:
- **usleep()** instead of **HAL_Delay()**
- **Direct GPIO register access** instead of **HAL_GPIO_WritePin()**
- **Memory mapping** for GPIO control

## Features

### 1. Power Sequence Test
- **Automatic sequence execution** following STM32 timing
- **Step-by-step logging** for debugging
- **Proper timing delays** matching STM32 behavior

### 2. Continuous Toggle Test
- **Continuous pin toggling** for monitoring
- **Oscilloscope-friendly** output
- **Configurable cycle count**

### 3. Manual Control Mode
- **Individual pin control** for testing
- **Real-time pin manipulation**
- **Interactive command interface**

## Building

```bash
# Build all programs
make all

# Build only power sequence test
make test_power_sequence

# Clean build files
make clean
```

## Usage

### Running the Program
```bash
# Run with sudo for GPIO access
sudo ./test_power_sequence
```

### Test Options

#### 1. Power Sequence Test
- **Purpose**: Mimics STM32 power sequence exactly
- **Use case**: Verify power-up behavior matches STM32
- **Output**: Step-by-step execution log

#### 2. Continuous Toggle Test
- **Purpose**: Continuous pin toggling for monitoring
- **Use case**: Oscilloscope analysis, timing verification
- **Output**: 10 cycles of alternating pin states

#### 3. Manual Control Mode
- **Purpose**: Individual pin control for debugging
- **Use case**: Testing specific pin behavior
- **Commands**:
  - `pq5h` - Set PQ.05 HIGH
  - `pq5l` - Set PQ.05 LOW
  - `pz6h` - Set PZ.06 HIGH
  - `pz6l` - Set PZ.06 LOW
  - `q` - Quit manual mode

## Power Sequence Details

### Step-by-Step Breakdown

1. **LCD_RESET_Pin HIGH** (PQ.05)
   - Sets reset pin to active state
   - 100ms delay for stabilization

2. **LCD_EN_Pin HIGH** (PZ.06)
   - Enables LCD functionality
   - 100ms delay for enable

3. **DSI_RESET_N_Pin HIGH** (PZ.06)
   - Releases DSI reset (same pin as LCD_EN)
   - 100ms delay for DSI stabilization

4. **LCD_RESET_Pin LOW** (PQ.05)
   - Triggers LCD reset sequence
   - 200ms delay for reset completion

5. **LCD_RESET_Pin HIGH** (PQ.05)
   - Releases LCD reset
   - 1 second delay for system stabilization

### Timing Analysis

| Step | Action | Delay | Total Time |
|------|--------|-------|------------|
| 1    | LCD_RESET HIGH | 100ms | 100ms |
| 2    | LCD_EN HIGH | 100ms | 200ms |
| 3    | DSI_RESET HIGH | 100ms | 300ms |
| 4    | LCD_RESET LOW | 200ms | 500ms |
| 5    | LCD_RESET HIGH | 1000ms | 1500ms |

**Total Sequence Time**: 1.5 seconds

## GPIO Configuration

### PADCTL Settings
```c
// Configure as GPIO Output
padctl[0] = 0x00000004;  // GPIO mode, output enabled
```

### Output Enable Register
```c
// Clear bits for output mode
oe_reg[0] &= ~((1U << PQ5_BIT) | (1U << PZ6_BIT));
```

### Pin Control
```c
// Set HIGH
out_reg[0] |= (1U << PQ5_BIT);   // PQ.05 HIGH
out_reg[0] |= (1U << PZ6_BIT);   // PZ.06 HIGH

// Set LOW
out_reg[0] &= ~(1U << PQ5_BIT);  // PQ.05 LOW
out_reg[0] &= ~(1U << PZ6_BIT);  // PZ.06 LOW
```

## Testing and Verification

### Hardware Verification
1. **Connect oscilloscope** to PQ.05 and PZ.06
2. **Run power sequence test**
3. **Verify timing** matches STM32 sequence
4. **Check signal integrity** and voltage levels

### Software Verification
1. **Run automatic sequence** and verify timing
2. **Use manual mode** to test individual pins
3. **Verify GPIO configuration** in kernel logs
4. **Check for error messages** during execution

### Expected Output
```
=== Starting Power Sequence Test ===
Step 1: Setting LCD_RESET_Pin (PQ.05) HIGH...
PQ.05 set HIGH
Step 2: Setting LCD_EN_Pin (PZ.06) HIGH...
PZ.06 set HIGH
Step 3: Setting DSI_RESET_N_Pin (PZ.06) HIGH...
PZ.06 set HIGH
Step 4: Setting LCD_RESET_Pin (PQ.05) LOW...
PQ.05 set LOW
Step 5: Waiting 200ms for reset to complete...
Step 6: Setting LCD_RESET_Pin (PQ.05) HIGH...
PQ.05 set HIGH
Step 7: Waiting 1 second for system to stabilize...
=== Power Sequence Test Complete ===
```

## Troubleshooting

### Common Issues

#### Permission Denied
```bash
# Run with sudo for GPIO access
sudo ./test_power_sequence
```

#### GPIO Not Working
- Check if pins are available: `ls /sys/class/gpio/`
- Verify memory mapping permissions
- Check kernel logs: `dmesg | grep gpio`

#### Timing Issues
- Verify usleep() resolution on your system
- Check for system load affecting timing
- Use oscilloscope for precise timing verification

#### Pin Configuration Errors
- Verify PADCTL offsets are correct
- Check GPIO base address
- Ensure pins are not used by other drivers

### Debug Commands
```bash
# Check GPIO status
ls /sys/class/gpio/

# Monitor kernel messages
dmesg | tail -f

# Check memory mapping
cat /proc/maps | grep 02434000
```

## Integration with Main Program

Once verified working, this power sequence can be integrated into `tc358870_init.c`:

1. **Add GPIO initialization** to main program
2. **Call power sequence** before I2C initialization
3. **Maintain timing** and error handling
4. **Add cleanup** on program exit

## Safety Considerations

1. **Voltage Levels**: Ensure GPIO output voltage is compatible
2. **Current Limits**: Check GPIO pin current rating
3. **Timing**: Maintain proper delays for device stability
4. **Cleanup**: Always set pins low before exit
5. **Interference**: Avoid conflicts with other GPIO operations

## Future Enhancements

1. **Configurable timing**: Adjustable delays via command line
2. **Multiple sequences**: Support for different power-up modes
3. **Status monitoring**: Read back pin states for verification
4. **Error recovery**: Automatic retry on sequence failure
5. **Logging**: Persistent logging of power sequence events

## License

This code is provided as-is for educational and development purposes.
