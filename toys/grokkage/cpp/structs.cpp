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


int main()
{
}
