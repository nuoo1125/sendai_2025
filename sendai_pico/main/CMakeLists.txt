add_executable(sendai_pico main.cpp)

target_include_directories(sendai_pico PRIVATE ../lib)

target_link_libraries(sendai_pico stepper gyro VL53L0X servo mcp3208 interface)
target_link_libraries(sendai_pico pico_stdlib hardware_pwm hardware_spi hardware_i2c hardware_pio hardware_clocks pico_i2c_slave)

pico_enable_stdio_usb(sendai_pico 1)
pico_enable_stdio_uart(sendai_pico 0)

pico_add_extra_outputs(sendai_pico)