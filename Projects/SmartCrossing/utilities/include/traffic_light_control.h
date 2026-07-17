#ifndef LED_STATE_H
#define LED_STATE_H

#define GREEN_LED_NUM                   17
#define YELLOW_LED_NUM                  12
#define RED_LED_NUM                     7

#define TIME_GREEN_PEOPLE_DEFAULT           10000
#define TIME_GREEN_CAR_DEFAULT              10000
#define TIME_TO_TURN_GREEN_PEOPLE_DEFAULT   3000
#define TIME_TO_TURN_GREEN_CAR_DEFAULT      3000
#define TIME_TO_CLOSE_CAR_AFTER_PRESENCE    3000
#define TIME_TO_CLOSE_CAR_MIN               3000

#define YELLOW_TIME                         3000

#define IS_PEOPLE(var)              ((var) == PEOPLE)
#define IS_CAR(var)                 ((var) == CAR)

extern uint16_t time_green_people;
extern uint16_t time_green_car;
extern uint16_t time_to_turn_green_people;
extern uint16_t time_to_turn_green_car;

enum TrafficState
{
    PEOPLE_GREEN = 0,
    PEOPLE_YELLOW,
    PEOPLE_RED,
    CAR_GREEN,
    CAR_YELLOW,
    CAR_RED
};

enum Entity
{
    PEOPLE = 0,
    CAR
};

void led_green_on();

void led_red_on();

void led_yellow_on();

void set_time_green(uint8_t people_or_car, uint16_t new_time);

void set_time_to_turn_green(uint8_t people_or_car, uint16_t new_time);

uint16_t get_time_green(uint8_t people_or_car);

uint16_t get_time_to_turn_green(uint8_t people_or_car);

#endif