#include <iostream>
#include <array>
#include <bitset>
#include <utility> // pair and tuple
#include <string>
#include <functional> // bind & placeholders

using namespace std;
using namespace placeholders;

void f(int *p, int sz) {
    int i;
    for (i = 0; i < sz; i++) {
        cout << "a[" << i << "]=" << p[i] << endl;
    }
}

class Shape {
public:
    void draw(string s) { cout << "draw: " << s << endl; }
};

int cube(int x) { return (x*x*x); }
void who(int a, string b) { cout << b << " is " << a << endl; }
void utils() {
    array<int,3> a = {1,2,3}; // stack allocated
    f(&a[0],3);
    f(a.data(), a.size());

    bitset<12> bits1{"100100111100"};
    bitset<12> bits2{0x93C};

    cout << "bits1: " << bits1 << ", bits2: " << bits2 << endl;
    cout << "bits1: " << bits1.to_string() << ", bits2: " << bits2.to_ullong() << endl;

    pair<string, int> pair1 = make_pair<string, int>("cat", 42);
    pair<string, int> pair2 = make_pair<string, int>("dog", 17);
    pair<string, int> pair3 = make_pair<string, int>("cat", 42);
    if (pair1 == pair3) {
        cout << "pairs are equal" << endl;
    } else {
        cout << "pairs are unequal" << endl;
    }
    cout << "animal: " << pair1.first << ", age: " << pair1.second << endl;

    auto t = make_tuple(string{"bart"}, string{"douche"}, 59);
    cout << "tuple: " << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << endl;

    // bind
    auto cube2 = bind(cube, 2);
    cout << "cube2: " << cube2() << endl;

    auto whod = bind(who, 42, "dad");
    whod();
    auto whom = bind(who, _1, "mom");
    whom(17);

    // mem_fn -- used to create functions to member functions
    Shape s;
    s.draw("douche");
    auto draw = mem_fn(&Shape::draw);
    draw(&s, "bag");
    
    // function -- bind without auto
    function<int(int)> cb{cube};
    cout << "cb: " << cb(3) << endl;
    function<void(int,string)> w{who};
    w(27, "chad");


}

int main()
{
    utils();
}
