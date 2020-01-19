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

B = np.array([[1., 2., 3.],
              [4., 5., 6.],
              [7., 8., 9.]])
detB = np.linalg.det(B)
condB = np.linalg.cond(B)
print(detB)
print(condB)
