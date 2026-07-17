#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/i2c.h"

#include "include/buzzer_pwm.h"

// Definição dos pinos dos botões:
#define BUTTON_A 5
#define BUTTON_B 6

// Definição dos pinos do LED RGB:
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13

TaskHandle_t led_task_handle = NULL;
TaskHandle_t buzzer_task_handle = NULL;

void led_task() {

  gpio_init(LED_PIN_GREEN);
  gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
  gpio_init(LED_PIN_BLUE);
  gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
  gpio_init(LED_PIN_RED);
  gpio_set_dir(LED_PIN_RED, GPIO_OUT);

  while (true) {
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_GREEN, 1);
    vTaskDelay(500);
    gpio_put(LED_PIN_GREEN, 0);
    gpio_put(LED_PIN_BLUE, 1);
    vTaskDelay(500);
    gpio_put(LED_PIN_BLUE, 0);
    gpio_put(LED_PIN_RED, 1);
    vTaskDelay(500);
  }
}

void buzzer_task() {
  pwm_init_audio(BUZZER_PIN);
  while(true){
    play_tone(BUZZER_PIN, 300, 100);
    vTaskDelay(1000);
  }
}

void button_task() {

  // Inicializa botão A com pull_up:
  gpio_init(BUTTON_A);
  gpio_set_dir(BUTTON_A, GPIO_IN);
  gpio_pull_up(BUTTON_A);

  // Inicializa botão B com pull_up:
  gpio_init(BUTTON_B);
  gpio_set_dir(BUTTON_B, GPIO_IN);
  gpio_pull_up(BUTTON_B);

  static bool buzzer_on = true;
  static bool led_on = true;

  while(true){
    if(!gpio_get(BUTTON_A)){
      if(led_on) {
        led_on = false;
        vTaskSuspend(led_task_handle);
      }
      else{
        led_on = true;
        vTaskResume(led_task_handle);
      }
    }
    if(!gpio_get(BUTTON_B)){
      if(buzzer_on) {
        buzzer_on = false;
        vTaskSuspend(buzzer_task_handle);
      }
      else{
        buzzer_on = true;
        vTaskResume(buzzer_task_handle);
      }    
    }

    vTaskDelay(100);
  }
}

int main() {
  stdio_init_all();

  xTaskCreate(led_task, "LED_Task", 256, NULL, 1, &led_task_handle);
  xTaskCreate(buzzer_task, "BUZZER_Task", 256, NULL, 1, &buzzer_task_handle);
  xTaskCreate(button_task, "BUTTON_Task", 256, NULL, 2, NULL);
  vTaskStartScheduler();

  while(1){};
}