#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <stdexcept>

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
    link_t(const T& data) : data(data), next(0) {}
    T data;
    std::shared_ptr<link_t<T>> next;
};

template <typename T>
struct list_iterator {
    using value_type = T;

    list_iterator(std::shared_ptr<link_t<T>> entry) : entry(entry) {}

    T& operator*() { return entry->data; }
    const T& operator*() const { return entry->data; }

    list_iterator<T> operator++() {
        entry = entry->next; return *this;
    }
    list_iterator<T> operator++(int i) {
        list_iterator<T> tmp(*this);
        entry = entry->next; 
        return tmp;
    }

    bool operator!=(const list_iterator<T>& other) const
    { return entry != other.entry; }

    std::shared_ptr<link_t<T>> entry;
};

template <typename T>
struct list_t {
    list_t() : first(0), last(nullptr) {}
    ~list_t() {
        while (first) {
            auto tmp = first->next;
            first = tmp;
        }
    }
    void append(const T& x)
    {
        auto tmp = std::make_shared<link_t<T>>(x);
        last = (first? last->next : first) = tmp; //std::make_shared<link_t<T>>(x);
    }    
    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(0); }
    std::shared_ptr<link_t<T>> first, last;
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

