#!/usr/bin/env python

import serial

ser = serial.Serial('COM6', 38400, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
#ser = serial.Serial('/dev/cu.usbmodem14201', 115200, timeout=.1, parity=serial.PARITY_EVEN, rtscts=1)

while True:
    #data = ser.read(100)       # read up to one hundred bytes
#   data = ser.readline()[:-2] #the last bit gets rid of the new-line chars
    if data:
        print(data)
