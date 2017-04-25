#include <iostream>
#include "StrVec.h"

using namespace std;

int main()
{
    StrVec v;
    StrVec u(v);
    u = v;

    StrVec v1, v2;
    v1 = v2;
    //StrVec getVec(istream &);
    //v2 = getVec(cin);
    v1.push_back("sup"); // uses move
    string s("bart"); // uses copy
    v1.push_back(s);

    cout << "emplace" << endl;
    v1.emplace_back(10, 'c');
    v1.emplace_back("hello", "world");
    v1.emplace_back(1,2,3,4);

}
