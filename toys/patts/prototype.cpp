#include <iostream>
#include <vector>

using namespace std;

class Storage {
public:
   virtual Storage* clone() = 0;
   virtual void backup() = 0;
};

class Factory {
public:
   static Storage* make_Storage( int choice );
private:
   static Storage* s_prototypes[4];
};

class Disk : public Storage {
public:
   Storage* clone() { return new Disk; }
   void backup() { cout << "Disk: poke eyes\n"; }
};

class Tape : public Storage {
public:
   Storage* clone() { return new Tape; }
   void backup() { cout << "Tape: slap head\n"; }
};

class DVD : public Storage {
public:
   Storage* clone() { return new DVD; }
   void backup() { cout << "DVD: suffer abuse\n"; }
};

Storage* Factory::s_prototypes[] = { 0, new Disk, new Tape, new DVD };

Storage* Factory::make_Storage( int choice ) {
   return s_prototypes[choice]->clone();
}

int main() {
    vector<Storage*> roles;
    int             choice;

    roles.push_back(Factory::make_Storage( 1 ) );
    roles.push_back(Factory::make_Storage( 2 ) );
    roles.push_back(Factory::make_Storage( 3 ) );

    for (int i=0; i < roles.size(); ++i) roles[i]->backup();

    for (int i=0; i < roles.size(); ++i) delete roles[i];
}

