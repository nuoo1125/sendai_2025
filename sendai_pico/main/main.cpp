#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include <stdlib.h>
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
int shiki = 500;
int stage = 0;
void photo() {
    left_photo = mcp3208_read(5);
    mid_photo = mcp3208_read(6);
    right_photo = mcp3208_read(7);
    printf("L:%d", left_photo);
    printf(" ");
    printf("M:%d", mid_photo);
    printf(" ");
    printf("R:%d\n", right_photo);
}

void linetrace() {
    if(mid_photo > shiki && left_photo > shiki && right_photo < shiki)
        stepper_slow(1, 0);
    else if(mid_photo > shiki && left_photo < shiki && right_photo > shiki)
        stepper_slow(0, 1);
    else if(mid_photo < shiki && left_photo < shiki && right_photo < shiki){
        stage += 1;
        stepper_break();
        buzzer();
        sleep_ms(1000);
        stepper_slow(1, 1);
        sleep_ms(300);
    }
    else
        stepper_slow(1, 1);
}

int main() {
    char buffer[128];
    int index = 0;
    int value = 0;
    stdio_init_all();
    ws2812_program_init(WS2812_PIN,800000,IS_RGBW);
    mcp3x08_init();
    init_bno055();
    stepper_setup();
    VL53L0X tof_forward(i2c1,VL53L0X_DEFAULT_ADDRESS);
    VL53L0X tof_backward(i2c0,VL53L0X_DEFAULT_ADDRESS);
    tof_forward.init();
    tof_backward.init();
    tof_forward.setTimeout(500);
    tof_backward.setTimeout(500);
    tof_forward.startContinuous();
    tof_backward.startContinuous();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    stepper_slow(1,1);
    while (true) {
        if (uart_is_readable(UART_ID)){
            char c = uart_getc(UART_ID);
            if (c == '\n' || c == '\r') {
                buffer[index] = '\0';
                value = atoi(buffer);
                printf("受信した数値: %d\n", value);
                value -= 160;
                if(value > 0){move_to_stepper(read_angle()-value/4);}
                else move_to_stepper(read_angle()-value/4);
                stepper_break();
            if(tof_forward.readRangeSingleMillimeters()<=150){
                arm_down();
                sleep_ms(500);
                arm_open();
                sleep_ms(1000);
                stepper_slow(1,1);
                sleep_ms(350);
                stepper_break();
                arm_close();
                sleep_ms(1000);
                arm_up();
                sleep_ms(1000);        
                arm_on();
                sleep_ms(1000);
                arm_down();
                sleep_ms(3000);
            }
            else stepper_slow(1,1);
                index = 0;
            } else if (index < sizeof(buffer) - 1) {
                buffer[index++] = c;
            }
        }
        
        sleep_ms(10);
    }
}
