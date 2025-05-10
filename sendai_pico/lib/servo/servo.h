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
void arm_open();
void arm_close();
void arm_up();
void arm_down();
void arm_on();
#ifdef __cplusplus
}
#endif