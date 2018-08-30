#include <iostream>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    int** seq {new int*[N]};   

    for (int i = 0; i < N; ++i) {
        int len;
        cin >> len;
        seq[i] = new int[len];
        for (int j = 0; j < len; ++j) {
            cin >> seq[i][j];
        }
    }

    for (int i = 0; i < Q; ++i) {
        int a, b;
        cin >> a >> b;
        cout << seq[a][b] << endl;
    }

}
