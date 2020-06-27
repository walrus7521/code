#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

N = input('Enter num points: ')
freq = input('Enter frequency of sine wave: ')
phase = input('Enter phase of sine wave: ')

tau = 1.0 # time increment
N = int(N) # convert str to int
freq = float(freq)
phase = float(phase)
T = 1 / freq

t = np.linspace(0.0, N*1.0, N)

y = np.sin(2*np.pi*t*freq + phase)
    
f = np.arange(N)/(N*tau) # f = [0, 1.(N*tau), 2/(N*tau), ...]

### compute the transform
yt = np.zeros(N, dtype=complex)
Method = input('Compute transform by: 1) Direct summation; 2) FFT :')

import time
startTime = time.time()
if Method == '1':
    twoPiN = -2.0 * np.pi * (1j)/N # (1j = sqrt(-1)
    for k in range(N):
        for j in range(N):
            expTerm = np.exp( twoPiN*j*k )
            yt[k] += y[j] * expTerm

else: # FFT method
    yt = np.fft.fft(y)

stopTime = time.time()

print('Elapsed time = ', stopTime - startTime, ' seconds')

#Graph the time series and its transform
plt.subplot(1, 2, 1) # Left plot
plt.plot(t, y)
plt.title('Original time series')
plt.xlabel('Time')

plt.subplot(1, 2, 2) # Right plot
plt.plot(f, np.real(yt), '-', f, np.imag(yt), '--')
plt.legend(['Real', 'Imaginery '])
plt.title('Fourier tranform')
plt.xlabel('Frequency')

plt.show()

# Compute PSD
powspec = np.empty(N)
for i in range(N):
    powspec[i] = abs(yt[i])**2
plt.semilogy(f, powspec, '-')
plt.title('Power spectrum (unnormalized)')
plt.xlabel('Frequency')
plt.ylabel('Power')

plt.show()



