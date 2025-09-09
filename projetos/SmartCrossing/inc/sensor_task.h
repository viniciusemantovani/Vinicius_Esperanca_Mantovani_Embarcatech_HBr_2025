#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void sensor_task(void *params);

#endif