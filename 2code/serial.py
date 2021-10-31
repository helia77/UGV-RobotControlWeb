
import serial

ser=serial.Serial("/dev/ttyUSB1",9600)  
ser.baudrate=9600
#ser.open()
while True:
	read_ser=ser.readline()
	ch= read_ser.decode()
	fo=open('test.txt','w')
	fo.write(ch)
	print(ch)
	fo.close()
