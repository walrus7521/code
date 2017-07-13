#include <memory>
#include <iostream>

using namespace std;

struct connection {
    int x;
};

struct destination {
    int y;
};

void end_connection(connection *p)
{
    cout << "end connection: " << p->x << endl;
}

void del_unique(int *p)
{
    cout << "del_unique: " << *p << endl;
}

int main()
{
    connection c;
    // what this does is use the deleter facility for p to 
    // free the connection c when it's done.
    shared_ptr<connection> p(&c, end_connection);
    c.x = 42;

    // can also use deleters with unique_ptr
    unique_ptr<int, decltype(del_unique)*> r(new int(), del_unique);
    *r = 43;

}
