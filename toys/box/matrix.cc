#include <iostream>
#include <cmath>

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

void show(const int a[2][2]) {
    int i, j, row=2, col=2;
    for( i=0;i<row;i++){
        cout<< endl;
        for( j=0;j<col;j++){
            cout<<"\t"<< a[i][j]<<"    ";
        }
    }
}

int main(){
    const int row=2,col=2;
    int var, i, j;
    int A[row][col] = { {1, -1},
                        {3, 2}};
    int B[row][col] = { {1, 0},
                        {0, 1}};
    int C[row][col], T[row][col];

    cout << endl << "show mult" << endl;
    mxmult(A, B, C, 2);
    show(C);

    cout << endl << "show trans" << endl;
    mxtrans(C, T, 2);
    show(T);

    return 0;
}

