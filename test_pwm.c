#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

// PWM Constants (matching STM32 Timer 1 configuration)
#define PWM_PERIOD        640      // Timer period (htim1.Init.Period = 639 + 1)
#define PWM_MAX_DUTY      13107    // Maximum duty cycle (sConfigOC.Pulse)
#define BRIGHTNESS_MAX    100      // Maximum brightness percentage
#define PWM_UPDATE_RATE   50       // PWM update rate in milliseconds

// PWM Thread Global Variables
static pthread_t pwm_thread;
static int pwm_running = 0;
static int current_brightness = 50;  // Start at 50%
static int target_brightness = 50;
static pthread_mutex_t pwm_mutex = PTHREAD_MUTEX_INITIALIZER;
static int pwm_fd = -1;  // PWM chip file descriptor

// Function prototypes
int write_pwm_duty_cycle(int duty_cycle);
void *pwm_thread_function(void *arg);
int init_pwm_thread(void);
void cleanup_pwm_thread(void);
int set_brightness(int percentage);
int get_brightness(void);
void signal_handler(int sig);

// Write PWM duty cycle to sysfs interface
int write_pwm_duty_cycle(int duty_cycle) {
    if (pwm_fd < 0) {
        printf("PWM not initialized\n");
        return -1;
    }
    
    char path[128];
    snprintf(path, sizeof(path), "/sys/class/pwm/pwmchip%d/pwm0/duty_cycle", pwm_fd);
    
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Failed to open PWM duty_cycle file\n");
        return -1;
    }
    
    fprintf(fp, "%d", duty_cycle);
    fclose(fp);
    
    printf("PWM duty cycle set to %d\n", duty_cycle);
    return 0;
}

// Main PWM thread function - continuously adjusts brightness
void *pwm_thread_function(void *arg) {
    printf("PWM thread started\n");
    
    while (pwm_running) {
        int local_target, local_current;
        
        // Safely read current values
        pthread_mutex_lock(&pwm_mutex);
        local_target = target_brightness;
        local_current = current_brightness;
        pthread_mutex_unlock(&pwm_mutex);
        
        // Smooth transition towards target brightness
        if (local_current < local_target) {
            local_current++;
        } else if (local_current > local_target) {
            local_current--;
        }
        
        // Update current brightness if changed
        if (local_current != current_brightness) {
            pthread_mutex_lock(&pwm_mutex);
            current_brightness = local_current;
            pthread_mutex_unlock(&pwm_mutex);
            
            // Calculate duty cycle based on brightness percentage
            int duty_cycle = (local_current * PWM_MAX_DUTY) / BRIGHTNESS_MAX;
            write_pwm_duty_cycle(duty_cycle);
        }
        
        // Update rate: 50ms (like STM32 timer)
        usleep(PWM_UPDATE_RATE * 1000);
    }
    
    printf("PWM thread stopped\n");
    return NULL;
}

// Initialize PWM thread and hardware
int init_pwm_thread(void) {
    printf("Initializing PWM thread...\n");
    
    // Find available PWM chip
    for (int chip = 0; chip < 4; chip++) {
        char path[128];
        snprintf(path, sizeof(path), "/sys/class/pwm/pwmchip%d", chip);
        
        if (access(path, F_OK) == 0) {
            pwm_fd = chip;
            printf("Found PWM chip %d\n", chip);
            break;
        }
    }
    
    if (pwm_fd < 0) {
        printf("No PWM chip found\n");
        return -1;
    }
    
    // Export PWM channel 0
    char export_path[128];
    snprintf(export_path, sizeof(export_path), "/sys/class/pwm/pwmchip%d/export", pwm_fd);
    
    FILE *fp = fopen(export_path, "w");
    if (!fp) {
        printf("Failed to export PWM channel\n");
        return -1;
    }
    fprintf(fp, "0");
    fclose(fp);
    
    // Set PWM period
    char period_path[128];
    snprintf(period_path, sizeof(period_path), "/sys/class/pwm/pwmchip%d/pwm0/period", pwm_fd);
    
    fp = fopen(period_path, "w");
    if (!fp) {
        printf("Failed to set PWM period\n");
        return -1;
    }
    fprintf(fp, "%d", PWM_PERIOD);
    fclose(fp);
    
    // Set initial duty cycle (50% brightness)
    int initial_duty = (current_brightness * PWM_MAX_DUTY) / BRIGHTNESS_MAX;
    write_pwm_duty_cycle(initial_duty);
    
    // Enable PWM
    char enable_path[128];
    snprintf(enable_path, sizeof(enable_path), "/sys/class/pwm/pwmchip%d/pwm0/enable", pwm_fd);
    
    fp = fopen(enable_path, "w");
    if (!fp) {
        printf("Failed to enable PWM\n");
        return -1;
    }
    fprintf(fp, "1");
    fclose(fp);
    
    // Start PWM thread
    pwm_running = 1;
    if (pthread_create(&pwm_thread, NULL, pwm_thread_function, NULL) != 0) {
        printf("Failed to create PWM thread\n");
        pwm_running = 0;
        return -1;
    }
    
    printf("PWM thread initialized successfully\n");
    return 0;
}

// Cleanup PWM thread and hardware
void cleanup_pwm_thread(void) {
    printf("Cleaning up PWM thread...\n");
    
    // Stop thread
    pwm_running = 0;
    
    // Wait for thread to finish
    if (pwm_thread) {
        pthread_join(pwm_thread, NULL);
    }
    
    // Disable and unexport PWM
    if (pwm_fd >= 0) {
        char enable_path[128];
        snprintf(enable_path, sizeof(enable_path), "/sys/class/pwm/pwmchip%d/pwm0/enable", pwm_fd);
        
        FILE *fp = fopen(enable_path, "w");
        if (fp) {
            fprintf(fp, "0");
            fclose(fp);
        }
        
        char unexport_path[128];
        snprintf(unexport_path, sizeof(unexport_path), "/sys/class/pwm/pwmchip%d/unexport", pwm_fd);
        
        fp = fopen(unexport_path, "w");
        if (fp) {
            fprintf(fp, "0");
            fclose(fp);
        }
        
        pwm_fd = -1;
    }
    
    // Cleanup mutex
    pthread_mutex_destroy(&pwm_mutex);
    
    printf("PWM thread cleanup complete\n");
}

// Set brightness (0-100%)
int set_brightness(int percentage) {
    if (percentage < 0 || percentage > BRIGHTNESS_MAX) {
        printf("Invalid brightness value: %d\n", percentage);
        return -1;
    }
    
    pthread_mutex_lock(&pwm_mutex);
    target_brightness = percentage;
    pthread_mutex_unlock(&pwm_mutex);
    
    printf("Brightness target set to %d%%\n", percentage);
    return 0;
}

// Get current brightness
int get_brightness(void) {
    pthread_mutex_lock(&pwm_mutex);
    int brightness = current_brightness;
    pthread_mutex_unlock(&pwm_mutex);
    
    return brightness;
}

// Signal handler for clean shutdown
void signal_handler(int signum) {
    printf("Received signal %d. Exiting gracefully.\n", signum);
    cleanup_pwm_thread();
    exit(0);
}

int main() {
    // Set up signal handlers for clean shutdown
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("PWM Thread Test Program\n");
    printf("=======================\n");
    
    // Initialize PWM thread
    if (init_pwm_thread() != 0) {
        printf("Failed to initialize PWM thread\n");
        return 1;
    }
    
    printf("\nPWM thread is running in background.\n");
    printf("Commands:\n");
    printf("  b <0-100>  - Set brightness (0-100%%)\n");
    printf("  g           - Get current brightness\n");
    printf("  q           - Quit\n");
    printf("  Ctrl+C      - Exit gracefully\n\n");
    
    // Simple command interface
    char input[32];
    while (1) {
        printf("PWM> ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline
            
            if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
                printf("User requested exit\n");
                break;
            } else if (strncmp(input, "b ", 2) == 0) {
                int brightness = atoi(input + 2);
                if (brightness >= 0 && brightness <= 100) {
                    set_brightness(brightness);
                    printf("Brightness set to %d%%\n", brightness);
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
    
    cleanup_pwm_thread();
    printf("Program terminated.\n");
    return 0;
}
