#!/usr/bin/env python3

import numpy as np
from scipy import signal
import matplotlib.pyplot as plt

# Construct transfer function H(s)
#        s^2 + 3s + 3     num = [1,3,3]
# H(s) = ------------  => 
#        s^2 + 2s + 1     den = [1,2,1]

num = [1, 3, 3]
den = [1, 2, 1]

# continuous
cont = signal.TransferFunction(num, den)
print(cont)

# discrete - sample time 0.1 seconds
disc = signal.TransferFunction(num, den, dt=0.1)
print(disc)

a = [1,2,2,1] ; b = [0,1,0.5]
c = np.convolve(a, b)
print(c)
#plt.plot(a, '-')
#plt.plot(b, '+')
plt.plot(c, 'o')
plt.show()
quit()

t_c,y_c = signal.step(cont)

#t_d,y_d = signal.step(disc)
#t_d,y_d = step_response(disc, T)


plt.figure(1)
plt.plot(t_c, y_c,)
plt.xlabel('time')
plt.show()


