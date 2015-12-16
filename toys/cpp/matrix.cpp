#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <set>

using namespace std;

class Matrix
{
    private:
    public:
        int nrows, ncols;
        vector<vector<double>> M;
        Matrix(int rows, int cols) {
            this->nrows = rows;
            this->ncols = cols;
            M.resize( cols , vector<double>( rows ) );
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    M[r][c] = 0.0;
                }
            }
        }
        ~Matrix() {
        }
        void show() {
            for (int row = 0; row < nrows; row++) {
                for (int col = 0; col < ncols; col++) {
                    printf("%lf ", M[row][col]);
                }
                printf("\n");
            }
        }

};

void dump(const Matrix& m) {
    for (int row = 0; row < m.nrows; row++) {
        for (int col = 0; col < m.ncols; col++) {
            printf("%.2lf ", m.M[row][col]);
        }
        printf("\n");
    }
}

int main()
{
    int nrows, ncols, i;
    nrows = ncols = 4;
    Matrix m(nrows, ncols);
    //m.show();
    dump(m);
    return 0;
}

