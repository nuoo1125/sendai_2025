#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "gyro/gyro.h"
#include "VL53L0X/VL53L0X.h"

#define I2C_SDA 16
#define I2C_SCL 17

int main() {
    stdio_init_all();
    // Initialize I2C0 at 400kHz
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Initialize VL53L0X sensor
    VL53L0X sensor;
    sensor.init();
    sensor.setTimeout(500);

    // Start continuous back-to-back mode (take readings as fast as possible)
    sensor.startContinuous();
    while(1){
        printf("millimeters: %d", sensor.readRangeContinuousMillimeters());
    }
}
