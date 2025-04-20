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
int mid_photo;
int left_photo;
int right_photo;
void linetrace(){
    int shiki = 800;
    if(mid_photo > shiki && left_photo > shiki && right_photo<shiki)stepper_slow(0,1);
    else if(mid_photo > shiki && left_photo < shiki && right_photo>shiki)stepper_slow(1,0);
    else stepper_slow(1,1);
}
void photo(){
    left_photo = mcp3208_read(0);
    mid_photo = mcp3208_read(1);
    right_photo = mcp3208_read(2);
    printf("L:");
    printf("%d\n",left_photo);
    printf("M:");
    printf("%d\n",mid_photo);
    printf("R:");
    printf("%d\n",right_photo);
}

int main() {
    stdio_init_all();
    stepper_setup();
    mcp3x08_init();
    gpio_init(25);
    gpio_set_dir(25,GPIO_OUT);
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin,GPIO_OUT);
    while(1){
        photo();
        linetrace();
    }
    return 0;
}