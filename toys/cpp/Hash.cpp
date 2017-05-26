#include <string>
#include <vector>
#include <iostream>

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
    //array<vector<pair<K,V>, 1>> *symtab;
    vector<Entry<K,V>> table[NUM_BUCKETS]; // an array of vectors<Entry>
};

template <typename K, typename V>
void Hash_show(Hash<K,V> *hash);

template <typename K, typename V>
bool Hash_lookup(Hash<K,V> *hash, pair<K,V> p);

template <typename K, typename V>
Hash<K,V> *Hash_create(int buckets, int multiplier)
{
    Hash<K,V> *hash = new Hash<K,V>();
    hash->buckets = buckets;
    hash->multiplier = multiplier;
    //hash->symtab = new vector<pair<K,V>>[buckets];
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
        hash_val = ((hash_val << 5) + hash_val) + c; /* hash_val * 33 + c */
    return hash_val % NUM_BUCKETS;
}

template <typename K, typename V>
void Hash_set(Hash<K,V> *hash, pair<K,V> p)
{
    int h = 31; 
    K key = p.first;
    V val = p.second;
    if (!Hash_lookup(hash, p)) {
        //cout << "type1 K: " << is_integral<K>::value << " " << endl;
        //cout << "type1 V: " << is_integral<V>::value << " " << endl;
        //cout << "type2 K: " << typeid(key).name() << " " << endl;
        //cout << "type2 V: " << typeid(val).name() << " " << endl;
        //if (is_integral<K>::value) {
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
bool Hash_lookup(Hash<K,V> *hash, pair<K,V> p)
{
    //static pair<K,V> invalid;
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
    //return invalid;
}

template <typename K, typename V>
void Hash_show(Hash<K,V> *hash)
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
    Hash<string, int> hash;// = Hash_create<string, int>(13, 15);
    Hash_set(&hash, make_pair(string("bart"), 42));
    Hash_set(&hash, make_pair(string("cindy"), 36));
    Hash_show(&hash);

    Hash<int, string> hash2;
    Hash_set(&hash2, make_pair(44, string("bart")));
    Hash_set(&hash2, make_pair(37, string("cindy")));
    Hash_show(&hash2);
}

