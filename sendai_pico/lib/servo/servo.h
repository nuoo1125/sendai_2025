#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#ifdef __cplusplus
extern "C" {
#endif
void set_pwm(int gpio);
#ifdef __cplusplus
}
#endif