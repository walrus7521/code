#!/usr/bin/python

# pip install pythonnet

import sys
import clr

sys.path.append(r"c:\code\toys\py\com")
#clr.AddReference(r"c:\code\toys\py\com\calc.dll")
clr.AddReference(r"c:\code\toys\py\com\calc.exe")

from DynamicCS import DynamicCalc

calc=DynamicCalc()

print calc.__class__.__name__
# display the name of the class: 'DynamicCalc' 

a=7.5
b=2.5

res = calc.add(a, b)
print a, '+', b, '=', res

res = calc.sub(a, b)
print a, '-', b, '=', res

raw_input('Press any key to finish...')
