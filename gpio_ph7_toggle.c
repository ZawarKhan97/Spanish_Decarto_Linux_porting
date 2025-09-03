#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PADCTL_G4_BASE       0x02434000        // PADCTL_G4 base address
#define PADCTL_PH7_OFFSET    0x8C              // Offset for PH.07 (GPIO41)
#define PADCTL_PH7_ADDR      (PADCTL_G4_BASE + PADCTL_PH7_OFFSET)

#define GPIO4_BASE           0x02434000        // GPIO3 base address
#define GPIO_SIZE            0x1000            // GPIO block size

#define GPIO_OUT_REG         0x000             // Output value register
#define GPIO_OE_REG          0x004             // Output enable register

#define PH7_BIT              7
#define BIT(x)               (1U << (x))

int main() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("open /dev/mem");
        return 1;
    }

    // --- Map PADCTL_G4 for PH.07 pinmux ---
    long pagesize = sysconf(_SC_PAGESIZE);
    off_t padctl_page = PADCTL_PH7_ADDR & ~(pagesize - 1);
    off_t padctl_offset = PADCTL_PH7_ADDR & (pagesize - 1);

    uint32_t *padctl = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, padctl_page);
    if (padctl == MAP_FAILED) {
        perror("mmap padctl");
        close(fd);
        return 2;
    }

    printf("Original PADCTL[PH.07]: 0x%08x\n", padctl[padctl_offset / 4]);

    // Set as GPIO Output → value = 0x00000004
    padctl[padctl_offset / 4] = 0x00000004;

    printf("Configured PADCTL[PH.07]: 0x%08x\n", padctl[padctl_offset / 4]);

    // --- Map GPIO3 block ---
    volatile uint32_t *gpio = mmap(NULL, GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO3_BASE);
    if (gpio == MAP_FAILED) {
        perror("mmap gpio");
        munmap(padctl, pagesize);
        close(fd);
        return 3;
    }

    // Set PH.07 as output (clear bit 7 in OE register)
    gpio[GPIO_OE_REG / 4] &= ~BIT(PH7_BIT);

    // Set HIGH
    gpio[GPIO_OUT_REG / 4] |= BIT(PH7_BIT);
    printf("PH.07 set HIGH\n");
    sleep(1);

    // Set LOW
    gpio[GPIO_OUT_REG / 4] &= ~BIT(PH7_BIT);
    printf("PH.07 set LOW\n");

    // Cleanup
    munmap((void*)padctl, pagesize);
    munmap((void*)gpio, GPIO_SIZE);
    close(fd);

    return 0;
}
