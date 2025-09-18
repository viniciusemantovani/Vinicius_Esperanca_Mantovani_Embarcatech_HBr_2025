#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define MAX_DIST_PEDESTER_DETECTION 100

void sensor_task(void *params);

#endif