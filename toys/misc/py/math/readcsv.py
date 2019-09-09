#`/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import scipy.fftpack
import csv
import sys

# http://stackoverflow.com/questions/16503560/read-specific-columns-from-a-csv-file-with-csv-module

x = []
y = []
f = open("samples.csv", 'rt')
T = 1.0 / 100.0
maxF = 0
try:
    reader = csv.reader(f, delimiter=',')
    #headers = reader.next()
    headers = next(reader)
    
    print("headers: %s" % headers)
    for row in reader:
        #print(row[1])
        frame = int(row[0])
        y.append(float(row[13]))
        x.append(frame)
        if (frame > maxF):
            maxF = frame

    xf = np.linspace(0.0, 1.0/(2.0*T), int(maxF))
    yf = scipy.fftpack.fft(y)
    print(xf)
    print(len(xf))
    print(len(yf))
    #quit()
    #plt.plot(x, y, label='Loaded from file!')
    plt.plot(abs(yf))
    plt.xlabel('frame(n)')
    plt.ylabel('psi')
    plt.show()

finally:
    f.close()

