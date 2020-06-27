#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

# http://stackoverflow.com/questions/16503560/read-specific-columns-from-a-csv-file-with-csv-module
DATE      = 0
HIGH      = 1
LOW       = 2
OPEN      = 3
CLOSE     = 4
VOLUME    = 5
ADJ_CLOSE = 6
x = []
y = []
# ['Date', 'High', 'Low', 'Open', 'Close', 'Volume', 'Adj Close']

def process(stock_csv):
#f = open("OXY.csv", 'rt')
    f = open(stock_csv, 'rt')
    try:
        reader = csv.reader(f)
        #headers = reader.next() # python 2.7
        #headers = next(reader) # python 3
        #print("headers: %s" % headers)
        for row in reader:
            print(row)
            y.append(row[OPEN])
            x.append(row[CLOSE])

        plt.plot(x, y)
        plt.xlabel('sample(n)')
        plt.ylabel('voltage(V)')
        plt.show()
    finally:
        f.close()

def main():
    process('OXY.csv');

if __name__ == "__main__":
    # execute only if run as a script
    main()
