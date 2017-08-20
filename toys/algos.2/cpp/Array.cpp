// sorting/strings
//
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void show(vector<T>& v)
{
    for (auto e : v) cout << e << ",";
    cout << endl;
}

template <typename T>
void merge(vector<T>& v, int first, int mid, int last)
{
    vector<T> tmp;
    int idxA = first;
    int idxB = mid;

    while (idxA < mid && idxB < last) {
        if (v[idxA] < v[idxB]) tmp.push_back(v[idxA++]);
        else                   tmp.push_back(v[idxB++]);
    }
    while (idxA < mid) tmp.push_back(v[idxA++]);
    while (idxB < last) tmp.push_back(v[idxB++]);
    // copy tmp back to v
    idxA = first; // starting at first
    int idxV = 0;
    while (idxV < tmp.size()) v[idxA++] = tmp[idxV++];
}

// merge sort
template <typename T>
void split(vector<T>& v, int first, int last)
{
    if (first + 1 < last) {
        int mid = (last + first) / 2;
        split(v, first, mid);
        split(v, mid, last);
        merge(v, first, mid, last);
    }
}

void do_mergesort()
{
    vector<int> v = {25,10,7,19,3,48,12,17,56,30,21};
    vector<string> s = {"Dallas","Akron","Wausau","Phoenix",
                        "Fairbanks","Miami"};
    split(v,0,v.size());
    show(v);
    split(s,0,s.size());
    show(s);
}

void do_quicksort()
{
}

int main()
{
    do_mergesort();
    do_quicksort();
}

