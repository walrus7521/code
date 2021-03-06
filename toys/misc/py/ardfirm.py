#!/usr/bin/env python3

# https://realpython.com/arduino-python/
# https://github.com/tino/pyFirmata
# http://firmata.org/wiki/Main_Page
# https://github.com/firmata/protocol
# https://pyfirmata.readthedocs.io/en/latest/

"""
mega = {
...         'digital' : tuple(x for x in range(54)),
...         'analog' : tuple(x for x in range(16)),
...         'pwm' : tuple(x for x in range(2,14)),
...         'use_ports' : True,
...         'disabled' : (0, 1, 14, 15) # Rx, Tx, Crystal
...         }
"""

import pyfirmata
import time
import os

print(os.name)

board = None
if (os.name == 'posix'):
    board = pyfirmata.Arduino('/dev/cu.usbmodem14201')
elif (os.name == 'nt'):
    board = pyfirmata.Arduino('COM8')
elif (os.name == 'Linux'):
    board = pyfirmata.Arduino('/dev/ttyACM0')

while True:
    board.digital[13].write(1)
    time.sleep(1)
    board.digital[13].write(0)
    time.sleep(1)

