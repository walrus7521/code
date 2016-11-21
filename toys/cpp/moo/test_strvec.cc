#include <iostream>
#include "StrVec.h"

int main()
{
    StrVec v;
    StrVec u(v);
    u = v;
}
