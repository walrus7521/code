#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Hash {
public:
    Hash(int nB) : B(nB) {
        table = new list<int>[B];
    }
    void addHash(int v) {
        int b = hash(v);
        table[b].push_back(v);
    }
    bool findHash(int v) {
        int b = hash(v);
        list<int>::iterator j; // used for bucket list entries
        for(j = table[b].begin(); j != table[b].end(); ++j) {
            if (v == *j) {
                return true;
            }
        }
        return false;
    }
    void show() {
        list<int>::iterator j; // used for bucket list entries
        for (int i = 0; i < B; ++i) {
            for(j = table[i].begin(); j != table[i].end(); ++j) {
               cout << *j << endl;
            }
        }
    }
private:
    int hash(int v) {
        return v % B;
    }
    int B;     // No. of hash buckets
    list<int> *table; // Pointer to an array containing buckets of hash entries
        
};


