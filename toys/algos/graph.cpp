#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void graph_show(vector<vector<int>> p, string name) {
    int i, j,n = p.size();
    cout << "graph: " << name << endl;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            cout << p[i][j] << '\t';
        cout << endl;
    }
    cout << endl;
}

// is "v" reachable
int reach[20];
void dfs_r(int v, vector<vector<int>> a) {
    int i, n = a.size();
    reach[v] = 1;
    cout << "dfs: " << v << endl;
    for (i = 0; i < n; i++) {
        if (a[v][i] && !reach[i]) { 
            dfs_r(i, a);
        }
    }
}

void test_dfs()
{
    int n = 6;
    vector<vector<int>> p = { { 0, 0, 1, 1, 1, 0 }, 
                    { 0, 0, 0, 0, 1, 1 }, 
                    { 1, 0, 0, 1, 0, 1 }, 
                    { 1, 0, 1, 0, 0, 0 }, 
                    { 1, 1, 0, 0, 0, 1 }, 
                    { 0, 1, 1, 0, 1, 0 } };

    graph_show(p,"dfs");
    dfs_r(0, p);
    int i, count;
    for (i = 0; i < n; i++) { 
        if(reach[i]) count++; 
    }
    cout << "count: " << count << ", n: " << n << endl;
    if(count == n)
        cout << "Graph is connected" << endl; 
    else
        cout << "Graph is not connected" << endl;
}

int main()
{
    test_dfs();
    return 0;
}

