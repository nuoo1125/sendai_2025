#pragma once
//gyro系
#define I2C_GYRO i2c0
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
#define step_angle 0.9
//tof系
#define VL53L0X_DEFAULT_ADDRESS 0x29
#define I2C_TOF i2c1
#define SDA_TOF 0
#define SCL_TOF 1
//mcp3208系
#define SPI_PIN_SCK  2
#define SPI_PIN_MOSI 3
#define SPI_PIN_MISO 4
#define SPI_PIN_CS   5
#define SPI_PORT spi0
//servo系
#define gpio 0
#define gpio2 1
#define gpio3 2
