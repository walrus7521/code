#include <iostream>
#include <vector>

using namespace std;

// B[0] <= B[1] >= B[2] <= B[3] >= B[4] <= B[5] >= ...
void Rearrange(vector<int>* A) {
    auto& A_ref = *A;
    for (size_t i = 1; i < A_ref.size(); ++i) {
        if ((!(i & 1) && A_ref[i-1] < A_ref[i]) ||
            ( (i & 1) && A_ref[i-1] > A_ref[i])) {
            swap(A_ref[i-1], A_ref[i]);
        }
    }
}

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int main()
{
    vector<int> vi = {1,2,3,4,5};
    show(vi);
    Rearrange(&vi);
    show(vi);
}
