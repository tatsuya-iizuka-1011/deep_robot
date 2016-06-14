import serial, time, json
serialPath = '/dev/cu.wchusbserial1410'
arduino = serial.Serial(serialPath, 115200, timeout=.1)
#time.sleep(2) #give the connection a second to settle
#arduino.write("m 200 ")
time.sleep(2)
while True:
	data = arduino.readline()
	if data:
		j = json.loads(data)
 		print j['distance']
		print j['wheel_r_speed']
		print j['wheel_l_speed']
		print j['arm_r_speed']
		print j['arm_l_speed']
