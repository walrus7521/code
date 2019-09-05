#!/usr/bin/env python3

from pylab import *
import scipy.signal as signal
import filter_plot as flt

# low pass filter
n = 61
a = signal.firwin(n, cutoff = 0.3, window = "hamming")
#Frequency and phase response
flt.mfreqz(a)
show()
#Impulse and step response
figure(2)
flt.impz(a)
show()

# high pass filter
n = 101
a = signal.firwin(n, cutoff = 0.3, window = "hanning")
#Spectral inversion
a = -a
#a[n/2] = a[n/2] + 1
flt.mfreqz(a)
show()

figure(2)
flt.impz(a)
show()

# impulse function
imp = signal.unit_impulse(8)
print('impulse: ', imp)


# https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.unit_impulse.html
print("butter resp")

imp = signal.unit_impulse(100, 'mid')
b, a = signal.butter(4, 0.2)
response = signal.lfilter(b, a, imp)
plt.plot(np.arange(-50, 50), imp)
plt.plot(np.arange(-50, 50), response)
plt.margins(0.1, 0.1)
plt.xlabel('Time [samples]')
plt.ylabel('Amplitude')
plt.grid(True)
plt.show()




