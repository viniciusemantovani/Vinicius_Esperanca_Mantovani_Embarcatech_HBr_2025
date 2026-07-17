// Extending content from https://github.com/BitDogLab/BitDogLab-C/blob/main/neopixel_pio/neopixel_pio.c
// to use as a library.

#ifndef NEOPIXEL_H
#define NEOPIXEL_H

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição de pixel GRB
typedef struct{
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
}npLED_t;

/**
 * @brief Inicializa a máquina PIO para controle da matriz de LEDs.
 * @param pin: define o pino a 
 */
void np_init(uint pin);

/**
 * Atribui uma cor RGB a um LED.
 */
void np_set_led(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);

/**
 * Limpa o buffer de pixels.
 */
void np_clear();

/**
 * Escreve os dados do buffer nos LEDs.
 */
void np_write();

#endif