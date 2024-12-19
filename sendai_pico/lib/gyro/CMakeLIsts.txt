add_library(gyro gyro.c)
target_link_libraries(gyro pico_stdlib hardware_i2c hardware_pwm hardware_adc hardware_spi)