#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::streamsize;
using std::endl;
using std::setprecision;
using std::setw;

int main()
{
    int i, squares;

    for (i = 0; i < 32; i++) {
        cout << setw(6) << i << ":" << i * i << endl;
    }

    return 0;
}
