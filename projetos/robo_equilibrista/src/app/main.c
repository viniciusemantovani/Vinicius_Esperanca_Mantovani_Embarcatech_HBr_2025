#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "motor.h"
#include "mpu6050_i2c.h"

int main() {
    stdio_init_all();
    mpu6050_setup_i2c();
    mpu6050_reset();
    motor_setup();

    int16_t accel_raw[3], gyro_raw[3], temp;
    float accel[3], gyro[3];

    while( true ) {
        mpu6050_read_raw( accel_raw, gyro_raw, &temp );
        for( uint8_t i = 0; i < 3; ++i )
        {
            accel[i] = ( float )accel_raw[i] / 16384.0f;
            gyro[i] = ( float )gyro_raw[i] / 131.0f;
        }

        motor_enable();
        bool direction_test = (( accel[0] < 0 ) && ( gyro[1] < 0 ));
        uint16_t power = (uint16_t)fminf(fabsf(0.350f*gyro[1]), 255.0f) << 8;
        motor_set_both_level( power, direction_test );
        
        sleep_ms( 100 );
    }
}