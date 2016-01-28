#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct vertex{
    typedef pair<int, vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    vertex(string s) { name=s; }
};

typedef map<string, vertex *> vmap;
class graph
{
public:
    vmap work;
    void addvertex(const string&);
    void addedge(const string& from, const string& to, double cost);
    bool is_connected(const string& from, const string& to);
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

void graph::show()
{
    cout << "show" << endl;
    vmap::iterator itr;
    for (itr = work.begin(); itr != work.end(); ++itr) {
        cout << itr->first << endl;
    }
}

int main()
{
    graph g;
    string a, b;
    a = "bart";
    b = "cindy";
    g.addvertex(a);
    g.addvertex(b);
    g.addedge(a, b, 1);
    g.show();
    if (g.is_connected(a, b)) {
        cout << a << " is connected to " << b << endl;
    }
}

