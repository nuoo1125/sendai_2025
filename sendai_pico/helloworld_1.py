import sensor, image, lcd
from machine import UART
from fpioa_manager import fm
prev_cx_r = None
prev_cx_b = None
prev_cx_y = None
stable_counter = 0
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
fm.register(34, fm.fpioa.UART2_TX)
fm.register(35, fm.fpioa.UART2_RX)
uart2 = UART(UART.UART2, 115200)
while True:
    img = sensor.snapshot()
    blobs_blue = img.find_blobs([blue_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    blobs_yellow = img.find_blobs([yellow_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    blobs_red = img.find_blobs([red_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    for blob in blobs_red:
        if 0.8 < blob.w()/blob.h()<1.2:
            img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color=(255,0,0))
            if prev_cx_r is not None and abs(blob.cx()-prev_cx_r)<=5:
                stable_count += 1
            else:
                stable_count = 0
            prev_cx_r = blob.cx()
            if stable_count >= 3:
                print("send",blob.cx())
                uart2.write(str(blob.cx())+"\n")
                stable_count = 0
    lcd.display(img)
    '''
        for blob in blobs_blue:
                if 0.8 < blob.w()/blob.h()<1.2:
                img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color=(0,0,255))
                print(blob.cx())
        for blob in blobs_yellow:
            if 0.8 < blob.w()/blob.h()<1.2:
                img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color = (255,255,0))
                print(blob.cx())
                '''

