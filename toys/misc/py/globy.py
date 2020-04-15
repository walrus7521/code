#!/usr/bin/en python3

import glob

print(glob.__file__)

a = glob.glob('*.py')
print(a)

print('Named explicitly:') 
for name in glob.glob('c:\\sandbox\\theplan.xlsx'): 
    print(name) 
  
# Using '*' pattern  
print('\nNamed with wildcard *:') 
for name in glob.glob('c:\\sandbox\\*'): 
    print(name) 
  
# Using '?' pattern 
print('\nNamed with wildcard ?:') 
for name in glob.glob('c:\\sandbox\\thepla?.xlsx'): 
    print(name) 
  
# Using [a-z] pattern 
print('\nNamed with wildcard ranges:') 
for name in glob.glob('c:\\sandbox\\the*[a-z].*'): 
    print(name) 

