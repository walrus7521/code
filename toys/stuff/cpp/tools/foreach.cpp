#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void myfunction (int i) {  // function:
    std::cout << ' ' << i;
}

struct myclass {           // function object type:
    void operator() (int i) {std::cout << ' ' << i;}
} myobject;

int in_channel(int i)
{
    if (i == 10 || i == 20 || i == 30 || i == 40) {
        return 0;
    }
    return 1;
}

int main () {
    std::vector<int> myvector;
    myvector.push_back(10);
    myvector.push_back(20);
    myvector.push_back(30);
    myvector.push_back(40);

    std::cout << "myvector contains:";
    for_each (myvector.begin(), myvector.end(), myfunction);
    std::cout << '\n';

    // or:
    std::cout << "myvector contains:";
    for_each (myvector.begin(), myvector.end(), myobject);
    std::cout << '\n';


    // interate contents and erase
    cout << "pre-erase size: " << myvector.size() << endl;
    for (vector<int>::const_iterator it = myvector.begin();
                it != myvector.end(); ) {
        cout << *it << endl;
        if (!in_channel(*it)) {
            it = myvector.erase(it);
        } else {
            ++it;
        }
    }
 
    // verify erasure
    cout << "post-erase size: " << myvector.size() << endl;
    for (vector<int>::const_iterator it = myvector.begin();
                it != myvector.end(); ++it) {
        cout << *it << endl;
    }

  return 0;
}

