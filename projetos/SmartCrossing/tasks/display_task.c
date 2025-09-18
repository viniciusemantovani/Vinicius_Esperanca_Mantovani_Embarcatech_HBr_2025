#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "vl53l0x_wrapper.h"
#include "ssd1306.h"
#include "display_task.h"
#include "task_handles.h"
#include "traffic_light_control.h"

ssd1306_t disp;
bool time_count_on = 0;
absolute_time_t time = 0;

void write_in_display(uint32_t x, uint32_t y, uint32_t scale, const char *s)
{
    ssd1306_draw_string(&disp, x, y, scale, s);
    xTaskNotifyGive(handle_display_task);
}

void draw_line_in_display(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    ssd1306_draw_line(&disp, x1, y1, x2, y2);
    xTaskNotifyGive(handle_display_task);
}

void draw_empty_square_in_display(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    ssd1306_draw_empty_square(&disp, x, y, width, height);
    xTaskNotifyGive(handle_display_task);
}

// void time_in_display()
// {
//     time = get_absolute_time();
//     time_count_on = 0;
// }

void time_stop(){
    time_count_on = 0;
}

void clear_display()
{
    ssd1306_clear(&disp);
}

void display_task(void *params)
{
    i2c_init(I2C_PORT, 1000*1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
    vTaskDelay(pdMS_TO_TICKS(20));
    xTaskNotifyGive(handle_sensor_task);

    while(1)
    {
        ssd1306_show(&disp);
        ulTaskNotifyTake(pdTRUE, MAX_TIME_UPDATE_DISPLAY);

        absolute_time_t new_time;

        while(time_count_on == 1)
        {
            new_time == get_absolute_time();
            int64_t time_difference_us = absolute_time_diff_us(time, new_time);
            double time_difference_seconds = time_difference_us / 1000000;
            char time_string[3]; 
            snprintf(time_string, sizeof(time_string), "%.0f\0", time_green_people - time_difference_seconds);
            write_in_display(10, 20, 2, time_string);
            vTaskDelay(pdMS_TO_TICKS(200));
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }

}