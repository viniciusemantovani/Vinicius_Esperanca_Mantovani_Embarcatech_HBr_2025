#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "traffic_lights_task.h"
#include "neopixel.h"
#include "traffic_light_control.h"
#include "display_task.h"
#include "udp_util.h"

const char WIFI_SSID[] = "RP_AP";
const char WIFI_PASSWORD[] = "Smart_Crossing";

void sta_task(void *params)
{
    sync_sensor = xSemaphoreCreateCounting(2, 0);
    sync_light = xSemaphoreCreateCounting(2, 0);

    vTaskDelay(pdMS_TO_TICKS(3000));
    
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
    }
    else
    {
        printf("Wi-Fi init successfully\n");
    }

    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect\n");
    } 
    else
    {
        printf("successfully connected\n");
    }

    udp_init_recv(&udppcb);

    udp_send_message(udppcb, START);
    xSemaphoreGive(sync_light);
    xSemaphoreGive(sync_sensor);

    while(true)
    {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}