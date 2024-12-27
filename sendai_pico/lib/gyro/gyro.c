#include "gyro.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

int16_t merge(uint8_t low, uint8_t high) {
    int16_t result = (high << 8) | low;
    if (result > 32767) {
        result -= 65536;
    }
    return result;
}
void i2c_init_custom() {
    i2c_init(I2C_PORT, 100000); // 100 kHzのI2C通信
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void init_bno055() {
    uint8_t chip_id;
    
    // チップIDを確認
    i2c_write_blocking(I2C_PORT, ADDRESS, (uint8_t[]){0x00}, 1, true); // チップIDを読み取るためのレジスタアドレス
    i2c_read_blocking(I2C_PORT, ADDRESS, &chip_id, 1, false); // 1バイトを読み取る

    if (chip_id != 0xA0) {
        while (true) {
            printf("BNO055 not found...\n");
            sleep_ms(1000);
        }
    }

    // 設定を送信
    uint8_t config[][3] = {
        {0x3D, 0x00, 80},
        {0x3E, 0x00, 80},
        {0x07, 0x00, 80},
        {0x3D, 0x0C, 80}
    };

    for (int i = 0; i < 4; i++) {
        uint8_t reg = config[i][0];
        uint8_t value = config[i][1];
        uint8_t delay = config[i][2];

        uint8_t data[2] = {reg, value};
        i2c_write_blocking(I2C_PORT, ADDRESS, data, 2, false); // レジスタへ書き込み
        sleep_ms(delay); // 指定された待機時間
    }
}

// Euler角のデータを取得する関数
void read_euler_angles(int16_t* yaw, int16_t* roll, int16_t* pitch) {
    uint8_t buffer[6];
    
    // Euler角レジスタからデータを読み取る
    i2c_write_blocking(I2C_PORT, ADDRESS, (uint8_t[]){EULER_REGISTER}, 1, true); // レジスタアドレスを送信
    i2c_read_blocking(I2C_PORT, ADDRESS, buffer, 6, false); // 6バイトのデータを読み取る

    // 16ビットのデータをマージ
    *yaw = merge(buffer[0], buffer[1]);
    *roll = merge(buffer[2], buffer[3]);
    *pitch = merge(buffer[4], buffer[5]);
}
