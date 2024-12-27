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
    // I2Cの初期化
    i2c_init_custom();

    // BNO055の初期化
    init_bno055();

    int16_t yaw, roll, pitch;
    stepper_setup();
    stepper_slow(0,0);
    while(1){
        stepper_angle(5000,0);
        stepper_angle(5000,1);
    }
 //   move_to_stepper(80);
    return 0;
}