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
    for (double i = 0.0; i < 32.0; i += 1.0) {
        double squares = i * i;
        streamsize prec = cout.precision();
        cout << setw(6) << setprecision(6) << squares
                        << setprecision(prec) << endl;
    }

    return 0;
}
