from flask import Flask, jsonify, render_template, request
from random import *
import threading
import time
import serial


app = Flask(__name__)

ser = serial.Serial(
   port='/dev/ttyUSB0',
   baudrate = 38400,
   parity=serial.PARITY_NONE,
   stopbits=serial.STOPBITS_ONE,
   bytesize=serial.EIGHTBITS,
   timeout=1
)

@app.route('/_Stop')
def forward_m():
    ser.write(b'S0 0\n')
    time.sleep(1)
    
@app.route('/_forward')
def forward_m():
    ser.write(b'S50 50\n')
    time.sleep(1)

@app.route('/_backward')
def backward_m():
    ser.write(b'S-50 -50\n')
    time.sleep(1)

@app.route('/_left')
def left_m():
    ser.write(b'S-50 50\n')
    time.sleep(1)

@app.route('/_right')
def right_m():
    ser.write(b'S50 -50\n')
    time.sleep(1)

	



@app.route('/')
def index():
    return render_template('index.html')

app.run(port=3131,threaded=True,host='0.0.0.0');
