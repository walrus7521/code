from numpy import *
from numpy import linalg

# http://scipy.github.io/old-wiki/pages/Numpy_Example_List
# http://docs.scipy.org/doc/scipy/reference/tutorial/linalg.html
# http://mathworld.wolfram.com/RotationMatrix.html

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


# rotation 
print("2D rotate")
theta = 1.2 #radian
st = sin(theta)
ct = cos(theta)
Rth = [[ct, -st], [st, ct]]
Rth = matrix(Rth)
print(Rth)

print("3D rotate")
theta = 1.2 #radian
a = 2.3 # alpha
b = 3.5 # beta
g = 4.5 # gamma
sa = sin(a)
ca = cos(a)
sb = sin(b)
cb = cos(b)
sg = sin(g)
cg = cos(g)
Rx = [[ 1,  0,   0], [  0, ca, sa], [ 0, -sa, ca]]
Ry = [[cb,  0, -sb], [  0,  1,  0], [sb,   0, cb]]
Rz = [[cg, sg,   0], [-sg, cg,  0], [ 0,   0,  1]]
Rx = matrix(Rx)
Ry = matrix(Ry)
Rz = matrix(Rz)
Rot = Rx * Ry * Rz
print(Rx)
print(Ry)
print(Rz)
print(Rot)

# DCM - angles in degrees
print("DCM")
degrees_to_radians = 0.0174533
theta = 10 * degrees_to_radians
gamma = 20 * degrees_to_radians
psi   = 30 * degrees_to_radians

st = sin(theta)
ct = cos(theta)
sg = sin(gamma)
cg = cos(gamma)
sp = sin(psi)
cp = cos(psi)

rxx = ct*cg
ryx = ct*sg
rzx = -st
rxy = (sp*st*cg) - (cp*sg)
ryy = (sp*st*sg) + (cp*cg)
rzy = sp*ct
rxz = (cp*st*cg) + (sp*sg)
ryz = (cp*st*sg) - (sp*cg)
rzz = cp*ct

R = [[ rxx, ryx, rzx],
     [ rxy, ryy, rzy],
     [ rxz, ryz, rzz]]
R = matrix(R)

print("DCM Identity - via transpose")
I = transpose(R) * R
print(I)
print("DCM Identity - via inverse")
I = linalg.inv(R) * R
print(I)


