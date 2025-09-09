#ifndef UDP_RECEIVE_H
#define UDP_RECEIVE_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "pico/stdlib.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#define START "start"
#define ACK "ack"
#define PERSON_DETECTED "pd"

#define UDP_PORT 4444
#define AP_IP "192.168.4.1"

extern SemaphoreHandle_t sync_sensor;
extern SemaphoreHandle_t sync_light;
extern struct udp_pcb *udppcb;

void udp_init_recv(struct udp_pcb **pcb);

void udp_send_message(struct udp_pcb *pcb, char *message);

void udp_recv_function(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

#endif