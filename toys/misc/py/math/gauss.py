#!/usr/bin/python2.7

import numpy as np
import matplotlib.pyplot as plt

A = np.array([[3., 2., -1.],
              [-1., 3., 2.],
              [1., -1., -1.]])

bx = 1.; by = 1.; bz = 1.
b = np.array([[bx], [by], [bz]])

x = np.linalg.solve(A, b)

print(x)

