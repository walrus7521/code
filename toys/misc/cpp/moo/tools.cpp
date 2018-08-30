#include <iostream>
#include <string>
#include <exception>

// exception handling
class isbn_mismatch: public std::logic_error {
public:
    explicit isbn_mismatch(const std::string &s)
        : std::logic_error(s) {}
    isbn_mismatch(const std::string &s,
            const std::string &lhs, const std::string &rhs) 
        : std::logic_error(s), left(lhs), right(rhs) {}
    const std::string left, right;
};

using namespace std;

void excepts()
{
    // see Blob for function try block
    string isbn = "123";
    string left = "left";
    string right = "right";
    try {
        throw isbn_mismatch("wrong isbns", left, right);
    } catch (const isbn_mismatch &e) {
        cerr << e.what() << ": left isbn(" << e.left 
             << ") right isbn(" << e.right << ")" << endl;
    }
}

void excepts2()
{
    throw range_error("dude, this is horked:");
}

namespace dookie {
    inline namespace dookie_latest { // default (unqualified)
        int dookestr(int n) { cout << "latest dook: " << n << endl; return n; }
    }
    namespace dookie_ver1 {
        int dookestr(int n) { cout << "ver1 dook: " << n << endl; return n; }
    }
}

using namespace dookie;

void namespaces()
{
    dookestr(42); // requires using
    dookie::dookie_ver1::dookestr(42); // requires using
}




// multiple & virtual inheritance
class ZooAnimal {
public:
    ZooAnimal() { cout << "default ctor: ZooAnimal" << endl; }
    ZooAnimal(int ident) : id(ident) { cout << "ctor(id): ZooAnimal" << endl; }
    virtual ~ZooAnimal(){ cout << "dtor: ZooAnimal" << endl; }
    virtual void print() const { cout << "i am ZooAnimal" << endl; }
    int id; // shared between virtual inheritors
};

class Endangered {
public:
    enum Type { critical, ok, bad };
    Type t_;
    Endangered(Type t) : t_(t) { cout << "ctor: Endangered" << endl; }
    ~Endangered(){ cout << "dtor: Endangered" << endl; }
    void print() const { cout << "i am Endangered" << endl; }
};

class Bear : public ZooAnimal {
public:
    Bear(std::string nm, bool onExhibit, std::string spec) 
    : name(nm), onex(onExhibit), species(spec) {
        cout << "ctor: Bear" << endl;
    }
    ~Bear(){ cout << "dtor: Bear" << endl; }
    void print() const { cout << "i am Bear" << endl; }
protected: // allow derived class to access these
    std::string name;
    bool onex;
    std::string species;
};

class Panda : public Bear, public Endangered {
public:
    Panda(std::string name, bool onExhibit)
        : Bear(name, onExhibit, "Panda"),
          Endangered(Endangered::critical) 
    {
        cout << "ctor: Panda" << endl;
    }
    ~Panda(){ cout << "dtor: Panda" << endl; }
    void whoami() { cout << Bear::name << endl; }
    void print() const { cout << "i am Panda" << endl; }
};

// dynamic binding
void print(ZooAnimal &animal) {
    animal.print();
    cout << "id: " << animal.id << endl;
}


// virtual base classes -- allows a base class to be inherited multiple times
// with only a single shared instance between all subobjects - such as sharing
// the same IO buffer for iostream (read) and iostream (write)
class Racoon : public virtual ZooAnimal {
public:
    Racoon(){
        cout << "ctor: Racoon" << endl;
        //ZooAnimal::id = 47;
    }
    ~Racoon(){
        cout << "dtor: Racoon" << endl;
    }
};

class Bear2 : public virtual ZooAnimal {
public:
    Bear2(std::string nm, bool onExhibit, std::string spec) 
    : name(nm), onex(onExhibit), species(spec) {
        cout << "ctor: Bear2" << endl;
        //ZooAnimal::id = 43;
    }
    ~Bear2(){
        cout << "dtor: Bear2" << endl;
    }
protected: // allow derived class to access these
    std::string name;
    bool onex;
    std::string species;
};

class Panda2 : public Bear2, public Racoon, public Endangered {
public:
    Panda2(std::string name, bool onExhibit)
        : ZooAnimal(42), // responsible for initializing the shared base class
          Bear2(name, onExhibit, "Panda"),
          Racoon(),
          Endangered(Endangered::critical)
    {
        cout << "ctor: Panda2" << endl;
    }
    void print() const { cout << "i am Panda2" << endl; }
    ~Panda2(){
        cout << "dtor: Panda2" << endl;
    }
};


void virtuals()
{
    class Panda panda("dook", true);
    class Panda ying_yang("ying_yang", true);
    class Panda ling_ling = ying_yang;
    ling_ling.whoami();
    class Bear bear("grizzy", true, "cub");

    class ZooAnimal *animal;

    print(panda);
    print(bear);
    //animal = &ling_ling;
    //print(animal);

    class Panda2 panda2("dook2", true);
    print(panda2);

}


int main()
{
    //excepts();

    try {
        excepts2();
    } catch (const range_error& re) {
        cerr << re.what() << endl;
    }
    //namespaces();
    //virtuals();
}
