#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udp_util.h"
#include "task_handles.h"

struct udp_pcb *udppcb = NULL;
SemaphoreHandle_t sync_sensor;
SemaphoreHandle_t sync_light;

ip4_addr_t ip_other_pico;
bool ip_other_pico_is_set = false;

void udp_init_recv(struct udp_pcb **pcb)
{
    *pcb = udp_new();
    udp_bind(*pcb, IP_ADDR_ANY, UDP_PORT); 
    udp_recv(*pcb, udp_recv_function, NULL);
}

void udp_send_message(struct udp_pcb *pcb, char *message)
{
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, strlen(message), PBUF_RAM);
    pbuf_take(p, message, strlen(message));

    if(ip_other_pico_is_set)
    {
        udp_sendto(pcb, p, &ip_other_pico, UDP_PORT);
    }
    else
    {
        ip4addr_aton(AP_IP, &ip_other_pico);
        udp_sendto(pcb, p, &ip_other_pico, UDP_PORT);
        ip_other_pico_is_set = true;
    }
}

void udp_recv_function(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    if (p != NULL)
    {
        char buffer[p->tot_len + 1];
        pbuf_copy_partial(p, buffer, p->tot_len, 0);
        buffer[p->tot_len] = '\0';

        if(!ip_other_pico_is_set)
        {
            ip_other_pico = *addr;
            ip_other_pico_is_set = true;
        }

        if(!strcmp(buffer, START))
        {
            xSemaphoreGive(sync_light);
            xSemaphoreGive(sync_sensor);
            udp_send_message(udppcb, ACK);
        }
        else if(!strcmp(buffer, ACK))
        {

        }
        else if(!strcmp(buffer, PERSON_DETECTED))
        {
            xTaskNotifyGive(handle_tl_task);
        }

        pbuf_free(p);
    }
}