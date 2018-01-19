#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <stack>
#include <array>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    list<int> li; // useful for finding elements
    li.push_front(1);
    li.push_back(2);
    li.push_front(3);
    li.push_back(4);
    while (!li.empty()) { cout << li.front() << endl; li.pop_front(); }

    stack<string> ss;
    ss.push("hello");
    ss.push("goodbye");
    while (!ss.empty()) { cout << ss.top() << endl; ss.pop(); }

    queue<int> qi;
    qi.push(42);
    qi.push(76);
    while (!qi.empty()) { cout << qi.front() << endl; qi.pop(); }

    map<string, int> msi = {{"bart",42},{"cindy",1},{"alusia",90}};
    for (auto& k : msi) { cout << k.first << " => " << k.second << endl; }    

    set<int> seti = {1,1,2,2,5,6};
    for (auto& s : seti) cout << s << endl;

    // easy max heap
    priority_queue<string, vector<string>, less<string>> pq_max;
    pq_max.push("bbb");
    pq_max.push("aaa");
    pq_max.push("ccc");
    while (!pq_max.empty()) { cout << pq_max.top() << endl; pq_max.pop(); }

    // easy min heap
    priority_queue<string, vector<string>, greater<string>> pq_min;
    pq_min.push("bbb");
    pq_min.push("aaa");
    pq_min.push("ccc");
    while (!pq_min.empty()) { cout << pq_min.top() << endl; pq_min.pop(); }

    priority_queue<string, vector<string>, function<bool(string, string)>>
        heap(
            [](const string& a, const string& b) { 
                //return a.size() >= b.size(); // size based
                return a >= b;  // min heap
                //return a < b;  // max heap
                });
    heap.push("bbb");
    heap.push("aaa");
    heap.push("ccc");
    while (!heap.empty()) { cout << heap.top() << endl; heap.pop(); }

    // graph
    unordered_map<string, unordered_set<string>> graph;
    graph["a"] = {"b","c"};
    graph["b"] = {"a","c"};

    map<string,map<string,int>> wg; //weighted_graph;
    wg["a"]["b"] = 4;
    wg["b"]["c"] = 1;
    wg["a"]["c"] = 2;

    cout << wg["a"]["b"] << endl;
    for(auto mit = wg.begin();mit!=wg.end(); ++mit) {
        for(auto eptr=mit->second.begin();eptr!=mit->second.end(); ++eptr) {
            cout << eptr->first << " " << eptr->second << endl;
        }
    }


    // 2d-matrix
    array<array<int, 2>, 4> aai = {{{0,1},{2,3},{4,5},{6,7}}};

    
}
