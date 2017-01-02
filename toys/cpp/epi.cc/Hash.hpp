#ifndef _Hash_h_
#define _Hash_h_

#include "pch.hpp"

#define NUM_BUCKETS 1001
template <typename K, typename V>
struct Entry {
    K key;
    V value;
};

// http://www.cplusplus.com/forum/general/40249/

template <typename K, typename V>
struct Hash {
    //std::array<std::vector<std::pair<K,V>, 1>> *symtab;
    std::vector<Entry<K,V>> table[NUM_BUCKETS]; // an array of vectors<Entry>
};

template <typename K, typename V>
void Hash_show(Hash<K,V> *hash);

template <typename K, typename V>
Hash<K,V> *Hash_create(int buckets, int multiplier)
{
    Hash<K,V> *hash = new Hash<K,V>();
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    //hash->symtab = new std::vector<std::pair<K,V>>[buckets];
    return hash;
}

template <typename K, typename V>
void Hash_set(Hash<K,V> *hash, std::pair<K,V> p)
{
    int h = 31; 
    K key = p.first;
    V val = p.second;
    Entry<K,V> e = {.key = key, .value = val };
    hash->table[h].push_back(e);
}

template <typename K, typename V>
std::pair<K,V> Hash_lookup(Hash<K,V> *hash)
{
    static std::pair<K,V> invalid;
    return invalid;
}

template <typename K, typename V>
void Hash_show(Hash<K,V> *hash)
{
    Hash<K,V> hd = *hash;
    std::cout << "show hash:" << std::endl;
    for (int i = 0; i < NUM_BUCKETS; ++i) {
        if (hash->table[i].size() > 0) {
            for (int j = 0; j < hash->table[i].size(); ++j) {
                Entry<K,V> e = hash->table[i][j];
                std::cout << e.key << ": " << e.value << std::endl;
            }
        }
    }
}

#endif // _Hash_h_
