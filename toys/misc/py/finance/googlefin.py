#!/usr/bin/env python3

import yfinance as yf
import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
import csv
import sys


tick = []
f = open('nasdaq.csv', 'rt')
try:
    reader = csv.reader(f)
#    #headers = reader.next() # python 2.7
    headers = next(reader) # python 3
#    #print("headers: %s" % headers)
    for row in reader:
#        #print row
        sym = row[0]
#       print(sym)
        tick.append(sym)
except:
    print('ouch')


start = '2013-01-01'
end   = '2019-01-01'

for sym in tick:
    print(sym)
#    try:
    data = yf.download(sym,start,end)
#   data['Adj Close'].plot()
#   plt.show()

    ## Number of samplepoints
    N = 2048
    ## sample spacing
    T = 1.0 / N
    x = np.linspace(0.0, N*T, N)
    #y = np.sin(50.0 * 2.0*np.pi*x) + 0.5*np.sin(80.0 * 2.0*np.pi*x)
    y = data
    yf = scipy.fftpack.fft(y)
    xf = np.linspace(0.0, 1.0/(2.0*T), int(N/2))
    #
    fig, ax = plt.subplots()
#   ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
    #ax.plot(yf)
#   plt.show()
#    except:
    print('suck')
    yf.clear()

    
