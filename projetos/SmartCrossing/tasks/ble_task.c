#include "btstack_config.h"
#include <stdio.h>              // Biblioteca padrão de entrada/saída, usada para o printf().
#include <string.h>             // Biblioteca para manipulação de strings.
#include "pico/stdlib.h"         // Biblioteca principal do SDK do Raspberry Pi Pico.
#include "pico/cyw43_arch.h"     // Biblioteca para controle do chip wireless (CYW43439) da Pico W.
#include "btstack.h"             // Biblioteca principal da pilha de software Bluetooth (BTstack).
#include "FreeRTOS.h"
#include "task.h"
#include "udp_util.h"

void ble_task(void *params)
{
    if(xSemaphoreTake(sync_ble, portMAX_DELAY) == pdTRUE);

    init_ble_process();
}
