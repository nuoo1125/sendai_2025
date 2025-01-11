import sensor, image, lcd


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
#sensor.set_auto_gain(False)  
sensor.set_auto_whitebal(False)  
sensor.set_vflip(True)  
sensor.set_hmirror(True)  
lcd.init()
sensor.skip_frames(time=2000)


blue_threshold = (0, 100, -86, 22, -8, 24)

while True:
    img = sensor.snapshot()
    blobs = img.find_blobs([blue_threshold], pixels_threshold=200, area_threshold=200, merge=True)
    
    for blob in blobs: 
        if 0.8 < blob.w()/blob.h()<1.2:
            img.draw_circle(blob.cx(),blob.cy(),blob.w()//2,color=(0,0,255))
            print(blob.cx())
    else:
        img.draw_string(10, 10, "No Ball Found", color=(255, 0, 0), scale=2)
        lcd.display(img)
