#!/usr/bin/env python

import pyfirmata
import time

board = pyfirmata.Arduino('COM8')
#board = pyfirmata.Arduino('/dev/ttyACM0')

while True:
    board.digital[13].write(1)
    time.sleep(1)
    board.digital[13].write(0)
    time.sleep(1)

