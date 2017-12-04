#include "types.hpp"

using namespace std;

unique_ptr<Trie> new_trie() {
    unique_ptr<Trie> trie = make_unique<Trie>();
    for (int i = 0; i < TRIE_SIZE; i++) trie->m[i] = nullptr;
    return trie;
}

void insert(unique_ptr<Trie> &root, string &key) {
    printf("insert: %s\n", key.c_str());
    int len = key.size();
    Trie *t = root.get();
    for (int i = 0; i < len; i++) {
        int idx = key[i] - 'a';
        if (t->m[idx] == nullptr) { t->m[idx] = new_trie(); }
        t = t->m[idx].get(); // advance to next trie
    }
    int idx = TERMINATOR; // terminate all strings here
    t->m[idx] = new_trie();
}

bool find(const unique_ptr<Trie> &root, string &key) {
    printf("find: %s => ", key.c_str());
    int len = key.size();
    Trie *t = root.get();
    for (int i = 0; i < len; i++) {
        int idx = key[i] - 'a';
        //printf("check %c => %d\n", key[i], idx);
        if (t->m[idx] == nullptr) {
            printf("not found\n");
            return false;
        }
        t = t->m[idx].get();
    }
    int idx = TERMINATOR; //'\0' - 'a';
    if (t->m[idx] == nullptr) { // was key terminated?
        printf("not found\n");
        return false;
    } else {
        printf("found\n");
        return true;
    }
}

int main()
{
    unique_ptr<Trie> root = new_trie();
    string key;
    key = "bart"; insert(root, key);
    key = "cindy"; insert(root, key);
    key = "douche"; find(root, key);
    key = "bar"; find(root, key);
}

