#include <iostream>
#include <vector>

using namespace std;

int do_vec()
{
    vector<int> ni = {1,2,3,4};
    cout << "yo sup homi" << endl;
    for (auto& it : ni) {
        cout << it << endl;
    }
}
