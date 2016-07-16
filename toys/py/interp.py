import Tkinter as tk
import numpy as np
import matplotlib.pyplot as plt


# need values, slopes
A = np.matrix([[1, 2],[3, 4]])
#matrix([[1, 2],
#        [3, 4]])
print A

for row in range(0,1+1,1):
    for col in range(0,1+1,1):
        x = A.item((row, col))
        print x

