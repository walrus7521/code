#!/usr/bin/env python3

import os
import sys

def CountFile(f):
    counter = 0
    if f.endswith('.c'):
        print("file: {0}".format(f))
        with open(f, "rb") as fin:
            for line in fin:
                counter = counter + 1
        fin.close()
    else:
        pass
    return counter

def CountDir(dirname):
    counter = 0
    for f in os.listdir(dirname):
        fa = os.path.join(dirname, f)
        if os.path.isdir(fa):
            dcount = CountDir(fa)
            counter = counter + dcount
        else:
            fcount = CountFile(fa)
            counter = counter + fcount
    return counter

# give it a directory path
print(CountDir(sys.argv[1]))

