// tour code
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int test()
{
    map<string, set<int> > concordance;

    concordance["newcastle"].insert(98056);
    concordance["newcastle"].insert(98057);
    concordance["renton"].insert(98054);
    concordance["renton"].insert(98055);
    concordance["bellevue"].insert(98035);
    concordance["issaquah"].insert(98027);

    map<string, set<int> >::const_iterator iter =
        concordance.begin();
    while (iter != concordance.end()) {
        cout << (*iter).first << endl;
        set<int>::const_iterator siter = (*iter).second.begin();
        while (siter != (*iter).second.end()) {
            cout << " : " << (*siter) << endl;
            siter++;
        }
        iter++;
    }
}


int main()
{
    test();
    return 0;
}

