
import yfinance as yf
import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
import csv
import sys


# https://medium.com/@jouneidraza522/yahoo-finance-api-to-get-stocks-tickers-data-in-python-c49820249a18

# Get the data for the stock AAPL
#start = '2013-01-01'
#end   = '2019-01-01'
#ticker = 'INTC' #'WDC'
#data = yf.download(ticker,start,end)
#data['Adj Close'].plot()
#plt.show()

## Number of samplepoints
#N = 2048
## sample spacing
#T = 1.0 / N
#x = np.linspace(0.0, N*T, N)
##y = np.sin(50.0 * 2.0*np.pi*x) + 0.5*np.sin(80.0 * 2.0*np.pi*x)
#y = data
#yf = scipy.fftpack.fft(y)
#xf = np.linspace(0.0, 1.0/(2.0*T), int(N/2))
#
#fig, ax = plt.subplots()
#ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
##ax.plot(yf)
#plt.show()


##### comments and stuff

# Import the yfinance. If you get module not found error the run 
# !pip install yfinance from your Jupyter notebook

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

