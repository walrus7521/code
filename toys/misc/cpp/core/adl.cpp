#include <iostream>

using namespace std;

namespace rocketscience {

    struct matrix { char c; };
    void initialize(matrix& A) { cout << "sup: " << A.c << endl; }
    void add(const matrix& A, const matrix& B, matrix& C) {}
    matrix operator+(const matrix& A, const matrix& B)
    {
        matrix C;
        initialize(C);
        add(A,B,C);
        return C;
    }
    ostream& operator<<(ostream& os, const matrix& A) { os << A.c; return os; }
}


int main()
{
    rocketscience::matrix A, B, C, D;
    A.c = 'a';
    B.c = 'b';
    C.c = 'c';
    D.c = 'd';
    rocketscience::initialize(B);
    initialize(C); // argument dependent lookup

    cout << A << B << C << D << endl;
}

