#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "strblob.h"

using std::cout; using std::endl;

int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        cout << "b1=" << b1.data.use_count() << endl;
        cout << "b2=" << b2.data.use_count() << endl;
    }
    cout << "b1=" << b1.data.use_count() << endl;
    return 0;
}
