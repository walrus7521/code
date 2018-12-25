#!/usr/bin/env python

# https://stackoverflow.com/questions/24640817/python-ctypes-definition-for-c-struct

import ctypes

# struct emxArray_real_T
# {
#     double *data;
#     int *size;
#     int allocatedSize;
#     int numDimensions;
#     boolean_T canFreeData;
# };

class EmxArray(ctypes.Structure):
    """ creates a struct to match emxArray_real_T """

    _fields_ = [('data', ctypes.POINTER(ctypes.c_double)),
                ('size', ctypes.POINTER(ctypes.c_int)),
                ('allocatedSize', ctypes.c_int),
                ('numDimensions', ctypes.c_int),
                ('canFreeData', ctypes.c_bool)]

data = (1.3, 3.5, 2.7, 4.1)
L = len(data)
x = EmxArray()
x.data = (ctypes.c_double * L)(*data)
x.size = (ctypes.c_int * 1)(L)
LL = len(x.data[:L])
print(LL)
for v in x.data[:L]:
    print(v)

## alternatively or whatever
# make some random data to pass in
data_in = [1., 2., 4., 8., 16.]
L = len(data_in)
# create an empty array of the same size for the output
data_ou = [0] * L

# put this in a ctypes array
ina = (ctypes.c_double * L)(*data_in)
oua = (ctypes.c_double * L)(*data_ou)
# create a pointer for these arrays & set the rows and columns of the matrix
inp = ctypes.pointer(ina)
oup = ctypes.pointer(oua)

nrows = ctypes.c_int(1)
ncols = ctypes.c_int(L)

print(nrows, ncols)
print(ina[:L])
print(oua[:L])


