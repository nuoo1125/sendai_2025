#pragma once

#include "pico/stdlib.h"
#include "../config.h"
#ifdef __cplusplus
extern "C" {
#endif
void mcp3x08_init();
uint16_t mcp3208_read(uint8_t ch);
void read_photo(int *photo);
#ifdef __cplusplus
}
#endif