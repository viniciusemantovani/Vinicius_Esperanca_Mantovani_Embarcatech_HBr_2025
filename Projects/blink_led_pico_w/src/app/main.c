#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "include/hal_led.h"
#include "include/led_embutido.h"

int main() {
    stdio_init_all();
    if(init_wifi_module() == -1) return -1;

    while (true) {
        led_switch();
        sleep_ms(500);
    }
}