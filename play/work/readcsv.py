import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

# http://stackoverflow.com/questions/16503560/read-specific-columns-from-a-csv-file-with-csv-module

x = []
y = []
f = open("20181116_FreqSweep0_25Hz.csv", 'rt')
try:
    reader = csv.reader(f)
    headers = reader.next()
    print("headers: %s" % headers)
    for row in reader:
        #print row
        y.append(row[9])
        x.append(row[0])

    plt.plot(x, y)
    plt.xlabel('frame')
    plt.ylabel('amplitude')
    plt.show()

finally:
    f.close()

