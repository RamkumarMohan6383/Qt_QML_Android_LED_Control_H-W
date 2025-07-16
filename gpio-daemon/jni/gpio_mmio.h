#ifndef GPIO_MMIO_H
#define GPIO_MMIO_H

void setup_hardware_pwm();
void set_pwm_duty(int duty);
void set_gpio_alt(int gpio, int alt);
void debug_gpio_fsel(int gpio);
void set_gpio_input(int gpio);

#endif
