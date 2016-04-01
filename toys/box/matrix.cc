#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

void mxtrans(const int a[2][2], int t[2][2], int dim) {
    int i, j, row=2, col=2;
    for (i = 0; i < dim; i++) {
        for( j = 0; j < dim; j++ ) {
            t[j][i] = a[i][j];
        }
    }
}

void mxmult(const int a[2][2], const int b[2][2], int c[2][2], int dim) {
    int var, i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for(int k = 0; k < dim; k++) {
                var=var+(a[i][k]*b[k][j]);
            }
            c[i][j]=var;
            var=0;
        }
    }
}

void mxcross(const int a[2][2], const int b[2][2], int c[2][2], int dim) {
    int var, i, j, d;
    int bt[2][2];
    mxtrans(b, bt, dim);
    mxmult(a, bt, c, dim);
}

void mxdot(const int a[2][2], const int b[2][2], int c[2][2], int dim) {
    int var, i, j, d;
    int at[2][2];
    mxtrans(a, at, dim);
    mxmult(at, b, c, dim);
}

void show(const int **a, int dim) {
    int i, j;
    for( i=0;i<dim;i++){
        cout<< endl;
        for( j=0;j<dim;j++){
            cout<<"\t"<< a[i][j]<<"    ";
        }
    }
}

int mxinv() {

    int i,j, dim=3;
    float determinant=0;
    int a[3][3] = {{3, 5, 2},
                   {1, 5, 8},
                   {3, 9, 2}};
    float inv[3][3];

    cout << "The matrix is:" << endl;
    for(i=0;i<dim;i++){
        cout << endl;
        for(j=0;j<dim;j++)
            cout << a[i][j] << '\t';
    }
    cout << endl;

    determinant = 0;
    for(i = 0; i < dim; i++) {
        determinant = determinant + (a[0][i] * (a[1][(i+1) % dim] * a[2][(i+2) % dim] - a[1][(i+2) % dim] * a[2][(i+1) % dim]));
    }

    cout << "the determinant is: " << determinant << endl;
    cout << "Inverse of matrix is: " << endl;
    float v;
    for(i=0;i<dim;i++) {
        for(j=0;j<dim;j++) {
            v = ((a[(i+1)%3][(j+1)%3] * a[(i+2)%3][(j+2)%3]) - (a[(i+1)%3][(j+2)%3]*a[(i+2)%3][(j+1)%3]))/ determinant;
            inv[i][j] = v;
            printf("%.2f\t", v);
            //printf("%.2f\t",((a[(i+1)%3][(j+1)%3] * a[(i+2)%3][(j+2)%3]) - (a[(i+1)%3][(j+2)%3]*a[(i+2)%3][(j+1)%3]))/ determinant);
        }
        printf("\n");
    }
        printf("\n");

    for(i=0;i<dim;i++) {
        for(j=0;j<dim;j++) {
            v = inv[i][j];
            printf("%.2f\t", v);
        }
        printf("\n");
    }
    
   return 0;
}

int main(){
    const int row=2,col=2;
    int var, i, j, dim = 2;
    int A[row][col] = { {1, -1},
                        {3, 2}};
    int B[row][col] = { {1, 0},
                        {0, 1}};
    int C[row][col], T[row][col];

    mxinv();
    //return 0;

    cout << endl << "show mult" << endl;
    mxmult(A, B, C, dim);
    show((const int **) C, dim);

    cout << endl << "show trans" << endl;
    mxtrans(C, T, dim);
    show((const int **) T, dim);

    cout << endl << "show dot" << endl;
    mxdot(A, B, C, dim);
    show((const int **) C, dim);
    
    cout << endl << "show cross" << endl;
    mxcross(A, B, C, dim);
    show((const int **) C, dim);
    
    return 0;
}

