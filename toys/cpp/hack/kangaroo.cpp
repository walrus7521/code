#include <vector>
#include <iostream>

using namespace std;


int main(){
    int x1;
    int v1;
    int x2;
    int v2;
    cin >> x1 >> v1 >> x2 >> v2;

    if ((x2 > x1) && (v2 > v1)) {
        cout << "NO" << endl;
        return 0;
    }
    if ((x2 > x1) && (v1 > v2)) {
        // check if multiple
    }

    return 0;
}

