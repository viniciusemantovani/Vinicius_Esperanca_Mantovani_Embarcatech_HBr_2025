#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "ssd1306_font.h"
#include "hardware/i2c.h"
#include "libraries/inc/ssd1306.h"

// Definição dos pinos dos botões:
const uint8_t BUTTON_A = 5;
const uint8_t BUTTON_B = 6;

absolute_time_t actual_time = 0;
uint8_t count_secs = 9;
uint8_t countB = 0;
uint8_t counting = 0; // 0 - não conta; 1 - contando.
//----------------------------------------------------------------------------------
//DISPLAY:

const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;

uint8_t ssd[ssd1306_buffer_length];
struct render_area frame_area = {
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

void dispCountNum(int num, uint8_t *ssd, struct render_area frame_area){
  char str_resultado[17];
  char str_B_clicks[17];
  sprintf(str_resultado, " Count:  %d      ", num);
  sprintf(str_B_clicks,  " Clicks: %d      ", countB);
  organizeStrings("    Counter     ", str_resultado, str_B_clicks, ssd, frame_area);
}

//----------------------------------------------------------------------------------

void ButtonHandler(uint gpio, uint32_t event_mask){
  static absolute_time_t deb_time_B = 0;
  static absolute_time_t deb_time_A = 0;

  if(gpio == BUTTON_B){

    if(event_mask == GPIO_IRQ_EDGE_FALL && absolute_time_diff_us(deb_time_B, get_absolute_time()) > 30000){
      countB++;
      if(counting == 1){
        dispCountNum(count_secs, ssd, frame_area);
      }      
    } else if(event_mask = GPIO_IRQ_EDGE_RISE && absolute_time_diff_us(deb_time_B, get_absolute_time()) > 30000){
      deb_time_B = get_absolute_time();
    }

  }

  else if (gpio == BUTTON_A){
    if(event_mask == GPIO_IRQ_EDGE_FALL && absolute_time_diff_us(deb_time_A, get_absolute_time()) > 30000){
      count_secs = 9;
      countB = 0;
      counting = 1;
      actual_time = get_absolute_time();
      clearDisplay(ssd, frame_area);
      dispCountNum(count_secs, ssd, frame_area);  
    } else if(event_mask == GPIO_IRQ_EDGE_RISE && absolute_time_diff_us(deb_time_A, get_absolute_time()) > 30000){
      deb_time_A = get_absolute_time();
    }
  }

}

int main()
{
    stdio_init_all();

    // Inicializa botão A com pull_up:
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Inicializa botão B com pull_up:
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL|GPIO_IRQ_EDGE_RISE, 1, &ButtonHandler);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL|GPIO_IRQ_EDGE_RISE, 1, &ButtonHandler);

    i2cInitDisplay(I2C_SDA, I2C_SCL); // Inicialização do i2c e do display OLED
    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)

    calculate_render_area_buffer_length(&frame_area);
    // Limpa o display
    
    clearDisplay(ssd, frame_area);

    dispCountNum(count_secs, ssd, frame_area);

    while (true) {
      if(counting){
        dispCountNum(count_secs, ssd, frame_area);
        while(absolute_time_diff_us(actual_time, get_absolute_time()) < 1000000);
        actual_time = get_absolute_time();
        count_secs--;
        if(count_secs == 0){
          dispCountNum(count_secs, ssd, frame_area);
          counting = 0;
        }
      }
    }
}
