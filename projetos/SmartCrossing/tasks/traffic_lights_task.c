#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "traffic_lights_task.h"
#include "neopixel.h"
#include "traffic_light_control.h"
#include "display_task.h"
#include "task.h"
#include "semphr.h"
#include "udp_util.h"
#include "task_handles.h"
#include "main.h"

uint8_t traffic_state;

void traffic_lights_task(void *params)
{
    if(xSemaphoreTake(sync_light, portMAX_DELAY) == pdTRUE);

    np_init(LED_PIN);
    traffic_state = PEOPLE_GREEN;
    vTaskDelay(pdMS_TO_TICKS(200));

    if(comm_side == AP_TASK)
    {
        clear_display();
        led_red_on();
        np_write();
        write_in_display(10, 5, 2, "FECHADO!");
    }

    while(1)
    {
        switch (traffic_state)
        {
            case PEOPLE_GREEN:
                if(comm_side == STA_TASK)
                {
                    led_green_on();
                    np_write();
                    clear_display();
                    write_in_display(10, 5, 2, "ABERTO!");
                }
                // time_in_display();
                vTaskDelay(pdMS_TO_TICKS(get_time_green(PEOPLE)));
                traffic_state = PEOPLE_YELLOW;
                time_stop();
                break;
    
            case PEOPLE_YELLOW:
                set_time_green(PEOPLE, TIME_GREEN_PEOPLE_DEFAULT);
                if(comm_side == STA_TASK)
                {
                    led_yellow_on();
                    np_write();
                }
                vTaskDelay(pdMS_TO_TICKS(YELLOW_TIME));
                traffic_state = PEOPLE_RED;
                break;
    
            case PEOPLE_RED:
                if(comm_side == STA_TASK)
                {
                    led_red_on();
                    np_write();
                    clear_display();
                    write_in_display(10, 10, 2, "FECHADO!");
                }
                vTaskDelay(pdMS_TO_TICKS(get_time_to_turn_green(CAR)));
                traffic_state = CAR_GREEN;
                break;
    
            case CAR_GREEN:
                if(comm_side == AP_TASK)
                {
                    led_green_on();
                    np_write();
                    clear_display();
                    write_in_display(10, 5, 2, "ABERTO!");
                }            
                vTaskDelay(pdMS_TO_TICKS(TIME_TO_CLOSE_CAR_MIN));
                xTaskNotifyGive(handle_sensor_task);
                ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(get_time_green(CAR)));
                vTaskDelay(pdMS_TO_TICKS(TIME_TO_CLOSE_CAR_AFTER_PRESENCE));
                traffic_state = CAR_YELLOW;
                break;
    
            case CAR_YELLOW:
                if(comm_side == AP_TASK)
                {
                    led_yellow_on();
                    np_write();
                }   
                vTaskDelay(pdMS_TO_TICKS(YELLOW_TIME));
                traffic_state = CAR_RED;
                break;
    
            case CAR_RED:
                if(comm_side == AP_TASK)
                {
                    led_red_on();
                    np_write();
                    clear_display();
                    write_in_display(10, 5, 2, "FECHADO!");
                }   
                vTaskDelay(pdMS_TO_TICKS(get_time_to_turn_green(PEOPLE)));
                traffic_state = PEOPLE_GREEN;
                break;
    
            default:
                break;
        }

    }
}