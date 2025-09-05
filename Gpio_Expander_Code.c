#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#define I2C_DEV "/dev/i2c-1"  // Use correct I2C bus
#define SX1508B_ADDR 0x20     // Default I2C address

// SX1508B Register Map
#define REG_DIR                 0x07
#define REG_DATA                0x08
#define REG_MISC                0x10
#define REG_CLOCK               0x0F
#define REG_LED_DRIVER_ENABLE   0x11
// LED Driver registers for GPIO4 (LCD brightness PWM)
#define REG_T_ON4               0x20    // ON time register for I/O[4]
#define REG_I_ON4               0x21    // ON intensity register for I/O[4] 
#define REG_OFF4                0x22    // OFF time/intensity register for I/O[4]

// Additional registers needed for LED driver setup
#define REG_INPUT_DISABLE       0x00    // Input buffer disable register
#define REG_PULL_UP             0x03    // Pull-up register
#define REG_OPEN_DRAIN          0x05    // Open drain register

// GPIO Pin assignments
#define GPIO_DSI_RESET_N        0       // IO0 = DSI_RESET_N_PIN
#define GPIO_LCD_RESET          6       // IO6 = LCD_RESET_PIN  
#define GPIO_LCD_ENABLE         7       // IO7 = LCD_ENABLE_PIN
#define GPIO_LCD_BRIGHTNESS     4       // IO4 = LCD_DISPLAY_BRIGHTNESS_PIN (PWM)

int write_reg(int fd, uint8_t reg, uint8_t val) {
    uint8_t buf[2] = {reg, val};
    printf("DEBUG: Writing to register 0x%02X with value 0x%02X\n", reg, val);
    if (write(fd, buf, 2) != 2) {
        perror("ERROR: Failed to write to I2C register");
        return -1;
    }
    printf("DEBUG: Successfully wrote to register 0x%02X\n", reg);
    return 0;
}

void delay_ms(uint32_t ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int init_sx1508b(int fd) {
    printf("INFO: Starting SX1508B initialization for LCD brightness PWM (GPIO4)...\n");
    
    // Step 1: Disable input buffer for GPIO4 (LCD brightness PWM pin)
    printf("INFO: Step 1 - Disabling input buffer for GPIO4 (LCD brightness)...\n");
    if (write_reg(fd, REG_INPUT_DISABLE, 0b00010000)) {  // Bit 4 = GPIO4
        printf("ERROR: Failed to disable input buffer for GPIO4\n");
        return -1;
    }

    // Step 2: Disable pull-up for GPIO4
    printf("INFO: Step 2 - Disabling pull-up for GPIO4...\n");
    if (write_reg(fd, REG_PULL_UP, 0b00000000)) {  // No pull-ups
        printf("ERROR: Failed to disable pull-up for GPIO4\n");
        return -1;
    }

    // Step 3: Enable open drain for GPIO4
    printf("INFO: Step 3 - Enabling open drain for GPIO4...\n");
    if (write_reg(fd, REG_OPEN_DRAIN, 0b00010000)) {  // Bit 4 = GPIO4
        printf("ERROR: Failed to enable open drain for GPIO4\n");
        return -1;
    }

    // Step 4: Set direction to output for all GPIO pins (0,4,6,7)
    printf("INFO: Step 4 - Setting pin directions (GPIO0,4,6,7 as OUTPUT)...\n");
    uint8_t dir_mask = 0b00101110;  // GPIO0,4,6,7 = output (0), rest = input (1)
    if (write_reg(fd, REG_DIR, dir_mask)) {
        printf("ERROR: Failed to set pin directions\n");
        return -1;
    }

    // Step 5: Set initial data states (all pins LOW initially)
    printf("INFO: Step 5 - Setting initial GPIO states (all pins LOW)...\n");
    uint8_t data_out = 0b00000000;  // All pins LOW initially
    if (write_reg(fd, REG_DATA, data_out)) {
        printf("ERROR: Failed to set initial GPIO states\n");
        return -1;
    }

    // Step 6: Enable oscillator
    printf("INFO: Step 6 - Enabling internal oscillator...\n");
    if (write_reg(fd, REG_CLOCK, 0b00000001)) {  // Enable oscillator
        printf("ERROR: Failed to enable oscillator\n");
        return -1;
    }

    // Step 7: Configure LED driver clock and mode
    printf("INFO: Step 7 - Configuring LED driver clock and mode...\n");
    if (write_reg(fd, REG_MISC, 0b00000000)) {  // Default LED driver mode
        printf("ERROR: Failed to configure LED driver mode\n");
        return -1;
    }

    // Step 8: Enable LED driver operation for GPIO4 (LCD brightness)
    printf("INFO: Step 8 - Enabling LED driver operation for GPIO4 (LCD brightness)...\n");
    if (write_reg(fd, REG_LED_DRIVER_ENABLE, 0b00010000)) {  // Bit 4 = GPIO4
        printf("ERROR: Failed to enable LED driver for GPIO4\n");
        return -1;
    }

    // Step 9: Configure LED driver parameters for GPIO4 (50% duty cycle for brightness)
    printf("INFO: Step 9 - Configuring LED driver parameters for GPIO4 (LCD brightness)...\n");
    
    // Set ON time (how long brightness stays on in each cycle)
    uint8_t on_time = 128;  // 50% of 255
    printf("INFO: Setting ON time to %d (50%% brightness duty cycle)\n", on_time);
    if (write_reg(fd, REG_T_ON4, on_time)) {
        printf("ERROR: Failed to set ON time for GPIO4\n");
        return -1;
    }

    // Set ON intensity (brightness level when on)
    uint8_t on_intensity = 255;  // Maximum brightness
    printf("INFO: Setting ON intensity to %d (maximum brightness)\n", on_intensity);
    if (write_reg(fd, REG_I_ON4, on_intensity)) {
        printf("ERROR: Failed to set ON intensity for GPIO4\n");
        return -1;
    }

    // Set OFF time/intensity (how long brightness stays off in each cycle)
    uint8_t off_time = 127;  // 50% of 255
    printf("INFO: Setting OFF time to %d (50%% brightness duty cycle)\n", off_time);
    if (write_reg(fd, REG_OFF4, off_time)) {
        printf("ERROR: Failed to set OFF time for GPIO4\n");
        return -1;
    }

    // Step 10: Set GPIO4 data bit low to start LED driver (LCD brightness PWM)
    printf("INFO: Step 10 - Starting LCD brightness PWM by setting GPIO4 LOW...\n");
    uint8_t start_brightness = 0b00000000;  // GPIO4=0 (PWM started)
    if (write_reg(fd, REG_DATA, start_brightness)) {
        printf("ERROR: Failed to start LCD brightness PWM\n");
        return -1;
    }

    printf("INFO: SX1508B LCD brightness PWM initialization completed successfully!\n");
    printf("INFO: GPIO4=PWM (50%% brightness), GPIO0,6,7 ready for LCD power sequence\n");
    return 0;
}

int lcd_power_sequence(int fd) {
    printf("INFO: Starting LCD power sequence...\n");
    
    // Step 1: Set LCD_RESET_PIN (GPIO6) HIGH
    printf("INFO: Step 1 - Setting LCD_RESET_PIN (GPIO6) HIGH...\n");
    uint8_t lcd_reset_high = 0b01000000;  // GPIO6 = 1
    if (write_reg(fd, REG_DATA, lcd_reset_high)) {
        printf("ERROR: Failed to set LCD_RESET_PIN HIGH\n");
        return -1;
    }
    printf("INFO: LCD_RESET_PIN set HIGH\n");
    
    // Step 2: Delay 100ms
    printf("INFO: Step 2 - Waiting 100ms...\n");
    delay_ms(100);
    printf("INFO: 100ms delay completed\n");
    
    // Step 3: Set LCD_EN_PIN (GPIO7) HIGH
    printf("INFO: Step 3 - Setting LCD_EN_PIN (GPIO7) HIGH...\n");
    uint8_t lcd_en_high = 0b11000000;  // GPIO6=1, GPIO7=1
    if (write_reg(fd, REG_DATA, lcd_en_high)) {
        printf("ERROR: Failed to set LCD_EN_PIN HIGH\n");
        return -1;
    }
    printf("INFO: LCD_EN_PIN set HIGH\n");
    
    // Step 4: Set DSI_RESET_N_PIN (GPIO0) HIGH
    printf("INFO: Step 4 - Setting DSI_RESET_N_PIN (GPIO0) HIGH...\n");
    uint8_t dsi_reset_high = 0b11000001;  // GPIO0=1, GPIO6=1, GPIO7=1
    if (write_reg(fd, REG_DATA, dsi_reset_high)) {
        printf("ERROR: Failed to set DSI_RESET_N_PIN HIGH\n");
        return -1;
    }
    printf("INFO: DSI_RESET_N_PIN set HIGH\n");
    
    // Step 5: Delay 200ms
    printf("INFO: Step 5 - Waiting 200ms...\n");
    delay_ms(200);
    printf("INFO: 200ms delay completed\n");
    
    // Step 6: Set DSI_RESET_N_PIN (GPIO0) LOW
    printf("INFO: Step 6 - Setting DSI_RESET_N_PIN (GPIO0) LOW...\n");
    uint8_t dsi_reset_low = 0b11000000;  // GPIO0=0, GPIO6=1, GPIO7=1
    if (write_reg(fd, REG_DATA, dsi_reset_low)) {
        printf("ERROR: Failed to set DSI_RESET_N_PIN LOW\n");
        return -1;
    }
    printf("INFO: DSI_RESET_N_PIN set LOW\n");
    
    // Step 7: Delay 1000ms
    printf("INFO: Step 7 - Waiting 1000ms...\n");
    delay_ms(1000);
    printf("INFO: 1000ms delay completed\n");
    
    printf("SUCCESS: LCD power sequence completed successfully!\n");
    printf("INFO: Final state - LCD_RESET=HIGH, LCD_EN=HIGH, DSI_RESET_N=LOW\n");
    return 0;
}

int main() {
    printf("=== SX1508B GPIO Expander Test Program ===\n");
    printf("INFO: Starting program...\n");
    
    printf("INFO: Opening I2C device: %s\n", I2C_DEV);
    int fd = open(I2C_DEV, O_RDWR);
    if (fd < 0) {
        perror("ERROR: Failed to open I2C bus");
        printf("ERROR: Make sure I2C is enabled and the device exists\n");
        return EXIT_FAILURE;
    }
    printf("INFO: Successfully opened I2C device (fd: %d)\n", fd);

    printf("INFO: Setting I2C slave address to 0x%02X\n", SX1508B_ADDR);
    if (ioctl(fd, I2C_SLAVE, SX1508B_ADDR) < 0) {
        perror("ERROR: Failed to set I2C slave address");
        printf("ERROR: Check if SX1508B is connected and address is correct\n");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("INFO: Successfully set I2C slave address\n");

    printf("INFO: Calling SX1508B initialization function...\n");
    if (init_sx1508b(fd) != 0) {
        fprintf(stderr, "ERROR: SX1508B initialization failed.\n");
        printf("ERROR: Check I2C connection and device functionality\n");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("SUCCESS: SX1508B initialized successfully!\n");
    printf("SUCCESS: LCD brightness PWM configured on GPIO4 (50%%)\n");
    
    printf("INFO: Starting LCD power sequence...\n");
    if (lcd_power_sequence(fd) != 0) {
        fprintf(stderr, "ERROR: LCD power sequence failed.\n");
        printf("ERROR: Check LCD connections and power sequence timing\n");
        close(fd);
        return EXIT_FAILURE;
    }
    
    printf("SUCCESS: LCD power sequence completed successfully!\n");
    printf("SUCCESS: LCD should now be powered on and ready\n");
    printf("INFO: Entering main loop to maintain PWM output...\n");
    printf("INFO: Press Ctrl+C to exit\n");

    // Keep running to maintain PWM
    int loop_count = 0;
    while (1) {
        sleep(1);
        loop_count++;
        if (loop_count % 10 == 0) {
            printf("INFO: Program running... (loop %d)\n", loop_count);
        }
    }

    printf("INFO: Closing I2C device...\n");
    close(fd);
    printf("INFO: Program terminated normally\n");
    return EXIT_SUCCESS;
}
