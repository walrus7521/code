#!/usr/bin/env python

import ctypes
from ctypes import cdll

lib = cdll.LoadLibrary('./libmx.so')

lib.restype = ctypes.POINTER(ctypes.c_int * 10)

#class Foo(object):
#    def __init__(self):
#        self.obj = lib.Foo_new()
#
#    def bar(self):
#        lib.Foo_bar(self.obj)
#
#f = Foo()
#f.bar() #and you will see "Hello" on the screen

#ArrayType = ctypes.c_char*10
ArrayType = ctypes.c_double*10

# http://stackoverflow.com/questions/14887378/how-to-return-array-from-c-function-to-python-using-ctypes
# parse file
with open("test.mx") as f:
    for line in f:
        output = lib.xrefpy(line.rstrip());
        #print [i for i in output.contents] 
        print(output)
        #print "xrefpy: %s" % (output)
        #for i in output.contents:
            #print ": " % output.contents


