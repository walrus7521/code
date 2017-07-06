#include <iostream>

using namespace std;

int main(){
    int N;
    int i;
    int result;
    cin >> N;
    if (N >= 2 && N <= 20) {
        for(int i=1; i <= 10; i++) {
            result = N * i;
            cout << N << " x " << i << " = " << result << endl;
        }
    }

    return 0;
}
