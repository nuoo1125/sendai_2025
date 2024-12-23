#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "gyro/gyro.h"
#include "VL53L0X/VL53L0X.h"

#define I2C_SDA 16
#define I2C_SCL 17

void sg90(int angle){
    gpio_set_function(0,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num = pwm_gpio_to_slice_num(0);
    pwm_set_wrap(pwm_slice_num,25000);
    pwm_set_clkdiv(pwm_slice_num,64.0f);
    float duty_cycle = 0.5 + (angle * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num, pwm_gpio_to_channel(0), level);
    pwm_set_enabled(pwm_slice_num,true);
}
int main() {
    stdio_init_all();
    while(1){
        sg90(50);
        sleep_ms(1000);
        sg90(180);
        sleep_ms(1000);
    }
}

