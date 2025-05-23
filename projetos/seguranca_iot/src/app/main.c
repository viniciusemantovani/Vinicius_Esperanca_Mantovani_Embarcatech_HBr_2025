#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "wifi_conn.h"
#include "mqtt_comm.h"    // Header file com as declarações locais
#include "lwip/apps/mqtt.h"       // Biblioteca MQTT do lwIP

#define WIFI_SSID "HSC"
#define WIFI_PASS "humbertosc744"
#define PC_IP "192.168.31.169"

int main()
{
    stdio_init_all();

    sleep_ms(5000);

    connect_to_wifi(WIFI_SSID, WIFI_PASS);
    mqtt_setup("RP_PI", PC_IP , NULL, NULL);
    mqtt_comm_publish("test", "mensagem\0", 9);
    while (true) {
        sleep_ms(1000);
    }
}
