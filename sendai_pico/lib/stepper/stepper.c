#include <stdlib.h>
#include "stepper.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "../config.h"
#include "gyro.h"

void stepper_setup(){
    gpio_set_function(clock_l,GPIO_FUNC_PWM);
    gpio_set_function(clock_r,GPIO_FUNC_PWM);
    gpio_init(direction_l);
    gpio_init(direction_r);
    gpio_init(reset);
    gpio_init(sleep);
    gpio_set_dir(sleep,GPIO_OUT);
    gpio_set_dir(direction_l,GPIO_OUT);
    gpio_set_dir(reset,GPIO_OUT);
    gpio_set_dir(direction_r,GPIO_OUT);
} 
void stepper_slow(bool forward_l,bool forward_r){
    if(forward_l == 1 && forward_r == 1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
    }
    else if(forward_l == 0 && forward_r == 1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);        
    }
    else if(forward_l == 0 && forward_r == 0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);        
    }
    else if(forward_l == 1 &&forward_r == 0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,1);        
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l, 1000);
    pwm_set_wrap(slice_num_l, 2500);
    pwm_set_chan_level(slice_num_l, chan_l, 1000);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r, 1000);
    pwm_set_wrap(slice_num_r, 2500);
    pwm_set_chan_level(slice_num_r, chan_r, 1000);
    pwm_set_enabled(slice_num_l, true);
    pwm_set_enabled(slice_num_r, true);
}
void stepper_break(){
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    pwm_set_enabled(slice_num_l,false);
    pwm_set_enabled(slice_num_r, false);
}
void move_to_stepper(int target_angle){
    int16_t yaw,roll,pitch;
    read_euler_angles(&yaw,&roll,&pitch);
    int16_t current_angle = yaw;
    while(current_angle != target_angle){
        int16_t angle_diff = target_angle - current_angle;
        bool right = angle_diff > 0;
        int steps = abs(angle_diff)/step_angle;
        stepper_angle(steps,right);
        read_euler_angles(&yaw,&roll,&pitch);
        current_angle = yaw;
    }
}
