#include <stdio.h>
#include "pico/stdlib.h"
#include "mpu6050_i2c.h"

int main() {
    stdio_init_all();           // Inicializa USB serial
    mpu6050_setup_i2c();       // Configura barramento I2C
    mpu6050_reset();           // Reinicia o sensor

    int16_t accel[3], gyro[3], temp;

    while (1) {
        mpu6050_read_raw(accel, gyro, &temp); // Armazena valores lidos nas variaveis

        printf("Accel X: %d, Y: %d, Z: %d\n", accel[0], accel[1], accel[2]);
        sleep_ms(1000); // espera 1 segundo
    }
}