#include <stdint.h>

/**
 * @brief converte o valor lido do ADC para graus Celsius.
 * @param adc_value valor lido pelo ADC
 */
float adc_to_temperature(uint16_t adc_value);