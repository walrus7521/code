#include <iostream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
 
/*
 * create a singleton class to implement methods
 *
*/

using namespace std;

class Singleton
{
    public:
        static Singleton* getInstance() {
            static Singleton *instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            if (!instance) {
                cout << "new singleton..." << endl;
                instance = new Singleton;
            } else {
                cout << "old singleton..." << endl;
            }
            return instance;
        }

        void pulse() {
            cout << "pulsing singleton..." << endl;
        }
        
    private:
        Singleton() {}; // Constructor? (the {} brackets) are needed here.
        // C++ 03
        // ========
        // Dont forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
        Singleton(Singleton const&);      // Don't Implement
        void operator=(Singleton const&); // Don't implement
        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
        //S(S const&)               = delete;
        //void operator=(S const&)  = delete;
};

class GlobalClass
{
    int m_value;
    static GlobalClass *s_instance;
    GlobalClass(int v = 0)
    {
        m_value = v;
    }
  public:
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
    static GlobalClass *instance()
    {
        if (!s_instance)
          s_instance = new GlobalClass;
        return s_instance;
    }
};

GlobalClass *GlobalClass::s_instance = 0;
Singleton *s = Singleton::getInstance();

void foo(void)
{
  GlobalClass::instance()->set_value(1);
  cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void)
{
  GlobalClass::instance()->set_value(2);
  cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

int main() {
    Singleton *s = Singleton::getInstance();
    s->pulse();
    cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
    foo();
    bar();
    return 0;
}

