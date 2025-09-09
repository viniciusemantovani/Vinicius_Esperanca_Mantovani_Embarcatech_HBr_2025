#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "vl53l0x_wrapper.h"
#include "sensor_task.h"
#include "task_handles.h"
#include "lwip/udp.h"
#include "udp_util.h"

#define VL0X_SDA 0
#define VL0X_SCL 1
#define I2C_PORT i2c0
#define SENSOR_ADDR 0x29

void sensor_task(void *params)
{
    i2c_init(I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(VL0X_SDA, GPIO_FUNC_I2C);
    gpio_set_function(VL0X_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(VL0X_SDA);
    gpio_pull_up(VL0X_SCL);

    // Create the sensor object using the wrapper function
    VL53L0X_t* sensor = VL53L0X_create(I2C_PORT, SENSOR_ADDR);

    if (sensor == NULL) {
        // printf("Problem creating sensor object!");
        return;
    }

    // Initialize the sensor
    if (!VL53L0X_init(sensor, true)) {
        VL53L0X_destroy(sensor); // Clean up
        // printf("Problem initializing sensor!");
        return;
    }
    
    uint16_t range = 0;

    while(1)
    {
        if(xSemaphoreTake(sync_sensor, portMAX_DELAY) == pdTRUE)
        {
            range = VL53L0X_readRangeSingleMillimeters(sensor);
    
            if (VL53L0X_timeoutOccurred(sensor)) {
            
            } else {
                if(ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
                {
                    vTaskDelay(pdMS_TO_TICKS(5));
                    if(range < 1000)
                    {
                        udp_send_message(udppcb, PERSON_DETECTED);
                        xTaskNotifyGive(handle_tl_task);
                    }
                }
            }
    
            xSemaphoreGive(sync_sensor);
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }

    VL53L0X_destroy(sensor);

}