/* 
 *  compute the intersection of 2 sorted arrays
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::cout;
using std::endl;
using std::unordered_map;

/* brute force
*/
vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
    vector<int> intersect;
    for (int i = 0; i < A.size(); ++i) {
        if (i == 0 || A[i] != A[i-1]) {
            for (int j = 0; j < B.size(); ++j) {
                if (A[i] == B[j]) {
                    intersect.emplace_back(A[i]);
                    break;
                }
            }
        }
    }
    return intersect;
}

vector<int> IntersectTwoSortedArrays2(const vector<int>& A,
                                     const vector<int>& B) {
    vector<int> intersect;
    for (int i = 0; i < A.size(); ++i) {
        if ((i == 0 || A[i] != A[i-1]) &&
            binary_search(B.cbegin(), B.cend(), A[i])) {
                intersect.emplace_back(A[i]);
        }
    }
    return intersect;
}

vector<int> IntersectTwoSortedArrays3(const vector<int>& A,
                                     const vector<int>& B) {
    vector<int> intersect;
    int i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
        if (A[i] == B[j] && (i == 0 || A[i] != A[i-1])) {
            intersect.emplace_back(A[i]);
            ++i, ++j;
        } else
        if (A[i] < B[j]) {
            ++i;
        } else { // A[i] > B[j]
            ++j;
        }
    }
    return intersect;
}

/* sweet!! use a hash
 */
vector<int> IntersectTwoSortedArrays4(const vector<int>& A,
                                     const vector<int>& B) {
    vector<int> intersect;
    unordered_map<int, int> hash;
    for (int i = 0; i < A.size(); ++i) {
        ++hash[A[i]];
    }
    for (int i = 0; i < B.size(); ++i) {
        if (hash[B[i]] > 0) {
            intersect.emplace_back(B[i]);
        }
    }
    return intersect;
}

/* sweet!! remember the last j and matched, and since
 * the arrays are sorted, no need to restart the j loop
 * at zero.
 */
vector<int> IntersectTwoSortedArrays5(const vector<int>& A,
                                     const vector<int>& B) {
    vector<int> intersect;
    int start_j = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (i == 0 || A[i] != A[i-1]) {
            for (int j = start_j; j < B.size(); ++j) {
                if (A[i] == B[j]) {
                    intersect.emplace_back(A[i]);
                    start_j = j;
                    break;
                }
            }
        }
    }
    return intersect;
}

int main()
{
    vector<int> v1 = {0, 2, 4, 8, 9, 11, 14};
    vector<int> v2 = {1, 3, 5, 9, 11, 13};
    vector<int> v3 = IntersectTwoSortedArrays5(v1, v2);
    for (vector<int>::const_iterator vi = v3.begin();
            vi != v3.end(); ++vi) {
        cout << *vi << endl;
    }
    return 0;
}
