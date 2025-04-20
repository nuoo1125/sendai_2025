#include "debug.h"

#include "pico/stdlib.h"
#include "../config.h"

void buzzer(){
    gpio_init(buzzer);
    gpio_set_dir(buzzer,GPIO_OUT);
    gpio_put(buzzer,true);
    sleep_ms(500);
    gpio_put(buzzer,false);
}