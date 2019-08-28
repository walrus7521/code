#!/usr/bin/env python3

# Numerical Methods for Physics
# interp - program to interpolate data using Lagrange
# polynomial to fit quadratic to 3 data points

import numpy as np
import matplotlib.pyplot as plt

def interpf(xi, x, y):
    """ Function to interpolate between data points 
    using Lagrange polynomial (quadratic)
    Inputs:
        x   Vector of x coordinates of data points (3 values)
        y   Vector of y coordinates of data points (3 values)
        xi  The x value where interpolation is computed

    Output:
        yi  The interpolated polynomial evaluated at xi
    """
    
    #* Calculate yi = p(xi) using Lagrange polynomial
    yi = ( (xi-x[1])*(xi-x[2])/((x[0]-x[1])*(x[0]-x[2])) * y[0]
    +      (xi-x[0])*(xi-x[2])/((x[1]-x[0])*(x[1]-x[2])) * y[1]
    +      (xi-x[0])*(xi-x[1])/((x[2]-x[0])*(x[2]-x[1])) * y[2] )
    return yi

#* Initialize data points to be fit by quadratic
x = np.empty(3)
x = np.array([-1., 0.5, 2.])
y = np.empty(3)
y = np.array([1., 0.25, 3.])

#temp = np.arange(0,0)
#print('Enter data points as x,y pairs (e.g., [1,2]')
#for i in range(3):
#    temp = np.array(input('Enter data point: '))
#    print(temp)

#* Establish min, max values of range of interpolation
xr = np.array([-3., 3.])

nplot = 100 # number data points
xi = np.empty(nplot)
yi = np.empty(nplot)
for i in range(nplot):
    xi[i] = xr[0] + (xr[1]-xr[0])* i/float(nplot)
    yi[i] = interpf(xi[i], x, y)

#* plot the curve
plt.plot(x, y, '*', xi, yi, '-')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Three point interp')
plt.legend(['data points', 'Interp  '])
plt.show()


