#include <iostream>
#include <vector>
#include <string>
#include <memory>

// array
// vector<int> a;
// string

// list
template <typename T>
struct ListNode {
    T data;
    //std::shared_ptr<ListNode<T>> next;
    ListNode<T> *next;
};

// tree
template <typename T>
struct BinaryTreeNode {
    T data;
    std::unique_ptr<BinaryTreeNode<T>> left, right;
};

// trie
#define TRIE_SIZE  (27)
#define TERMINATOR (26)
struct Trie {
    std::unique_ptr<Trie> m[TRIE_SIZE];
};

// heap -> use array

// hash
// vector<vector<string>>
// cache
// unordered_map<int, int> cache;

