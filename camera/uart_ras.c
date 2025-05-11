#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>

#define UART_ID uart1
#define BAUD_RATE 115200

#define UART_TX_PIN 8 
#define UART_RX_PIN 9  

int main() {
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    while (true) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            if (c == '\n' || index >= sizeof(buffer) - 1) {
                buffer[index] = '\0';
                printf("受信行: %s\n", buffer);
                index = 0;
            } else {
                buffer[index++] = c;
            }   
    }
    return 0;
    }
}
