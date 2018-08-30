#include <iostream>
#include <string>

using namespace std;

class Subject // abstract subject
{
public:
    virtual void execute() = 0;
};

class RealSubject: public Subject // concrete subject
{
public:
    RealSubject(string s) {
        _str = s;
        cout << "real: " << s << endl;
    }
    virtual void execute() { // override/implementation
        cout << _str;
    }
private:
    string _str;
};

class ProxySubject: public Subject
{
public:
    ProxySubject(string s) {
        // caching, proxy and shimming
        _first  = "proxy: ";
        _second = "pre-filter: ";
        _third  = " :post-filter";
        _ptr = new RealSubject(s); // allocate real object
    }
    ~ProxySubject() { // RAII
        delete _ptr;
    }
    RealSubject *operator->() {
        cout << _first << ' ';
        return _ptr;
    }
    virtual void execute() { // override
        cout << _second;
        _ptr->execute();
        cout << _third << '\n';
    }
private:
    string _first, _second, _third;
    RealSubject *_ptr;
};

int main()
{
  ProxySubject obj(string("the quick brown fox jumped over the dog"));
  obj->execute();
  cout << endl;
  obj.execute();
}
