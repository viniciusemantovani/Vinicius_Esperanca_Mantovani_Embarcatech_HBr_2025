#include "pico/cyw43_arch.h"
#include "led_embutido.h"

int init_wifi_module(){
    if (cyw43_arch_init()) {
        return -1;
    }
    return 1;
}

void led_on(){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}

void led_off(){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}