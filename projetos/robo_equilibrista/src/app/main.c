#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "motor.h"
#include "mpu6050_i2c.h"

#define FORWARD_DIRECTION 1
#define BACKWARD_DIRECTION 0

#define PI 3.14159265

volatile int16_t accel_raw[3], gyro_raw[3], temp;
volatile float accel[3], gyro[3];
volatile float fs_factor = 0.98, accel_angle = 0, gyro_angle = 0, angle = 0;
volatile float Kp = 0;
volatile float duty = 0;
volatile bool dir = false;


bool loop_irq( struct repeating_timer *t )
{
    mpu6050_read_raw( accel_raw, gyro_raw, &temp );

    for( uint8_t i = 0; i < 3; ++i )
    {
        accel[i] = ( float )accel_raw[i] / 16384.0f;
        gyro[i] = ( float )gyro_raw[i] / 131.0f;
    }

    accel_angle = atan2( accel[0], accel[2] );          /* Angulo pelo acelerometro */
    gyro_angle = gyro_angle + ( gyro[1] * 0.0001 );     /* Angulo pelo giroscopio */
    angle = fs_factor * ( angle + gyro[1] * 0.0001 ) \
            + ( 1 - fs_factor ) * accel_angle;          /* Angulo pela fusao */

    duty = ( angle * Kp ) << 8;                         /* Duty-cycle considerando somente Kp */

    if( angle > PI / 32 )
    {
        dir = false; /* Acelerar para trás */
    }
    else
    {
        dir = true; /* Acelerar para frente */
    }

    motor_set_both_level(duty, dir);
}

int main() {
    stdio_init_all();
    mpu6050_setup_i2c();
    mpu6050_reset();
    motor_setup();
    motor_enable();

    struct repeating_timer timer; /* Timer para loop */
    add_repeating_timer_ms(0.1, loop_irq, NULL, &timer); /* Inicializa temporizador para loop */

    while( true ) 
    {

    }
}