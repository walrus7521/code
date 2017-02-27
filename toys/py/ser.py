#!/usr/bin/env python

import serial

ser = serial.Serial()
ser.baudrate = 19200
ser.port = 'COM11'
ser.open()
print ser.is_open
ser.close()
print ser.is_open

print ser
