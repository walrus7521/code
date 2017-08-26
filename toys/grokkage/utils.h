#ifndef _UTILS_H_
#define _UTILS_H_

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exchg(A, B) { int t = A; A = B; B = t; } 

#define GE(x, y) ((x) >= (y))
#define LE(x, y) ((x) <= (y))
#define LT(x, y) ((x) < (y))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define exchg2(X, Y) { \
    (X) = (X) ^ (Y);   \
    (Y) = (Y) ^ (X);   \
    (X) = (X) ^ (Y); }

#define cmpexchg(A, B) if (less(B, A)) exchg(A, B)


#endif // _UTILS_H_
