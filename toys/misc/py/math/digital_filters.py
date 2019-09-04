#!/usr/bin/env python2.7

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

