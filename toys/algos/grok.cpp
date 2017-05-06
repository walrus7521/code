// tour code
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class vbase {
public:
    vbase(){cout << "ctor: vbase" << endl;}
    ~vbase(){cout << "dtor: vbase" << endl;}
    virtual void f() = 0;
private:
};

class derived : public vbase {
public:
    derived(){cout << "ctor: derived" << endl;
              /*concordance = new map<string, set<int>>();*/}
    ~derived(){cout << "dtor: derived" << endl;}
    virtual void f() {}
    void add(string s, int a) { concordance[s].insert(a); }
    void show() {
        map<string, set<int> >::const_iterator iter =
            concordance.begin();
        while (iter != concordance.end()) {
            cout << (*iter).first << endl;
            set<int>::const_iterator siter = (*iter).second.begin();
            while (siter != (*iter).second.end()) {
                cout << " : " << (*siter) << endl;
                siter++;
            }
            iter++;
        }        
    }
private:
    map<string, set<int>> concordance;
};


void classes()
{
    derived d;
    d.add("newcastle",98057);
    d.add("renton",98054);
    d.add("renton",98055);
    d.add("bellevue",98035);
    d.add("issaquah",98027);
    d.show();
}

int main()
{
    classes();
    //test();
    return 0;
}

