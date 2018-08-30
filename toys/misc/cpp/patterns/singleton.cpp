#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton* getInstance() {
        if (inst == NULL) {
            inst = new Singleton();
        }
        return inst;
    }
    void setValue(int val) { value = val; }
    int  getValue() { return value; }
    ~Singleton() { cout << "dtor()" << endl; }
private:
    int value;
    static Singleton* inst;
    Singleton() : value(42) {}
    // don't allow copy or assign construction
    Singleton(const Singleton&); // = delete;
    Singleton& operator=(const Singleton&); // = delete
};

Singleton* Singleton::inst = NULL;

int main()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    p2->setValue(77);
    cout << "Value = " << p1->getValue() << endl;
    delete p1; // will invoke the dtor(), not usually needed
}
