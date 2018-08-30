# include <iostream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class Session {
public:
    int Id;
    Session() {}
    Session(string nm, int id) : name(nm), Id(id) {}
    void Show(string msg) { cout << msg << endl; }
    string name;
};

// also have factory keep list of all
// instances it creates within itself
class SessionFactory {

public:
    static list<Session*> instances;
    static map<int, Session*> instmap;
    static int count;
    static int UniqueId;
    static void ShowList();
    static void ShowMap();
    int GetCount() { return count; }
    void IncCount() { ++count; }
    Session Create(string nm);
    Session* CreatePtr(string nm);
    void Create(Session*& p, string nm);
    void Destroy(); // destroy all Sessions
};

// return a copy of a stack object
Session SessionFactory::Create(string nm) {
    Session s(nm, ++UniqueId);
    //instances.push_back(&s);
    //count++;
    IncCount();
    return (s);
}

// return a pointer to a heap object
Session *SessionFactory::CreatePtr(string nm) {
    Session *s = new Session(nm, ++UniqueId);
    instances.push_back(s);
    instmap[s->Id] = s;
    IncCount();
    return (s);
}

// update the callers pointer with address of object
void SessionFactory::Create(Session*& p, string nm) {
    p = new Session(nm, ++UniqueId);
    instmap[p->Id] = p;
    instances.push_back(p);
    //count++;
    IncCount();
}

void SessionFactory::Destroy() {
    for (list<Session*>::iterator p = instances.begin();
            p != instances.end(); ++p) {
        cout << "erasing: " << (*p)->name << endl;
        instances.erase(p); //cout << (*p)->name << endl;
    }
}

void SessionFactory::ShowList()
{
    cout << "Number of listed sessions: " << count << endl;
    for (list<Session*>::iterator p = instances.begin();
            p != instances.end(); ++p) {
        cout << "id: " << (*p)->Id << ": " << (*p)->name << endl;
    }
}

void SessionFactory::ShowMap()
{
    cout << "Number of mapped sessions: " << count << endl;
    for (map<int, Session*>::iterator mis = instmap.begin();
            mis != instmap.end(); ++mis) {
        cout << "id: " << mis->first << ": " << mis->second->name << endl;
    }
}

static SessionFactory f; // the one and only factory
list<Session*> SessionFactory::instances; // list of Sessions
map<int, Session*> SessionFactory::instmap; // list of Sessions
int SessionFactory::count = 0;
int SessionFactory::UniqueId = 0;

int main()
{
    Session *p1 = new Session();
    Session *p2;
    Session *p3;

    p1->Show("used new");
    *p1 = f.Create("one"); // this returns object
    f.instances.push_back(p1);
    f.instmap[p1->Id] = p1;
    p1->Show("used Create");
    p2 = f.CreatePtr("two");
    p2->Show("used CreatePtr");
    f.Create(p3, "three");
    p3->Show("used Create(p)");

    f.ShowList();
    f.ShowMap();

    cout << "map[" << 1 << "] = " << f.instmap[1]->name << endl;
    cout << "map[" << 2 << "] = " << f.instmap[2]->name << endl;
    cout << "map[" << 3 << "] = " << f.instmap[3]->name << endl;

    f.Destroy();
    //delete &f; // don't do this
}
