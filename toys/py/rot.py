#!/usr/bin/python

from numpy import *
from numpy import linalg

a = 1.4
Rx = [[1,      0,       0, 0],
      [0, cos(a), -sin(a), 0],
      [0, sin(a),  cos(a), 0],
      [0,      0,       0, 1]]
Rx = matrix(Rx)
print Rx

b = 0.4
Ry = [[ cos(b),  0,  sin(b), 0],
      [      0,  1,       0, 0],
      [-sin(b),  0,  cos(b), 0],
      [      0,  0,       0, 1]]
Ry = matrix(Ry)
print Ry

c = 0.4
Rz = [[ cos(c), -sin(c), 0, 0],
      [ sin(c),  cos(c), 0, 0],
      [      0,       0, 1, 0],
      [      0,       0, 0, 1]]
Rz = matrix(Rz)
print Rz

# rotates about z, then y, then x
Rot = Rx*Ry*Rz
print Rot


