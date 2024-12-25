#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"



#ifdef __cplusplus
extern "C" {
#endif
void stepper_setup();
void stepper_fast(bool forward_l,bool forward_r);
void stepper_slow(bool forward_l,bool forward_r);
void stepper_angle(int16_t angle_l,int16_t angle_r);
void stepper_right();
void stepper_left();
void stepper_turn();
void stepper_break();
#ifdef __cplusplus
}
#endif