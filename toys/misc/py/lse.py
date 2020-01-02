#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

x = np.random.rand(3, 2) * 10
a = np.matrix([ [1,x[0][0]], [1,x[1][0]], [1,x[2][0]] ])
b = np.matrix([ [x[0][1]], [x[1][1]], [x[2][1]] ])
yy = (a.T * a).I * a.T * b
xx = np.linspace(1, 10, 50)
y = np.array(yy[0] + yy[1] * xx)

plt.figure(1)
plt.plot(xx, y.T, color='r')
plt.scatter([x[0][0], x[1][0], x[2][0] ], [x[0][1], x[1][1], x[2][1] ]) 
plt.show()
