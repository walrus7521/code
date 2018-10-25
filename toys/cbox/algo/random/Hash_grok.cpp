#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

template <typename K, typename V>
struct Entry {
    K key;
    V value;
};

// http://www.cplusplus.com/forum/general/40249/

template <typename K, typename V>
struct Hash {
    vector<vector<Entry<K,V>>> table;
    int buckets;
    int multiplier;
};

template <typename K, typename V>
using HashPtr = shared_ptr<Hash<K,V>>;

template <typename K, typename V>
void Hash_show(Hash<K,V> *hash);

template <typename K, typename V>
bool Hash_lookup(Hash<K,V> *hash, pair<K,V> p);

template <typename K, typename V>
HashPtr<K,V> Hash_create(int buckets, int multiplier)
{
    HashPtr<K,V> hash(new Hash<K,V>);
    hash->table.resize(buckets);
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    return hash;
}

int hasher(int key, int num_buckets)
{
    return key % num_buckets;
}

int hasher(string str, int num_buckets)
{
    char *ps = (char *) str.c_str();
    int c, hash_val = 5381;
    while ((c = *ps++) == true)
        hash_val = ((hash_val << 5) + hash_val) + c;
    return hash_val % num_buckets;
}

template <typename K, typename V>
void Hash_set(HashPtr<K,V> hash, pair<K,V> p)
{
    int h = 31; 
    K key = p.first;
    V val = p.second;
    if (!Hash_lookup(hash, p)) {
        h = hasher(key, hash->buckets);
        Entry<K,V> e = {.key = key, .value = val };
        hash->table[h].push_back(e);
    }
}

template <typename K, typename V>
bool Hash_lookup(HashPtr<K,V> hash, pair<K,V> p)
{
    K key = p.first;
    V val = p.second;
    int h = hasher(key, hash->buckets);
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
void Hash_show(HashPtr<K,V> hash)
{
    Hash<K,V> hd = *hash;
    cout << "show hash:" << endl;
    for (int i = 0; i < hash->buckets; ++i) {
        if (hash->table[i].size() > 0) {
            for (int j = 0; j < hash->table[i].size(); ++j) {
                Entry<K,V> e = hash->table[i][j];
                cout << e.key << ": " << e.value << endl;
            }
        }
    }
}

#define NUM_BUCKETS 1001
int main()
{
    HashPtr<string, int> hash = 
        Hash_create<string, int>(NUM_BUCKETS, 5331);
    Hash_set(hash, make_pair(string("bart"), 42));
    Hash_set(hash, make_pair(string("cindy"), 36));
    Hash_show(hash);
}

