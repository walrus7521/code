#!/usr/bin/env python3

# Numerical Methods for Physics

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv


x = 3.
y = -2.
a = np.array([[1.],[2.],[3.]])  # column vector
b = np.array([0., 3., -4.])     # row vector
C = np.array([[1., 0., 1.],[0., 1., -1.],[1., 2., 0.]])
D = np.array([[0., 1., 1.], [2., 3., -1], [0., 0., 1.]])
E = np.array([[0., np.pi],[0., -1.], [x**2, np.sqrt(2.)]])


print('matrix: ')
print(D)
# transpose and invert matrices
dT = D.transpose()
print('transpose: ')
print(dT)

dInv = inv(D)
print('inverse: ')
print(dInv)

dot = np.dot(D, dInv)
print('dot(D, dInv): ')
print(dot)

cross = np.cross(D, dInv)
print('cross(D, dInv): ')
print(cross)


z = 5.
t = -6.
F = np.array([[1.,1.,4.],[2.,4.,-2.],[1.,2.,1.]])
G = np.array([[4, np.pi + np.sqrt(2)], [-3., -1.-np.sqrt(2)], [1., np.pi-2]])
z = x - y
t = np.dot(b, a)
F = C + D
G = np.dot(C, E)


#print(t)

H = C * D
J = E ** x
#print(H)
#print(J)

print(b[2])
print(G[0,1])

first1 = C[:,0]
first2 = np.array(C[:,0])
print(first1)
print(first2)

#x = input('dude enter: ')
#print(x)

x = np.arange(0,200)
y = np.empty(20*10)

for i in x:
    xi = i * 0.1
    y[i] = np.exp(-1.* xi/4. ) * np.sin(1.*xi)
#print(y)

#plt.plot(x,y)
#plt.semilogy(x,y)
#plt.polar(x,y)

#xmin = 0. ; xmax = 20.
ymin = 1.e-10; ymax = 1.
axes = plt.gca()
#axes.set_xlim([xmin,xmax])
axes.set_ylim([ymin,ymax])

#plt.show()

# test for orthogonality
# enter as [1, 1, 1]
#a = np.array(input('enter vector 1: '))
#b = np.array(input('enter vector 2: '))
a = np.array([1.,1.,1.])
b = np.array([1.,-2.,1.])

a_dot_b = 0.
for i in range(3):
    print(i, a[i], b[i])
    a_dot_b += a[i] * b[i]

print(a_dot_b)
a_dot_b = 0.
a_dot_b = np.dot(a, b)
print(a_dot_b)

if a_dot_b == 0:
    print('vectors are ortho')
else:
    print('vectors are NOT ortho')
    

