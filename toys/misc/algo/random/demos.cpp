#include <iostream>
#include <map>
#include <string>
#include <array>
#include <list>

using namespace std;

void demo_list()
{
    list<string> p;
    p.push_back("claire");
    p.push_back("mac");
    p.push_back("chad");
    p.push_back("grant");
    p.push_back("cindy");
    p.push_back("bart");

    for (const auto& s : p) {
        cout << s << endl;
    }
}

void demo_array()
{
    array<int, 3> a = {1,2,3};

    for (const auto& i : a) {
        cout << i << endl;
    }
}

void demo_map()
{
    map<string,map<string,int>> graph;

    graph["start"]["a"]=6;
    graph["start"]["b"]=2;
    graph["a"]["fin"]=1;
    graph["b"]["a"]=3;
    graph["b"]["fin"]=5;
    graph["fin"][""]=-1;

    for (const auto& m : graph) {
        cout << m.first << '\n' ;
        for (const auto& n : m.second) {
            cout << "     " << n.first << '{' << n.second << "}\n" ;    
        }
    }
}

int main ()
{
    demo_map();
    demo_array();
    demo_list();
    return 0;
}
