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
#include "interface/interface.h"

int mid_photo;
int left_photo;
int right_photo;
int shiki = 800;


void linetrace(){//白1100 黒300
    if(mid_photo > shiki && left_photo > shiki && right_photo<shiki)stepper_slow(1,0);
    else if(mid_photo > shiki && left_photo < shiki && right_photo > shiki)stepper_slow(0,1);
    else if(mid_photo<shiki && left_photo < shiki && right_photo < shiki)buzzer();
    else stepper_slow(1,1);
}
void photo(){
    left_photo = mcp3208_read(5);
    mid_photo = mcp3208_read(6);
    right_photo = mcp3208_read(7);
    printf("L:");
    printf("%d\n",left_photo);
    printf("M:");
    printf("%d\n",mid_photo);
    printf("R:");
    printf("%d\n",right_photo);
}

int main() {
    int16_t yaw, roll, pitch;
    stdio_init_all();
    ws2812_program_init(WS2812_PIN,800000,IS_RGBW);
    stepper_setup();
    mcp3x08_init();
    init_bno055();
    VL53L0X tof_forward(i2c1,VL53L0X_DEFAULT_ADDRESS);
    VL53L0X tof_backward(i2c0,VL53L0X_DEFAULT_ADDRESS);
    tof_forward.init();
    tof_backward.init();
    tof_forward.setTimeout(500);
    tof_backward.setTimeout(500);
    tof_forward.startContinuous();
    tof_backward.startContinuous();
    stepper_slow(1,1);
    while(1){
        while(tof_backward.readRangeSingleMillimeters()>500){
            stepper_slow(1,1);
        }
        stepper_break();
    }
    return 0;
}