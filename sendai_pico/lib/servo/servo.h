#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif
void sg90_angle(float angle);
void mg996r(float angle);
void lock();
void unlock();
void s35_stop();
void s35_up();
void s35_down();
#ifdef __cplusplus
}
#endif