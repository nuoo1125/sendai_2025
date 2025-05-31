from machine import UART
from fpioa_manager import fm
import time
import lcd
fm.register(34, fm.fpioa.UART2_TX)
fm.register(35, fm.fpioa.UART2_RX)

uart2 = UART(UART.UART2, 115200)
while True:
    msg = "Hello  from M5StickV\r\n"
    uart2.write(msg)
    time.sleep(1)
