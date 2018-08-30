#!/usr/bin/python

# Mac OS: build/lib.macosx-10.9-intel-2.7/Extest.so -> /Library/Python/2.7/site-packages

from distutils.core import setup, Extension

# c version
#MOD = 'Extest'
#setup(name=MOD, ext_modules=[Extension(MOD, sources=['Extest2.c'])])

# c++ version
MOD = 'Extest'
setup(name=MOD, ext_modules=[Extension(MOD, sources=['Extest3.cc'])])


