#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct vertex{
    typedef pair<int, vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    vertex(string s) { name=s; }
    int in_degree;
    int out_degree;
    bool visited;
};

typedef map<string, vertex *> vmap;
class graph
{
public:
    vmap work;
    void addvertex(const string&);
    void addedge(const string& from, const string& to, double cost);
    bool is_connected(const string& from, const string& to);
    int num_hops(const string& from, const string& to);
    void prep_search();
    void show();
};

void graph::addvertex(const string &name)
{
    vmap::iterator itr=work.begin();
    itr = work.find(name);
    if (itr == work.end()) {
        vertex *v;
        v= new vertex(name);
        work[name]=v;
        return;
    }
    cout<<"\nVertex already exists!";
}

void graph::addedge(const string& from, const string& to, double cost)
{
    vertex *f = (work.find(from)->second);
    vertex *t = (work.find(to)->second);
    pair<int, vertex *> edge = make_pair(cost,t);
    f->adj.push_back(edge);
    f->out_degree++;
    t->in_degree++;
}

bool graph::is_connected(const string& from, const string& to)
{
    bool found = false;
    vertex *f = (work.find(from)->second);
    for (vector<pair<int, vertex *> >::const_iterator itr = f->adj.begin(); itr != f->adj.end(); ++itr) {
        if (to == itr->second->name) {
            found = true;
        }
    }
    return found;
}

void graph::prep_search()
{
    vmap::iterator itr;
    for (itr = work.begin(); itr != work.end(); ++itr) {
        itr->second->visited = false;
    }
}

int graph::num_hops(const string& from, const string& to)
{
    // do bfs
    int hops = 0;
    prep_search(); // need set visited boolean to false

    queue<vertex *> bfsq;
    vertex *f = (work.find(from)->second);
    bfsq.push(f);

    while(!bfsq.empty()) {
        vertex *u = bfsq.front();
        bfsq.pop();
        //Now look at all neighbours of u
        for (vector<pair<int, vertex *> >::const_iterator itr = u->adj.begin(); itr != u->adj.end(); ++itr) {
            vertex *v = itr->second;
            if (!v->visited) {
                v->visited = true;
                bfsq.push(v);
                hops++;
                if (v->name == to) {
                    //cout << "bfs: " << v->name << " hops " << hops << endl;
                    return hops;
                }
            }
        }
    }

    return hops;
}

void graph::show()
{
    cout << "show" << endl;
    vmap::iterator itr;
    for (itr = work.begin(); itr != work.end(); ++itr) {
        cout << itr->first; //endl;
        cout << ", ins " << itr->second->in_degree; // << endl;
        cout << ", outs " << itr->second->out_degree << endl;
    }
}

int main()
{
    graph g;
    string a, b, c, d;
    a = "bart";
    b = "cindy";
    c = "mackenzie";
    d = "clarissa";
    g.addvertex(a);
    g.addvertex(b);
    g.addvertex(c);
    g.addvertex(d);
    g.addedge(a, b, 1);
    g.addedge(b, c, 1);
    g.addedge(c, d, 1);
    g.show();
    //if (g.is_connected(a, b)) {
    //    cout << a << " is connected to " << b << endl;
    //}
    int hops = g.num_hops(a, b);
    cout << "num hops from " << a << " to " << b << " is " << hops << endl;
    hops = g.num_hops(a, c);
    cout << "num hops from " << a << " to " << c << " is " << hops << endl;
    hops = g.num_hops(a, d);
    cout << "num hops from " << a << " to " << d << " is " << hops << endl;
}

