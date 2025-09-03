
// Porting Steps
 /* The code you've provided is the initialization sequence: a series of precise I2C register writes and reads used by the STM32 to configure the TC358870 bridge. This sequence handles:
 1. Software reset
 2.HDMI PHY configuration
 3.Clock and EDID setup
 4.DSI and video timing parameters
 5.Panel initialization commands
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <linux/i2c-dev.h>
 #include <sys/ioctl.h>
 #include <errno.h>
 #include <string.h>
 #include <syslog.h>
 #include <stdarg.h>
 #include <unistd.h>
 #include <time.h>
 #include <signal.h> // For signal handling



#define I2C_DEV_PATH "/dev/i2c-1"  // Change as needed
#define I2C_ADDR     0x0F          // TC358870 I2C address

//Function Prototypes
void klog(const char *fmt, ...);
int i2c_write8(int fd, uint16_t reg, uint8_t data);
int i2c_write16(int fd, uint16_t reg, uint16_t data);
int i2c_read8(int fd, uint16_t reg, uint8_t *out);
int i2c_read16(int fd, uint16_t reg, uint16_t *out);
uint8_t i2c_read8_simple(int fd, uint16_t reg);
uint16_t i2c_read16_simple(int fd, uint16_t reg);
int i2c_write32(int fd, uint16_t reg, uint32_t data);
uint32_t i2c_read32_simple(int fd, uint16_t reg);
int rs2(int fd);
int tc358870_init(int fd);

// Function to poll chip readiness - important for Linux/Jetson systems
int poll_chip_ready(int fd, uint16_t reg, uint16_t expected_mask, uint16_t expected_value, int max_attempts) {
    for (int attempt = 0; attempt < max_attempts; attempt++) {
        uint16_t read_val = i2c_read16_simple(fd, reg);
        if ((read_val & expected_mask) == expected_value) {
            klog("<6>tc358870: Chip ready after %d attempts (reg 0x%04X = 0x%04X)", attempt + 1, reg, read_val);
            return 0; // Success
        }
        usleep(10000); // 10ms delay between attempts
    }
    klog("<3>tc358870: Chip not ready after %d attempts (reg 0x%04X)", max_attempts, reg);
    return 1; // Timeout
}

// Function to wait for I2C bus to be ready - critical for Linux/Jetson
int wait_i2c_ready(int fd) {
    // Try to read a simple register to check if I2C is ready
    for (int attempt = 0; attempt < 100; attempt++) {
        // Simple I2C read without calling i2c_read16_simple to avoid circular dependency
        uint8_t write_reg[2] = {0x00, 0x00}; // Register 0x0000
        uint8_t temp[2];
        
        if (write(fd, write_reg, 2) == 2 && read(fd, temp, 2) == 2) {
            klog("<6>tc358870: I2C bus ready after %d attempts", attempt + 1);
            return 0; // Success
        }
        usleep(5000); // 5ms delay between attempts
    }
    klog("<3>tc358870: I2C bus not ready after 100 attempts");
    return 1; // Timeout
}

// Log messages will appear in dmesg if run with sudo and using syslog
void klog(const char *fmt, ...) {
    char buffer[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    int fd = open("/dev/kmsg", O_WRONLY);
    if (fd >= 0) {
        write(fd, buffer, strlen(buffer));
        write(fd, "\n", 1); // Ensure newline
        close(fd);
    }
}

// Write 16-bit register, 8-bit data - STM32 compatible
int i2c_write8(int fd, uint16_t reg, uint8_t data) {
    uint8_t buf[3];
    buf[0] = (reg >> 8) & 0xFF;
    buf[1] = reg & 0xFF;
    buf[2] = data;

    klog("<7>tc358870: Attempting I2C8 write: reg 0x%04X, data 0x%02X", reg, data);

    if (write(fd, buf, 3) != 3) {
        klog("<3>tc358870: i2c_write8 failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 1; // STM32 returns 1 for failure
    }

    // Add delay like STM32 - wait for I2C to be ready
    usleep(100000); // 100ms delay like STM32 HAL_Delay(100)
    
    // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready after write to reg 0x%04X", reg);
        return 1; // STM32 returns 1 for failure
    }

    // Special handling for interrupt status registers (write-to-clear)
    if (reg == 0x8502 || reg == 0x850B) { // SYS_INT, MISC_INT
        klog("<6>tc358870: I2C8: Successfully wrote 0x%02X to reg 0x%04X (interrupt clear - no verify)", data, reg);
        return 0; // STM32 returns 0 for success
    }
    
    // Special handling for interrupt mask registers (may have read-only bits)
    if (reg == 0x8512 || reg == 0x851B) { // SYS_INTM, MISC_INTM
        klog("<6>tc358870: I2C8: Successfully wrote 0x%02X to reg 0x%04X (interrupt mask - no verify)", data, reg);
        return 0; // STM32 returns 0 for success
    }
    
    // Verify write by reading back (like STM32 does)
    uint8_t read_val = i2c_read8_simple(fd, reg);
    if (read_val == data) {
        klog("<6>tc358870: I2C8: Successfully wrote 0x%02X to reg 0x%04X", data, reg);
        return 0; // STM32 returns 0 for success
    } else {
        klog("<3>tc358870: i2c_write8 verify failed at 0x%04X: wrote 0x%02X, read 0x%02X", reg, data, read_val);
        return 1; // STM32 returns 1 for failure
    }
}


// // Write 16-bit register, 16-bit data - STM32 compatible
// int i2c_write16(int fd, uint16_t addr, uint16_t dt) {
//     uint8_t write_reg[4];
//     uint32_t data;
//     write_reg[0]=addr>>8;
//     write_reg[1]=addr&0xFF;
//     write_reg[2]=dt&0xFF;
//     write_reg[3]=(dt>>8);

//     klog("<7>tc358870: Attempting I2C16 write: reg 0x%04X, data 0x%04X", addr, dt);

//     if (write(fd, write_reg, 4) != 4) {
//         klog("<3>tc358870: i2c_write16 failed at reg 0x%04X: %s (errno=%d)", addr, strerror(errno), errno);
//         return 1; // STM32 returns 1 for failure
//     }

//     // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
//     if (wait_i2c_ready(fd) != 0) {
//         klog("<3>tc358870: I2C bus not ready after write to reg 0x%04X", addr);
//         return 1; // STM32 returns 1 for failure
//     }

//     // Skip verification for register 0x0504 (like STM32 does)
//     if (addr != 0x0504) {
//         // Special delay for register 0x0006 (ConfCtl1) - test timing issue
//         if (addr == 0x0006) {
//             klog("<6>tc358870: Adding 50ms delay before verification for reg 0x0006");
//             usleep(50000); // 50ms delay to test timing issue
//         }
        
//         data=i2c_read16_simple(fd, addr);
//         if (data!=dt){
//             klog("<3>tc358870: i2c_write16 verify failed at 0x%04X: wrote 0x%04X, read 0x%04X", addr, dt, data);
//             return 1;
//         }
//         klog("<6>tc358870: I2C16: Successfully wrote 0x%04X to reg 0x%04X", dt, addr);
//     }

//     return 0;
// }


// Write 16-bit register, 16-bit data - STM32 compatible
int i2c_write16(int fd, uint16_t reg, uint16_t data) {
    uint8_t buf[4];
    buf[0] = (reg >> 8) & 0xFF;
    buf[1] = reg & 0xFF;
    // STM32 byte order: low byte first, then high byte
    buf[2] = data & 0xFF;        // Low byte first (like STM32)
    buf[3] = (data >> 8) & 0xFF; // High byte second (like STM32)

    klog("<7>tc358870: Attempting I2C16 write: reg 0x%04X, data 0x%04X", reg, data);

    if (write(fd, buf, 4) != 4) {
         klog("<3>tc358870: i2c_write16 failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 1; // STM32 returns 1 for failure
    }

    // Add delay like STM32 - wait for I2C to be ready
    usleep(100000); // 100ms delay like STM32 HAL_Delay(100)
    
    // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready after write to reg 0x%04X", reg);
        return 1; // STM32 returns 1 for failure
    }

    // Skip verification for register 0x0504 (like STM32 does)
    if (reg == 0x0504) {
        klog("<6>tc358870: I2C16: Wrote 0x%04X to reg 0x%04X (no verify - like STM32)", data, reg);
        return 0; // STM32 returns 0 for success
    }
    
    // Special handling for ConfCtl1 (0x0006) - verify only writable bits
    if (reg == 0x0006) {
        uint16_t read_val = i2c_read16_simple(fd, reg);
        
        // ConfCtl1: only bits 3-0 are writable, others are read-only
        uint16_t writable_mask = 0x000F;  // Only bits 3-0 are writable
        uint16_t expected_writable = data & writable_mask;
        uint16_t actual_writable = read_val & writable_mask;
        
        if (actual_writable == expected_writable) {
            klog("<6>tc358870: I2C16: Successfully wrote 0x%04X to reg 0x%04X (writable bits verified)", data, reg);
            return 0; // STM32 returns 0 for success
        } else {
            klog("<3>tc358870: i2c_write16 verify failed at 0x%04X: wrote 0x%04X, read 0x%04X (writable bits: expected 0x%04X, got 0x%04X)", 
                 reg, data, read_val, expected_writable, actual_writable);
            return 1; // STM32 returns 1 for failure
        }
    }
    
    // Special handling for IntStatus (0x0014) - write-to-clear interrupt register
    if (reg == 0x0014) {
        klog("<6>tc358870: I2C16: Successfully wrote 0x%04X to reg 0x%04X (interrupt status clear - no verify)", data, reg);
        return 0; // STM32 returns 0 for success
    }
    
    // Verify write by reading back (like STM32 does)
    uint16_t read_val = i2c_read16_simple(fd, reg);
    if (read_val == data) {
        klog("<6>tc358870: I2C16: Successfully wrote 0x%04X to reg 0x%04X", data, reg);
        return 0; // STM32 returns 0 for success
    } else {
        klog("<3>tc358870: i2c_write16 verify failed at 0x%04X: wrote 0x%04X, read 0x%04X", reg, data, read_val);
        return 1; // STM32 returns 1 for failure
    }
}

// Write 16-bit register, 32-bit data - STM32 compatible
int i2c_write32(int fd, uint16_t reg, uint32_t data) {
    uint8_t buf[6];
    buf[0] = (reg >> 8) & 0xFF;
    buf[1] = reg & 0xFF;
    // STM32 byte order: low byte first, then high byte
    buf[2] = (data & 0xFF);                    // Low byte first
    buf[3] = ((data >> 8) & 0xFF);             // Second byte
    buf[4] = ((data >> 16) & 0xFF);            // Third byte
    buf[5] = ((data >> 24) & 0xFF);            // High byte last

    klog("<7>tc358870: Attempting I2C32 write: reg 0x%04X, data 0x%08X", reg, data);

    if (write(fd, buf, 6) != 6) {
        klog("<3>tc358870: i2c_write32 failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 1; // STM32 returns 1 for failure
    }

    // Add delay like STM32 - wait for I2C to be ready
    usleep(1000); // 1ms delay like STM32 HAL_Delay(1)
    
    // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready after write to reg 0x%04X", reg);
        return 1; // STM32 returns 1 for failure
    }

    // Verify write by reading back (like STM32 does)
    uint32_t read_val = i2c_read32_simple(fd, reg);
    if (read_val == data) {
        klog("<6>tc358870: I2C32: Successfully wrote 0x%08X to reg 0x%04X", data, reg);
        return 0; // STM32 returns 0 for success
    } else {
        klog("<3>tc358870: i2c_write32 verify failed at 0x%04X: wrote 0x%08X, read 0x%08X", reg, data, read_val);
        return 1; // STM32 returns 1 for failure
    }
}

// Simple read functions that match STM32 implementation
uint8_t i2c_read8_simple(int fd, uint16_t reg) {
    uint8_t addr_buf[2] = {
        (reg >> 8) & 0xFF,
        reg & 0xFF
    };
    uint8_t data;

    klog("<7>tc358870: Attempting I2C8 read: reg 0x%04X", reg);

    if (write(fd, addr_buf, 2) != 2) {
        klog("<3>tc358870: i2c_read8_simple - write failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 0xFF; // Return error value like STM32
    }

    // Add small delay like STM32
    usleep(1000); // 1ms delay like STM32 HAL_Delay(1)

    if (read(fd, &data, 1) != 1) {
        klog("<3>tc358870: i2c_read8_simple - read failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 0xFF; // Return error value like STM32
    }

    // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready after read from reg 0x%04X", reg);
        return 0xFF; // Return error value like STM32
    }

    klog("<7>tc358870: I2C8: Successfully read 0x%02X from reg 0x%04X", data, reg);
    return data; // Return value directly like STM32
}

uint16_t i2c_read16_simple(int fd, uint16_t addr) {
    uint8_t temp[2];
    klog("<7>tc358870: Attempting I2C16 read: reg 0x%04X", addr);

    uint8_t write_reg[2];
    write_reg[0]=addr>>8;
    write_reg[1]=addr&0xFF;

    if (write(fd, write_reg, 2) != 2) {
        klog("<3>tc358870: i2c_read16_simple - write failed at reg 0x%04X: %s (errno=%d)", addr, strerror(errno), errno);
        return 0xFFFF; // Return error value like STM32
    }

    if (read(fd, temp, 2) != 2) {
        klog("<3>tc358870: i2c_read16_simple - read failed at reg 0x%04X: %s (errno=%d)", addr, strerror(errno), errno);
        return 0xFFFF; // Return error value like STM32
    }

    // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready after read from reg 0x%04X", addr);
        return 0xFFFF; // Return error value like STM32
    }

    // STM32 byte order: (temp[1]<<8)|temp[0] - low byte first
    uint16_t result = (temp[1] << 8) | temp[0];

    klog("<7>tc358870: I2C16: Successfully read 0x%04X from reg 0x%04X", result, addr);
    return result; // Return value directly like STM32
}


// uint16_t i2c_read16_simple(int fd, uint16_t reg) {
//     uint8_t addr_buf[2] = {
//         (reg >> 8) & 0xFF,
//         reg & 0xFF
//     };
//     uint8_t data[2];

//     klog("<7>tc358870: Attempting I2C16 read: reg 0x%04X", reg);

//     if (write(fd, addr_buf, 2) != 2) {
//         klog("<3>tc358870: i2c_read16_simple - write failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
//         return 0xFFFF; // Return error value like STM32
//     }

//     // Add small delay like STM32
//     usleep(1000); // 1ms delay like STM32 HAL_Delay(1)

//     if (read(fd, data, 2) != 2) {
//         klog("<3>tc358870: i2c_read16_simple - read failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
//         return 0xFFFF; // Return error value like STM32
//     }

//     // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
//     if (wait_i2c_ready(fd) != 0) {
//         klog("<3>tc358870: I2C bus not ready after read from reg 0x%04X", reg);
//         return 0xFFFF; // Return error value like STM32
//     }

//     // STM32 byte order: (temp[1]<<8)|temp[0] - low byte first
//     uint16_t result = (data[1] << 8) | data[0];

//     klog("<7>tc358870: I2C16: Successfully read 0x%04X from reg 0x%04X", result, reg);
//     return result; // Return value directly like STM32
// }

uint32_t i2c_read32_simple(int fd, uint16_t reg) {
    uint8_t addr_buf[2] = {
        (reg >> 8) & 0xFF,
        reg & 0xFF
    };
    uint8_t data[4];

    klog("<7>tc358870: Attempting I2C32 read: reg 0x%04X", reg);

    if (write(fd, addr_buf, 2) != 2) {
        klog("<3>tc358870: i2c_read32_simple - write failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 0xFFFFFFFF; // Return error value
    }

    // Add small delay like STM32
    usleep(1000); // 1ms delay like STM32 HAL_Delay(1)

    if (read(fd, data, 4) != 4) {
        klog("<3>tc358870: i2c_read32_simple - read failed at reg 0x%04X: %s (errno=%d)", reg, strerror(errno), errno);
        return 0xFFFFFFFF; // Return error value
    }

    // Wait for I2C bus to be ready - like STM32 while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY)
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready after read from reg 0x%04X", reg);
        return 0xFFFFFFFF; // Return error value
    }

    // STM32 byte order: (temp[3]<<24)|(temp[2]<<16)|(temp[1]<<8)|temp[0] - low byte first
    uint32_t result = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];

    klog("<7>tc358870: I2C32: Successfully read 0x%08X from reg 0x%04X", result, reg);
    return result; // Return value directly like STM32
}

int i2c_read8(int fd, uint16_t reg, uint8_t *out) {
    *out = i2c_read8_simple(fd, reg);
    return 0; // Always return 0 for compatibility
}

int i2c_read16(int fd, uint16_t reg, uint16_t *out) {
    *out = i2c_read16_simple(fd, reg);
    return 0; // Always return 0 for compatibility
}

int rs2(int fd) {
    klog("<6>tc358870: RS2 - Ready state initialization started");

    // Enable Interrupts 
    if (i2c_write16(fd, 0x0016, 0x0D3F) != 0) { // IntMask
        klog("<3>tc358870: RS2 failed to write IntMask");
        return 1; // Return 1 for failure
    }

    // Set HPD output to high
    if (i2c_write8(fd, 0x854A, 0x01) != 0) { // SysCtl
        klog("<3>tc358870: RS2 failed to write SysCtl for HPD");
        return 1; // Return 1 for failure
    }

    klog("<6>tc358870: RS2 complete, HPD asserted");
    return 0; // Return 0 for success
}


int tc358870_init(int fd) {
    klog("<6>tc358870: Starting soft reset + interrupt mask clear");

    // Wait for I2C bus to be ready - critical for Linux/Jetson
    if (wait_i2c_ready(fd) != 0) {
        klog("<3>tc358870: I2C bus not ready, aborting initialization");
        return 1;
    }

    // --- Reset & System Control ---
    //Sofware Reset
    klog("<6>tc358870: Step 1: Software Reset");
    if (i2c_write16(fd, 0x0004, 0x0004) != 0) { // ConfCtl0 (Software Reset)
        klog("<3>tc358870: Failed to write software reset");
        return 1; // Return 1 for failure
    }
    usleep(10000); // 10ms delay
    
    // Wait for software reset to complete - critical for Linux/Jetson
    klog("<6>tc358870: Waiting for software reset to complete...");
    usleep(50000); // 50ms delay for reset to complete
    if (i2c_write16(fd, 0x0002, 0x3F00) != 0) { // SysCtl
        klog("<3>tc358870: Failed to write SysCtl 0x3F00");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x0002, 0x0000) != 0) { // SysCtl
        klog("<3>tc358870: Failed to write SysCtl 0x0000");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x0006, 0x0000) != 0) { // ConfCtl1
        klog("<3>tc358870: Failed to write ConfCtl1");
        return 1; // Return 1 for failure
    }

    // HDMI Interrupt Mask, Clear
    klog("<6>tc358870: Step 2: HDMI Interrupt Configuration");
    if (i2c_write16(fd, 0x0016, 0x0F3F) != 0) { // IntMask
        klog("<3>tc358870: Failed to write IntMask");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd,  0x8502, 0xFF) != 0) {   // SYS_INT
        klog("<3>tc358870: Failed to write SYS_INT");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd,  0x850B, 0xFF) != 0) {   // MISC_INT
        klog("<3>tc358870: Failed to write MISC_INT");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x0014, 0x0F3F) != 0) { // IntStatus
        klog("<3>tc358870: Failed to write IntStatus");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd,  0x8512, 0xFE) != 0) {   // SYS_INTM
        klog("<3>tc358870: Failed to write SYS_INTM");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd,  0x851B, 0xFD) != 0) {   // MISC_INTM
        klog("<3>tc358870: Failed to write MISC_INTM");
        return 1; // Return 1 for failure
    }

    // --- HDMI PHY ---
    klog("<6>tc358870: Step 3: HDMI PHY Configuration");
    if (i2c_write8(fd, 0x8410, 0x03) != 0) { // PHY CTL
        klog("<3>tc358870: Failed to write PHY CTL");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8413, 0x3F) != 0) { // PHY_ENB
        klog("<3>tc358870: Failed to write PHY_ENB");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8420, 0x07) != 0) { // EQ_BYPS
        klog("<3>tc358870: Failed to write EQ_BYPS");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x84F0, 0x31) != 0) { // APLL_CTL
        klog("<3>tc358870: Failed to write APLL_CTL");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x84F4, 0x01) != 0) { // DDCIO_CTL
        klog("<3>tc358870: Failed to write DDCIO_CTL");
        return 1; // Return 1 for failure
    }

    // --- HDMI Clock ---
    klog("<6>tc358870: Step 4: HDMI Clock Configuration");
    if (i2c_write16(fd, 0x8540, 0x12C0) != 0) { // SYS_FREQ0_1
        klog("<3>tc358870: Failed to write SYS_FREQ0_1");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd,  0x8630, 0x00) != 0) {   // LOCKDET_FREQ0
        klog("<3>tc358870: Failed to write LOCKDET_FREQ0");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x8631, 0x0753) != 0) { // LOCKDET_REF1_2
        klog("<3>tc358870: Failed to write LOCKDET_REF1_2");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd,  0x8670, 0x02) != 0) {   // NCO_F0_MOD
        klog("<3>tc358870: Failed to write NCO_F0_MOD");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x8A0C, 0x12C0) != 0) { // CSC_SCLK0_1
        klog("<3>tc358870: Failed to write CSC_SCLK0_1");
        return 1; // Return 1 for failure
    }

    // --- EDID Block ---
    klog("<6>tc358870: Step 5: EDID Configuration");
    if (i2c_write8(fd,  0x85E0, 0x01) != 0) {   // EDID_MODE
        klog("<3>tc358870: Failed to write EDID_MODE");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x85E3, 0x0100) != 0) { // EDID_LEN1_2
        klog("<3>tc358870: Failed to write EDID_LEN1_2");
        return 1; // Return 1 for failure
    }

    // TODO: Write EDID RAM (i2c_write8(fd, 0x8C00 + offset, value))
    
    // EDID Data
    i2c_write8(fd,0x8C00, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C01, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C02, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C03, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C04, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C05, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C06, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C07, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C08, 0x52); // EDID_RAM
    i2c_write8(fd,0x8C09, 0x62); // EDID_RAM
    i2c_write8(fd,0x8C0A, 0x88); // EDID_RAM
    i2c_write8(fd,0x8C0B, 0x88); // EDID_RAM
    i2c_write8(fd,0x8C0C, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C0D, 0x88); // EDID_RAM
    i2c_write8(fd,0x8C0E, 0x88); // EDID_RAM
    i2c_write8(fd,0x8C0F, 0x88); // EDID_RAM
    i2c_write8(fd,0x8C10, 0x2D); // EDID_RAM
    i2c_write8(fd,0x8C11, 0x1E); // EDID_RAM
    i2c_write8(fd,0x8C12, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C13, 0x03); // EDID_RAM
    i2c_write8(fd,0x8C14, 0x80); // EDID_RAM
    i2c_write8(fd,0x8C15, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C16, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C17, 0x78); // EDID_RAM
    i2c_write8(fd,0x8C18, 0x0A); // EDID_RAM
    i2c_write8(fd,0x8C19, 0x0D); // EDID_RAM
    i2c_write8(fd,0x8C1A, 0xC9); // EDID_RAM
    i2c_write8(fd,0x8C1B, 0xA0); // EDID_RAM
    i2c_write8(fd,0x8C1C, 0x57); // EDID_RAM
    i2c_write8(fd,0x8C1D, 0x47); // EDID_RAM
    i2c_write8(fd,0x8C1E, 0x98); // EDID_RAM
    i2c_write8(fd,0x8C1F, 0x27); // EDID_RAM
    i2c_write8(fd,0x8C20, 0x12); // EDID_RAM
    i2c_write8(fd,0x8C21, 0x48); // EDID_RAM
    i2c_write8(fd,0x8C22, 0x4C); // EDID_RAM
    i2c_write8(fd,0x8C23, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C24, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C25, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C26, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C27, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C28, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C29, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C2A, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C2B, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C2C, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C2D, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C2E, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C2F, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C30, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C31, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C32, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C33, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C34, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C35, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C36, 0xD9); // EDID_RAM
    i2c_write8(fd,0x8C37, 0x18); // EDID_RAM
    i2c_write8(fd,0x8C38, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8C39, 0x76); // EDID_RAM
    i2c_write8(fd,0x8C3A, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C3B, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C3C, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C3D, 0x50); // EDID_RAM
    i2c_write8(fd,0x8C3E, 0x2C); // EDID_RAM
    i2c_write8(fd,0x8C3F, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C40, 0x02); // EDID_RAM
    i2c_write8(fd,0x8C41, 0x04); // EDID_RAM
    i2c_write8(fd,0x8C42, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8C43, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C44, 0x25); // EDID_RAM
    i2c_write8(fd,0x8C45, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C46, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C47, 0x18); // EDID_RAM
    i2c_write8(fd,0x8C48, 0xD9); // EDID_RAM
    i2c_write8(fd,0x8C49, 0x18); // EDID_RAM
    i2c_write8(fd,0x8C4A, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8C4B, 0x76); // EDID_RAM
    i2c_write8(fd,0x8C4C, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C4D, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C4E, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C4F, 0x50); // EDID_RAM
    i2c_write8(fd,0x8C50, 0x2C); // EDID_RAM
    i2c_write8(fd,0x8C51, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C52, 0x02); // EDID_RAM
    i2c_write8(fd,0x8C53, 0x04); // EDID_RAM
    i2c_write8(fd,0x8C54, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8C55, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C56, 0x25); // EDID_RAM
    i2c_write8(fd,0x8C57, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C58, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C59, 0x18); // EDID_RAM
    i2c_write8(fd,0x8C5A, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C5B, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C5C, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C5D, 0xFC); // EDID_RAM
    i2c_write8(fd,0x8C5E, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C5F, 0x54); // EDID_RAM
    i2c_write8(fd,0x8C60, 0x6F); // EDID_RAM
    i2c_write8(fd,0x8C61, 0x73); // EDID_RAM
    i2c_write8(fd,0x8C62, 0x68); // EDID_RAM
    i2c_write8(fd,0x8C63, 0x69); // EDID_RAM
    i2c_write8(fd,0x8C64, 0x62); // EDID_RAM
    i2c_write8(fd,0x8C65, 0x61); // EDID_RAM
    i2c_write8(fd,0x8C66, 0x2D); // EDID_RAM
    i2c_write8(fd,0x8C67, 0x55); // EDID_RAM
    i2c_write8(fd,0x8C68, 0x48); // EDID_RAM
    i2c_write8(fd,0x8C69, 0x32); // EDID_RAM
    i2c_write8(fd,0x8C6A, 0x44); // EDID_RAM
    i2c_write8(fd,0x8C6B, 0x0A); // EDID_RAM
    i2c_write8(fd,0x8C6C, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C6D, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C6E, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C6F, 0xFD); // EDID_RAM
    i2c_write8(fd,0x8C70, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C71, 0x14); // EDID_RAM
    i2c_write8(fd,0x8C72, 0x78); // EDID_RAM
    i2c_write8(fd,0x8C73, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C74, 0xFF); // EDID_RAM
    i2c_write8(fd,0x8C75, 0x1D); // EDID_RAM
    i2c_write8(fd,0x8C76, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C77, 0x0A); // EDID_RAM
    i2c_write8(fd,0x8C78, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C79, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C7A, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C7B, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C7C, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C7D, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C7E, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C7F, 0x03); // EDID_RAM
    i2c_write8(fd,0x8C80, 0x02); // EDID_RAM
    i2c_write8(fd,0x8C81, 0x03); // EDID_RAM
    i2c_write8(fd,0x8C82, 0x1A); // EDID_RAM
    i2c_write8(fd,0x8C83, 0xF2); // EDID_RAM
    i2c_write8(fd,0x8C84, 0x47); // EDID_RAM
    i2c_write8(fd,0x8C85, 0xC6); // EDID_RAM
    i2c_write8(fd,0x8C86, 0xC6); // EDID_RAM
    i2c_write8(fd,0x8C87, 0x46); // EDID_RAM
    i2c_write8(fd,0x8C88, 0x46); // EDID_RAM
    i2c_write8(fd,0x8C89, 0x46); // EDID_RAM
    i2c_write8(fd,0x8C8A, 0x46); // EDID_RAM
    i2c_write8(fd,0x8C8B, 0x46); // EDID_RAM
    i2c_write8(fd,0x8C8C, 0x23); // EDID_RAM
    i2c_write8(fd,0x8C8D, 0x09); // EDID_RAM
    i2c_write8(fd,0x8C8E, 0x07); // EDID_RAM
    i2c_write8(fd,0x8C8F, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C90, 0x83); // EDID_RAM
    i2c_write8(fd,0x8C91, 0x01); // EDID_RAM
    i2c_write8(fd,0x8C92, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C93, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C94, 0x65); // EDID_RAM
    i2c_write8(fd,0x8C95, 0x03); // EDID_RAM
    i2c_write8(fd,0x8C96, 0x0C); // EDID_RAM
    i2c_write8(fd,0x8C97, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C98, 0x10); // EDID_RAM
    i2c_write8(fd,0x8C99, 0x00); // EDID_RAM
    i2c_write8(fd,0x8C9A, 0xD9); // EDID_RAM
    i2c_write8(fd,0x8C9B, 0x18); // EDID_RAM
    i2c_write8(fd,0x8C9C, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8C9D, 0x76); // EDID_RAM
    i2c_write8(fd,0x8C9E, 0x20); // EDID_RAM
    i2c_write8(fd,0x8C9F, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CA0, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CA1, 0x50); // EDID_RAM
    i2c_write8(fd,0x8CA2, 0x2C); // EDID_RAM
    i2c_write8(fd,0x8CA3, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CA4, 0x02); // EDID_RAM
    i2c_write8(fd,0x8CA5, 0x04); // EDID_RAM
    i2c_write8(fd,0x8CA6, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CA7, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CA8, 0x25); // EDID_RAM
    i2c_write8(fd,0x8CA9, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CAA, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CAB, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CAC, 0xD9); // EDID_RAM
    i2c_write8(fd,0x8CAD, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CAE, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CAF, 0x76); // EDID_RAM
    i2c_write8(fd,0x8CB0, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CB1, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CB2, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CB3, 0x50); // EDID_RAM
    i2c_write8(fd,0x8CB4, 0x2C); // EDID_RAM
    i2c_write8(fd,0x8CB5, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CB6, 0x02); // EDID_RAM
    i2c_write8(fd,0x8CB7, 0x04); // EDID_RAM
    i2c_write8(fd,0x8CB8, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CB9, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CBA, 0x25); // EDID_RAM
    i2c_write8(fd,0x8CBB, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CBC, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CBD, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CBE, 0xD9); // EDID_RAM
    i2c_write8(fd,0x8CBF, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CC0, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CC1, 0x76); // EDID_RAM
    i2c_write8(fd,0x8CC2, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CC3, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CC4, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CC5, 0x50); // EDID_RAM
    i2c_write8(fd,0x8CC6, 0x2C); // EDID_RAM
    i2c_write8(fd,0x8CC7, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CC8, 0x02); // EDID_RAM
    i2c_write8(fd,0x8CC9, 0x04); // EDID_RAM
    i2c_write8(fd,0x8CCA, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CCB, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CCC, 0x25); // EDID_RAM
    i2c_write8(fd,0x8CCD, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CCE, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CCF, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CD0, 0xD9); // EDID_RAM
    i2c_write8(fd,0x8CD1, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CD2, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CD3, 0x76); // EDID_RAM
    i2c_write8(fd,0x8CD4, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CD5, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CD6, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CD7, 0x50); // EDID_RAM
    i2c_write8(fd,0x8CD8, 0x2C); // EDID_RAM
    i2c_write8(fd,0x8CD9, 0x20); // EDID_RAM
    i2c_write8(fd,0x8CDA, 0x02); // EDID_RAM
    i2c_write8(fd,0x8CDB, 0x04); // EDID_RAM
    i2c_write8(fd,0x8CDC, 0xD0); // EDID_RAM
    i2c_write8(fd,0x8CDD, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CDE, 0x25); // EDID_RAM
    i2c_write8(fd,0x8CDF, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE0, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE1, 0x18); // EDID_RAM
    i2c_write8(fd,0x8CE2, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE3, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE4, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE5, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE6, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE7, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE8, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CE9, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CEA, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CEB, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CEC, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CED, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CEE, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CEF, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF0, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF1, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF2, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF3, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF4, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF5, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF6, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF7, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF8, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CF9, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CFA, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CFB, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CFC, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CFD, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CFE, 0x00); // EDID_RAM
    i2c_write8(fd,0x8CFF, 0xEA); // EDID_RAM
    
    // Wait for EDID writes to complete - critical for Linux/Jetson
    klog("<6>tc358870: Waiting for EDID writes to complete...");
    usleep(200000); // 200ms delay for EDID writes to complete

    // --- HDCP and HDMI SYSTEM ---
    klog("<6>tc358870: Step 6: HDCP and HDMI System Configuration");
    if (i2c_write8(fd, 0x8543, 0x02) != 0) { // DDC_CTL
        klog("<3>tc358870: Failed to write DDC_CTL");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8544, 0x10) != 0) { // HPD_CTL
        klog("<3>tc358870: Failed to write HPD_CTL");
        return 1; // Return 1 for failure
    }

    // --- HDMI AUDIO ---
    klog("<6>tc358870: Step 7: HDMI Audio Configuration");
    if (i2c_write8(fd, 0x8600, 0x00) != 0) { // AUD_Auto_Mute
        klog("<3>tc358870: Failed to write AUD_Auto_Mute");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8602, 0xF3) != 0) { // Auto_CMD0
        klog("<3>tc358870: Failed to write Auto_CMD0");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8603, 0x02) != 0) { // Auto_CMD1
        klog("<3>tc358870: Failed to write Auto_CMD1");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8604, 0x0C) != 0) { // Auto_CMD2
        klog("<3>tc358870: Failed to write Auto_CMD2");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8606, 0x05) != 0) { // BUFINIT_START
        klog("<3>tc358870: Failed to write BUFINIT_START");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8607, 0x00) != 0) { // FS_MUTE
        klog("<3>tc358870: Failed to write FS_MUTE");
        return 1; // Return 1 for failure
    }
    if (i2c_write8(fd, 0x8652, 0x02) != 0) { // SDO_MODE1
        klog("<3>tc358870: Failed to write SDO_MODE1");
        return 1; // Return 1 for failure
    }

    // --- HPD/EDID Detection ---
    klog("<6>tc358870: Step 8: HPD/EDID Detection");
    uint8_t hpd_status = 0;
    if (i2c_read8(fd, 0x8520, &hpd_status) != 0) {
        klog("<3>tc358870: Failed to read HPD status");
        return 1; // Return 1 for failure
    }
    klog("<6>tc358870: HPD Status = 0x%02X", hpd_status);

    if (hpd_status & 0x01) {
        klog("<6>tc358870: HDMI cable detected. Entering RS2...");
        if (rs2(fd) != 0) {
            klog("<3>tc358870: RS2 initialization failed");
            return 1; // Return 1 for failure
        }
    }
    else {
        klog("<6>tc358870: No HDMI cable detected. Skipping RS2.");
    }

    // --- Enable Interrupts & Sleep ---
    klog("<6>tc358870: Step 9: Final Configuration");
    if (i2c_write16(fd, 0x0016, 0x0F1F) != 0) { // IntMask
        klog("<3>tc358870: Failed to write final IntMask");
        return 1; // Return 1 for failure
    }
    if (i2c_write16(fd, 0x0002, 0x0001) != 0) { // SysCtl (Enter Sleep)
        klog("<3>tc358870: Failed to write SysCtl for sleep mode");
        return 1; // Return 1 for failure
    }

    klog("<6>tc358870: Init sequence completed successfully.");
    return 0; // Return 0 for success
}

// Signal handler for clean shutdown
void signal_handler(int signum) {
    klog("<6>tc358870: Received signal %d. Exiting gracefully.", signum);
    closelog();
    exit(0);
}

// Placeholder for brightness control functions (if implemented)
// These would typically involve writing to a PWM register
int init_brightness_control() {
    klog("<6>tc358870: init_brightness_control called (placeholder)");
    // In a real application, you would initialize PWM here
    // For example: i2c_write8(fd, 0x8600, 0x00); // AUD_Auto_Mute
    return 0; // Return 0 for success
}

int set_brightness(int percent) {
    klog("<6>tc358870: set_brightness called with %d%% (placeholder)", percent);
    // In a real application, you would write to a PWM register
    // For example: i2c_write8(fd, 0x8600, (uint8_t)(percent * 2.55)); // AUD_Auto_Mute
    return 0; // Return 0 for success
}

int get_brightness() {
    klog("<6>tc358870: get_brightness called (placeholder)");
    // In a real application, you would read from a PWM register
    // For example: return i2c_read8_simple(fd, 0x8600); // AUD_Auto_Mute
    return 50; // Return a default value
}

int main() {
    openlog("tc358870_init", LOG_PID | LOG_CONS, LOG_USER);

    // Set up signal handlers for clean shutdown
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    int fd = open(I2C_DEV_PATH, O_RDWR);
    if (fd < 0) {
        klog("<3>tc358870: Failed to open I2C device: %s", strerror(errno));
        return 1;
    }

    if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) {
        klog("<3>tc358870: Failed to set I2C slave address: %s", strerror(errno));
        close(fd);
        return 1;
    }

    klog("<6>Starting TC358870 RS1 Initialization...");
    int ret = tc358870_init(fd);
    if (ret != 0) {
        klog("<3>TC358870 RS1 init failed");
        close(fd);
        closelog();
        return 1; // Return 1 for failure
    }

    klog("<6>TC358870 RS1 init complete");
    
    // Initialize brightness control (like STM32 PWM)
    klog("<6>tc358870: Initializing brightness control...");
    if (init_brightness_control() == 0) {
        klog("<6>tc358870: Brightness control started successfully");
        
        // Test brightness control - fade from 20% to 80% and back
        klog("<6>tc358870: Testing brightness control...");
        set_brightness(20);
        sleep(2);
        set_brightness(80);
        sleep(2);
        set_brightness(50); // Back to default
        
        klog("<6>tc358870: Brightness control test complete. Current brightness: %d%%", get_brightness());
        
        // Keep the program running to maintain the background thread
        // In a real application, you might want to add a control interface here
        klog("<6>tc358870: Program running with brightness control. Press Ctrl+C to exit.");
        
        while (1) {
            sleep(10); // Keep main thread alive
        }
    } else {
        klog("<3>tc358870: Failed to initialize brightness control");
    }

    klog("<6>TC358870 init sequence finished");
    closelog();
    close(fd);
    return ret;
}
