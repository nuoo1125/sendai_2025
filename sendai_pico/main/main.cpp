#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "gyro/gyro.h"
#include "VL53L0X/VL53L0X.h"
#include "servo/servo.h"
#include "mcp3208/mcp3208.h"
#include "stepper/stepper.h"

int main() {
    stdio_init_all();
    /*
    init_bno055();
    int16_t yaw, roll, pitch;
    stepper_setup();
    stepper_slow(0,0);
    */
    gpio_set_dir(6,1);
    
    while(1){
        for(int i=0;i<8;i++){
            gpio_put(6,1);
            sleep_us(1.36);
            gpio_put(6,0);
            sleep_us(0.35);
        }
        for(int i=0;i<8;i++){
            gpio_put(6,1);
            sleep_us(0.35);
            gpio_put(6,0);
            sleep_us(1.36);
        }
        for(int i=0;i<8;i++){
            gpio_put(6,1);
            sleep_us(0.35);
            gpio_put(6,0);
            sleep_us(1.36);
        }
        sleep_us(50);
    }
    return 0;
}
