#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
    gpio_set_function(5, GPIO_FUNC_PWM);
    gpio_set_function(7,GPIO_FUNC_PWM);
    if(forward_l == 1 && forward_r == 1){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);        
    }
    else if(forward_l == 0 && forward_r == 1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);        
    }
    else if(forward_l == 0 && forward_r == 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
    }
    else if(forward_l == 1 &&forward_r == 0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,1);        
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l, 124);
    pwm_set_wrap(slice_num_l, 2047);
    pwm_set_chan_level(slice_num_l, chan_l, 1024);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r, 124);
    pwm_set_wrap(slice_num_r, 2047);
    pwm_set_chan_level(slice_num_r, chan_r, 1024);
    pwm_set_enabled(slice_num_l, true);
    pwm_set_enabled(slice_num_r, true);
}
void stepper_break(){
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    pwm_set_enabled(slice_num_l,false);
    pwm_set_enabled(slice_num_r, false);
}
void stepper_angle(int steps,bool right){
    gpio_set_function(5, GPIO_FUNC_PWM);
    gpio_set_function(7,GPIO_FUNC_PWM);
    if(right){
        gpio_put(direction_l,1);
        gpio_put(direction_r,1);
    }
    else{
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);
    }
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    pwm_set_enabled(slice_num_l,true);
    pwm_set_enabled(slice_num_r,true);
    sleep_ms(steps*2.08);
    stepper_break();
}
void move_to_stepper(float target_angle){
    target_angle = fmod((target_angle + 720.0), 360.0);  // 正規化

    float current_angle = read_angle();
//    printf("Start angle: %.2f\n", current_angle);

    while (1) {
        current_angle = fmod((current_angle + 720.0), 360.0);
        float angle_diff = target_angle - current_angle;

        if (angle_diff > 180) angle_diff -= 360;
        else if (angle_diff < -180) angle_diff += 360;

        if (fabs(angle_diff) < 0.5) break;

        bool right = angle_diff > 0;
        int steps = round(fabs(angle_diff) / step_angle); 

        if (steps == 0) break; 

        stepper_angle(steps, right);
        stepper_break();

        current_angle = read_angle();
      //  printf("Current angle: %.2f\n", current_angle);
    }
}
