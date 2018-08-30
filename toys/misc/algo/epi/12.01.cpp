#include <iostream>
#include <vector>

using std::cin;     using std::cout;
using std::endl;    using std::vector;

int SearchFirst(const vector<int>& A, int k)
{
    int left = 0, right = A.size() - 1, result = -1;
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        cout << "A[mid] = " << A[mid] << endl;
        if (A[mid] > k) {
            right = mid - 1;
        } else 
        if (A[mid] == k) {
            // records solution and keep searching the left part.
            result = mid, right = mid - 1;
            cout << "found it .. " << k << endl;
        } else {
            left = mid + 1;
        }
    }
    return result;
}


int main()
{
    vector<int> vi = {0, 2, 4, 8, 8, 8, 9, 11, 13};
    int f = 8;
    int s = SearchFirst(vi, f);
    cout << "found " << f << " at " << s << " : " << vi[s] << endl;
    return 0;
}
