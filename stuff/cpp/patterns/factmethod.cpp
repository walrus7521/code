#include <iostream>
#include <vector>

using namespace std;

class Storage
{
public:
    // Factory Method
    static Storage *make_storage(int choice);
    virtual void backup() = 0;
};

class Disk: public Storage
{
public:
    void backup() { cout << "Disk: poke eyes\n"; }
};
class Tape: public Storage
{
public:
    void backup() { cout << "Tape: slap head\n"; }
};
class DVD: public Storage
{
public:
    void backup() { cout << "DVD: suffer abuse\n"; }
};

Storage *Storage::make_storage(int choice)
{
    switch (choice) {
        case 1: return new Disk;
        case 2: return new Tape;
        case 3: return new DVD;
    }
}

int main() {
    vector<Storage*> roles;

    roles.push_back(Storage::make_storage( 1 ) );
    roles.push_back(Storage::make_storage( 2 ) );
    roles.push_back(Storage::make_storage( 3 ) );

    for (int i=0; i < roles.size(); ++i) roles[i]->backup();

    for (int i=0; i < roles.size(); ++i) delete roles[i];
}

