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
    //if (f == NULL) {
    //    addvertex(from);
    //    f = (work.find(from)->second);
    //}
    //if (t == NULL) {
    //    addvertex(to);
    //    t = (work.find(to)->second);
    //}
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
        hops++;
        //Now look at all neighbours of u
        for (vector<pair<int, vertex *> >::const_iterator itr = u->adj.begin(); itr != u->adj.end(); ++itr) {
            vertex *v = itr->second;
            if (!v->visited) {
                v->visited = true;
                bfsq.push(v);
                if (v->name == to) {
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
    string a, b, c, d, e, f, h, j;
    a = "bart";
    b = "cindy";
    c = "mackenzie";
    d = "clarissa";
    e = "grant";
    f = "chad";
    h = "taylor";
    j = "kevin";
    g.addvertex(a);
    g.addvertex(b);
    g.addvertex(c);
    g.addvertex(d);
    g.addvertex(e);
    g.addvertex(f);
    g.addvertex(h);
    g.addvertex(j);
    g.addedge(a, b, 1);
    g.addedge(b, c, 1);
    g.addedge(b, d, 1);
    g.addedge(a, e, 1);
    g.addedge(a, f, 1);
    g.addedge(c, h, 1);
    g.addedge(d, j, 1);
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
    hops = g.num_hops(a, e);
    cout << "num hops from " << a << " to " << e << " is " << hops << endl;
    hops = g.num_hops(a, f);
    cout << "num hops from " << a << " to " << f << " is " << hops << endl;
    hops = g.num_hops(a, h);
    cout << "num hops from " << a << " to " << h << " is " << hops << endl;
    hops = g.num_hops(a, j);
    cout << "num hops from " << a << " to " << j << " is " << hops << endl;
}

