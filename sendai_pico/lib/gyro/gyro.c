#include "gyro.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "../config.h"

int16_t merge(uint8_t low, uint8_t high) {
    int16_t result = (high << 8) | low;
    if (result > 32767) {
        result -= 65536;
    }
    return result;
}
void init_bno055() {
    uint8_t chip_id;
    i2c_init(I2C_GYRO, 100000); 
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    i2c_init(I2C_TOF,100*1000);
    gpio_set_function(SDA_TOF, GPIO_FUNC_I2C);
    gpio_set_function(SCL_TOF, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_TOF);
    gpio_pull_up(SCL_TOF);  
    i2c_write_blocking(I2C_GYRO, ADDRESS, (uint8_t[]){0x00}, 1, true); 
    i2c_read_blocking(I2C_GYRO, ADDRESS, &chip_id, 1, false); 
    if (chip_id != 0xA0) {
        while (true) {
            printf("BNO055 not found...\n");
            sleep_ms(1000);
        }
    }
    uint8_t config[][3] = {
        {0x3D, 0x00, 80},
        {0x3E, 0x00, 80},
        {0x07, 0x00, 80},
        {0x3D, 0x0C, 80}
    };
    for (int i = 0; i < 4; i++) {
        uint8_t reg = config[i][0];
        uint8_t value = config[i][1];
        uint8_t delay = config[i][2];

        uint8_t data[2] = {reg, value};
        i2c_write_blocking(I2C_GYRO, ADDRESS, data, 2, false); 
        sleep_ms(delay); 
    }
    printf("%d\n",1234);
}
void read_euler_angles(int16_t* yaw, int16_t* roll, int16_t* pitch) {
    uint8_t buffer[6];
    i2c_write_blocking(I2C_GYRO, ADDRESS, (uint8_t[]){EULER_REGISTER}, 1, true); 
    i2c_read_blocking(I2C_GYRO, ADDRESS, buffer, 6, false); 
    *yaw = merge(buffer[0], buffer[1]);
    *roll = merge(buffer[2], buffer[3]);
    *pitch = merge(buffer[4], buffer[5]);
}
