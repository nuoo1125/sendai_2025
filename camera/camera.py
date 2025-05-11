import sensor, image, lcd


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
yellow_threshold = (0, 74, -29, 127, 60, 128)

while True:
    img = sensor.snapshot()
    blobs_blue = img.find_blobs([blue_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    blobs_yellow = img.find_blobs([yellow_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    blobs_red = img.find_blobs([red_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    for blob in blobs_blue:
        if 0.8 < blob.w()/blob.h()<1.2:
            img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color=(0,0,255))
            print(blob.cx())
    for blob in blobs_yellow:
        if 0.8 < blob.w()/blob.h()<1.2:
            img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color = (255,255,0))
            print(blob.cx())

    for blob in blobs_red:
        if 0.8 < blob.w()/blob.h()<1.2:
            img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color=(255,0,0))
            print(blob.cx())
    lcd.display(img)
