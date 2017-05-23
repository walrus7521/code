#include <iostream>
#include <vector>

using namespace std;

typedef enum {
    DISK_TYPE,
    TAPE_TYPE,
    DVD_TYPE,
    STORAGE_TYPES_NUM_OF
} STORAGE_TYPES;

// abstract class to clone
class Storage {
public:
   virtual Storage* clone() = 0;
   virtual void backup() = 0;
};

class Factory {
public:
   static Storage* make_Storage( STORAGE_TYPES type );
private:
   static Storage* s_prototypes[STORAGE_TYPES_NUM_OF];
};

// concrete classes to clone
class Disk : public Storage {
public:
   Storage* clone() { return new Disk; }
   void backup() { cout << "Disk: backup\n"; }
};

class Tape : public Storage {
public:
   Storage* clone() { return new Tape; }
   void backup() { cout << "Tape: backup\n"; }
};

class DVD : public Storage {
public:
   Storage* clone() { return new DVD; }
   void backup() { cout << "DVD:  backup\n"; }
};

Storage* Factory::s_prototypes[] = { new Disk, new Tape, new DVD };

Storage* Factory::make_Storage( STORAGE_TYPES type ) {
   return s_prototypes[type]->clone();
}

int main() {
    vector<Storage*> roles;

    roles.push_back(Factory::make_Storage( DISK_TYPE ) );
    roles.push_back(Factory::make_Storage( TAPE_TYPE ) );
    roles.push_back(Factory::make_Storage( DVD_TYPE  ) );

    for (int i=0; i < roles.size(); ++i) roles[i]->backup();

    for (int i=0; i < roles.size(); ++i) delete roles[i];
}

