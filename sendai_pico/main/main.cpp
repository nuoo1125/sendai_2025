#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "config.h"
#include "VL53L0X/VL53L0X.h"
#include "gyro/gyro.h"
#include "mcp3208/mcp3208.h"
#include "servo/servo.h"
#include "stepper/stepper.h"

int main() {
    stdio_init_all();
    stepper_setup();
    unlock();
    sleep_ms(1000);
    s35_up();
    sleep_ms(10000);
    s35_stop();
    
    lock();
    sleep_ms(2000);
    s35_down();
    sleep_ms(10000);
    s35_stop();
    unlock();
}
