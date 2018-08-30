#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}


#if 0
void rotate_left_q(int* queue, const int count) {
    const int first_element = *(queue + 0);
    for (int index = 0; index < count; ++index) {
        *(queue + index) = *(queue + index + 1);
    }
    *(queue + count - 1) = first_element;
}
 
void rotate_right_q(int* queue, const int count) {
    const int last_element = *(queue + count - 1);
    for (int index = count - 1; index >= 0; --index) {
        *(queue + index) = *(queue + index - 1);
    }
    *(queue + 0) = last_element;
}

void rotate_left(vector<int>& queue, const int count) {
    const int first_element = queue[0];
    for (int index = 0; index < count; ++index) {
        queue[index] = queue[index + 1];
    }
    queue[count - 1] = first_element;
}

void rotate_right(vector<int>& queue, const int count) {
    const int last_element = queue[count-1];
    for (int index = count - 1; index >= 0; --index) {
        queue[index] = queue[index-1];
    }
    queue[0] = last_element;
}


void rotate_right2(vector<int>& queue, const int count) {
    const int last_element = queue[count-1];
    for (int index = count - 1; index >= 0; --index) {
        queue[index] = queue[index-1];
    }
    queue[0] = last_element;
}

void rotate_right(vector<int>& A, int k) {
    int i, j, n = A.size();
    k %= A.size();
    for (j = 0; j < k; ++j) {   
        int tmp = A[n-1];
        for (i = n-1; i > 0; --i) {
            A[i] = A[i-1];
        }
        A[0] = tmp;
    }
}

void shiftArrayLeft(vector<int>& theArray, int r)
{
    int size = theArray.size();
    std::reverse(theArray.begin()   , theArray.begin() + r   );
    std::reverse(theArray.begin()+ r, theArray.begin() + size);
    std::reverse(theArray.begin()   , theArray.begin() + size);
}

void test()
{
    int k = 5;
    vector<int> a = {2,0,1,3};
    vector<int> b = {2,0,1,3};
    show(a);
    cout << k << endl;
    shiftArrayRight(a, k);
    show(a);
    int j = k % a.size();
    cout << j << endl;
    shiftArrayRight(b, j);
    show(b);

}
#endif

void shiftArrayRight(vector<int>& theArray, int r)
{
    int size = theArray.size();
    std::reverse(theArray.begin()   , theArray.begin() + size);
    std::reverse(theArray.begin()   , theArray.begin() + r   );
    std::reverse(theArray.begin()+ r, theArray.begin() + size);
}

int main() {
    int n; // n element array
    int k; // times to shift 
    int q; // num queries
    int idx;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int shift = k % a.size();
    shiftArrayRight(a, shift);
    for (int i = 0; i < q; ++i) {
        cin >> idx;
        cout << a[idx] << endl;
    }
    return 0;
}

