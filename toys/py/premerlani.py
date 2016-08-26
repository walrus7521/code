#!/usr/bin/python

from numpy import *
from numpy import linalg

##############################

# normalize a matrix
print "normalize a matrix"
M = [[ 1, 2, 3],
     [-2, 1, 4],
     [-3,-4, 1]]
M  = matrix(M)
print M
Mn = linalg.norm(M)
print Mn
M = M/Mn
print M
print
##############################
# normalize a vector
print "normalize a vector"
A  = [1, 2, 3]
A  = array(A)
print A
Anorm = linalg.norm(A)
print Anorm
B = A/Anorm
print B

##############################

def normalized(a, axis=-1, order=2):
    l2 = atleast_1d(linalg.norm(a, order, axis))
    l2[l2==0] = 1
    return a / expand_dims(l2, axis)

#A = random.randn(3,3,3)
A = random.randn(3,3)
print A
print "now normalize row 0 of A"
print normalized(A,0)
#print normalized(A,1)
#print normalized(A,2)

#print normalized(arange(3)[:,None])
#print normalized(arange(3))

exit()

##############################



# enter - gyro readings for roll, pitch and yaw

print "Premerlani DCM algorithm"

# Body-to-Earth Rotation Matrix:
Reb = [[ 1, 2, 3],
       [-2, 1, 4],
       [-3,-4, 1]]

# Earth-to-Body (Inverse) Rotation Matrix:
Reb  = matrix(Reb)
Rbe  = linalg.inv(Reb)
Rbet = matrix.transpose(Reb)

print Reb
print Rbe
print Rbet
exit()

bx = 1
by = 2
bz = 3

Bb  = [bx, by, bz]
Bb  = matrix(Bb)
Bbt = matrix.transpose(Bb)

print Reb
print Bb
print Bbt

