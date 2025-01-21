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
void stepper_setup();
void stepper_slow(bool forward_l,bool forward_r);
void stepper_angle(int steps,bool right);
void move_to_stepper(int target_angle);
void stepper_break();
#ifdef __cplusplus
}
#endif