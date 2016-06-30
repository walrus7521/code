#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton* getInstance();

    void setValue(int val) { value = val; }
    int  getValue() { return value; }
    ~Singleton() { cout << "dtor()" << endl; }

protected:
    int value;

private:
    static Singleton* inst;
    Singleton() : value(0) {}
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};

Singleton* Singleton::inst = NULL;
Singleton* Singleton::getInstance() {
    if (inst == NULL) {
        inst = new Singleton();
    }
    return inst;
}

int main()
{
    Singleton *p1 = Singleton::getInstance();
    p1->setValue(77);
    Singleton *p2 = Singleton::getInstance();
    cout << "Value = " << p2->getValue() << endl;
    delete p1; // will invoke the dtor(), not usually needed
}
