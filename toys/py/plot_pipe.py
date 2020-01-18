#!/usr/bin/env python3

import sys
import re
import csv
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from datetime import date

CAPTURE_LENGTH = 6 #200
TRIM_LENGTH = 1

# columns
fieldnames = ['x', 'y', 'z']

tim = []
frm = []
x   = []
y   = []
z   = []

reader = csv.DictReader(sys.stdin, fieldnames)
counter = 0
transition = 0

for row in reader:
    if (transition == 0):

        print("trigger")
        transition = 1
        counter = counter + 1

    if (transition == 1 and counter < CAPTURE_LENGTH):
        xx = float(row['x'])
        yy = float(row['y'])
        zz = float(row['z'])

        print("accumulate: {0},{1},{2}", xx, yy, zz)
        counter = counter + 1

        frm.append(counter)
        x.append(float(row['x']))
        y.append(float(row['y']))
        z.append(float(row['z']))

    if counter > CAPTURE_LENGTH:
        print("plot")
        break

t = frm
s = x
data = list(s)
tt   = list(t)

fig, ax = plt.subplots()

ax.plot(frm, x, label='x')
ax.plot(frm, y, label='y')
ax.plot(frm, z, label='z')

ax.grid()
ax.legend()
plt.show()


"""
data
1, 2, 3
2, 3, 4
4, 5, 6
7, 8, 9
5, 6, 7
"""

