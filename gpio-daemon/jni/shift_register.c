#include <stdint.h>
#include <unistd.h>
#include "gpio_mmio.h"

/*#define DATA_GPIO  0
#define CLOCK_GPIO 6
#define LATCH_GPIO 13*/

/*void shift_out(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
        int bit = (data >> i) & 1;
        set_gpio(DATA_GPIO, bit);
        set_gpio(CLOCK_GPIO, 1);
        usleep(1);
        set_gpio(CLOCK_GPIO, 0);
    }
    set_gpio(LATCH_GPIO, 1);
    usleep(1);
    set_gpio(LATCH_GPIO, 0);
}*/
