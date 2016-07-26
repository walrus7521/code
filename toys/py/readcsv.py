import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

x = []
y = []
f = open("wave.csv", 'rt')
try:
    reader = csv.reader(f)
    headers = reader.next()
    #print("headers: %s" % headers)
    for row in reader:
        #print row
        y.append(row[1])
        x.append(row[0])

    plt.plot(x, y)
    plt.xlabel('sample(n)')
    plt.ylabel('voltage(V)')
    plt.show()

finally:
    f.close()

