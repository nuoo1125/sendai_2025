#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif
void sg90_angle(float angle);
#ifdef __cplusplus
}
#endif