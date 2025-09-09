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
#include "dhcp_server.h"
#include "udp_util.h"

const char *AP_NAME = "RP_AP";
const char *AP_PASS = "Smart_Crossing";

void ap_task(void *params)
{
    sync_sensor = xSemaphoreCreateCounting(2, 0);
    sync_light = xSemaphoreCreateCounting(2, 0);
    
    vTaskDelay(pdMS_TO_TICKS(3000));

    if (cyw43_arch_init()) {
        printf("Failed to initialise cyw43\n");
    }

    cyw43_arch_enable_ap_mode(AP_NAME, AP_PASS, CYW43_AUTH_WPA2_AES_PSK);

    ip4_addr_t mask;
    ip_addr_t ap_ip;

    ap_ip.addr = PP_HTONL(CYW43_DEFAULT_IP_AP_ADDRESS);
    mask.addr = PP_HTONL(CYW43_DEFAULT_IP_MASK);

    dhcp_server_t dhcp_server;
    dhcp_server_init(&dhcp_server, &ap_ip, &mask);

    udp_init_recv(&udppcb);

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
