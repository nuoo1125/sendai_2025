#include "LiDAR.h"
#include "servo.h"

bool Pico_LiDAR::init(uint8_t pin, i2c_inst_t *i2c) {
    if (!sensor.begin(VL53L0X_I2C_ADDR, i2c,  
                        Pico_VL53L0X::VL53L0X_Sense_config_t::VL53L0X_SENSE_DEFAULT))
    {
        return false;
    }

    servo_pin = pin;
    
    memset(distance, 0, sizeof(distance));

    set_servo_pin(pin);
    move_servo_angle(pin, (servo_angle_min+servo_angle_max)/2);

    return true;
}

bool Pico_LiDAR::startMearurement() {
    return sensor.startRangeContinuous(25);
}

bool Pico_LiDAR::stopMearurement() {
    if(sensor.stopMeasurement() == VL53L0X_ERROR_NONE)return true;
    return false;
}

bool Pico_LiDAR::isDataReady(){
    return sensor.isRangeComplete();
}

uint16_t Pico_LiDAR::readRange(uint8_t angle) {
    if(angle > servo_angle_max)angle = servo_angle_max;
    if(angle < servo_angle_min)angle = servo_angle_min;
    
    move_servo_angle(servo_pin, angle);
    return sensor.readRange();
}

void Pico_LiDAR::readAll() {
    for (int i = 0; i < 100; i++) {
        move_servo_angle(servo_pin, 20+i);
        while(!sensor.isRangeComplete());
        distance[i] = sensor.readRange();
    }
}
