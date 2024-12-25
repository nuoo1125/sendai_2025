#include "servo.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>
void set_pwm(int gpio){
    gpio_set_function(gpio,GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice_num,38.1469726562);
    pwm_set_wrap(slice_num,65535);
    uint chan = pwm_gpio_to_channel(gpio);
    pwm_set_chan_level(slice_num,chan,0);
    pwm_set_counter(slice_num,0);
    pwm_set_enabled(slice_num,true);
}
void servo_move(int gpio,int angle){
    
}
