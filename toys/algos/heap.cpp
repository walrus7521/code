#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <functional>

using namespace std;


struct IteratorCurrentAndEnd {
    bool operator>(const IteratorCurrentAndEnd& that) const {
        return *current > *that.current;
    }

    vector<int>::const_iterator current;
    vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>, 
        greater<>> min_heap;

    for (const vector<int>& sorted_array : sorted_arrays) {
        if (!sorted_array.empty()) {
            min_heap.emplace(
                IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()});
        }
    }

    vector<int> result;
    while (!min_heap.empty()) {
        auto smallest_array = min_heap.top();
        min_heap.pop();
        if (smallest_array.current != smallest_array.end) {
            result.emplace_back(*smallest_array.current);
            min_heap.emplace(IteratorCurrentAndEnd{next(smallest_array.current),
                    smallest_array.end});
        }
    }
    return result;
}

vector<int> SortKIncreasingDecreasingArray(const vector<int>& A)
{
    vector<vector<int>> sorted_subarrays;
    typedef enum { INCREASING, DECREASING } SubarrayType;
    SubarrayType subarray_type = INCREASING;
    int start_index = 0;
    for (int i = 0; i <= A.size(); ++i) {
        if (i == A.size() || // A is ended
            (A[i-1] <  A[i] && subarray_type == DECREASING) ||
            (A[i-1] >= A[i] && subarray_type == INCREASING)) {
            if (subarray_type == INCREASING) {
                sorted_subarrays.emplace_back(A.cbegin()+start_index, A.cbegin()+i);
            } else {
                sorted_subarrays.emplace_back(A.crbegin()+A.size()-i, 
                                              A.crbegin()+A.size() - start_index);
            }
            start_index = i;
            subarray_type = (subarray_type == INCREASING ? DECREASING : INCREASING);
        }
    }
    return MergeSortedArrays(sorted_subarrays);
}

int main()
{
    vector<int> a1 = {6,8,9,10,13};
    vector<int> a2 = {1,2,3,42,57};
    vector<int> a3 = {11,12,33,44,75};
    vector<int> a4 = {21,22,23,24,25};
    vector<int> a5 = {13,23,33,43,53};
    vector<vector<int>> vvi = {a1, a2, a3, a4, a5};

    vector<int> vi = MergeSortedArrays(vvi);

    //for (auto& i : vi) {
    //    cout << i << endl;
    //}

    //IteratorCurrentAndEnd ica{b1.cbegin(), b1.cend()};
    //for (auto& ic = ica.current; ic < ica.end; ic++) {
    //    cout << *ic << endl;
    //}

    priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>, 
        greater<>> min_heap;

    min_heap.emplace(IteratorCurrentAndEnd{a3.cbegin(), a3.cend()});
    min_heap.emplace(IteratorCurrentAndEnd{a2.cbegin(), a2.cend()});
    min_heap.emplace(IteratorCurrentAndEnd{a1.cbegin(), a1.cend()});

    while (!min_heap.empty()) {
        IteratorCurrentAndEnd arr = min_heap.top();
        min_heap.pop();
        for (auto& ic = arr.current; ic < arr.end; ++ic) {
            cout << *ic << endl;
        }
    }

    cout << "K increasing-decreasing array" << endl;
    vector<int> b1 = {57,131,493,294,221,339,418,452,442,190};
    vector<int> v2 = SortKIncreasingDecreasingArray(b1);
    for (auto& i : v2) {
        cout << i << endl;
    }
 
}


