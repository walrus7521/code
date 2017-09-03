#include "pch.h"

using namespace std;

template <typename T>
using Graph =  map<T,set<T>>;
template <typename T>
using QueueSet = queue<set<T>>;


template <typename T>
void bfs(Graph<T>& g, string& s)
{
    QueueSet<T> search_queue;
    search_queue.push(g[s]);
    set<T> searched;
    while (!search_queue.empty()) { 
        set<T> ss = search_queue.front(); search_queue.pop();
        for (auto it = ss.begin(); it != ss.end(); it++) {
            if (it->size()) {
                if (searched.insert(*it).second == true) {
                    cout << "pushing set: " << *it << endl; //", ";
                    search_queue.push(g[*it]);
                }
            }
        }
    }
}


int main()
{
    Graph<string> graph;
    graph["you"]    = {"alice", "bob", "claire"};
    graph["bob"]    = {"anuj", "peggy"};
    graph["alice"]  = {"peggy"};
    graph["claire"] = {"thom", "jonny"};
    graph["anuj"]   = {""};
    graph["peggy"]  = {""};
    graph["thom"]   = {""};
    graph["jonny"]  = {""};

    string target("you");
    bfs(graph, target); // # this one works

}


