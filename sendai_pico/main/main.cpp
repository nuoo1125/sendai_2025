#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "gyro/gyro.h"
#include "VL53L0X/VL53L0X.h"
#include "servo/servo.h"
#include "mcp3208/mcp3208.h"
#include "stepper/stepper.h"
#include "ws2812.pio.h"


int main() {
    stdio_init_all();
    sleep_ms(2000);
    /*
    init_bno055();
    int16_t yaw, roll, pitch;
    stepper_setup();
    stepper_slow(0,0);
    */
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    while (true) {
        set_pixel_color(pio, sm, 125, 0, 0);  
        sleep_ms(1000);

        set_pixel_color(pio, sm, 0, 125, 0);  
        sleep_ms(1000);

        set_pixel_color(pio, sm, 0, 0, 125);  
        sleep_ms(1000);

        set_pixel_color(pio, sm, 255, 255, 255);  
        sleep_ms(1000);

        set_pixel_color(pio, sm, 0, 0, 0); 
        sleep_ms(1000);
    }
}
