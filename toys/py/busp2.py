from pyBusPirateLite.SPI import *
from pyBusPirateLite.BitBang import PinCfg


# https://github.com/juhasch/pyBusPirateLite/blob/master/examples/spi_example.py
# https://code.google.com/archive/p/the-bus-pirate/wikis

SPISpeed speed = _30KHZ
spi = SPI('COM11', 115200)
#spi.connect('COM11', 115200)
#spi.enter_bb()
#spi.enter_spi()

