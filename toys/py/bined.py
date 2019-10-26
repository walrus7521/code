#!/usr/bin/env python3

# https://stackoverflow.com/questions/11462466/read-and-write-binary-file-in-python

with open("test.bin", "rb") as f:
    byte = f.read(1)
    while byte:
        # Do stuff with byte.
        byte = f.read(1)
        print(byte)


