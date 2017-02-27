from pyBusPirateLite.I2Chigh import *

# https://github.com/juhasch/pyBusPirateLite/blob/master/tests/test_bitbang.py

# create an instance of it, using the COM3 port and the Bus Pirate speed of 115200 baud, with a timeout of 5s
i2c = I2Chigh("COM11", 115200, 5)
print i2c

# enter Bit Bang mode
print i2c.BBmode()
# enter I2C mode
print i2c.enter_I2C()
# turn on the power supply and enable the pullups
i2c.cfg_pins(I2CPins.POWER | I2CPins.PULLUPS)
# read the byte at register address "0x00" on an I2C device with address "0x68
# this happens to be the "seconds" register of the DS3231 real-time clock (used in the popular ChronoDot)
print i2c.get_byte(0x68, 0x00)
# define a function to report the seconds:
def get_seconds():
    return i2c.get_byte(0x68, 0x00)

get_seconds()
