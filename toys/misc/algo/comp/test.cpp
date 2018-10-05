#include "utils.h"

int main()
{
    vi y;
    y.push_back(42);

    for(auto x : y) {
        cout << x << endl;
    }

    msi z {
        {"dude",  41},
        {"wusup", 42},
        {"dawg",  43},
    
    };

    for(auto x : z) {
        cout << x.first << " : " << x.second << endl;
    }
}
