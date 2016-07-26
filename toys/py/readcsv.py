import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

f = open("wave.csv", 'rt')
try:
    reader = csv.reader(f)
    headers = reader.next()
    print("headers: %s" % headers)
    for row in reader:
        print row
finally:
    f.close()


