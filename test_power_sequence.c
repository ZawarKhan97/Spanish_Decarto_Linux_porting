#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

// GPIO Configuration for Jetson Orin NX
#define GPIO_PQ5_BASE      0x02434000  // GPIO4 base address for PQ.05
#define GPIO_PZ6_BASE      0x02434000  // GPIO4 base address for PZ.06
#define GPIO_SIZE           0x1000      // GPIO block size

// GPIO Register Offsets
#define GPIO_OUT_REG        0x000       // Output value register
#define GPIO_OE_REG         0x004       // Output enable register
#define GPIO_IE_REG         0x008       // Input enable register
#define GPIO_DS_REG         0x014       // Drive strength register

// PADCTL Offsets for specific pins
#define PADCTL_PQ5_OFFSET  0x94        // PADCTL for PQ.05 (GPIO45)
#define PADCTL_PZ6_OFFSET  0x98        // PADCTL for PZ.06 (GPIO46)

// Pin bit positions
#define PQ5_BIT             5           // Bit 5 for PQ.05
#define PZ6_BIT             6           // Bit 6 for PZ.06

// Power sequence timing (in microseconds)
#define POWER_ON_DELAY      100000      // 100ms delay
#define RESET_DELAY         200000      // 200ms delay
#define STABLE_DELAY        1000000     // 1 second delay

// Global variables
static int running = 1;
static int gpio_mem_fd = -1;
static volatile uint32_t *gpio_regs = NULL;

// Function prototypes
void signal_handler(int sig);
int init_gpio(void);
void cleanup_gpio(void);
void set_pq5_high(void);
void set_pq5_low(void);
void set_pz6_high(void);
void set_pz6_low(void);
void power_sequence_test(void);
void continuous_power_test(void);

// Signal handler for clean shutdown
void signal_handler(int sig) {
    printf("Received signal %d. Exiting gracefully.\n", sig);
    running = 0;
}

// Initialize GPIO for power sequence
int init_gpio(void) {
    printf("Initializing GPIO for power sequence test...\n");
    printf("Using pins: PQ.05 (GPIO45) and PZ.06 (GPIO46)\n");
    
    // Open /dev/mem for GPIO access
    gpio_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (gpio_mem_fd < 0) {
        perror("Failed to open /dev/mem");
        return -1;
    }
    
    // Map GPIO registers
    long pagesize = sysconf(_SC_PAGESIZE);
    off_t gpio_page = GPIO_PQ5_BASE & ~(pagesize - 1);
    
    gpio_regs = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, gpio_mem_fd, gpio_page);
    if (gpio_regs == MAP_FAILED) {
        perror("Failed to map GPIO registers");
        close(gpio_mem_fd);
        gpio_mem_fd = -1;
        return -1;
    }
    
    // Configure PQ.05 (GPIO45) as GPIO output
    volatile uint32_t *padctl_pq5 = gpio_regs + (PADCTL_PQ5_OFFSET / 4);
    uint32_t original_padctl_pq5 = padctl_pq5[0];
    printf("Original PADCTL[PQ.05]: 0x%08x\n", original_padctl_pq5);
    
    // Set as GPIO Output → value = 0x00000004
    padctl_pq5[0] = 0x00000004;
    printf("Configured PADCTL[PQ.05]: 0x%08x\n", padctl_pq5[0]);
    
    // Configure PZ.06 (GPIO46) as GPIO output
    volatile uint32_t *padctl_pz6 = gpio_regs + (PADCTL_PZ6_OFFSET / 4);
    uint32_t original_padctl_pz6 = padctl_pz6[0];
    printf("Original PADCTL[PZ.06]: 0x%08x\n", original_padctl_pz6);
    
    // Set as GPIO Output → value = 0x00000004
    padctl_pz6[0] = 0x00000004;
    printf("Configured PADCTL[PZ.06]: 0x%08x\n", padctl_pz6[0]);
    
    // Set both pins as outputs (clear bits in OE register)
    volatile uint32_t *oe_reg = gpio_regs + (GPIO_OE_REG / 4);
    oe_reg[0] &= ~((1U << PQ5_BIT) | (1U << PZ6_BIT)); // Clear bits for output
    
    // Set initial state to LOW
    volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
    out_reg[0] &= ~((1U << PQ5_BIT) | (1U << PZ6_BIT));
    
    printf("GPIO pins configured as outputs\n");
    printf("GPIO initialization successful\n");
    return 0;
}

// Set PQ.05 HIGH
void set_pq5_high(void) {
    if (gpio_regs != NULL) {
        volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
        out_reg[0] |= (1U << PQ5_BIT);
        printf("PQ.05 set HIGH\n");
    }
}

// Set PQ.05 LOW
void set_pq5_low(void) {
    if (gpio_regs != NULL) {
        volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
        out_reg[0] &= ~(1U << PQ5_BIT);
        printf("PQ.05 set LOW\n");
    }
}

// Set PZ.06 HIGH
void set_pz6_high(void) {
    if (gpio_regs != NULL) {
        volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
        out_reg[0] |= (1U << PZ6_BIT);
        printf("PZ.06 set HIGH\n");
    }
}

// Set PZ.06 LOW
void set_pz6_low(void) {
    if (gpio_regs != NULL) {
        volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
        out_reg[0] &= ~(1U << PZ6_BIT);
        printf("PZ.06 set LOW\n");
    }
}

// Test the power sequence based on STM32 code
void power_sequence_test(void) {
    printf("\n=== Starting Power Sequence Test ===\n");
    printf("This mimics the STM32 power sequence:\n");
    printf("1. Set LCD_RESET_Pin (PQ.05) HIGH\n");
    printf("2. Set LCD_EN_Pin (PZ.06) HIGH\n");
    printf("3. Set DSI_RESET_N_Pin (PZ.06) HIGH\n");
    printf("4. Set LCD_RESET_Pin (PQ.05) LOW\n");
    printf("5. Wait 200ms\n");
    printf("6. Set LCD_RESET_Pin (PQ.05) HIGH\n");
    printf("7. Wait 1 second\n");
    
    // Step 1: Set LCD_RESET_Pin HIGH
    printf("\nStep 1: Setting LCD_RESET_Pin (PQ.05) HIGH...\n");
    set_pq5_high();
    usleep(POWER_ON_DELAY); // 100ms delay
    
    // Step 2: Set LCD_EN_Pin HIGH
    printf("\nStep 2: Setting LCD_EN_Pin (PZ.06) HIGH...\n");
    set_pz6_high();
    usleep(POWER_ON_DELAY); // 100ms delay
    
    // Step 3: Set DSI_RESET_N_Pin HIGH
    printf("\nStep 3: Setting DSI_RESET_N_Pin (PZ.06) HIGH...\n");
    set_pz6_high(); // Already HIGH from step 2
    usleep(POWER_ON_DELAY); // 100ms delay
    
    // Step 4: Set LCD_RESET_Pin LOW
    printf("\nStep 4: Setting LCD_RESET_Pin (PQ.05) LOW...\n");
    set_pq5_low();
    
    // Step 5: Wait 200ms
    printf("\nStep 5: Waiting 200ms for reset to complete...\n");
    usleep(RESET_DELAY);
    
    // Step 6: Set LCD_RESET_Pin HIGH
    printf("\nStep 6: Setting LCD_RESET_Pin (PQ.05) HIGH...\n");
    set_pq5_high();
    
    // Step 7: Wait 1 second
    printf("\nStep 7: Waiting 1 second for system to stabilize...\n");
    usleep(STABLE_DELAY);
    
    printf("\n=== Power Sequence Test Complete ===\n");
}

// Continuous power test for monitoring
void continuous_power_test(void) {
    printf("\n=== Starting Continuous Power Test ===\n");
    printf("This will continuously toggle the pins for monitoring\n");
    printf("Press Ctrl+C to stop\n");
    
    int cycle = 0;
    while (running) {
        printf("\n--- Cycle %d ---\n", ++cycle);
        
        // Toggle PQ.05
        printf("Toggling PQ.05 (LCD_RESET)...\n");
        set_pq5_high();
        usleep(500000); // 500ms
        set_pq5_low();
        usleep(500000); // 500ms
        
        // Toggle PZ.06
        printf("Toggling PZ.06 (LCD_EN/DSI_RESET_N)...\n");
        set_pz6_high();
        usleep(500000); // 500ms
        set_pz6_low();
        usleep(500000); // 500ms
        
        if (cycle >= 10) {
            printf("Completed 10 cycles. Stopping continuous test.\n");
            break;
        }
    }
}

// Cleanup GPIO
void cleanup_gpio(void) {
    printf("\nCleaning up GPIO...\n");
    
    if (gpio_regs != NULL) {
        // Set both pins low before cleanup
        volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
        out_reg[0] &= ~((1U << PQ5_BIT) | (1U << PZ6_BIT));
        
        munmap((void*)gpio_regs, GPIO_SIZE);
        gpio_regs = NULL;
    }
    
    if (gpio_mem_fd >= 0) {
        close(gpio_mem_fd);
        gpio_mem_fd = -1;
    }
    
    printf("GPIO cleanup complete\n");
}

int main() {
    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    printf("Power Sequence Test Program for TC358870\n");
    printf("========================================\n");
    printf("GPIO Pins: PQ.05 (LCD_RESET) and PZ.06 (LCD_EN/DSI_RESET_N)\n");
    
    // Initialize GPIO
    if (init_gpio() != 0) {
        printf("Failed to initialize GPIO\n");
        return 1;
    }
    
    printf("\nGPIO initialized successfully.\n");
    printf("Available tests:\n");
    printf("1. Power sequence test (mimics STM32)\n");
    printf("2. Continuous toggle test (for monitoring)\n");
    printf("3. Manual control\n");
    printf("4. Exit\n");
    
    char input[32];
    while (running) {
        printf("\nSelect test (1-4): ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline
            
            if (strcmp(input, "1") == 0) {
                power_sequence_test();
            } else if (strcmp(input, "2") == 0) {
                continuous_power_test();
            } else if (strcmp(input, "3") == 0) {
                printf("\nManual Control Mode:\n");
                printf("Commands: 'pq5h' (PQ.05 HIGH), 'pq5l' (PQ.05 LOW)\n");
                printf("         'pz6h' (PZ.06 HIGH), 'pz6l' (PZ.06 LOW)\n");
                printf("         'q' to quit manual mode\n");
                
                char cmd[32];
                while (1) {
                    printf("Manual> ");
                    if (fgets(cmd, sizeof(cmd), stdin) != NULL) {
                        cmd[strcspn(cmd, "\n")] = 0;
                        
                        if (strcmp(cmd, "q") == 0) {
                            break;
                        } else if (strcmp(cmd, "pq5h") == 0) {
                            set_pq5_high();
                        } else if (strcmp(cmd, "pq5l") == 0) {
                            set_pq5_low();
                        } else if (strcmp(cmd, "pz6h") == 0) {
                            set_pz6_high();
                        } else if (strcmp(cmd, "pz6l") == 0) {
                            set_pz6_low();
                        } else if (strlen(cmd) > 0) {
                            printf("Commands: 'pq5h', 'pq5l', 'pz6h', 'pz6l', 'q'\n");
                        }
                    }
                }
            } else if (strcmp(input, "4") == 0 || strcmp(input, "q") == 0) {
                printf("User requested exit\n");
                break;
            } else if (strlen(input) > 0) {
                printf("Invalid selection. Use 1-4\n");
            }
        }
    }
    
    // Cleanup
    cleanup_gpio();
    printf("Program terminated.\n");
    
    return 0;
}
