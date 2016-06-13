# include <iostream>

using namespace std;

class Session {
public:
    void Show(string msg) { cout << msg << endl; }
};

class SessionFactory {

public:
    Session Create();
    Session* CreatePtr();
    void Create(Session*& p);
};

// return a copy of a stack object
Session SessionFactory::Create() {
    Session s;
    return (s);
}

// return a pointer to a heap object
Session *SessionFactory::CreatePtr() {
    return (new Session());
}

// update the callers pointer with address of object
void SessionFactory::Create(Session*& p) {
    p = new Session();
}

static SessionFactory f; // the one and only factory

int main()
{
    Session *p1;
    Session *p2 = new Session();

    p2->Show("used new");
    *p2 = f.Create();
    p2->Show("used Create");
    p1 = f.CreatePtr();
    p1->Show("used CreatePtr");
    f.Create(p1);
    p1->Show("used Create(p)");
}
