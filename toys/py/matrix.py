from numpy import *
from numpy import linalg

# http://scipy.github.io/old-wiki/pages/Numpy_Example_List
# http://docs.scipy.org/doc/scipy/reference/tutorial/linalg.html

T = [[1,2,47,11],[3,2,8,15],[0,0,3,1],[0,0,8,1]]
S = [[113,49,2,283],[-113,0,3,359],[0,5,0,6],[0,20,0,12]]

T = matrix(T)
S = matrix(S)
print(S * T)


A = matrix('1 3 4; 5 6 9; 7 9 2') # matrix is synonymous with mat
B = matrix([[1, 3, 4],
            [5, 6, 9],
            [1, 2, 3]])
C = linalg.inv(A)
print("S^{-1} * A * B")
print(linalg.inv(B) * A * B)

F = matrix([[0.1, 0.3, 0.4],
            [0.5, 0.6, 0.9],
            [0.1, 0.2, 0.3]])

G = matrix([[0.0, 0.0, 1.0],
            [0.0, 0.0, 1.0],
            [0.0, 0.0, 1.0]])

print(F * matrix.transpose(G))

print("determinant")
print(linalg.det(F))


