import json,serial,time,random
serialPath = '/dev/cu.wchusbserial1410'
arduino = serial.Serial(serialPath, 115200, timeout=.1)
time.sleep(2) #necessary

i = 0

while True:
    time.sleep(0.2)
    if 50 < i%100:
        jsonData = {
            "wheel_r":int(-50-200*random.random()),
            "wheel_l":int(-50-200*random.random()),
            "arm_r":int(-50-200*random.random()),
            "arm_l":int(-50-200*random.random())
        }
    else:
        jsonData = {
            "wheel_r":int(50+200*random.random()),
            "wheel_l":int(50+200*random.random()),
            "arm_r":int(50+200*random.random()),
            "arm_l":int(50+200*random.random())
        }

    i = i+1



    jString = json.dumps(jsonData)
    jString += '#'
    print jString
    arduino.write(jString)
