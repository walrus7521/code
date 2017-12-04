#include <iostream>
#include <vector>
#include <string>

// array
// vector<int> a;
// string

// list
template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};

// tree
template <typename T>
struct BinaryTreeNode {
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
};

// heap

// hash
// vector<vector<string>>
// cache
// unordered_map<int, int> cache;

