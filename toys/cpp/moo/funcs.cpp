#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;

void print(string s)
{
    cout << s << ' ';
}

struct Log
{
    Log(): msg("") { }
    void operator()(string s) { cout << s << ' '; }
    string msg;
};

// function table
map<string, int(*)(int,int)> binops;
int addx(int i, int j) { return i + j; }
int subx(int i, int j) { return i - j; }
int mulx(int i, int j) { return i * j; }
int divx(int i, int j) { return i / j; }
auto modx = [](int i, int j) { return i % j; }; // lambda

// or
function<int(int,int)> f1 = addx;
function<int(int,int)> f2 = subx;
function<int(int,int)> f3 = mulx;
function<int(int,int)> f4 = divx;
function<int(int,int)> f5 = modx;
// create a function table using the function<> template
map<string, function<int(int,int)>> binops2 = {
    {"+", f1},
    {"-", f2},
    {"*", f3},
    {"/", f4},
    {"%", f5},
};

//template<typename T, typename U, typename V> using ifun = int(int, int);
template<typename T, typename U, typename V> using ifun = T(U, V);
function<ifun<int, int, int>> if1 = addx;
function<ifun<int, int, int>> if2 = subx;
function<ifun<int, int, int>> if3 = mulx;
function<ifun<int, int, int>> if4 = divx;
function<ifun<int, int, int>> if5 = modx;
// create a function table using the function<> template
map<string, function<int(int,int)>> binops3 = {
    {"+", if1},
    {"-", if2},
    {"*", if3},
    {"/", if4},
    {"%", if5},
};

using ifunx = ifun<int, int, int>;
function<ifunx> ifx1 = addx;
function<ifunx> ifx2 = subx;
function<ifunx> ifx3 = mulx;
function<ifunx> ifx4 = divx;
function<ifunx> ifx5 = modx;
// create a function table using the function<> template
map<string, function<ifunx>> binops4 = {
    {"+", ifx1},
    {"-", ifx2},
    {"*", ifx3},
    {"/", ifx4},
    {"%", ifx5},
};

int xz(string s, double d) { return 42; }
int yz(string s, double d) { return 7; }
using ifunz = ifun<int, string, double>;
function<ifunz> ifz1 = xz;
function<ifunz> ifz2 = yz;
map<string, function<ifunz>> ops5 = {
    {"+", ifz1},
    {"-", ifz2},
};


int main()
{
    plus<int> intAdd;
    negate<int> intNeg;
    int sum = intAdd(40, 2);
    cout << "sum: " << sum << endl;
    sum = intAdd(10, intNeg(10));
    cout << "sum2: " << sum << endl;

    vector<string> vs = { "cindy", "mac", "claire" };
    cout << endl;
    for_each(vs.begin(), vs.end(), print);
    cout << endl;

    // use binops
    cout << "---" << endl; 
    binops.insert({"+", addx});
    binops.insert({"-", subx});
    binops.insert({"*", mulx});
    binops.insert({"/", divx});
    binops.insert({"%", modx});
    cout << "-binops-" << endl; 
    cout << binops["+"](10,5) << endl;
    cout << binops["-"](10,5) << endl;
    cout << binops["*"](10,5) << endl;
    cout << binops["/"](10,5) << endl;
    cout << binops["%"](10,5) << endl;
    cout << "-f-" << endl; 
    cout << f1(4,2) << endl;
    cout << f2(4,2) << endl;
    cout << f3(4,2) << endl;
    cout << f4(4,2) << endl;
    cout << f5(4,2) << endl;
    cout << "-binops2-" << endl; 
    cout << binops2["+"](10,5) << endl;
    cout << binops2["-"](10,5) << endl;
    cout << binops2["*"](10,5) << endl;
    cout << binops2["/"](10,5) << endl;
    cout << binops2["%"](10,5) << endl;
    cout << "-binops3-" << endl; 
    cout << binops3["+"](10,5) << endl;
    cout << binops3["-"](10,5) << endl;
    cout << binops3["*"](10,5) << endl;
    cout << binops3["/"](10,5) << endl;
    cout << binops3["%"](10,5) << endl;
    
    cout << "-binops4-" << endl; 
    cout << binops4["+"](10,5) << endl;
    cout << binops4["-"](10,5) << endl;
    cout << binops4["*"](10,5) << endl;
    cout << binops4["/"](10,5) << endl;
    cout << binops4["%"](10,5) << endl;
    
    cout << "-ops5-" << endl; 
    cout << ops5["+"]("10",5.0) << endl;
    cout << ops5["-"]("11",6.0) << endl;

}

