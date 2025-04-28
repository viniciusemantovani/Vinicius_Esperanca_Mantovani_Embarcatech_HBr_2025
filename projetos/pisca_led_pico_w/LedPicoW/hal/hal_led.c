#include "pico/cyw43_arch.h"
#include "led_embutido.h"
#include "hal_led.h"

void led_switch(){
    if(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN)) led_off();
    else led_on();
}