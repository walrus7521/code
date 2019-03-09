#!/usr/bin/env python3

# andGate_Test.py
# convert the andGate.py to VHDL/Verilog code
# the resultant Verilog code is same as Listing 'andGate.v of Verilog tutorial

from myhdl import *
from andGate import andEx

x = Signal(bool(0)) # signal of type boolean size 1-bit
y = Signal(bool(0))
z = Signal(bool(0))

# convert into Verilog code
andEx_verilog = andEx(x, y, z)

# positional assigments
#andEx_verilog = andEx(x=x, y=y, z=z)

# initial_values = True will initialize the signal
# note that there is no signal in this design (all are ports)
andEx_verilog.convert(hdl="Verilog", initial_values=True)

