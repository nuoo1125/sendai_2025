#include "interface.h"

#include "pico/stdlib.h"
#include "../config.h"

void buzzer(){
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin,GPIO_OUT);
    gpio_put(buzzer_pin,true);
    sleep_ms(500);
    gpio_put(buzzer_pin,false);
}
void led_on(){
    gpio_init(25);
    gpio_set_dir(25,GPIO_OUT);
    gpio_put(25,1);
}
void led_off(){
    gpio_put(25,0);
}