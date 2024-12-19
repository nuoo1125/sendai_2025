#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "gyro/gyro.h"

int main() {
    stdio_init_all();

    // I2Cの初期化
    i2c_init_custom();

    // BNO055の初期化
    init_bno055();

    int16_t yaw, roll, pitch;

    while (true) {
        // Euler角を取得
        read_euler_angles(&yaw, &roll, &pitch);

        // データを表示
        printf("Yaw: %.2f, Roll: %.2f, Pitch: %.2f\n", yaw / 16.0, roll / 16.0, pitch / 16.0);
        sleep_ms(50);
    }

    return 0;
}
