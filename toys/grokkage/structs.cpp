#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <list>
#include <stack>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <functional>

using namespace std;

// linked lists
template <typename T>
struct List {
    T data;
    shared_ptr<List<T>> next;
};

template <typename T>
struct Tree {
    T data;
    unique_ptr<Tree<T>> left, right;
};

// graph
unordered_map<string, unordered_set<string>> graph;

int main()
{
    // array
    vector<int> vi = {1,2,3,4};
    
    // 2d-matrix
    array<array<int, 2>, 4> aai = {{{0,1},{2,3},{4,5},{6,7}}};

}

