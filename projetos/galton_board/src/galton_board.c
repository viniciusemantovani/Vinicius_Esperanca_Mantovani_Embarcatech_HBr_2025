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

#define PIN_LINES 10

ssd1306_t disp; // Instância do display.

// Estrutura da bola e dos pinos:
typedef struct ball{
    uint8_t x;
    uint8_t y;    
} ball;

//  Estrutura das barras do histograma:
typedef struct bar{
    uint8_t ymin;
    uint8_t ymax;
    uint8_t num_bolas;
} bar;

/**
 * @brief Gera pinos e barras.
 * @param pins vetor de pinos.
 * @param bars vetor de barras do histograma.
 */
void gen_pins_position(ball *pins, bar *bars){
    ball init_pos = {8,30}; // Centro em (9,31)
    int count = 0;
    for(int i = 0; i < PIN_LINES; i++){
        ball aux = init_pos;
        for(int j = 0; j < i + 1; j++){
            pins[count] = aux;
            if(i == PIN_LINES-1){ // Última linha. ADD bars.
                bars[j].ymax = aux.y + 4;
                bars[j].ymin = aux.y + 1;
                if(j == PIN_LINES-1){
                    bars[j+1].ymax = aux.y;
                    bars[j+1].ymin = aux.y - 3;
                }                
            }
            ssd1306_draw_square(&disp, pins[count].x, pins[count].y, 2, 2);
            aux.y -= 4; // Começa a 2 de distância do centro do esquerdo.
            count++;
        }
        init_pos.x = init_pos.x + 4; // Começa a 6 de distância do centro do superior.
        init_pos.y = init_pos.y + 2; // Começa a 2 de distância do centro do superior à esquerda dele.
    }

    for(int i= 0; i < PIN_LINES + 1; i++ ){
        printf("bars %d = (%d <-> %d)", i, bars[i].ymin, bars[i].ymax);
    }
    ssd1306_show(&disp);
}

/**
 * @brief Gera uma direção aleatória.
 * @return False - esquerda, True - direita.
 */
bool gen_rand_direction(){
    uint32_t rand_num = get_rand_32();
    uint32_t divide = 4294967295/2;
    return !(rand_num <= divide);

}

/**
 * @brief Posiciona uma bola na posição inicial, o centro no topo do display.
 * @param ballx ponteiro para bola a ser modificada.
 */
void start_ball(ball *ballx){
    ballx->x = 0;
    ballx->y = 30; // Centro em 31
    ssd1306_draw_square(&disp, ballx->x, ballx->y, 2, 2);
    ssd1306_show(&disp);
}

/**
 * @brief Verifica se a bola colidiu com um pino e move horizontalmente caso sim.
 * @param ballx ponteiro para bola a ser verificada e modificada.
 */
void handle_colision(ball *ballx, ball *pins, int pins_total){
    for(int i = 0; i < pins_total; i++){
        if(ballx->y <= pins[i].y+1 && ballx->y+1 >= pins[i].y && ballx->x+1 == pins[i].x){
            bool direction = gen_rand_direction();
            ballx->y = direction ? ballx->y - 2 : ballx->y + 2;
        }
    }
}

/**
 * @brief Atualiza posição da bola.
 * @param ballx ponteiro para a bola a ser modificada.
 */
void update_ball(ball *ballx, ball *pins, bar *bars, int pins_total){

    // Histograma:
    if(ballx->x >= 63){
        for(int i = 0; i <= PIN_LINES+1; i++){
            if(ballx->y > bars[i].ymin && ballx->y < bars[i].ymax){
                bars[i].num_bolas++;
                ssd1306_draw_square(&disp, 127 - bars[i].num_bolas, bars[i].ymin+1, 1, 2);
            }
        }

        ssd1306_clear_square(&disp, ballx->x, ballx->y, 2, 2); 
        ssd1306_show(&disp);
        ballx->x = 0;
        ballx->y = 30;
        return;
    }

    ssd1306_clear_square(&disp, ballx->x, ballx->y, 2, 2);

    ballx->x++;
    handle_colision(ballx, pins, pins_total);
    ssd1306_draw_square(&disp, ballx->x, ballx->y, 2, 2);
    ssd1306_show(&disp);
}

int main()
{
    int pins_total = 0;
    for(int i = 0; i < PIN_LINES; i++){
        pins_total += i + 1;
    }

    //  Pinos:
    ball pins_position[pins_total];
    // Barras do histograma:
    bar bars[PIN_LINES+1];

    stdio_init_all();

    //-----------------------------------------------------------------
    // Inicialização Display:

    // I2C Initialisation. Using it at 1Mhz.
    i2c_init(I2C_PORT, 1000*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    // ssd1306_draw_string(&disp, 8, 8, 1, "Teste!");
    // ssd1306_draw_string(&disp, 8, 16, 1, "Teste!");
    // ssd1306_show(&disp); 

    //-----------------------------------------------------------------

    bool direction;
    ball bola;
    start_ball(&bola);
    sleep_ms(5000);
    gen_pins_position(pins_position, bars);
    // for(int i = 0; i < 136; i++){
    //     printf("pos pin %d = (%d, %d)\n\n", i, pins_position[i].x, pins_position[i].y);

    // }
    while (true) {
        update_ball(&bola, pins_position, bars, pins_total);
        // printf("bola x: %u  y: %u\n", bola.x, bola.y);
    }
}
