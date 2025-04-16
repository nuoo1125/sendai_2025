#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "ws2812.pio.h"
#include "config.h"
#include "VL53L0X/VL53L0X.h"
#include "gyro/gyro.h"
#include "mcp3208/mcp3208.h"
#include "servo/servo.h"
#include "stepper/stepper.h"

int main() {
    stdio_init_all();
    gpio_init(0);
    gpio_set_dir(0,GPIO_OUT);
    while(1){
        s35_down();
        sleep_ms(1000*8);
        s35_up();
        sleep_ms(1000*8);
    }
}