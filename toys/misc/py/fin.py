#!/usr/bin/env python3

#from googlefinance import getQuotes
#import json
#print(json.dump(getQuotes('AAPL'), indent=2))

from fxcmpy import fxcmpy_tick_data_reader as tdr
import datetime as dt

print(tdr.get_available_symbols())

start = dt.datetime(2018, 6, 25)
stop  = dt.datetime(2018, 6, 30)

td = tdr('EURUSD', start, stop)
td.get_raw_data().info()
print(td.get_data().head())


