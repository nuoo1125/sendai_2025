#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "ws2812.pio.h"
#include "config.h"
#include "gyro/gyro.h"
#include "mcp3208/mcp3208.h"
#include "servo/servo.h"
#include "stepper/stepper.h"
#include "interface/interface.h"
#include "movement.h"

int mid_photo;
int left_photo;
int right_photo;
int shiki = 500;

void photo() {
    left_photo = mcp3208_read(5);
    mid_photo = mcp3208_read(6);
    right_photo = mcp3208_read(7);
    printf("L:%d\n", left_photo);
    printf("M:%d\n", mid_photo);
    printf("R:%d\n", right_photo);
}

void linetrace() {
    if(mid_photo > shiki && left_photo > shiki && right_photo < shiki)
        stepper_slow(1, 0);
    else if(mid_photo > shiki && left_photo < shiki && right_photo > shiki)
        stepper_slow(0, 1);
    else if(mid_photo < shiki && left_photo < shiki && right_photo < shiki){
        stepper_break();
        buzzer();
        sleep_ms(1000);
        stepper_slow(1, 1);
        sleep_ms(300);
    }
    else
        stepper_slow(1, 1);
}