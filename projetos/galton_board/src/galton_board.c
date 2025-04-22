#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/rand.h"

// #define I2C_PORT i2c1
// #define I2C_SDA 14
// #define I2C_SCL 15

/**
 * @brief Gera uma direção aleatória.
 * @return False - esquerda, True - direita.
 */
bool genRandDirection(){
    uint32_t rand_num = get_rand_32();
    uint32_t divide = 4294967295/2;
    if(rand_num <= divide){
        return false;
    } else{
        return true;
    }
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
    while (true) {
        sleep_ms(1000);

    }
}
