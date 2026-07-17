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
    sync_sensor = xSemaphoreCreateBinary();
    sync_light = xSemaphoreCreateBinary();
    sync_ble = xSemaphoreCreateBinary();
    
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_BRAZIL)) {
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
    xSemaphoreGive(sync_ble);

    while(true)
    {
        if(time_changed_ble == 1)
        {
            char time_send_str[12];
            sprintf(time_send_str, "time:%d\0", get_time_green(PEOPLE));
            udp_send_message(udppcb, time_send_str);
            printf("%s\n", time_send_str);
            time_changed_ble = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}