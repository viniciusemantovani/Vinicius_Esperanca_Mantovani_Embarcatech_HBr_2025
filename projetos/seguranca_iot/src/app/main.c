#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "wifi_conn.h"
#include "mqtt_comm.h"    // Header file com as declarações locais
#include "lwip/apps/mqtt.h"       // Biblioteca MQTT do lwIP

int main()
{
    stdio_init_all();

    sleep_ms(5000);

    connect_to_wifi("HBR Guest", "Visit@8523");
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
