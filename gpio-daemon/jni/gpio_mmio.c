#include "gpio_mmio.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>

#define GPIO_BASE  0xFE200000
#define PWM_BASE   0xFE20C000
#define CLK_BASE   0xFE101000
#define BLOCK_SIZE 4096

static volatile uint32_t* gpio_map = NULL;
static volatile uint32_t* pwm_map  = NULL;
static volatile uint32_t* clk_map  = NULL;

void setup_hardware_pwm() {
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("open /dev/mem");
        return;
    }

    gpio_map = (uint32_t*) mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
    pwm_map  = (uint32_t*) mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, PWM_BASE);
    clk_map  = (uint32_t*) mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, CLK_BASE);
    close(mem_fd);
}

/*void set_gpio_alt(int gpio, int alt) {
    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    gpio_map[reg] = (gpio_map[reg] & ~(7 << shift)) | ((4  ALT0 ) << shift);
}*/

void set_gpio_alt(int gpio, int alt) {
    printf("Setting GPIO%d to ALT%d\n", gpio, alt );  // ✅ Confirm real value used
    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    gpio_map[reg] = (gpio_map[reg] & ~(7 << shift)) | ((alt & 0x7) << shift);
}

/*void set_gpio_alt(int gpio, int alt) {
    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    gpio_map[reg] = (gpio_map[reg] & ~(7 << shift)) | ((alt & 0x7) << shift);
}*/

void set_pwm_duty(int duty) {
    // Stop PWM clock
    clk_map[40] = 0x5A000000 | (1 << 5);      // Kill clock
    usleep(10);

    // Set clock divider (to 100kHz)
    clk_map[41] = 0x5A000000 | (540 << 12);   // Divider = 540
    usleep(10);

    // Start PWM clock
    clk_map[40] = 0x5A000011;                 // Enable | source=oscillator
    usleep(10);

    // Reset PWM control
    pwm_map[0] = 0;          // Disable all
    usleep(10);

    pwm_map[4] = 1024;       // Range
    pwm_map[5] = duty;       // Data
    usleep(10);

    pwm_map[0] = 0x81;       // Enable PWM0 (bit 0) | MSEN0 (bit 7)
}

void debug_gpio_fsel(int gpio) {
    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    int val = (gpio_map[reg] >> shift) & 0x7;
    printf("GPIO%d ALT function set to: %d\n", gpio, val);
}

void set_gpio_input(int gpio) {
    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    gpio_map[reg] &= ~(7 << shift);  // Set function to 000 → INPUT
}
