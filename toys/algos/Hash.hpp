#include <iostream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class Hash {
public:
    Hash(int nB) : B(nB) {
        table = new list<pair<string, int>>[B];
    }
    virtual ~Hash(){}
    void insert(string k, int v) {
        int b = hash2(k);
        pair<string, int> p = std::make_pair(k, v);
        table[b].push_back(p);
    }
    bool lookup(string k, int v) {
        int b = hash2(k);
        list<pair<string, int>>::iterator j; // used for bucket list entries
        for(j = table[b].begin(); j != table[b].end(); ++j) {
            if (k == j->first) {
                return true;
            }
        }
        return false;
    }
    pair<string, int> fetch(string k, int v) {
        int b = hash2(k);
        list<pair<string, int>>::iterator j; // used for bucket list entries
        for(j = table[b].begin(); j != table[b].end(); ++j) {
            if (k == j->first) {
                return *j;
            }
        }
        return std::make_pair(string("err"), -1);
    }
    void show() {
        list<pair<string, int>>::iterator j; // used for bucket list entries
        for (int i = 0; i < B; ++i) {
            for(j = table[i].begin(); j != table[i].end(); ++j) {
               cout << j->first << " => " << j->second << endl;
            }
        }
    }
private:
    int hash(int v) {
        return v % B;
    }
    int hash2(string str)
    {
        unsigned int h = 0;
        string::iterator it;
        for ( it = str.begin(); it < str.end(); ++it) {
            h = (31 * h) + *it;
        }        
        return (h % B);
    }
    int B;     // No. of hash buckets
    list<pair<string, int>> *table; // Pointer to an array containing buckets of hash entries
        
};


