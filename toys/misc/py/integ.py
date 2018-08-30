#!/usr/bin/python

from sympy import *

quit()

x = symbols('x')
a = Integral(cos(x)*exp(x), x)
Eq(a, a.doit())
Eq(Integral(exp(x)*cos(x), x), exp(x)*sin(x)/2 + exp(x)*cos(x)/2)
