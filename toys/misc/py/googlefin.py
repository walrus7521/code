#!/usr/bin/env python3

# stock market data grabber

# https://stackoverflow.com/questions/49045208/how-do-i-retrieve-google-finance-historical-data-in-google-sheets-using-the-api
#
# https://aroussi.com/post/python-yahoo-finance
# https://towardsdatascience.com/a-comprehensive-guide-to-downloading-stock-prices-in-python-2cd93ff821d4
#
#from googlefinance import getQuotes
#import googlefinance
#import json


#amzn = googlefinance("AMZN", "all", "1/1/2018", "2/1/2018")
#print(amzn)
#print(getQuotes('AAPL'))


#import yfinance as yf
#import pandas as pd
#import matplotlib.pyplot as plt

#ticker = yf.Ticker("WDC")
#print(msft.info)
#hist = ticker.history(period="max")
#print(hist)

#hist['Close'].plot(title="TSLA's stock price")

#input("Press Enter to continue...")

#tsla_df = yf.download('TSLA', 
#                      start='2019-01-01', 
#                      end='2019-12-31', 
#                      progress=False)
#tsla_df.head()
#print(tsla_df)

# Import the yfinance. If you get module not found error the run !pip install yfinance from your Jupyter notebook
import yfinance as yf
import numpy as np
import scipy.fftpack
import matplotlib.pyplot as plt

# Get the data for the stock AAPL
start = '2010-01-01'
end   = '2020-04-11'
ticker = 'WDC'
#data = yf.download('AAPL','2016-01-01','2019-08-01')
data = yf.download(ticker,start,end)

data['Adj Close'].plot()
plt.show()

    # Number of samplepoints
N = 600
# sample spacing
T = 1.0 / 800.0
yf = scipy.fftpack.fft(data['Adj Close'])
xf = np.linspace(0.0, 1.0/(2.0*T), N/2)
fig,ax = plt.subplots()
ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
plt.show()

#ax.plot(fdata)

