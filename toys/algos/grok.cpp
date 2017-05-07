// tour code

/*
    key words
        auto
        range for: for (auto x : v) ... for (auto& x : v) ...
        shared_ptr => make_shared
        unique_ptr => make_unique, unique_copy
        lambda
        std::function
        friend
        template
        thread, mutex, async, condition_variable, promise, future, join
        constructors: default, move, move assn, copy, copy assn
        destructor
        std::move
        constexpr
        explicit
        delete
        operator
        overload
        class: concrete, abstract, virtual
        cast: dynamic_cast, static_cast








*/


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

