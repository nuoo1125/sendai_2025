#pragma once
//gyro系
#define gyro_reset 20
#define gyro_i2c i2c1
#define SDA_PIN 18
#define SCL_PIN 19
#define ADDRESS 0x28
#define EULER_REGISTER 0x1A
//stepper系
#define clock_l 5
#define direction_l  4
#define clock_r 7
#define direction_r 6 
#define sleep 3
#define reset 2
#define step_angle 0.9
//tof系
#define VL53L0X_DEFAULT_ADDRESS 0x29
#define tof_1 i2c1
#define tof_2 i2c0
#define SDA_TOF1 16
#define SCL_TOF1 17
#define xshut2 15
#define xshut1 14
//mcp3208系
#define SPI_PIN_SCK  10
#define SPI_PIN_MOSI 11
#define SPI_PIN_MISO 12
#define SPI_PIN_CS   13
#define SPI_PORT spi1
//servo系
#define gpio 28 //arm
#define gpio2 27 //arm
#define gpio3 26 //arm up/down
#define gpio4 22 //ひも引っ張る
#define gpio5 21 //rock
//deabgu系
#define buzzer_pin 0
#define led 25
#define WS2812_PIN 1
//camera
#define UART_ID uart1
#define BAUD_RATE 115200
#define UART_TX_PIN 8 
#define UART_RX_PIN 9  
