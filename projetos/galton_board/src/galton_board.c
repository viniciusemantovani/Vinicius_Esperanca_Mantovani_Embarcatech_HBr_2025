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

//Pinos:
const ball pins_position[10] = {{63, 7}, {60, 14}, {66, 14}, {56, 21}, {63, 21}, {70, 21}, {53, 28}, {60, 28}, {66, 28}, {73, 28}};

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
    for(int i = 0; i < 10; i++){
        if(ballx->y + 1 == pins_position[i].y && ballx->x == pins_position[i].x){
            bool direction = genRandDirection();
            ballx->x = direction ? ballx->x + 1 : ballx->x - 1;
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

    while (true) {
        sleep_ms(100);
        
    }
}
