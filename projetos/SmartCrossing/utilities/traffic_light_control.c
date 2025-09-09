#include <stdlib.h>
#include "pico/stdlib.h"
#include "neopixel.h"
#include "traffic_light_control.h"

uint16_t time_green_people = TIME_GREEN_PEOPLE_DEFAULT;
uint16_t time_green_car = TIME_GREEN_CAR_DEFAULT - (TIME_TO_CLOSE_CAR_MIN + TIME_TO_CLOSE_CAR_AFTER_PRESENCE);
uint16_t time_to_turn_green_people = TIME_TO_TURN_GREEN_PEOPLE_DEFAULT;
uint16_t time_to_turn_green_car = TIME_TO_TURN_GREEN_CAR_DEFAULT;

void led_green_on(uint8_t people_or_car)
{
    
    if(people_or_car == PEOPLE)
    {
        np_set_led(PEOPLE_RED_LED_NUM, 0, 0, 0);
        np_set_led(PEOPLE_GREEN_LED_NUM, 0, 200, 0);
    } 
    else if(people_or_car == CAR)
    {
        np_set_led(CAR_RED_LED_NUM, 0, 0, 0);
        np_set_led(CAR_GREEN_LED_NUM, 0, 200, 0);
    }
}

void led_red_on(uint8_t people_or_car)
{
    
    if(people_or_car == PEOPLE)
    {
        np_set_led(PEOPLE_YELLOW_LED_NUM, 0, 0, 0);
        np_set_led(PEOPLE_RED_LED_NUM, 200, 0, 0);
    } 
    else if(people_or_car == CAR)
    {
        np_set_led(CAR_YELLOW_LED_NUM, 0, 0, 0);
        np_set_led(CAR_RED_LED_NUM, 200, 0, 0);
    }
}

void led_yellow_on(uint8_t people_or_car)
{
    if(people_or_car == PEOPLE)
    {
        np_set_led(PEOPLE_GREEN_LED_NUM, 0, 0, 0);
        np_set_led(PEOPLE_YELLOW_LED_NUM, 200, 200, 0);
    } 
    else if(people_or_car == CAR)
    {
        np_set_led(CAR_GREEN_LED_NUM, 0, 0, 0);
        np_set_led(CAR_YELLOW_LED_NUM, 200, 200, 0);
    }
}

uint16_t get_time_green(uint8_t people_or_car)
{
    if(IS_PEOPLE(people_or_car))
    {
        return time_green_people;
    }
    else if(IS_CAR(people_or_car))
    {
        return time_green_car;
    }
}

uint16_t get_time_to_turn_green(uint8_t people_or_car)
{
    if(IS_PEOPLE(people_or_car))
    {
        return time_to_turn_green_people;
    }
    else if(IS_CAR(people_or_car))
    {
        return time_to_turn_green_car;
    }
}

void set_time_green(uint8_t people_or_car, uint16_t new_time)
{
    if(IS_PEOPLE(people_or_car))
    {
        time_green_people = new_time;
    }
    else if(IS_CAR(people_or_car))
    {
        time_green_car = new_time;
    }
}

void set_time_to_turn_green(uint8_t people_or_car, uint16_t new_time)
{
    if(IS_PEOPLE(people_or_car))
    {
        time_to_turn_green_people = new_time;
    }
    else if(IS_CAR(people_or_car))
    {
        time_to_turn_green_car = new_time;
    }
}