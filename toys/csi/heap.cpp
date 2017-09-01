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
 
}
