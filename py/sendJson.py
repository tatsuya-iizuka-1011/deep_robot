import json,serial,time,random
serialPath = '/dev/cu.wchusbserial1410'
arduino = serial.Serial(serialPath, 115200, timeout=.1)
time.sleep(2) #necessary

jsonData = {
    "sensor":"gps",
    "time":10
}
i = 0
while i < 100:
    time.sleep(2)
    jString = json.dumps(jsonData)
    arduino.write(jString)
    jsonData["time"] += 1
    print jsonData
