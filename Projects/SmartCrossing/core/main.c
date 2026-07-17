#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "traffic_lights_task.h"
#include "sensor_task.h"
#include "display_task.h"
#include "ap_task.h"
#include "sta_task.h"
#include "ble_task.h"
#include "task_handles.h"
#include "main.h"

#define BUTTON_A 5
#define BUTTON_B 6

TaskHandle_t handle_tl_task         = NULL;
TaskHandle_t handle_sensor_task     = NULL;
TaskHandle_t handle_display_task    = NULL;
TaskHandle_t handle_ap_task         = NULL;
TaskHandle_t handle_sta_task        = NULL;
TaskHandle_t handle_ble_task        = NULL;

bool comm_side = 0;

void init_buttons(){

  // Inicializa botão A com pull_up:
  gpio_init(BUTTON_A);
  gpio_set_dir(BUTTON_A, GPIO_IN);
  gpio_pull_up(BUTTON_A);

  // Inicializa botão B com pull_up:
  gpio_init(BUTTON_B);
  gpio_set_dir(BUTTON_B, GPIO_IN);
  gpio_pull_up(BUTTON_B);

}

int main() {

    bool button_pressed = 0;

    stdio_init_all();

    init_buttons();

    while (1)
    {
        if(!gpio_get(BUTTON_A))
        {
            xTaskCreate(ap_task, "Access Point", configMINIMAL_STACK_SIZE + 256, NULL, 1, &handle_ap_task);
            comm_side = AP_TASK;
            break;
        }
        else if(!gpio_get(BUTTON_B))
        {
            xTaskCreate(sta_task, "Station", configMINIMAL_STACK_SIZE + 256, NULL, 1, &handle_sta_task);
            comm_side = STA_TASK;
            break;
        }
    }

    xTaskCreate(traffic_lights_task, "Traffic Lights", configMINIMAL_STACK_SIZE + 256, NULL, 1, &handle_tl_task);
    xTaskCreate(sensor_task, "Presence Sensor", configMINIMAL_STACK_SIZE + 256, NULL, 1, &handle_sensor_task);
    xTaskCreate(display_task, "Display", configMINIMAL_STACK_SIZE + 256, NULL, 1, &handle_display_task);
    xTaskCreate(ble_task, "Bluetooth App", configMINIMAL_STACK_SIZE + 256, NULL, 1, &handle_ble_task);

    vTaskStartScheduler();

    while (1)
    {
        
    }

    return 0;
}
