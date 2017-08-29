#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <stack>
#include <array>
#include <map>
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

    priority_queue<string, vector<string>, function<bool(string, string)>>
        min_heap(
            [](const string& a, const string& b) { 
                //return a.size() >= b.size(); 
                return a >= b; 
                });
    min_heap.push("bbb");
    min_heap.push("aaa");
    min_heap.push("ccc");
    while (!min_heap.empty()) { cout << min_heap.top() << endl; min_heap.pop(); }

    priority_queue<string, vector<string>, function<bool(string, string)>>
        max_heap(
            [](const string& a, const string& b) { 
                //return a.size() < b.size(); 
                return a < b; 
                });
    max_heap.push("bbb");
    max_heap.push("aaa");
    max_heap.push("ccc");
    while (!max_heap.empty()) { cout << max_heap.top() << endl; max_heap.pop(); }
}

