#include "servo.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../config.h"
#include <stdio.h>
//33 to 180

void sg90_angle(float angle) {//left open 140 close35  right open 170 close270
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    gpio_set_function(gpio2,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t pwm_slice_num2 = pwm_gpio_to_slice_num(gpio2);
    pwm_set_wrap(pwm_slice_num, 25000); 
    pwm_set_clkdiv(pwm_slice_num, 64.0f);
    pwm_set_wrap(pwm_slice_num2, 25000); 
    pwm_set_clkdiv(pwm_slice_num2, 64.0f);
    
    float duty_cycle = 0.5 + (angle * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 

    pwm_set_chan_level(pwm_slice_num, pwm_gpio_to_channel(gpio), level);
    pwm_set_chan_level(pwm_slice_num2, pwm_gpio_to_channel(gpio2), level);
    pwm_set_enabled(pwm_slice_num, true);
    pwm_set_enabled(pwm_slice_num2, true);
}
void arm_open(){
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    gpio_set_function(gpio2,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t pwm_slice_num2 = pwm_gpio_to_slice_num(gpio2);
    pwm_set_wrap(pwm_slice_num, 25000); 
    pwm_set_clkdiv(pwm_slice_num, 64.0f);
    pwm_set_wrap(pwm_slice_num2, 25000); 
    pwm_set_clkdiv(pwm_slice_num2, 64.0f);
    float duty_cycle = 0.5 + (140* 2.0 / 180.0);
    float duty_cycle2 = 0.5 + (170 * 2.0/180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    uint16_t level2 =  (uint16_t)(duty_cycle2 * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num, pwm_gpio_to_channel(gpio), level);
    pwm_set_chan_level(pwm_slice_num2, pwm_gpio_to_channel(gpio2), level2);
    pwm_set_enabled(pwm_slice_num, true);
    pwm_set_enabled(pwm_slice_num2, true);
}
void arm_on(){
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    gpio_set_function(gpio2,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t pwm_slice_num2 = pwm_gpio_to_slice_num(gpio2);
    pwm_set_wrap(pwm_slice_num, 25000); 
    pwm_set_clkdiv(pwm_slice_num, 64.0f);
    pwm_set_wrap(pwm_slice_num2, 25000); 
    pwm_set_clkdiv(pwm_slice_num2, 64.0f);
    float duty_cycle = 0.5 + (85 * 2.0 / 180.0);
    float duty_cycle2 = 0.5 + (230 * 2.0/180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    uint16_t level2 =  (uint16_t)(duty_cycle2 * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num, pwm_gpio_to_channel(gpio), level);
    pwm_set_chan_level(pwm_slice_num2, pwm_gpio_to_channel(gpio2), level2);
    pwm_set_enabled(pwm_slice_num, true);
    pwm_set_enabled(pwm_slice_num2, true);
}
void arm_close(){
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    gpio_set_function(gpio2,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t pwm_slice_num2 = pwm_gpio_to_slice_num(gpio2);
    pwm_set_wrap(pwm_slice_num, 25000); 
    pwm_set_clkdiv(pwm_slice_num, 64.0f);
    pwm_set_wrap(pwm_slice_num2, 25000); 
    pwm_set_clkdiv(pwm_slice_num2, 64.0f);
    float duty_cycle = 0.5 + (35 * 2.0 / 180.0);
    float duty_cycle2 = 0.5 + (280 * 2.0/180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    uint16_t level2 =  (uint16_t)(duty_cycle2 * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num, pwm_gpio_to_channel(gpio), level);
    pwm_set_chan_level(pwm_slice_num2, pwm_gpio_to_channel(gpio2), level2);
    pwm_set_enabled(pwm_slice_num, true);
    pwm_set_enabled(pwm_slice_num2, true);
}
void lock(){
    pwm_set_chan_level(pwm_gpio_to_slice_num(5), pwm_gpio_to_channel(5), 0);
    gpio_set_function(5, GPIO_FUNC_SIO);  
    gpio_set_function(21,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num9 = pwm_gpio_to_slice_num(21);
    pwm_set_wrap(pwm_slice_num9, 25000); 
    pwm_set_clkdiv(pwm_slice_num9, 64.0f);
    float duty_cycle9 = 0.5 + (200 * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle9 * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num9, pwm_gpio_to_channel(21), level);
    pwm_set_enabled(pwm_slice_num9,true);
}
void unlock(){
    pwm_set_chan_level(pwm_gpio_to_slice_num(5), pwm_gpio_to_channel(5), 0);
    gpio_set_function(5, GPIO_FUNC_SIO);  
    gpio_set_function(21,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num9 = pwm_gpio_to_slice_num(21);
    pwm_set_wrap(pwm_slice_num9, 25000); 
    pwm_set_clkdiv(pwm_slice_num9, 64.0f);
    float duty_cycle9 = 0.5 + (70 * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle9 * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num9, pwm_gpio_to_channel(21), level);
    pwm_set_enabled(pwm_slice_num9,true);
}
void mg996r(float angle){
    gpio_set_function(gpio3,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num3 = pwm_gpio_to_slice_num(gpio3);
    pwm_set_wrap(pwm_slice_num3, 25000); 
    pwm_set_clkdiv(pwm_slice_num3, 64.0f);
    float duty_cycle = 0.5 + (angle * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num3, pwm_gpio_to_channel(gpio3), level);
    pwm_set_enabled(pwm_slice_num3,true);
}
void arm_up(){
    gpio_set_function(gpio3,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num3 = pwm_gpio_to_slice_num(gpio3);
    pwm_set_wrap(pwm_slice_num3, 25000); 
    pwm_set_clkdiv(pwm_slice_num3, 64.0f);
    float duty_cycle = 0.5 + (40 * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num3, pwm_gpio_to_channel(gpio3), level);
    pwm_set_enabled(pwm_slice_num3,true);

}
void arm_down(){
    gpio_set_function(gpio3,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num3 = pwm_gpio_to_slice_num(gpio3);
    pwm_set_wrap(pwm_slice_num3, 25000); 
    pwm_set_clkdiv(pwm_slice_num3, 64.0f);
    float duty_cycle = 0.5 + (260* 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 
    pwm_set_chan_level(pwm_slice_num3, pwm_gpio_to_channel(gpio3), level);
    pwm_set_enabled(pwm_slice_num3,true);
}
void s35_stop(){
    gpio_set_function(gpio4,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num4 = pwm_gpio_to_slice_num(gpio4);
    pwm_set_enabled(pwm_slice_num4,false);
    pwm_set_wrap(pwm_slice_num4, 19999); 
    pwm_set_clkdiv(pwm_slice_num4, 125);
    pwm_set_chan_level(pwm_slice_num4, pwm_gpio_to_channel(gpio4),1500);
    pwm_set_enabled(pwm_slice_num4,true);
}
void s35_down(){
    gpio_set_function(gpio4,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num4 = pwm_gpio_to_slice_num(gpio4);
    pwm_set_enabled(pwm_slice_num4,false);
    pwm_set_wrap(pwm_slice_num4, 19999); 
    pwm_set_clkdiv(pwm_slice_num4, 125);
    pwm_set_chan_level(pwm_slice_num4, pwm_gpio_to_channel(gpio4),2000);
    pwm_set_enabled(pwm_slice_num4,true);
}
void s35_up(){
    gpio_set_function(gpio4,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num4 = pwm_gpio_to_slice_num(gpio4);
    pwm_set_wrap(pwm_slice_num4,19999); 
    pwm_set_clkdiv(pwm_slice_num4, 125);
    pwm_set_chan_level(pwm_slice_num4, pwm_gpio_to_channel(gpio4),1000);
    pwm_set_enabled(pwm_slice_num4,true);
}