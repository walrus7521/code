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

void show(const int a[2][2]) {
    int i, j, row=2, col=2;
    for( i=0;i<row;i++){
        cout<< endl;
        for( j=0;j<col;j++){
            cout<<"\t"<< a[i][j]<<"    ";
        }
    }
}

int inv() {

  int i,j;
  float determinant=0;
  int a[2][2] = {{3, 5},
                 {3, 9}};

  cout << "The matrix is:" << endl;
  for(i=0;i<2;i++){
      cout << endl;
      for(j=0;j<2;j++)
           cout << a[i][j] << '\t';
  }
  cout << endl;
  //for(i=0;i<2;i++)
  //    determinant = determinant + (a[0][i]*(a[1][(i+1)%2]*a[2][(i+2)%2] - a[1][(i+2)%2]*a[2][(i+1)%2));

   cout << "Inverse of matrix is: " << endl;
#if 0
   for(i=0;i<2;i++){
      for(j=0;j<2;j++)
           printf("%.2f\t",((a[(i+1)%3][(j+1)%3] * a[(i+2)%3][(j+2)%3]) - (a[(i+1)%3][(j+2)%3]*a[(i+2)%3][(j+1)%3]))/ determinant);
       printf("\n");
   }
#endif
   return 0;
}


int main(){
    const int row=2,col=2;
    int var, i, j;
    int A[row][col] = { {1, -1},
                        {3, 2}};
    int B[row][col] = { {1, 0},
                        {0, 1}};
    int C[row][col], T[row][col];

    inv();
    return 0;

    cout << endl << "show mult" << endl;
    mxmult(A, B, C, 2);
    show(C);

    cout << endl << "show trans" << endl;
    mxtrans(C, T, 2);
    show(T);

    cout << endl << "show dot" << endl;
    mxdot(A, B, C, 2);
    show(C);
    
    cout << endl << "show cross" << endl;
    mxcross(A, B, C, 2);
    show(C);
    
    return 0;
}


