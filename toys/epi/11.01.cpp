#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::priority_queue;

struct Compare {
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.first > rhs.first;
    }
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> min_heap;
    // for each array in sorted_arrays, keeps index of next unprocessed element
    vector<int> heads(sorted_arrays.size(), 0);

    // puts each sorted_array's first element in min_heap
    for (int i = 0; i < sorted_arrays.size(); ++i) {
        if (!sorted_arrays[i].empty()) {
            min_heap.emplace(sorted_arrays[i][0], i);
            heads[i] = 1;
            cout << "heads[" << i << "] = " << heads[i] << " : ";
            cout << "first " << sorted_arrays[i][0] << " second " << i << endl;
        }
    }

    vector<int> result;
    while (!min_heap.empty()) {
        cout << "smallest_entry = " << min_heap.top().first << endl;
        cout << "smallest_array_number = " << min_heap.top().second << endl;
        int smallest_entry = min_heap.top().first;
        int smallest_array_number = min_heap.top().second;
        auto& smallest_array = sorted_arrays[smallest_array_number];
        auto& smallest_array_head = heads[smallest_array_number];
        result.emplace_back(smallest_entry);
        if (smallest_array_head < smallest_array.size()) {
            // add next entry of smallest_array into min_heap
            min_heap.emplace(smallest_array[smallest_array_head], min_heap.top().second);
            ++smallest_array_head;
        }
        min_heap.pop();
    }

    return result;
}

int main()
{
    vector<vector<int>> vvi;
    vector<int> vi1;
    vector<int> vi2;
    vector<int> vi3;
    vector<int> vi4;
    vector<int> rvi;
    
    for (int i = 0; i < 12; i++) {
        vi1.push_back(i);
    }
    for (int i = 0; i < 12; i++) {
        vi2.push_back(20+i);
    }
    for (int i = 0; i < 12; i++) {
        vi3.push_back(40+i);
    }
    for (int i = 0; i < 12; i++) {
        vi4.push_back(60+i);
    }
    vvi.push_back(vi1);
    vvi.push_back(vi2);
    vvi.push_back(vi3);
    vvi.push_back(vi4);
    
    rvi = MergeSortedArrays(vvi);

    for (int i = 0; i < rvi.size(); ++i) {
        //cout << "[" << i << "] = " << rvi[i] << endl;
    }
    return 0;
}
