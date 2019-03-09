#!/usr/bin/env python3

from myhdl import *

import re

def hello_hdl(
    pixelClock,
    Red,
    Green,
    Blue,
    hSync,
    vSync
):


    ### Image ###

    # From: figlet -f alphabet " Hello World "
    MSG = [
    "    H  H     l l        W     W         l    d    ",
    "    H  H     l l        W     W         l    d    ",
    "    HHHH eee l l ooo    W  W  W ooo rrr l  ddd    ",
    "    H  H e e l l o o     W W W  o o r   l d  d    ",
    "    H  H ee  l l ooo      W W   ooo r   l  ddd    ",
    ]

    # Convert spaces, letters to 0, 1
    def to_10(s):
        """Convert letters to 1, then spaces to 0"""
        s = re.sub(r'\w', '1', s)
        s = re.sub(r'\s', '0', s)
        return s

    MSG = [to_10(s) for s in MSG]
    assert len(MSG[1]) == 50

    # Setup image as a concatenation of rows
    BORDER =  '1' +  '0' * 48 + '1'
    NULL = '0' * 50
    IMAGE = [BORDER] + [NULL] + MSG + [NULL] * (37-len(MSG)-3) + [BORDER]
    assert len(IMAGE) == 37

    # Convert strings to ints for use in convertible code
    TABLE = tuple([int(s, 2) for s in IMAGE])

    ### Hardware behavior ###

    # Timing constants
    hMaxCount = 1056-1
    hStartSync = 840
    hEndSync = 968
    vMaxCount = 628-1
    vStartSync = 601
    vEndSync = 605

    # Signals
    hCounter = Signal(intbv(0)[11:])
    vCounter = Signal(intbv(0)[10:])
    shiftReg = Signal(modbv(0)[50:])

    @always_comb
    def assign():
        v = intbv(0)[4:]
        v[3] = shiftReg[49]
        Red.next = v
        Green.next = v
        Blue.next = v

    @always(pixelClock.posedge)
    def draw():
        row = intbv(0)[6:]
        if hCounter == hMaxCount:
            hCounter.next = 0
            if vCounter == vMaxCount:
                vCounter.next = 0
            else:
                row[:] = vCounter[10:4]
                shiftReg.next = TABLE[row]
                vCounter.next = vCounter + 1
        else:
            hCounter.next = hCounter + 1
            if hCounter[4:] == 15:
                shiftReg.next = shiftReg << 1

        hSync.next = hCounter >= hStartSync and hCounter < hEndSync
        vSync.next = vCounter >= vStartSync and vCounter < vEndSync

    return assign, draw


