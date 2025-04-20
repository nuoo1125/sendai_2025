#pragma once

#include "pico/stdlib.h"
#include "../config.h"
#ifdef __cplusplus
extern "C" {
#endif
void buzzer();
void led_on();
void led_off();
#ifdef __cplusplus
}
#endif