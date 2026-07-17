#include <stdio.h>             // Biblioteca padrão para entrada e saída, utilizada para printf.
#include "pico/stdlib.h"       // Biblioteca padrão para funções básicas do Pico, como GPIO e temporização.
#include "hardware/adc.h"      // Biblioteca para controle do ADC (Conversor Analógico-Digital).
#include "hardware/i2c.h"
#include "libraries/inc/ssd1306.h"

#define ADC_TEMPERATURE_CHANNEL 4   // Canal ADC que corresponde ao sensor de temperatura interno

// Definição dos pinos usados para o display:
const uint8_t I2C_SDA = 14;
const uint8_t I2C_SCL = 15;

uint8_t ssd[ssd1306_buffer_length]; // Buffer do display.
struct render_area frame_area = { // Area de renderização do display.
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
 * @brief converte o valor lido do ADC para graus Celsius.
 * @param adc_value valor lido pelo ADC
 */
float adc_to_temperature(uint16_t adc_value) {
    // Constantes fornecidas no datasheet do RP2040
    const float conversion_factor = 3.3f / (1 << 12);  // Conversão de 12 bits (0-4095) para 0-3.3V
    float voltage = adc_value * conversion_factor;     // Converte o valor ADC para tensão
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;  // Equação fornecida para conversão
    return temperature;
}

/**
 * @brief Escreve os valores da temperatura em Celsius e Farenheit no display.
 */
void printTempDisplay(float temp){
    char str_tempC[17];
    char str_tempF[17];
    sprintf(str_tempC, "    %.2f C      ", temp);
    sprintf(str_tempF, "    %.2f F      ", 32+1.8*temp);
    organizeStrings("  Temperatura:  ", str_tempC, str_tempF, ssd, frame_area);
}

int main() {
    // Inicializa a comunicação serial para permitir o uso de printf
    stdio_init_all();

    i2cInitDisplay(I2C_SDA, I2C_SCL); // Inicialização do i2c e do display OLED
    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)

    calculate_render_area_buffer_length(&frame_area);
    // Limpa o display
    
    clearDisplay(ssd, frame_area);

    // Inicializa o módulo ADC do Raspberry Pi Pico
    adc_init();

    // Seleciona o canal 4 do ADC (sensor de temperatura interno)
    adc_set_temp_sensor_enabled(true);  // Habilita o sensor de temperatura interno
    adc_select_input(ADC_TEMPERATURE_CHANNEL);  // Seleciona o canal do sensor de temperatura

    // Loop infinito para leitura contínua do valor de temperatura
    while (true) {
        // Lê o valor do ADC no canal selecionado (sensor de temperatura)
        uint16_t adc_value = adc_read();

        // Converte o valor do ADC para temperatura em graus Celsius
        float temperature = adc_to_temperature(adc_value);

        // Imprime a temperatura na comunicação serial
        printf("Temperatura em Celsius: %.2f °C\n", temperature);
        printf("Temperatura em Fahrenheit: %.2f °F\n", 32+1.8*temperature); // Converte e imprime a temperatura em Fahrenheit
        
        // Imprime a temperatura no display
        printTempDisplay(temperature);

        // Atraso de 1000 milissegundos (1 segundo) entre as leituras
        sleep_ms(1000);
    }

    return 0;
}
