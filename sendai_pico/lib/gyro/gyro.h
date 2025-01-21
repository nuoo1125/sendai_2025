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
void read_euler_angles(int16_t* yaw, int16_t* roll, int16_t* pitch);
#ifdef __cplusplus
}
#endif