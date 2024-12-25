#pragma once
//gyro系
#define I2C_PORT i2c0
#define SDA_PIN 16
#define SCL_PIN 17
#define ADDRESS 0x28
#define EULER_REGISTER 0x1A
//stepper系
#define clock_l 16
#define direction_l  17
#define clock_r 18
#define direction_r 19 
#define sleep 20
#define reset 21 
//tof系
#define VL53L0X_DEFAULT_ADDRESS 0x29
