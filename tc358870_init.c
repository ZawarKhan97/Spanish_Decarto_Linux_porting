
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



#define I2C_DEV_PATH "/dev/i2c-8"  // Change as needed
#define I2C_ADDR     0x0F          // TC358870 I2C address

//Function Prototypes
void klog(const char *fmt, ...);
int i2c_write8(int fd, uint16_t reg, uint8_t data);
int i2c_write16(int fd, uint16_t reg, uint16_t data);
int i2c_read8(int fd, uint16_t reg, uint8_t *out);
int i2c_read16(int fd, uint16_t reg, uint16_t *out);
int rs2(int fd);
int tc358870_init(int fd);

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

// Write 16-bit register, 8-bit data
int i2c_write8(int fd, uint16_t reg, uint8_t data) {
    uint8_t buf[3];
    buf[0] = (reg >> 8) & 0xFF;
    buf[1] = reg & 0xFF;
    buf[2] = data;

    if (write(fd, buf, 3) != 3) {
        klog("<3>tc358870: i2c_write8 failed at reg 0x%04X: %s", reg, strerror(errno));
        return -1;
    }

    uint8_t read_val = 0;
    if (i2c_read8(fd, reg, &read_val) != 0 || read_val != data) {
        klog("<3>tc358870: i2c_write8 verify failed at 0x%04X: wrote 0x%02X, read 0x%02X", reg, data, read_val);
        return -1;
    }

    klog("<6>tc358870: I2C8: Wrote 0x%02X to reg 0x%04X", data, reg);
    return 0;
}

// Write 16-bit register, 16-bit data
int i2c_write16(int fd, uint16_t reg, uint16_t data) {
    uint8_t buf[4];
    buf[0] = (reg >> 8) & 0xFF;
    buf[1] = reg & 0xFF;
    buf[2] = (data >> 8) & 0xFF;
    buf[3] = data & 0xFF;

    if (write(fd, buf, 4) != 4) {
         klog("<3>tc358870: i2c_write16 failed at reg 0x%04X: %s", reg, strerror(errno));
        return -1;
    }

    uint16_t read_val = 0;
    if (i2c_read16(fd, reg, &read_val) != 0 || read_val != data) {
        klog("<3>tc358870: i2c_write16 verify failed at 0x%04X: wrote 0x%04X, read 0x%04X", reg, data, read_val);
        return -1;
    }

    klog("<6>tc358870: I2C16: Wrote 0x%04X to reg 0x%04X", data, reg);
    return 0;
}

int i2c_read8(int fd, uint16_t reg, uint8_t *out) {
    uint8_t addr_buf[2] = {
        (reg >> 8) & 0xFF,
        reg & 0xFF
    };

    if (write(fd, addr_buf, 2) != 2) {
        klog("<3>tc358870: i2c_read8 - write failed at reg 0x%04X: %s", reg, strerror(errno));
        return -1;
    }

    if (read(fd, out, 1) != 1) {
        klog("<3>tc358870: i2c_read8 - read failed at reg 0x%04X: %s", reg, strerror(errno));
        return -1;
    }

    klog("<7>tc358870: I2C8: Read 0x%02X from reg 0x%04X", *out, reg);
    return 0;
}

int i2c_read16(int fd, uint16_t reg, uint16_t *out) {
    uint8_t addr_buf[2] = {
        (reg >> 8) & 0xFF,
        reg & 0xFF
    };
    uint8_t data[2];

    if (write(fd, addr_buf, 2) != 2) {
        klog("<3>tc358870: i2c_read16 - write failed at reg 0x%04X: %s", reg, strerror(errno));
        return -1;
    }

    if (read(fd, data, 2) != 2) {
        klog("<3>tc358870: i2c_read16 - read failed at reg 0x%04X: %s", reg, strerror(errno));
        return -1;
    }

    *out = (data[0] << 8) | data[1];

    klog("<7>tc358870: I2C16: Read 0x%04X from reg 0x%04X", *out, reg);
    return 0;
}

int rs2(int fd) {
    klog("<6>tc358870: RS2 - Ready state initialization started");

    // Enable Interrupts 
    i2c_write16(fd, 0x0016, 0x0D3F); // IntMask

    // Set HPD output to high
    i2c_write8(fd, 0x854A, 0x01); // SysCtl

    klog("<6>tc358870: RS2 complete, HPD asserted");
    return 0;
}


int tc358870_init(int fd) {
    klog("<6>tc358870: Starting soft reset + interrupt mask clear");

    // --- Reset & System Control ---
    //Sofware Reset
    i2c_write16(fd, 0x0004, 0x0004); // ConfCtl0 (Software Reset)
    i2c_write16(fd, 0x0002, 0x3F00); // SysCtl
    i2c_write16(fd, 0x0002, 0x0000); // SysCtl
    i2c_write16(fd, 0x0006, 0x0008); // ConfCtl1

    // HDMI Interrupt Mask, Clear
    i2c_write16(fd, 0x0016, 0x0F3F); // IntMask
    i2c_write8(fd,  0x8502, 0xFF);   // SYS_INT
    i2c_write8(fd,  0x850B, 0xFF);   // MISC_INT
    i2c_write16(fd, 0x0014, 0x0F3F); // IntStatus
    i2c_write8(fd,  0x8512, 0xFE);   // SYS_INTM
    i2c_write8(fd,  0x851B, 0xFD);   // MISC_INTM

    // --- HDMI PHY ---
    i2c_write8(fd, 0x8410, 0x03); // PHY CTL
    i2c_write8(fd, 0x8413, 0x3F); // PHY_ENB
    i2c_write8(fd, 0x8420, 0x07); // EQ_BYPS
    i2c_write8(fd, 0x84F0, 0x31); // APLL_CTL
    i2c_write8(fd, 0x84F4, 0x01); // DDCIO_CTL

    // --- HDMI Clock ---
    i2c_write16(fd, 0x8540, 0x12C0); // SYS_FREQ0_1
    i2c_write8(fd,  0x8630, 0x00);   // LOCKDET_FREQ0
    i2c_write16(fd, 0x8631, 0x0753); // LOCKDET_REF1_2
    i2c_write8(fd,  0x8670, 0x02);   // NCO_F0_MOD
    i2c_write16(fd, 0x8A0C, 0x12C0); // CSC_SCLK0_1

    // --- EDID Block ---
    i2c_write8(fd,  0x85E0, 0x01);   // EDID_MODE
    i2c_write16(fd, 0x85E3, 0x0100); // EDID_LEN1_2

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

    // --- HDCP and HDMI SYSTEM ---
    i2c_write8(fd, 0x8543, 0x02); // DDC_CTL
    i2c_write8(fd, 0x8544, 0x10); // HPD_CTL

    // --- HDMI AUDIO ---
    i2c_write8(fd, 0x8600, 0x00); // AUD_Auto_Mute
    i2c_write8(fd, 0x8602, 0xF3); // Auto_CMD0
    i2c_write8(fd, 0x8603, 0x02); // Auto_CMD1
    i2c_write8(fd, 0x8604, 0x0C); // Auto_CMD2
    i2c_write8(fd, 0x8606, 0x05); // BUFINIT_START
    i2c_write8(fd, 0x8607, 0x00); // FS_MUTE
    i2c_write8(fd, 0x8652, 0x02); // SDO_MODE1

    // --- HPD/EDID Detection ---
    uint8_t hpd_status = 0;
    i2c_read8(fd, 0x8520, &hpd_status);
    klog("<6>tc358870: HPD Status = 0x%02X", hpd_status);

    if (hpd_status & 0x01) {
        klog("<6>tc358870: HDMI cable detected. Entering RS2...");
        rs2(fd);
    }
    else {
        klog("<6>tc358870: No HDMI cable detected. Skipping RS2.");
    }

    // --- Enable Interrupts & Sleep ---
    i2c_write16(fd, 0x0016, 0x0F1F); // IntMask
    i2c_write16(fd, 0x0002, 0x0001); // SysCtl (Enter Sleep)

    klog("<6>tc358870: Init sequence completed.");
    return 0;
}

int main() {
    openlog("tc358870_init", LOG_PID | LOG_CONS, LOG_USER);

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
        return ret;
    }

    klog("<6>TC358870 RS1 init complete");
    klog("<6>TC358870 init sequence finished");
    closelog();
    close(fd);
    return ret;
}