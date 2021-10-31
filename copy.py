import serial

########################## Global variables: ##########################

serial_port = 0
data=[]
left_speed = 0
right_speed = 0
SPEED_MAX = 200
SPEED_STEP = 50

############################ Functions: ############################
def read_data():
	global serial_port
	while True:
		number = ""
		while True:
			ch = serial_port.read()
			if ch.decode("utf-8")=="\n":
				break
			if ch.decode("utf-8")=="":
				break
			number += ch.decode("utf-8")
		if ch.decode("utf-8")=="":
			break
		data.append(number)
	show_data()

def show_data():
	global serial_port
	global right_speed
	global left_speed
	text = "\n"
	text += "Port File Descriptor: {}\n".format(serial_port.port)
	text += "Left Motor Speed: {}\n".format(left_speed)
	text += "Right Motor Speed: {}\n".format(right_speed)
	text += "Left Shaft Encoder Data: {}\n".format(data[0])
	text += "Right Shaft Encoder Data: {}\n".format(data[1])
	text += "Rear Sonar Data: {}\n".format(data[2])
	text += "Rear-Left Sonar Data: {}\n".format(data[3])
	text += "Front Sonar Data: {}\n".format(data[4])
	text += "Front-Left Sonar Data: {}\n".format(data[5])
	text += "Front Sonar Data: {}\n".format(data[6])
	text += "Rear-Right Sonar Data: {}\n".format(data[7])
	text += "Battery Voltage: {}\n".format(data[8])
	print(text)

def update_robot():
	global serial_port
	global right_speed
	global left_speed
	if right_speed > SPEED_MAX:
		right_speed = SPEED_MAX
	elif right_speed < -SPEED_MAX:
		right_speed = -SPEED_MAX
	if left_speed > SPEED_MAX:
		left_speed = SPEED_MAX
	elif left_speed < -SPEED_MAX:
		left_speed = -SPEED_MAX
	serial_port.write(("R{} {}\n".format(left_speed,right_speed)).encode())
	read_data()

############################ Code: ############################
# Serial Port from Robot
serial_port = serial.Serial('/dev/ttyUSB0', baudrate=38400, timeout=1.0)

# Serial Port from Nodemcu
ser = serial.Serial("COM7",9600)  
ser.baudrate = 9600

if serial_port!= 0:
	print("Serial is Connected on port: {}".format(serial_port.port))
else:
	print("Unable to connect to serial port.")


while True:
    read_ser = ser.readline()
	ch = read_ser.decode()
    
	# Go forward:
	if 'w' in ch:
		left_speed = right_speed
		right_speed = right_speed + SPEED_STEP
		left_speed = left_speed + SPEED_STEP
	# Go backward:
	elif 's' in ch:
		left_speed = right_speed
		right_speed = right_speed - SPEED_STEP
		left_speed = left_speed - SPEED_STEP
	# Go Left:
	elif 'a' in ch:	
		right_speed = right_speed - SPEED_STEP
		left_speed = left_speed + SPEED_STEP
	# Go Right:
	elif 'd' in ch:
		right_speed = right_speed + SPEED_STEP
		left_speed = left_speed - SPEED_STEP
	# No key:
	elif 'z' in ch:
		left_speed = 0
		right_speed = 0
	update_robot()