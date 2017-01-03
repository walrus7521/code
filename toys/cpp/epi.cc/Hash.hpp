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
bool Hash_lookup(Hash<K,V> *hash, std::pair<K,V> p);

template <typename K, typename V>
Hash<K,V> *Hash_create(int buckets, int multiplier)
{
    Hash<K,V> *hash = new Hash<K,V>();
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    //hash->symtab = new std::vector<std::pair<K,V>>[buckets];
    return hash;
}

int hasher(int key)
{
    return key % NUM_BUCKETS;
}

int hasher(std::string str)
{
    char *ps = (char *) str.c_str();
    int c, hash_val = 5381;
    while ((c = *ps++) == true)
        hash_val = ((hash_val << 5) + hash_val) + c; /* hash_val * 33 + c */
    return hash_val % NUM_BUCKETS;
}

template <typename K, typename V>
void Hash_set(Hash<K,V> *hash, std::pair<K,V> p)
{
    int h = 31; 
    K key = p.first;
    V val = p.second;
    if (!Hash_lookup(hash, p)) {
        //std::cout << "type1 K: " << std::is_integral<K>::value << " " << std::endl;
        //std::cout << "type1 V: " << std::is_integral<V>::value << " " << std::endl;
        //std::cout << "type2 K: " << typeid(key).name() << " " << std::endl;
        //std::cout << "type2 V: " << typeid(val).name() << " " << std::endl;
        //if (std::is_integral<K>::value) {
        //    h = hasher(key);
        //} else {
        //    h = hasher(key);
        //}
        h = hasher(key);
        Entry<K,V> e = {.key = key, .value = val };
        hash->table[h].push_back(e);
    }
}

template <typename K, typename V>
bool Hash_lookup(Hash<K,V> *hash, std::pair<K,V> p)
{
    //static std::pair<K,V> invalid;
    K key = p.first;
    V val = p.second;
    int h = hasher(key);
    std::vector<Entry<K,V>> t = hash->table[h];
    for (int i = 0; i < t.size(); ++i) {
        Entry<K,V> e = t[i];
        if (e.value == val) {
            std::cout << "found: " << val << std::endl;
            return true;
        }
    }
    return false;
    //return invalid;
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
