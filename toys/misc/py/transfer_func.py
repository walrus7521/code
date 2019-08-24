#!/usr/bin/env python3

from scipy import signal
import matplotlib.pyplot as plt

num = [1, 3, 3]
den = [1, 2, 1]

sys = signal.TransferFunction(num, den)
print(sys)
t,y = signal.step(sys)

plt.figure(1)
plt.plot(t, y,)
plt.xlabel('time')
plt.show()

