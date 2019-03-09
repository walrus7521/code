#!/usr/bin/env python3

# gateEx.py
# the resultant Verilog code is same as Listing 'andEx.v of Verilog tutorial

from myhdl import *

# Module : and gate
@block
def andEx(x, y, z):
    """ input : x, y
        output : z
    """

    # behavior : and gate
    # i.e. implement and gate using combinational logic
#@always_comb
    def and_behave():
        z.next = x & y # and operation

    # return instances individually
    # return and_behave

    # this is more convenient as it returns all the instances automatically
    return instances()

