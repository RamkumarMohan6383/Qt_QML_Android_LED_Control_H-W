#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "gpio_mmio.h"

#define SOCKET_PATH "/data/local/tmp/gpiod.sock"
#define ALT0 4
#define ALT1 5
#define ALT2 6
#define ALT3 7
#define ALT4 3
#define ALT5 2

void handle_client(int fd) {
    int cmd, val;
    while (read(fd, &cmd, sizeof(int)) > 0 &&
           read(fd, &val, sizeof(int)) > 0) {
         printf("Received cmd: %d, val: %d\n", cmd, val);  // <-- Add this
        switch (cmd) {
        case 4: set_pwm_duty(val); break;
        case 5: set_pwm_duty(1023); break;
        case 6: set_pwm_duty(0); break;
        }
    }
    close(fd);
}

int main() {
    setup_hardware_pwm();
    set_gpio_alt(18, ALT5); // GPIO12 ALT0 → PWM0 //GPIO18 ALT5 -> PWM0
    debug_gpio_fsel(18); // Optional debug
    set_gpio_input(12);       // Disable PWM0 on GPIO12
    set_pwm_duty(1023);
    unlink(SOCKET_PATH);
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    chmod(SOCKET_PATH, 0666);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd >= 0) handle_client(client_fd);
    }
    return 0;
}
