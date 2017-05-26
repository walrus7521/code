#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

#define NUM_BUCKETS 1001
template <typename K, typename V>
struct Entry {
    K key;
    V value;
};

// http://www.cplusplus.com/forum/general/40249/

template <typename K, typename V>
struct Hash {
    vector<Entry<K,V>> table[NUM_BUCKETS];
    int buckets;
    int multiplier;
};

template <typename K, typename V>
void Hash_show(Hash<K,V> *hash);

template <typename K, typename V>
bool Hash_lookup(Hash<K,V> *hash, pair<K,V> p);

template <typename K, typename V>
shared_ptr<Hash<K,V>> Hash_create(int buckets, int multiplier)
{
    shared_ptr<Hash<K,V>> hash(new Hash<K,V>);
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    return hash;
}

int hasher(int key)
{
    return key % NUM_BUCKETS;
}

int hasher(string str)
{
    char *ps = (char *) str.c_str();
    int c, hash_val = 5381;
    while ((c = *ps++) == true)
        hash_val = ((hash_val << 5) + hash_val) + c;
    return hash_val % NUM_BUCKETS;
}

template <typename K, typename V>
void Hash_set(shared_ptr<Hash<K,V>> hash, pair<K,V> p)
{
    int h = 31; 
    K key = p.first;
    V val = p.second;
    if (!Hash_lookup(hash, p)) {
        h = hasher(key);
        Entry<K,V> e = {.key = key, .value = val };
        hash->table[h].push_back(e);
    }
}

template <typename K, typename V>
bool Hash_lookup(shared_ptr<Hash<K,V>> hash, pair<K,V> p)
{
    K key = p.first;
    V val = p.second;
    int h = hasher(key);
    vector<Entry<K,V>> t = hash->table[h];
    for (int i = 0; i < t.size(); ++i) {
        Entry<K,V> e = t[i];
        if (e.value == val) {
            cout << "found: " << val << endl;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
void Hash_show(shared_ptr<Hash<K,V>> hash)
{
    Hash<K,V> hd = *hash;
    cout << "show hash:" << endl;
    for (int i = 0; i < NUM_BUCKETS; ++i) {
        if (hash->table[i].size() > 0) {
            for (int j = 0; j < hash->table[i].size(); ++j) {
                Entry<K,V> e = hash->table[i][j];
                cout << e.key << ": " << e.value << endl;
            }
        }
    }
}

int main()
{
    shared_ptr<Hash<string, int>> hash = 
        Hash_create<string, int>(NUM_BUCKETS, 5331);
    Hash_set(hash, make_pair(string("bart"), 42));
    Hash_set(hash, make_pair(string("cindy"), 36));
    Hash_show(hash);
}

