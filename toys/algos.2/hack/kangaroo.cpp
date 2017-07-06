#include <vector>
#include <iostream>

using namespace std;

int main() {
    int x1;
    int v1;
    int x2;
    int v2;

    cin >> x1 >> v1 >> x2 >> v2;

    while (1) {
        if ((x2 > x1) && (v2 > v1) || 
            (x1 > x2) && (v1 > v2) || 
            (v1 == v2)) 
        {
            cout << "NO" << endl;
            break;
        }

        if (x1 == x2) 
        {
            cout << "YES" << endl;
            break;
        }

        x1 += v1;
        x2 += v2;
    }
    return 0;
}


