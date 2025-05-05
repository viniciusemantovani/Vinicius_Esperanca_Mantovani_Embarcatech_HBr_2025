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

// Definição dos pinos dos botões:
#define BUTTON_A 5
#define BUTTON_B 6

#define PIN_LINES 12 // Número de linhas de pinos
#define FREQ 60 // Frequência de atualização do display

// Variávei que desequilibra a probabilidade:
volatile int8_t left_right = 0;

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
 * @brief Handler de interrupções para os botões.
 * @param gpio indica o número do gpio que gera a interrupção
 * @param event_mask indica o número referente ao evento que gera a interrupção
 */
void ButtonHandler(uint gpio, uint32_t event_mask){
    static absolute_time_t deb_time_B = 0; // Contador para debounce do botão B
    static absolute_time_t deb_time_A = 0; // Contador para debounce do botão A
  
    if(gpio == BUTTON_B){ // Para o botão B, soma um ao contador caso esteja contando e atualiza o display.
  
        if(event_mask == GPIO_IRQ_EDGE_FALL && absolute_time_diff_us(deb_time_B, get_absolute_time()) > 800){
            if(left_right <= 2) left_right++;
        } else if(event_mask = GPIO_IRQ_EDGE_RISE && absolute_time_diff_us(deb_time_B, get_absolute_time()) > 800){
            deb_time_B = get_absolute_time();
        }
  
    }
  
    else if (gpio == BUTTON_A){ // Para o botão A, atualiza o contador de segundos, reiniciando a contagem e atualizando o display para o início.
        if(event_mask == GPIO_IRQ_EDGE_FALL && absolute_time_diff_us(deb_time_A, get_absolute_time()) > 800){
            if(left_right >= -2) left_right--;
        } else if(event_mask == GPIO_IRQ_EDGE_RISE && absolute_time_diff_us(deb_time_A, get_absolute_time()) > 800){
            deb_time_A = get_absolute_time();
        }
    }
  
}

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
                bars[j].num_bolas = 0;

                if(j == PIN_LINES-1){
                    bars[j+1].ymax = aux.y;
                    bars[j+1].ymin = aux.y - 3;
                    bars[j+1].num_bolas = 0;

                }                
            }
            ssd1306_draw_square(&disp, pins[count].x, pins[count].y, 2, 2);

            aux.y -= 4; // Começa a 2 de distância do centro do esquerdo.
            count++;
        }
        init_pos.x = init_pos.x + 4; // Começa a 6 de distância do centro do superior.
        init_pos.y = init_pos.y + 2; // Começa a 2 de distância do centro do superior à esquerda dele.
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
    return !(rand_num <= divide + left_right*500000000);

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
        for(int i = 0; i < PIN_LINES+1; i++){
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
    stdio_init_all();

    int pins_total = 0;
    for(int i = 0; i < PIN_LINES; i++){
        pins_total += i + 1;
    }

    //  Pinos:
    ball pins_position[pins_total];
    // Barras do histograma:
    bar bars[PIN_LINES+1];

    //-----------------------------------------------------------------
    // Inicialização Botões:

    // Inicializa botão A com pull_up:
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Inicializa botão B com pull_up:
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Preparando interrupções para os botões:
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL|GPIO_IRQ_EDGE_RISE, 1, &ButtonHandler);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL|GPIO_IRQ_EDGE_RISE, 1, &ButtonHandler);

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

    gen_pins_position(pins_position, bars); ///ERRADO PARA MAIS QUE 10

    while (true) {
        update_ball(&bola, pins_position, bars, pins_total);
    }
}
