#!/usr/bin/python

import os, sys
import binascii

def hexdump(buf, hexSize):

    PrintHeading()

    # print hex and ascii
    for i in range(0, hexSize, 16):
        for j in range(0,16):
            if (i == 0):
                print "%08x " % i,
            else:
                byteValue = buf[i+j]
#                print "%02x " % binascii.hexlify(byteValue),
                print "%s " % binascii.hexlify(byteValue),
        print " ",
        for j in range(0,16):
            byteValue = buf[i+j]
            if (byteValue >= 0x20 and byteValue <= 0x7f):
                print "%c" % byteValue,
            else:
                print '.',
        print
    return


def PrintHeading():
    print("Offset 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E OF ASCII")
    print("------------------------------------------------------------")
    return

def main():
    s = sys.stdin.read()    
    hexdump(s, 256)

if __name__=='__main__':
    main()
