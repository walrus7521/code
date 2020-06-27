#!/usr/bin/env python3

from pandas_datareader import data as pdr
import pandas as pd
import yfinance as yf
from datetime import datetime

# Tickers list
# We can add and delete any ticker from the list to get desired ticker live data
#ticker_list = ['AMZN', 'MSFT', 'WDC', 'FB', 'AAPL']
ticker_list = ['WDC', 'OXY', 'IVV']

today = datetime.today()
# We can get data by our choice by giving days bracket
start_date = datetime(2020, 3, 1) #'2017–01–01'
end_date   = datetime(2020, 6, 26) #'2019–11–30'
files=[]
def getData(ticker):
    print (ticker)
    data = pdr.get_data_yahoo(ticker, start=start_date, end=today)
    return data
#    data = pdr.get_data_yahoo(ticker, start="2017-08-13",end="2017-08-14")    
#   dataname = ticker + '_' + str(today)
#   files.append(dataname)
#   SaveData(data, dataname)

# Create a data folder in your current dir.
#def SaveData(df, filename):
#    df.to_csv('./data/'+filename+'.csv')

#This loop will iterate over ticker list, will pass one ticker to get data, and save that data as file.
for tik in ticker_list:
    data = getData(tik)
#    for dp in data:
#        print(dp)
    print(len(data['Close'].values))
#   print(data)
#   data.to_csv(r'%s.csv' % tik) 
    for v in data['Close'].values:
        fv = float(v)
        print(fv)
