#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/rand.h"

// #define I2C_PORT i2c1
// #define I2C_SDA 14
// #define I2C_SCL 15

// Estrutura da bola:
typedef struct ball{
    uint8_t x;
    uint8_t y;    
} ball;

//Estrutura das barras do histograma:
typedef struct bars{
    uint8_t xmin;
    uint8_t xmax;
} bars;

//Pinos:
const ball pins_position[28] = {
                                {63, 4},
                                {60, 8}, {66, 8},
                                {57, 12}, {63, 12}, {69, 12},
                                {54, 16}, {60, 16}, {66, 16}, {72, 16},
                                {51, 20}, {57, 20}, {63, 20}, {69, 20}, {75, 20},
                                {48, 24}, {54, 24}, {60, 24}, {66, 24}, {72, 24}, {78, 24},
                                {45, 28}, {51, 28}, {57, 28}, {63, 28}, {69, 28}, {75, 28}, {81, 28}
                               };

/**
 * @brief Gera uma direção aleatória.
 * @return False - esquerda, True - direita.
 */
bool genRandDirection(){
    uint32_t rand_num = get_rand_32();
    uint32_t divide = 4294967295/2;
    return !(rand_num <= divide);

}

/**
 * @brief Posiciona uma bola na posição inicial, o centro no topo do display.
 * @param ballx ponteiro para bola a ser modificada.
 */
void startBall(ball *ballx){
    ballx->x = 63;
    ballx->y = 0;
}

/**
 * @brief Verifica se a bola colidiu com um pino e move horizontalmente caso sim.
 * @param ballx ponteiro para bola a ser verificada e modificada.
 */
void handleColision(ball *ballx){
    for(int i = 0; i < 28; i++){
        if(ballx->y == pins_position[i].y && ballx->x == pins_position[i].x){
            bool direction = genRandDirection();
            ballx->x = direction ? ballx->x + 3 : ballx->x - 3;
        }
    }
}

/**
 * @brief Atualiza posição da bola.
 * @param ballx ponteiro para a bola a ser modificada.
 */
void updateBall(ball *ballx){
    ballx->y++;
    handleColision(ballx);
}

int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    // i2c_init(I2C_PORT, 400*1000);
    
    // gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SDA);
    // gpio_pull_up(I2C_SCL);

    bool direction;
    ball bola;
    startBall(&bola);

    while (true) {
        sleep_ms(1000);
        updateBall(&bola);
        printf("bola x: %u  y: %u\n", bola.x, bola.y);
    }
}
