#ifndef TASK_HANDLES_H
#define TASK_HANDLES_H

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t handle_tl_task;
extern TaskHandle_t handle_sensor_task;
extern TaskHandle_t handle_display_task;
extern TaskHandle_t handle_ap_task;
extern TaskHandle_t handle_sta_task;
extern TaskHandle_t handle_ble_task;

#endif