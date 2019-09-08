#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack

# Number of samplepoints
N = 600
# sample spacing
T = 1.0 / 800.0
x = np.linspace(0.0, N*T, N)

# lines at 50 and 80 hz    
y = 2.0*np.sin(50.0 * 2.0*np.pi*x) + 0.5*np.sin(80.0 * 2.0*np.pi*x)
yf = scipy.fftpack.fft(y)
xf = np.linspace(0.0, 1.0/(2.0*T), int(N/2))

fig, ax = plt.subplots()
ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
plt.show()

### input raw data and analyze spectral content
#data = [0,1,2,3,4,3,1,5,6,7,8] #wav.read('bells.wav')
#fft_out = scipy.fftpack.fft(data)
#plt.plot(data, np.abs(fft_out))
#plt.show()

