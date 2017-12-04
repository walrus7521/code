#include "types.hpp"

using namespace std;

unique_ptr<Trie> new_trie() {
    unique_ptr<Trie> trie = make_unique<Trie>();
    for (int i = 0; i < TRIE_SIZE; i++) trie->m[i] = nullptr;
    return trie;
}

void insert(unique_ptr<Trie> root, char *key) {
    printf("insert: %s\n", key);
    int len = strlen(key);
    unique_ptr<Trie> t = root;
    for (int i = 0; i < len; i++) {
        int idx = key[i] - 'a';
        //if (t->m[idx] == nullptr) { t->m[idx] = new_trie<T>(); }
        //t = t->m[idx]; // advance to next trie
    }
    int idx = TERMINATOR; // terminate all strings here
    //t->m[idx] = new_trie<T>();
}

int main()
{
    unique_ptr<Trie> root = new_trie();
    char key[] = "bart";
    insert(root, key);
    
}

