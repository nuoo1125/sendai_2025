import sensor, image, lcd
from machine import UART
from fpioa_manager import fm

fm.register(34, fm.fpioa.UART2_TX)
fm.register(35, fm.fpioa.UART2_RX)
uart2 = UART(UART.UART2, 115200)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_vflip(True)
sensor.set_hmirror(True)
lcd.init()
sensor.skip_frames(time=2000)
blue_threshold = (0, 100, -86, 22, -8, 24)
red_threshold = (0, 54, 19, 65, -49, 127)
yellow_threshold = (0, 83, -31, -2, 57, 127)

prev_cx_r = None
stable_count = 0
STABLE_THRESHOLD = 2
STABLE_FRAMES = 20

while True:
    img = sensor.snapshot()
    blobs_red = img.find_blobs([red_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    largest_blob = None
    max_area = 0
    largest_color = ""
    for blob in blobs_red:
        if 0.8 < blob.w() / blob.h() < 1.2:
            area = blob.pixels()
            if area >= max_area:
                largest_blob = blob
                max_area = area
                largest_color = "R"
    for blob in blobs_yellow:
        if 0.8 < blob.w() / blob.h() < 1.2:
            area = blob.pixels()
            if area >= max_area:
                largest_blob = blob
                max_area = area
                largest_color = "Y"
    for blob in blobs_blue:
        if 0.8 < blob.w() / blob.h() < 1.2:
            area = blob.pixels()
            if area >= max_area:
                largest_blob = blob
                max_area = area
                largest_color = "B"
    if largest_blob:
        img.draw_circle(largest_blob.cx(), largest_blob.cy(), largest_blob.w() // 2, color=(255, 0, 0))
        if prev_cx_r is not None and abs(largest_blob.cx() - prev_cx_r) <= STABLE_THRESHOLD:
            stable_count += 1
        else:
            stable_count = 0
        prev_cx_r = largest_blob.cx()
        if stable_count >= STABLE_FRAMES:
            print("SEND:",largest_color + ":" + largest_blob.cx())
            uart2.write(largest_color + ":" + str(largest_blob.cx()) + "\n")
            stable_count = 0
    lcd.display(img)

