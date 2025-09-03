#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <pthread.h>

// GPIO PWM Configuration
#define GPIO_PWM_PIN      41       // GPIO41 (PH.07) for PWM output
#define GPIO_PWM_BASE     0x02434000 // GPIO4 base address
#define GPIO_PWM_SIZE     0x1000   // GPIO block size
#define GPIO_OUT_REG      0x000    // Output value register
#define GPIO_OE_REG       0x004    // Output enable register
#define PADCTL_PH7_OFFSET 0x8C     // PADCTL for PH.07

// PWM Parameters
#define PWM_PERIOD        640      // PWM period
#define PWM_MAX_DUTY      13107    // Maximum duty cycle
#define BRIGHTNESS_MAX    100      // Maximum brightness percentage
#define PWM_UPDATE_RATE   50       // PWM update rate in milliseconds

// Global variables
static int running = 1;
static int current_brightness = 50;
static int target_brightness = 50;
static pthread_mutex_t brightness_mutex = PTHREAD_MUTEX_INITIALIZER;
static int gpio_mem_fd = -1;
static volatile uint32_t *gpio_regs = NULL;

// Function prototypes
void signal_handler(int sig);
int init_gpio(void);
void cleanup_gpio(void);
void generate_pwm_signal(int duty_cycle);
void *pwm_thread_function(void *arg);
int set_brightness(int percentage);
int get_brightness(void);

// Signal handler for clean shutdown
void signal_handler(int sig) {
    printf("Received signal %d. Exiting gracefully.\n", sig);
    running = 0;
}

// Initialize GPIO for PWM
int init_gpio(void) {
    printf("Initializing GPIO PWM on PH.07 (GPIO41)...\n");
    
    // Open /dev/mem for GPIO access
    gpio_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (gpio_mem_fd < 0) {
        perror("Failed to open /dev/mem");
        return -1;
    }
    
    // Map GPIO registers
    long pagesize = sysconf(_SC_PAGESIZE);
    off_t gpio_page = GPIO_PWM_BASE & ~(pagesize - 1);
    
    gpio_regs = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, gpio_mem_fd, gpio_page);
    if (gpio_regs == MAP_FAILED) {
        perror("Failed to map GPIO registers");
        close(gpio_mem_fd);
        gpio_mem_fd = -1;
        return -1;
    }
    
    // Configure PH.07 as GPIO output
    volatile uint32_t *padctl = gpio_regs + (PADCTL_PH7_OFFSET / 4);
    uint32_t original_padctl = padctl[0];
    printf("Original PADCTL[PH.07]: 0x%08x\n", original_padctl);
    
    // Set as GPIO Output → value = 0x00000004
    padctl[0] = 0x00000004;
    printf("Configured PADCTL[PH.07]: 0x%08x\n", padctl[0]);
    
    // Set PH.07 as output (clear bit 7 in OE register)
    volatile uint32_t *oe_reg = gpio_regs + (GPIO_OE_REG / 4);
    oe_reg[0] &= ~(1U << 7); // Clear bit 7 for output
    printf("PH.07 configured as output\n");
    
    // Set initial state to LOW
    volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
    out_reg[0] &= ~(1U << 7);
    
    printf("GPIO PWM initialized successfully\n");
    return 0;
}

// Generate PWM signal by toggling GPIO
void generate_pwm_signal(int duty_cycle) {
    if (gpio_regs == NULL) {
        return;
    }
    
    volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
    
    // Calculate PWM timing based on duty cycle
    int high_time_us = (duty_cycle * 1000) / PWM_MAX_DUTY;  // Convert to microseconds
    int low_time_us = 1000 - high_time_us;  // Total period is 1000us (1ms)
    
    // Generate one PWM cycle
    if (high_time_us > 0) {
        out_reg[0] |= (1U << 7);   // Set PH.07 HIGH
        usleep(high_time_us);
    }
    
    if (low_time_us > 0) {
        out_reg[0] &= ~(1U << 7);  // Set PH.07 LOW
        usleep(low_time_us);
    }
}

// PWM thread function
void *pwm_thread_function(void *arg) {
    printf("PWM thread started\n");
    
    while (running) {
        int local_brightness;
        
        // Safely read current brightness
        pthread_mutex_lock(&brightness_mutex);
        local_brightness = current_brightness;
        pthread_mutex_unlock(&brightness_mutex);
        
        // Generate PWM signal
        int duty_cycle = (local_brightness * PWM_MAX_DUTY) / BRIGHTNESS_MAX;
        generate_pwm_signal(duty_cycle);
        
        // Small delay to control PWM frequency
        usleep(100);  // 100us delay between PWM cycles
    }
    
    printf("PWM thread stopped\n");
    return NULL;
}

// Set brightness (0-100%)
int set_brightness(int percentage) {
    if (percentage < 0 || percentage > BRIGHTNESS_MAX) {
        printf("Invalid brightness value: %d\n", percentage);
        return -1;
    }
    
    pthread_mutex_lock(&brightness_mutex);
    target_brightness = percentage;
    current_brightness = percentage;  // Immediate change for GPIO PWM
    pthread_mutex_unlock(&brightness_mutex);
    
    printf("Brightness set to %d%%\n", percentage);
    return 0;
}

// Get current brightness
int get_brightness(void) {
    pthread_mutex_lock(&brightness_mutex);
    int brightness = current_brightness;
    pthread_mutex_unlock(&brightness_mutex);
    
    return brightness;
}

// Cleanup GPIO
void cleanup_gpio(void) {
    printf("Cleaning up GPIO...\n");
    
    if (gpio_regs != NULL) {
        // Set GPIO low before cleanup
        volatile uint32_t *out_reg = gpio_regs + (GPIO_OUT_REG / 4);
        out_reg[0] &= ~(1U << 7); // Set PH.07 LOW
        
        munmap((void*)gpio_regs, GPIO_PWM_SIZE);
        gpio_regs = NULL;
    }
    
    if (gpio_mem_fd >= 0) {
        close(gpio_mem_fd);
        gpio_mem_fd = -1;
    }
    
    pthread_mutex_destroy(&brightness_mutex);
    printf("GPIO cleanup complete\n");
}

int main() {
    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    printf("GPIO PWM Test Program for PH.07 (GPIO41)\n");
    printf("========================================\n");
    
    // Initialize GPIO
    if (init_gpio() != 0) {
        printf("Failed to initialize GPIO\n");
        return 1;
    }
    
    // Start PWM thread
    pthread_t pwm_thread;
    if (pthread_create(&pwm_thread, NULL, pwm_thread_function, NULL) != 0) {
        printf("Failed to create PWM thread\n");
        cleanup_gpio();
        return 1;
    }
    
    printf("\nGPIO PWM is running on PH.07 (GPIO41).\n");
    printf("Commands:\n");
    printf("  b <0-100>  - Set brightness (0-100%%)\n");
    printf("  g           - Get current brightness\n");
    printf("  q           - Quit\n");
    printf("  Ctrl+C      - Exit gracefully\n\n");
    
    // Test sequence
    printf("Running test sequence...\n");
    set_brightness(20);
    sleep(2);
    set_brightness(80);
    sleep(2);
    set_brightness(50);
    printf("Test sequence complete\n\n");
    
    // Command interface
    char input[32];
    while (running) {
        printf("GPIO_PWM> ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline
            
            if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
                printf("User requested exit\n");
                break;
            } else if (strncmp(input, "b ", 2) == 0) {
                int brightness = atoi(input + 2);
                if (brightness >= 0 && brightness <= 100) {
                    set_brightness(brightness);
                } else {
                    printf("Invalid brightness. Use 0-100\n");
                }
            } else if (strcmp(input, "g") == 0 || strcmp(input, "get") == 0) {
                int current = get_brightness();
                printf("Current brightness: %d%%\n", current);
            } else if (strlen(input) > 0) {
                printf("Commands: 'b <0-100>' set brightness, 'g' get current, 'q' quit\n");
            }
        }
    }
    
    // Cleanup
    pthread_join(pwm_thread, NULL);
    cleanup_gpio();
    printf("Program terminated.\n");
    
    return 0;
}
