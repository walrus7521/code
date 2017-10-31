#include "pch.h"

using namespace std;

typedef enum { W, B } Color;
struct Coordinate {
    bool operator=(const Coordinate& that) const {
        return x == that.x && y == that.y;
    }
    int x, y;
};

template <typename T>
using Grid =  vector<vector<T>>;
template <typename T>
using UnweightedGraph =  map<T,set<T>>;
template <typename T>
using WeightedGraph = map<T,map<T,int>>;

template <typename T>
using QueueSet = queue<set<T>>;

template <typename T>
void showGrid(Grid<T> g)
{
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename T>
void showUnweightedGraph(UnweightedGraph<T> g)
{
    cout << "Unweighted Graph:" << endl;
    for (auto& v : g) {
        cout << v.first << ": ";
        for (auto& it : v.second) {
            cout << it << ", ";
        }
        cout << endl;
    }
}

template <typename T>
void showWeightedGraph(WeightedGraph<T> wg)
{
    cout << "Weighted Graph:" << endl;
    for(auto mit = wg.begin();mit!=wg.end(); ++mit) {
        cout << mit->first << ": ";
        for(auto eptr=mit->second.begin();eptr!=mit->second.end(); ++eptr) {
            cout << "{" << eptr->first << "," << eptr->second << "}, ";
        }
        cout << endl;
    }
}

template <typename T>
void Grid2Graph(Grid<T> grid, UnweightedGraph<int>& graph)
{
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == B) {
                graph[i].insert(j);
            }
        }
    }
}

template <typename T>
void bfs(UnweightedGraph<T>& g, T& s)
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

template <typename T>
void maze(UnweightedGraph<T>& g, const Coordinate& s, const Coordinate& e)
{
    cout << "maze s: (" << s.x << "," << s.y << ")" << endl;
    vector<Coordinate> path;
}

int main()
{
    UnweightedGraph<string> graph;
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
    showUnweightedGraph(graph);

    Grid<Color> grid;
    grid.resize(10);
    grid = { { B,W,W,W,W,W,B,B,W,W}, 
             { W,W,B,W,W,W,W,W,W,W }, 
             { B,W,B,W,W,B,B,W,B,B }, 
             { W,W,W,B,B,B,W,W,B,W }, 
             { W,B,B,W,W,W,W,W,W,W }, 
             { W,B,B,W,W,B,W,B,B,W }, 
             { W,W,W,W,B,W,W,W,W,W }, 
             { B,W,B,W,B,W,B,W,W,W }, 
             { B,W,B,B,W,W,W,B,B,B }, 
             { W,W,W,W,W,W,W,B,B,W } };

    showGrid(grid);
    UnweightedGraph<int> graph2;
    Grid2Graph(grid, graph2);
    showUnweightedGraph(graph2);
    int v = 3;
    Coordinate s = {2,3};
    Coordinate e = {8,8};
    maze(graph2, s, e);

    WeightedGraph<string> wGraph;
    wGraph["a"]["b"] = 4;
    wGraph["b"]["c"] = 1;
    wGraph["a"]["c"] = 2;
    showWeightedGraph(wGraph);

}

