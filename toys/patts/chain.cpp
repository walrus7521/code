#include <iostream>
#include <ctime>
#include <memory>

using namespace std;

class Handler { // abstract
    shared_ptr<Handler> successor; // 1. "successor" pointer in the base class
public:
    Handler() { successor = nullptr; }
    void setNext(shared_ptr<Handler> n) { successor = n; }
    void Add(shared_ptr<Handler> n) {
        if (successor) successor->Add(n);
        else successor = n;
    }
    // "chain" method in base class always delegates to successor obj
    virtual void HandleRequest(int i) { successor->HandleRequest(i); }
};

class ConcreteHandler1: public Handler {
public:
    virtual void HandleRequest(int i) {
        if (rand() % 3) {
            cout << "H1 passed " << i << "  ";
            Handler::HandleRequest(i); // 3. Delegate to the base class
        } else {
          cout << "H1 handled " << i << "  ";
        }
    }
};

class ConcreteHandler2: public Handler {
public:
    virtual void HandleRequest(int i) {
        if (rand() % 3) {
            cout << "H2 passed " << i << "  ";
            Handler::HandleRequest(i);
        } else {
          cout << "H2 handled " << i << "  ";
        }
    }
};

class ConcreteHandler3: public Handler {
public:
     virtual void HandleRequest(int i) {
        if (rand() % 3) {
            cout << "H3 passed " << i << "  ";
            Handler::HandleRequest(i);
        } else {
          cout << "H3 handled " << i << "  ";
        }
    }
};

int main()
{
  srand(time(0));
  shared_ptr<ConcreteHandler1> root(new ConcreteHandler1());
  shared_ptr<ConcreteHandler2> two(new ConcreteHandler2());
  shared_ptr<ConcreteHandler3> three(new ConcreteHandler3());
  root->Add(two);
  root->Add(three);
  three->setNext(root);
  for (int i = 1; i < 10; i++) {
    root->HandleRequest(i); // prints handlers
    cout << '\n';
  }
}
