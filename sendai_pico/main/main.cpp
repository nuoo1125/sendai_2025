#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "hardware/i2c.h"
#include "VL53L0X/VL53L0X.h"
#include "config.h"
int main() {
    stdio_init_all();
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(SDA_TOF1, GPIO_FUNC_I2C);
    gpio_set_function(SCL_TOF1, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_TOF1);
    gpio_pull_up(SCL_TOF1);
    VL53L0X tof_sensor(i2c0,VL53L0X_DEFAULT_ADDRESS);
    tof_sensor.init();
    tof_sensor.setTimeout(500);
    while(1){
        printf("millimeters: %d", tof_sensor.readRangeSingleMillimeters());
        sleep_ms(500);
    }
}
