#include <iostream>
#include <vector>
#include <string>
#include <memory>

#define exchg(X, Y) { \
    (X) = (X) ^ (Y);  \
    (Y) = (Y) ^ (X);  \
    (X) = (X) ^ (Y); }


// array
// vector<int> a;
// string

// list
template <typename T>
struct link_t {
    T data;
    std::shared_ptr<link_t<T>> next;
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

