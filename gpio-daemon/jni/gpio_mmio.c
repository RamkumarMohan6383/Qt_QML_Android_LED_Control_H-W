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

void set_gpio_alt(int gpio, int alt) {
    int reg = gpio / 10;
    int shift = (gpio % 10) * 3;
    gpio_map[reg] = (gpio_map[reg] & ~(7 << shift)) | ((4 /* ALT0 */) << shift);
}

void set_pwm_duty(int duty) {
    clk_map[40] = 0x5A000000 | (1 << 5);      // Kill clock
    usleep(10);
    clk_map[41] = 0x5A000000 | (540 << 12);   // Divider = 540 → 100kHz
    clk_map[40] = 0x5A000011;                 // Enable PWM clock
    usleep(10);

    pwm_map[0] = 0;
    usleep(10);
    pwm_map[4] = 1024;                        // Range
    pwm_map[5] = duty;                        // Data (duty cycle)
    usleep(10);
    pwm_map[0] = 0x81;                        // Enable PWM0, MSEN0
}
