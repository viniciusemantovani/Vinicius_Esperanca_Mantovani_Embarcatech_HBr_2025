#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "include/ssd1306.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/rand.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15

// Estrutura da bola:
typedef struct ball{
    uint8_t x;
    uint8_t y;    
} ball;

//  Estrutura das barras do histograma:
typedef struct bar{
    uint8_t xmin;
    uint8_t xmax;
    uint8_t num_bolas;
} bar;

//  Pinos:
const ball pins_position[28] = {
                                    {63, 4},
                                    {60, 8}, {66, 8},
                                    {57, 12}, {63, 12}, {69, 12},
                                    {54, 16}, {60, 16}, {66, 16}, {72, 16},
                                    {51, 20}, {57, 20}, {63, 20}, {69, 20}, {75, 20},
                                    {48, 24}, {54, 24}, {60, 24}, {66, 24}, {72, 24}, {78, 24},
                                    {45, 28}, {51, 28}, {57, 28}, {63, 28}, {69, 28}, {75, 28}, {81, 28}
                               };

// Barras do histograma:
bar bars[8] =  {{39, 45, 0}, {45, 51, 0}, {51, 57, 0}, {57, 63, 0}, {63, 69, 0}, {69, 75, 0}, {75, 81, 0}, {81, 87, 0}};

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

/**TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 * TESTAR
 */

/**
 * @brief Atualiza posição da bola.
 * @param ballx ponteiro para a bola a ser modificada.
 */
void updateBall(ball *ballx){
    if(ballx->y >= 32){
        for(int i = 0; i <= 8; i++){
            if(ballx->x > bars[i].xmin && ballx->x < bars[i].xmax){
                bars[i].num_bolas++;
                printf("caiu no %u, número bolas: %u  ", bars[i].xmin, bars[i].num_bolas);
            }
        }
        ballx->x = 0;
        ballx->y = 0;
        return;
    }
    ballx->y++;
    handleColision(ballx);
}

int main()
{
    stdio_init_all();

    //-----------------------------------------------------------------
    // Inicialização Display:

    // I2C Initialisation. Using it at 1Mhz.
    i2c_init(I2C_PORT, 1000*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_t disp;
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 8, 8, 1, "Teste!");
    ssd1306_draw_string(&disp, 8, 16, 1, "Teste!");
    ssd1306_show(&disp);

    //-----------------------------------------------------------------

    bool direction;
    ball bola;
    startBall(&bola);

    while (true) {
        sleep_ms(1000);
        updateBall(&bola);
        printf("bola x: %u  y: %u\n", bola.x, bola.y);
    }
}
