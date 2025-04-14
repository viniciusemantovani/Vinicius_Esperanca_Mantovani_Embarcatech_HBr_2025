#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "libraries/joystick.h"
#include "libraries/inc/ssd1306.h"

// Definição dos pinos usados para o display:
const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;

uint8_t ssd[ssd1306_buffer_length]; // Buffer do display.
struct render_area frame_area = { // Área de renderização display.
  start_column : 0,
  end_column : ssd1306_width - 1,
  start_page : 0,
  end_page : ssd1306_n_pages - 1
};

/**
 * @brief Escreve um conjunto de strings no display dada uma mensagem.
 * @param text vetor de strings para serem impressos no display
 * @param ssd buffer do display
 * @param frame_area area do quadro
*/ 
void writeString(char **text, uint8_t *ssd, struct render_area frame_area){
    int y = 0;
    for (uint i = 0; i < count_of(*text); i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);
}

/**
 * @brief Organiza um conjunto de strings e envia para serem escritas no display.
 * @param str1 primeira linha
 * @param str2 segunda linha
 * @param str3 terceira linha
 * @param ssd buffer do display
 * @param frame_area area do quadro
*/ 
void organizeStrings(char *str1, char *str2, char *str3, uint8_t *ssd, struct render_area frame_area){
    char *msg[] = {str1, str2, str3, "                "};
    writeString(msg, ssd, frame_area); // Escreve a mensagem no display
}

/**
 * @brief Escreve os valores de leitura do joystick no display.
 * @param Valor lido pelo ADC no eixo x
 * @param Valor lido pelo ADC no eixo y
 */
void writeValuesOnDisplay(uint16_t vrx_value, uint16_t vry_value){
    char str_vx[17];
    char str_vy[17];

    sprintf(str_vx, "Eixo X: %d", vrx_value);
    sprintf(str_vy, "Eixo Y: %d", vry_value);

    if(vrx_value < 1000){
        sprintf(str_vx, "Eixo X: 0%d", vrx_value);
    } else if(vry_value < 1000){
        sprintf(str_vy, "Eixo Y: 0%d", vry_value);
    }

    organizeStrings("    JOYSTICK    ", str_vy, str_vx, ssd, frame_area);
}

int main()
{
    uint16_t vrx_value, vry_value; // Para armazenar valores dos eixos x e y do joystick.

    stdio_init_all();

    i2cInitDisplay(I2C_SDA, I2C_SCL); // Inicialização do i2c e do display OLED
    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)

    calculate_render_area_buffer_length(&frame_area);
    // Limpa o display
    
    clearDisplay(ssd, frame_area);

    setup_joystick(); //Inicaliza o joystick.

    while (true) {
        joystick_read_axis(&vrx_value, &vry_value); // Lê valores do joystick (0-4095)
        writeValuesOnDisplay(vrx_value, vry_value);
    }
}
