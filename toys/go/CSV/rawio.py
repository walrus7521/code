#!/usr/bin/env python3

import fieldnames # auto-generated file from parser

# https://www.devdungeon.com/content/working-binary-data-python
records = {
    "frame" : 4,
    "x" : 4,
    "y" : 4,
    "z" : 4
    }

data = records

"""
with open("dude.log", "rb") as binary_file:
    # Seek a specific position in the file and read N bytes
    binary_file.seek(0, 0)  # Go to beginning of the file
    recno = 0
    while (True):
        binary_file.seek(recno * 16, 1)  # Go to beginning of the file
        print()
        for r in records:
            #print(r, " : ", records[r])
            x = binary_file.read(records[r])
            y = int.from_bytes(x, byteorder='little', signed=False)
            #print(x, " =>", y)
            print(y)

"""
def bytes_from_file(filename, chunksize=16):
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(chunksize)
            if chunk:
                for b in chunk:
                    yield b
            else:
                break

# example:
for b in bytes_from_file('dude.log'):
    print(b)
