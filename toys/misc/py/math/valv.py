#!/usr/bin/env python3

from pylab import *
import scipy.signal as signal
import filter_plot as flt


#print('lpf')
#lti = signal.lti([1.0], [1.0, 1.0])
#t, y = signal.step(lti)
#plt.plot(t, y)
#plt.xlabel('Time [s]')
#plt.ylabel('Amplitude')
#plt.title('Step response for 1. Order Lowpass')
#plt.grid()
#plt.show()
#quit()


print('valvano')
# test of valvano pg 273
t = np.linspace(-1, 1, 201)
x = (np.sin(2*np.pi*0.75*t*(1-t) + 2.1) +
      0.1*np.sin(2*np.pi*1.25*t + 1) +
      0.18*np.cos(2*np.pi*3.85*t))
xn = x + np.random.randn(len(t)) * 0.08
#Create an order 3 lowpass butterworth filter:

imp  = signal.unit_impulse(201, 'mid')
step = signal.unit_impulse(201, 'mid')

#b, a = signal.butter(4, 0.05)
#print(b, a)
b = [1,0,0,0,-1]
a = [1,-1,0,0,0]
#y = signal.lfilter(b, a, imp) # imp or x
lti = signal.lti(b, a)
print(lti)
t, y = signal.step(lti)
#plt.plot(t, imp) # imp or x
plt.plot(t, y)
plt.show()
quit()
# Apply the filter to xn. Use lfilter_zi to choose the initial condition of the filter:

zi = signal.lfilter_zi(b, a)
z, _ = signal.lfilter(b, a, xn, zi=zi*xn[0])
# Apply the filter again, to have a result filtered at an order the same as filtfilt:

z2, _ = signal.lfilter(b, a, z, zi=zi*z[0])
# Use filtfilt to apply the filter:


y = signal.filtfilt(b, a, xn)
# Plot the original signal and the various filtered versions:

plt.figure
plt.plot(t, xn, 'b', alpha=0.75)
plt.plot(t, z, 'r--', t, z2, 'r', t, y, 'k')
plt.legend(('noisy signal', 'lfilter, once', 'lfilter, twice',
             'filtfilt'), loc='best')
plt.grid(True)
plt.show()



