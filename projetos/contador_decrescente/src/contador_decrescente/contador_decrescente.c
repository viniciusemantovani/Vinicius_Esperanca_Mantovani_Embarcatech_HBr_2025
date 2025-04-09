#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "ssd1306_font.h"
#include "hardware/i2c.h"
#include "libraries/inc/ssd1306.h"

//----------------------------------------------------------------------------------
//DISPLAY:

const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;

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




void dispCountNum(int num, uint8_t *ssd, struct render_area frame_area){
  char str_resultado[17];
  sprintf(str_resultado, "       %d       ", num);
  organizeStrings("    COUNT     ", str_resultado, "                ", ssd, frame_area);
}

//----------------------------------------------------------------------------------

int main()
{
    stdio_init_all();
    i2cInitDisplay(I2C_SDA, I2C_SCL); // Inicialização do i2c e do display OLED
    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
      start_column : 0,
      end_column : ssd1306_width - 1,
      start_page : 0,
      end_page : ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);
    // Limpa o display
    uint8_t ssd[ssd1306_buffer_length];
    clearDisplay(ssd, frame_area);

    absolute_time_t actual_time = 0;
    uint8_t count_secs = 9;

    while (true) {
        printf("%d", count_secs);
        dispCountNum(count_secs, ssd, frame_area);
        while(absolute_time_diff_us(actual_time, get_absolute_time()) < 1000000);
        actual_time = get_absolute_time();
        count_secs--;
        if(count_secs == 255) count_secs = 9;
    }
}
