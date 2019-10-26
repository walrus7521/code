#!/usr/bin/python

import numpy as np    

names = [ "Grant", "Chad", "Alex", "MacKenzie", "Taylor", "Clarissa", "Kevin", "Cindy", "Bart", "Alusia" ]

b=list(range(10))
c=list(range(10))
np.random.shuffle(b)
np.random.shuffle(c)
print(b)
print(c)
#for n in b:
#    print names[n]

#for n in c:
#    print names[n]

for i in range(0, 10):
    print(names[b[i]], "...", names[c[i]])

