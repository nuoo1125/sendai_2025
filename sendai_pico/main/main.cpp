#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
int main() {
    stdio_init_all();
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(sm, offset, WS2812_PIN, 800000, IS_RGBW);

    while (true) {
        set_pixel_color(sm, 255, 0, 0);  // 赤
        sleep_ms(1000);

        set_pixel_color(sm, 0, 255, 0);  // 緑
        sleep_ms(1000);

        set_pixel_color(sm, 0, 0, 255);  // 青
        sleep_ms(1000);

        set_pixel_color(sm, 255, 255, 255);  // 白
        sleep_ms(1000);

        set_pixel_color(sm, 0, 0, 0);  // 消灯
        sleep_ms(1000);
    }
}
