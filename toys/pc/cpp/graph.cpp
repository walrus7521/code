

/*
 * C++ Program to Check whether Undirected Graph is Connected using BFS
 *  http://www.sanfoundry.com/cpp-programming-examples-graph-problems-algorithms/
 */
#include <iostream>
#include <list>
#include <queue>
#include <cstdio>
using namespace std;
/*
 * Class Declaration
 */
class Graph
{
    private:
        int V;
        list<int> *adj;
    public:
        Graph(int V)
        {
            this->V = V;
            adj = new list<int>[V];
        }
        void addEdge(int v, int w);
        void BFS(int s, bool visited[]);
        Graph getTranspose();
        bool isConnected();
        void show();
};
 
void Graph::show()
{
    int s;
    list<int>::iterator i;
    printf("printing graph...\n");
    for (s = 0; s < V; s++) {
        printf("%02d: ", s);
        for(i = adj[s].begin(); i != adj[s].end(); ++i) {
            printf(" (%02d), ", *i);
        }
        cout << endl;
    }
#if 0

    list<int> q;
    list<int>::iterator i;
    visited[s] = true;
    q.push_back(s);
    while (!q.empty())
    {
        s = q.front();
        q.pop_front();
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                q.push_back(*i);
                cout << "-> " << *i << endl;
            }
        }
    }
#endif
}


/*
 * Add Edge to connect v and w
 */
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
 
/*
 *  A recursive function to print BFS starting from s
 */
void Graph::BFS(int s, bool visited[])
{
    list<int> q;
    list<int>::iterator i;
    visited[s] = true;
    q.push_back(s);
    while (!q.empty())
    {
        s = q.front();
        q.pop_front();
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                q.push_back(*i);
                cout << "-> " << *i << endl;
            }
        }
    }
}
/*
 * Function that returns reverse (or transpose) of this graph
 */
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
/*
 * Check if Graph is Connected
 */
bool Graph::isConnected()
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    BFS(0, visited);
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            return false;
    Graph gr = getTranspose();
    for(int i = 0; i < V; i++)
        visited[i] = false;
    gr.BFS(0, visited);
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            return false;
    return true;
}

void test()
{
/*
 *  6 5
 *  ...*.
 *  ...**
 *  .*...
 *  .....
 *  .....
 *  .....
 *  0 0

 01 02 03 04 05
 06 07 08 09 10
 11 12 13 14 15
 16 17 18 19 20
 21 22 23 24 25
 26 27 28 29 30

 */
#define MAX_ROW 6
#define MAX_COL 5
    int row, col, vertices = (MAX_ROW+2)*(MAX_COL+2);
    Graph g(vertices);
    for (row = 1; row <= MAX_ROW; row++) {
        for (col = 1; col <= MAX_COL; col++) {
            g.addEdge(row-1, col-1);
            g.addEdge(row-1, col);
            g.addEdge(row-1, col+1);
            g.addEdge(row,   col-1);
            g.addEdge(row+1, col+1);
            g.addEdge(row+1, col-1);
            g.addEdge(row,   col+1);
            g.addEdge(row+1, col);
        }
    }
    g.show();
    //bool visited[vertices];
    //g.BFS(7, visited);
}

void test1()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    if (g.isConnected())
        cout<<"The Graph is Connected"<<endl;
    else
        cout<<"The Graph is not Connected"<<endl;
}

void test2()
{
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 0);
    g1.addEdge(2, 4);
    g1.addEdge(4, 2);
    if (g1.isConnected())
        cout<<"The Graph is Connected"<<endl;
    else
        cout<<"The Graph is not Connected"<<endl;
}

/*
 * Main Contains Menu
 */
int main()
{ 
    //test1();
    //test2();
    test();
    return 0;
}

