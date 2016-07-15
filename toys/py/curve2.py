import Tkinter as tk
import numpy as np
import matplotlib.pyplot as plt

# http://docs.scipy.org/doc/numpy/reference/generated/numpy.linalg.lstsq.html 

# Fit a line, y = mx + c, through some noisy data-points:
#x = np.array([0, 1, 2, 3])
#y = np.array([-1, 0.2, 0.9, 2.1])

x = np.array([50, 70, 90])
y = np.array([0.25, 0.50, 2.00])

A = np.vstack([x, np.ones(len(x))]).T
print A

m, c = np.linalg.lstsq(A, y)[0]
#print(m, c)
print "slope: %f, intercept: %f" % (m, c)

# Plot the data along with the fitted line:

plt.plot(x, y, 'o', label='Original data', markersize=10)
plt.plot(x, m*x + c, 'r', label='Fitted line')
plt.legend()
plt.show()

