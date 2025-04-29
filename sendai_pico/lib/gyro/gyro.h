#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "../config.h"



#ifdef __cplusplus
extern "C" {
#endif
int16_t merge(uint8_t low, uint8_t high);
void init_bno055();
int16_t read_angle();
#ifdef __cplusplus
}
#endif