#include <iostream>
#include "util.h"

using namespace std;

int main()
{
    string str = "wusup";
    cout << "check     : " << UtilApi::Check() << endl;
    cout << "check(str): " << UtilApi::Check(str) << endl;
}
