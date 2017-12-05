#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <queue>

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
struct tree_t {
    T data;
    std::shared_ptr<tree_t<T>> left, right;
};

// trie
#define TRIE_SIZE  (27)
#define TERMINATOR (26)
struct trie_t {
    std::shared_ptr<trie_t> m[TRIE_SIZE];
};

// heap -> use array

/* graph
 */
#define MAX_VERT (16)
template <typename T>
struct graph_t {
    graph_t<T>(int verts) : n_vert(verts) {
        m.resize(MAX_VERT);
        parent.resize(MAX_VERT);
        visited.resize(MAX_VERT);
    }
    int n_vert;
    std::vector<std::vector<T>> m;
    std::vector<T> parent;
    std::vector<T> visited;
};

// hash
// vector<vector<string>>
// cache
// unordered_map<int, int> cache;

