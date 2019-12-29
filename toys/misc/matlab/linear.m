% solve system of equations:
%
% 4x -  2y + 6z = 8
% 2x +  8y + 2z = 4
% 6x + 10y + 3z = 0
%
% AX = B
% A [x, y, z]' = B

A = [4, -2, 6; 2, 8, 2; 6, 10, 3];
B = [8; 4; 0];
X = A\B %  left div

% or solve using inverse
Xb = inv(A)*B

% XC = D
% [, y, z] C = D
C = [4, 2, 6; -2, 8, 10; 6, 2, 3];
D = [8, 4, 0];
Xc = D / C % right division

% element by element
