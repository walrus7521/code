#!/usr/bin/env python3

# https://thehackerdiary.wordpress.com/2017/06/09/it-is-ridiculously-easy-to-generate-any-audio-signal-using-python/

import struct
import numpy as np
from scipy import signal as sg
import matplotlib.pyplot as plt


sampling_rate = 44100
freq = 440
samples = 44100
x = np.arange(samples)

# sine wave
y = 100 * np.sin(2 * np.pi * freq * x / sampling_rate)

# square wave
y = 100 * sg.square(2 * np.pi * freq * x / sampling_rate)
# square wave with duty cycle
y = 100 * sg.square(2 * np.pi * freq * x / sampling_rate, duty = 0.8)
# sawtooth wave
y = 100 * sg.sawtooth(2 * np.pi * freq * x / sampling_rate)


f = open('test.wav','wb')
for i in y:
    f.write(struct.pack('b',int(i)))
f.close()

n = len(y)
Y = np.fft.fft(y)/n # fft computing and normalization    

plt.plot(x,Y)
plt.show()

