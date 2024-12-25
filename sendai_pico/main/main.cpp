#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "gyro/gyro.h"
#include "VL53L0X/VL53L0X.h"

#define I2C_SDA 16
#define I2C_SCL 17

int main() {
    stdio_init_all();
    i2c_init_custom();
    init_bno055();
    int16_t yaw,roll,pitch;
}

